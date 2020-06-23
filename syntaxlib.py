import copy
import re
import networkx as nx
import matplotlib.pyplot as plt

from typing import Type, List, Set, Dict, Tuple, Optional
from pycparser import c_parser, c_ast, parse_file, c_generator

# Sync variables are anotated with the unfolding number where they belong
SYNCVAR_UNFOLD = '_(\d)'

def rename_syncvar(name, iteration):
    newname = name + SYNCVAR_UNFOLD
    return newname.replace('(\d)', str(iteration))

def unfold(ast, k: int, syncvariables):
    """This function assumes a C code with a unique "while" statement. The 
    result is the code unfolded "k" times, where unfolding means replacing 
    every occurrence of a "continue" statement with the content of the "while"
    body.

    Parameters
    ----------
    ast : pycparser.c_ast.Node
    k : number of unfoldings of the main loop
    syncvariables : synchronization variables defined in the config
    """
    declare_iterated_variables(ast, syncvariables, k)

    main_while = get_main_while(ast)

    while_body = copy.deepcopy(main_while.stmt.block_items)

    rename_if_body_variables(main_while, syncvariables, 0)

    for i in range(1,k):
        body_iteration = copy.deepcopy(while_body)

        # syncvars outside upons (typically mbox) must be renamed
        # TODO: consider a visitor that ignores if bodies
        for n in body_iteration:
            if type(n) == c_ast.Assignment and n.lvalue.name in syncvariables:
                n.lvalue.name = rename_syncvar(n.lvalue.name, i-1)
        
        # syncvariables referenced in upon conditions are renamed to the 
        # previous unfolding
        rename_if_cond_variables(body_iteration, syncvariables, i-1)

        # syncvariables inside upon statements live in the new unfolding
        rename_if_body_variables(body_iteration, syncvariables, i)

        insert_node_after_continue(main_while, body_iteration)   

    

def insert_node_after_continue(ast, node):
    
    typ = type(ast) 

    if typ == c_ast.If:
        insert_node_after_continue(ast.iftrue, node)

        if ast.iffalse is not None:
            insert_node_after_continue(ast.iffalse, node)
        
    elif typ == c_ast.While:
        insert_node_after_continue(ast.stmt, node)

    elif typ == c_ast.Compound:
        continues = [n for n in ast.block_items if type(n)==c_ast.Continue]
        
        if len(continues)>0:
            
            items = copy.copy(ast.block_items)
            for i in items:
                if type(i) == c_ast.Continue:
                    ast.block_items.remove(i)
                    body = copy.deepcopy(node)
                    for e in body:
                        ast.block_items.append(e)
        else:
            for i in ast.block_items:
                insert_node_after_continue(i, node)

    elif typ == c_ast.FuncDef:
        insert_node_after_continue(ast.body, node)

def replace_node_by_type(ast, find_type, replace):
    """Replace nodes with `replace` where its type match `find_type` 

    Parameters
    ----------
    ast : a pycparser.c_ast.Node
    """

    typ = type(ast) 

    if typ == c_ast.If:
        replace_node_by_type(ast.iftrue, find_type, replace)

        if ast.iffalse is not None:
            replace_node_by_type(ast.iffalse, find_type, replace)
        
    elif typ == c_ast.While:
        replace_node_by_type(ast.stmt, find_type, replace)

    elif typ == c_ast.Compound:
            
            for i in ast.block_items:
                if type(i) == find_type:
                    replace_copy = copy.deepcopy(replace)
                    index = ast.block_items.index(i)
                    ast.block_items.insert(index, replace_copy)
                    ast.block_items.remove(i)
                else:
                    replace_node_by_type(i, find_type, replace)

    elif typ == c_ast.FuncDef:
        replace_node_by_type(ast.body, find_type, replace)

def remove_c99_comments(text):
    """remove c-style comments"""

    pattern = r"""
                            ##  --------- COMMENT ---------
           //.*?$           ##  Start of // .... comment
         |                  ##
           /\*              ##  Start of /* ... */ comment
           [^*]*\*+         ##  Non-* followed by 1-or-more *'s
           (                ##
             [^/*][^*]*\*+  ##
           )*               ##  0-or-more things which don't start with /
                            ##    but do end with '*'
           /                ##  End of /* ... */ comment
         |                  ##  -OR-  various things which aren't comments:
           (                ##
                            ##  ------ " ... " STRING ------
             "              ##  Start of " ... " string
             (              ##
               \\.          ##  Escaped char
             |              ##  -OR-
               [^"\\]       ##  Non "\ characters
             )*             ##
             "              ##  End of " ... " string
           |                ##  -OR-
                            ##
                            ##  ------ ' ... ' STRING ------
             '              ##  Start of ' ... ' string
             (              ##
               \\.          ##  Escaped char
             |              ##  -OR-
               [^'\\]       ##  Non '\ characters
             )*             ##
             '              ##  End of ' ... ' string
           |                ##  -OR-
                            ##
                            ##  ------ ANYTHING ELSE -------
             .              ##  Anything other char
             [^/"'\\]*      ##  Chars which doesn't start a comment, string
           )                ##    or escape
    """
    regex = re.compile(pattern, re.VERBOSE|re.MULTILINE|re.DOTALL)
    noncomments = [m.group(2) for m in regex.finditer(text) if m.group(2)]

    return "".join(noncomments)


