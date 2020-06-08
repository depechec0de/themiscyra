import copy
import re
import networkx as nx
import matplotlib.pyplot as plt

from pycparser import c_parser, c_ast, parse_file, c_generator


"""
    This function assumes a C code with a unique "while" statement. The result is
    the code unfolded "k" times, where unfolding means replacing every occurrence 
    of a "continue" statement with the content of the "while" body.

    ast: a pycparser AST 
    k: number of unfoldings of the main loop
    returns: nothing, it alters the original "ast" object

"""
def unfold(ast, k: int):

    (main_while, while_parent) = get_main_while(ast)

    while_body = copy.deepcopy(main_while.stmt.block_items)

    for i in range(1,k):
        insert_node_after_continue(main_while, while_body)

    # replace continues with returns
    #zero = c_ast.Constant(type=int, value='0')
    #return_ast = c_ast.Return(expr=zero)

    #replace_node_by_type(while_parent, c_ast.Continue, return_ast)


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

"""
    Replace every "continue;" statement with "returns 0;"

    ast: a pycparser AST 
    returns: nothing, it alters the original "ast" object 
"""
def replace_node_by_type(ast, find_type, replace):

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

""" 
    remove c-style comments.
    text: blob of text with comments (can include newlines)
    returns: text with comments removed
"""
def remove_c99_comments(text):

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
    Placeholders AST nodes for delimitating the scope of "while"s and "if"s in the CFG
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

    """
    Return the induced graph of the nodes in all paths from start to end
    """
    def get_subgraph_between_nodes(self, start, end):
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
    
    """
    This method insert "graph" (a CFG) after "place" (a node), connecting "place" 
    to the first node of "graph"
    """
    def insert_graph(self, place, graph):
        
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
            
"""
Recursively compute the CFG from a AST. Given a AST node (can be any complex structure) the function will return 
the first and last nodes of the CFG in a tuple and will modify de "cfg" parameter adding the corresponding nodes 
and edges representing the final CFG.

:param ast: AST node to be translated into a CFG
:type node: pycparser.c_ast.Node
:type cfg: ControlFlowGraph
:return: A tuple with references to the first and last element of the CFG
:rtype: (first, last)
"""
def ast_to_cfg(digraph, ast: c_ast.Node) -> (c_ast.Node, c_ast.Node):

    # Depending on the node type, we need to build a DiGraph and return its starting/ending nodes
    # We call ast_to_cfg = cfg in the comments
    # Nodes marqued with * are adhoc nodes to have only one end in the graph

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

        false_branch_first = c_ast.If(c_ast.UnaryOp("!",ast.cond), None, None, coord=ast.coord)
        digraph.add_node(false_branch_first)
        digraph.add_edge(first, false_branch_first)

        if ast.iffalse is not None:

            false_branch_body_start, false_branch_body_last = ast_to_cfg(digraph, ast.iffalse)
            
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
 
"""
    Generates a AST from a CFG path (No FileAST support, it handles FuncDecl, If, While and no compound objects)
"""
def cfg_path_to_ast(cfg):

    
    current_compound = c_ast.Compound([])
    ast = current_compound
    previous_compound = None

    nodes = list(nx.topological_sort(cfg))

    for n in nodes:

        if type(n) in {c_ast.FuncDef, c_ast.While, c_ast.If}:

            previous_compound = current_compound
            current_compound = c_ast.Compound([])

            if type(n) == c_ast.FuncDef:
                inner_ast = c_ast.FuncDef(n.decl, n.param_decls, current_compound)
            elif type(n) == c_ast.While:
                inner_ast = c_ast.While(n.cond, current_compound)
            elif type(n) == c_ast.If:
                inner_ast = c_ast.If(n.cond, current_compound, None)  

            previous_compound.block_items.append(inner_ast)

        elif type(n) not in {ControlFlowGraph.FuncDefEnd, ControlFlowGraph.IfEnd, ControlFlowGraph.IfStart, ControlFlowGraph.WhileEnd}:
            
            current_compound.block_items.append(n)

    return ast 


def is_var_assigment(n : c_ast.Node, variable):
    return type(n) == c_ast.Assignment and n.op == '=' and n.lvalue.name == variable

def get_assigment_value(n : c_ast.Node):
    return str(n.rvalue.name)

def count_variable_assigments(path, variable):
    i = 0
    for n in path:
        if is_var_assigment(n, variable):
            i=i+1
    return i

def count_continues(path):
    i = 0
    for n in path:
        if type(n) == c_ast.Continue:
            i=i+1
    return i

"""
    ast: A pycparser AST 
    returns: the outer while of the AST
"""
class MainWhileVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.current_parent = None
        self.result = None

    def visit_While(self, node):
        self.result = (node, self.current_parent)

    def generic_visit(self, node):
        oldparent = self.current_parent
        self.current_parent = node
        for c in node:
            self.visit(c)
        self.current_parent = oldparent

def get_main_while(ast):
    v = MainWhileVisitor()
    v.visit(ast)
    return v.result

"""
    ast: a pycparser AST 
    funcname: a function name to find
    returns: the corresponding FuncDef node in the AST defined as "funcname"
"""
class FuncDefVisitor(c_ast.NodeVisitor):
    def __init__(self, funcname):
        self.funcname = funcname
        self.result = None

    def visit_FuncDef(self, node):
        if node.decl.name == self.funcname:
            self.result = node
        elif hasattr(node, 'args'):
            self.visit(node.args)

def get_funcdef_node(ast, funcname):
    v = FuncDefVisitor(funcname)
    v.visit(ast)
    return v.result

"""
    ast: a pycparser AST 
    returns: enum definitions in the AST as a dictionary: {enum_type_name: [const1, ...]}
"""
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

def get_enum_declarations(ast):
    v = EnumDeclarationVisitor()
    v.visit(ast)
    return v.result

"""
    ast: a pycparser AST 
    returns: enum variable declarations as a dictionary {variable: enum_type_name}
"""
class EnumVariableDeclarationVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.result = {}

    def visit_Decl(self, node):
        if type(node.type) == c_ast.TypeDecl and type(node.type.type) == c_ast.Enum:
            self.result[node.name] = node.type.type.name


def get_declared_enum_vars(ast):
    v = EnumVariableDeclarationVisitor()
    v.visit(ast)
    return v.result