class ControlFlowGraph(nx.DiGraph):
    """
    Placeholders AST nodes for delimitating the scope of c_ast.While and 
    c_ast.If in the CFG
    """
    class WhileEnd(c_ast.EmptyStatement):
        def __init__(self, coord=None):
            super().__init__(coord)

    class IfStart(c_ast.EmptyStatement):
        def __init__(self, coord=None):
            super().__init__(coord)

    class IfEnd(c_ast.EmptyStatement):
        def __init__(self, coord=None):
            super().__init__(coord)

    class FuncDefEnd(c_ast.EmptyStatement):
        def __init__(self, coord=None):
            super().__init__(coord)

    def __init__(self, ast=None, data=None):
        super().__init__(data)

        if ast is not None:
            ast_to_cfg(self, ast)

    def get_subgraph_between_nodes(self, start, end):
        """ Return the induced graph of the nodes in all paths from start to 
        end.
        """
        nodes = set()
        nodes.add(start)

        to_visit = set()
        to_visit.add(start)

        while len(to_visit) > 0:
            current_visit = copy.copy(to_visit)
            for tv in current_visit:
                to_visit.remove(tv)
                if tv is not end:
                    for s in self.successors(tv):
                        to_visit.add(s)
                        nodes.add(s)

        nodes.add(end)

        return self.subgraph(nodes) 
    
    def insert_graph(self, place, graph):
        """
        This method insert `graph` after `place`, connecting `place` to the 
        first node of `graph`.

        Parameters
        ----------
        graph : ControlFlowGraph()
        place : pycparser.c_ast.Node
        """
        if len(graph)>0:
            
            # Create and insert the graph
            graph_copy = copy.deepcopy(graph)
            augmented_graph = nx.union(self, graph_copy)

            self.update(augmented_graph.edges(), augmented_graph.nodes())

            # Connect the new graph in place
            graph_copy_nodes_ordered = list(nx.topological_sort(graph_copy))
            first_node_graph = graph_copy_nodes_ordered[0]
            last_node_graph = graph_copy_nodes_ordered[-1]

            # Disconnect old predecessors to the insertion place
            old_predecessors = copy.copy(self.predecessors(place))
            old_successors = copy.copy(self.successors(place))

            for s in old_successors:
                self.remove_edge(place, s)

            self.add_edge(place, first_node_graph)                   

    def draw(self):
        labels = dict(self.nodes())
        for k in labels.keys():
            labels[k] = str(k.__class__.__name__)+" "+str(k.coord).split(":")[1]

        nx.draw_networkx(self, labels=labels, pos=nx.planar_layout(self))
        plt.show()

    def print_cfg(self):
        for n in self.nodes():
            print("############")
            print(str(type(n))+" "+str(n.coord)+" "+str(hex(id(n))))
            print("successors")
            for s in list(self.successors(n)):
                print(str(type(s))+" "+str(s.coord)+" "+str(hex(id(s))))
            print("")
            
def ast_to_cfg(digraph, ast: c_ast.Node) -> (c_ast.Node, c_ast.Node):
    """Recursively compute the CFG from a AST. Given a AST node (can be any 
    complex structure) the function will return the first and last nodes of the
    CFG in a tuple and will modify `cfg` adding the corresponding nodes and 
    edges representing the final CFG.

    Parameters
    ----------
    digraph : networkx.DiGraph
    ast : pycparser.c_ast.Node to be translated into a CFG
    
    Returns
    -------
    A tuple with references to the first and last element of the CFG

    Notes
    -----
    Depending on the node type, we need to build a DiGraph and return its 
    starting/ending nodes.
    Nodes marqued with * in figures are adhoc nodes to have only one end in the
    graph.
    """
    typ = type(ast) 

    # A c_ast.If in CFG is:
    #            if(c)(cfg(body.true))
    #           /                      \
    # ifstart(c)                        endif*
    #           \                      /
    #            if(!c)(cfg(body.false))
    #
    # returns (if(c), endif)

    if typ == c_ast.If:
        
        first = ControlFlowGraph.IfStart(coord=str(ast.coord)+":END")

        last = ControlFlowGraph.IfEnd(coord=str(ast.coord)+":END")
        digraph.add_node(last)

        true_branch_first = c_ast.If(ast.cond, None, None, coord=ast.coord)
        true_branch_body_first, true_branch_body_last = ast_to_cfg(digraph, ast.iftrue)
        false_branch_body_start = None
        false_branch_body_last = None
        

        digraph.add_node(first, true_start=true_branch_body_first, 
                                true_end=true_branch_body_last,
                                false_start=false_branch_body_start,
                                false_end=false_branch_body_last,
                                body_end=last)

        
        digraph.add_node(true_branch_first)

        digraph.add_node(true_branch_body_first)
        digraph.add_node(true_branch_body_last)
        
        digraph.add_edge(first, true_branch_first)
        digraph.add_edge(true_branch_first, true_branch_body_first)    
        digraph.add_edge(true_branch_body_last, last)   

        false_branch_first = c_ast.If(  c_ast.UnaryOp("!",ast.cond), None, 
                                        None, coord=ast.coord)
        digraph.add_node(false_branch_first)
        digraph.add_edge(first, false_branch_first)

        if ast.iffalse is not None:

            false_branch_body_start, false_branch_body_last = \
            ast_to_cfg(digraph, ast.iffalse)
            
            digraph.add_node(false_branch_body_start)
            digraph.add_node(false_branch_body_last)
            
            digraph.add_edge(false_branch_first, false_branch_body_start)
            digraph.add_edge(false_branch_body_last, last)
        else:
            digraph.add_edge(false_branch_first, last)

        return (first, last)

    # A c_ast.While in CFG is:
    #           cfg(body)
    #          /         \
    # while(c)            endwhile* -->--+
    #       ^  \         /               |
    #       |   ---->----                |
    #       +----------------------------+
    #
    # returns (while(c), endwhile*)
    
    elif typ == c_ast.While:

        body_first, body_last = ast_to_cfg(digraph, ast.stmt)
        

        first = c_ast.While(ast.cond, None, coord=ast.coord)
        last = ControlFlowGraph.WhileEnd(coord=str(ast.coord)+":END")

        digraph.add_node(first, body_start=body_first, body_end=body_last)

        digraph.add_edge(first, body_first)
        digraph.add_edge(body_last, last)
        digraph.add_edge(first, last)
        
        return first, last

    # A c_ast.Compound in CFG is:
    #
    # cfg(block(1)) --> cfg(block(2)) --> ... --> cfg(block(n))
    #
    # return (cfg(block(1)).first, cfg(block(n)).last)

    elif typ == c_ast.Compound:
        
        items = ast.block_items
        
        (first, last) = (None, None)

        old_i_last = None
        for i in items:
            i_first, i_last = ast_to_cfg(digraph, i)

            if old_i_last is not None:
                digraph.add_edge(old_i_last, i_first)

            if first is None:
                first = i_first

            old_i_last = i_last
        
        last = old_i_last
        
        return first, last

    # A c_ast.Compound in CFG is:
    #
    # function.name --> cfg(function.body).first
    #
    # return (function.name, cfg(function.body).last)

    elif typ == c_ast.FuncDef:

        (first_body, last_body) = ast_to_cfg(digraph, ast.body)

        first = c_ast.FuncDef(ast.decl, ast.param_decls, None, coord=ast.coord)
        last = ControlFlowGraph.FuncDefEnd(coord=str(ast.coord)+":END")

        digraph.add_node(first, body_start=first_body, body_end=last_body)

        digraph.add_edge(first, first_body)
        digraph.add_edge(last_body, last)

        return first, last
    else:
        digraph.add_node(ast)
        return ast, ast   
 

def cfg_path_to_ast(cfg):
    """Generates a AST from a CFG path (No FileAST support, it handles 
    FuncDecl, If, While and no compound objects).

    Parameters
    ----------
    cfg : ControlFlowGraph
    """
    current_compound = c_ast.Compound([])
    ast = current_compound
    previous_compound = None

    nodes = list(nx.topological_sort(cfg))

    for n in nodes:

        if type(n) in {c_ast.FuncDef, c_ast.While, c_ast.If}:

            previous_compound = current_compound
            current_compound = c_ast.Compound([])

            if type(n) == c_ast.FuncDef:
                inner_ast = c_ast.FuncDef(n.decl, n.param_decls, 
                                          current_compound)
            elif type(n) == c_ast.While:
                inner_ast = c_ast.While(n.cond, current_compound)
            elif type(n) == c_ast.If:
                inner_ast = c_ast.If(n.cond, current_compound, None)  

            previous_compound.block_items.append(inner_ast)

        elif type(n) not in {ControlFlowGraph.FuncDefEnd,
                            ControlFlowGraph.IfEnd, 
                            ControlFlowGraph.IfStart, 
                            ControlFlowGraph.WhileEnd}:
            
            current_compound.block_items.append(n)

    return ast 

def get_if_path(path):
    nodes = [node for node in list(nx.topological_sort(path)) 
            if type(node)==c_ast.If]
    
    new_path = ControlFlowGraph()
    nx.add_path(new_path, nodes)

    return new_path

def remove_whiles(ast : c_ast.Node):
    typ = type(ast) 

    if typ == c_ast.If:
        remove_whiles(ast.iftrue)

        if ast.iffalse is not None:
            remove_whiles(ast.iffalse)

    elif typ == c_ast.Compound:
            new_block_items = copy.copy(ast.block_items)
            for i in range(0,len(ast.block_items)):
                if type(ast.block_items[i]) == c_ast.While:
                    new_block_items[i] = c_ast.Compound(ast.block_items[i].stmt)
                else:
                    remove_whiles(i)

                ast.block_items = new_block_items

    elif typ == c_ast.FuncDef:
        remove_whiles(ast.body)

def variable_assigments_by_value(cfg, variable) -> Dict[str, List[c_ast.Assignment]]:
    """Returns a dictionary that maps rvalues to all nodes in the `cfg` where 
    `variable` is assigned.

    Parameters
    ----------
    cfg : ControlFlowGraph
    variable : string
        The name of the variable to match in the CFG assigments

    Example
    -------
    considering the following C99 code in form of a CFG:

    1   foo = val1;
    2   foo = val2;
    3   foo = val1;
    4   foo = val3;
    5   var = val1;

    >>> variable_assigments_by_value(cfg, 'foo') 
    >>> {val1: [node:1, node:3], val2: [node:2], val3: [node:4]}
    """
    map_rvalue_nodes = {}

    variable_assigments = [node for node in cfg if is_syncvar_assignment(node, variable)]

    for n in variable_assigments:
        value = get_assigment_value(n)

        if not value in map_rvalue_nodes:
            map_rvalue_nodes[value] = []

        map_rvalue_nodes[value].append(n)

    return map_rvalue_nodes

def variable_increments(cfg, variable):
    return [node for node in cfg if is_var_increment(node, variable)]

def is_syncvar_assignment(n : c_ast.Node, variable):
    if type(n) == c_ast.Assignment:
        # we discard the unfolding index
        basename = re.sub(SYNCVAR_UNFOLD, '', n.lvalue.name)
        return  n.op == '=' and basename == variable
    else:
        return False

def is_syncvar_assigned_to_value(n : c_ast.Node, variable, value):
    if type(n) == c_ast.Assignment:
        # we discard the unfolding index
        basename = re.sub(SYNCVAR_UNFOLD, '', n.lvalue.name)
        return  n.op == '=' and basename == variable and n.rvalue.name == value
    else:
        return False

def is_var_increment(n : c_ast.Node, variable):
    return  type(n) == c_ast.UnaryOp and n.op == 'p++' and \
            n.expr.name == variable

def get_assigment_value(n : c_ast.Assignment):
    # TODO: support different types 
    return str(n.rvalue.name)

def count_variable_assigments(path, variable):
    i = 0
    for n in path:
        if is_syncvar_assignment(n, variable):
            i=i+1
    return i

def count_continues(path):
    i = 0
    for n in path:
        if type(n) == c_ast.Continue:
            i=i+1
    return i

##########################################################
############ pycparser.c_ast VISITORS ####################
##########################################################

class MainWhileVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.result = None

    def visit_While(self, node):
        self.result = node

def get_main_while(ast):
    """ Return the outer while of the AST """
    v = MainWhileVisitor()
    v.visit(ast)
    return v.result

class FuncDefVisitor(c_ast.NodeVisitor):
    def __init__(self, funcname):
        self.funcname = funcname
        self.result = None

    def visit_FuncDef(self, node):
        if node.decl.name == self.funcname:
            self.result = node
        elif hasattr(node, 'args'):
            self.visit(node.args)

def get_funcdef_node(ast, funcname) -> c_ast.FuncDef:
    """ Returns  the corresponding FuncDef node in the AST defined as 
    `funcname`.

    Parameters
    ----------
    ast : a pycparser AST 
    funcname : a function name to find
    """
    v = FuncDefVisitor(funcname)
    v.visit(ast)
    return v.result

class EnumDeclarationVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.result = {}

    def visit_Decl(self, node):
        if type(node.type) == c_ast.Enum:
            enum_name = node.type.name
            enum_constants = []
            for c in node.type.values.enumerators:
                enum_constants.append(c.name)

            self.result[enum_name] = enum_constants

def get_enum_declarations(ast) -> Dict[str, List[str]]:
    """ Returns enum definitions in the AST as a dictionary: {enum_type_name: [const1, ...]}

    Parameters
    ----------
    ast : pycparser.c_ast.Node 
    """
    v = EnumDeclarationVisitor()
    v.visit(ast)
    return v.result


class EnumVariableDeclarationVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.result = {}

    def visit_Decl(self, node):
        if type(node.type) == c_ast.TypeDecl and type(node.type.type) == c_ast.Enum:
            self.result[node.name] = node.type.type.name


def get_declared_enum_vars(ast):
    """ Returns enum variable declarations as a dictionary {variable: enum_type_name}

    Parameters
    ----------
    ast: a pycparser AST 
    """
    v = EnumVariableDeclarationVisitor()
    v.visit(ast)
    return v.result

class RenameVariablesVisitor(c_ast.NodeVisitor):
    def __init__(self, variables, iteration):
        self.variables = variables
        self.iteration = iteration

    def visit_ID(self, node):
        if node.name in self.variables:
            node.name = rename_syncvar(node.name, self.iteration)
    
def rename_iterated_variables(ast, variables, iteration):
    v = RenameVariablesVisitor(variables, iteration)
    v.visit(ast)

class RenameIfBodyVisitor(c_ast.NodeVisitor):
    def __init__(self, variables, iteration):
        self.variables = variables
        self.iteration = iteration

    def visit_If(self, node):
        rename_iterated_variables(node.iftrue, self.variables, self.iteration)
    
def rename_if_body_variables(ast, variables, iteration):
    v = RenameIfBodyVisitor(variables, iteration)
    v.visit(ast)

class RenameIfCondVisitor(c_ast.NodeVisitor):
    def __init__(self, variables, string):
        self.variables = variables
        self.string = string

    def visit_If(self, node):
        rename_iterated_variables(node.cond, self.variables, self.string)
    
def rename_if_cond_variables(ast, variables, string):
    v = RenameIfCondVisitor(variables, string)
    v.visit(ast)

class DeclareIteratedVariablesVisitor(c_ast.NodeVisitor):
    def __init__(self, variables, iterations):
        self.variables = variables
        self.iterations = iterations
        self.visited = []
        self.current_parent = None

    def visit_Decl(self, node):
        if  type(node.type) == c_ast.TypeDecl:
            if  type(node.type.type) == c_ast.Enum and \
                node.name in self.variables and \
                node not in self.visited:
                    self.visited.append(node)
                    for i in range(0,self.iterations):
                        new_decl = copy.deepcopy(node)
                        new_decl.name = new_decl.name + '_' + str(i)
                        new_decl.type.declname = new_decl.name
                        
                        self.visited.append(new_decl)
                        self.current_parent.block_items.insert(0,new_decl)

        elif type(node.type) == c_ast.PtrDecl:
            if  node.type.type.declname in self.variables and \
                node not in self.visited:
                self.visited.append(node)
                for i in range(0,self.iterations):
                    new_decl = copy.deepcopy(node)
                    new_decl.name = new_decl.name + '_' + str(i)
                    new_decl.type.type.declname = new_decl.name
                    
                    self.visited.append(new_decl)
                    self.current_parent.block_items.insert(0,new_decl)

    def generic_visit(self, node):
        """ Called if no explicit visitor function exists for a
            node. Implements preorder visiting of the node.
        """
        oldparent = self.current_parent
        self.current_parent = node
        for c in node:
            self.visit(c)
        self.current_parent = oldparent

        

def declare_iterated_variables(ast, variables, iterations):
    """ Look for `var` in `variables` and copy its declarations adding the 
    iteration number.

    Example
    -------
    If the code declares:

    enum phase;

    and `iterations` equals 2, we need to add two declarations:

    enum phase;
    enum phase_1;
    enum phase_2;
    """
    v = DeclareIteratedVariablesVisitor(variables, iterations)
    v.visit(ast)