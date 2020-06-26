import copy
import re

from typing import Type, List, Set, Dict, Tuple, Optional
from pycparser import c_parser, c_ast, parse_file, c_generator

from semanticlib.c99theory import *

# Sync variables are anotated with the unfolding number where they belong
SYNCVAR_UNFOLD_REGEX = '_(\d)_(\d)'
SYNCVAR_UNFOLD = '_ITER_PATH'

def rename_syncvar(name, iteration, path):
    newname = name + SYNCVAR_UNFOLD
    newname = newname.replace('PATH', str(path))
    newname = newname.replace('ITER', str(iteration))

    return newname

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

    main_while = get_main_while(ast)
    while_statements = main_while.stmt.block_items

    while_body = copy.deepcopy(main_while.stmt.block_items)

    upons = [n for n in while_statements if type(n) == c_ast.If]

    # TODO: fix +1 or justify it
    declare_iterated_variables(ast, syncvariables, k, len(upons)+1)

    _unfold(while_statements, while_body, syncvariables, 0, 0, k-1)


def _unfold(ast, while_body, syncvariables, iteration, parent_path, unfoldings):

    # rename out of scope variables like mbox
    if iteration>0:
        for n in ast:
            if type(n) == c_ast.Assignment and n.lvalue.name in syncvariables:
                n.lvalue.name = rename_syncvar(n.lvalue.name, iteration-1, parent_path)

    upons = [n for n in ast if type(n) == c_ast.If]

    if unfoldings-iteration > 0:
        path = 0

        for upon in upons:
            
            if iteration>0:
                rename_if_cond_variables(upon, syncvariables, iteration-1, parent_path)

            rename_if_body_variables(upon, syncvariables, iteration, path)

            insert_node_after_continue(upon, copy.deepcopy(while_body))  

            _unfold(upon.iftrue, while_body, syncvariables, iteration+1, path, unfoldings)

            path=path+1
    else:
        for upon in upons:
            rename_if_cond_variables(upon, syncvariables, iteration-1, parent_path)
            # path is 0 because we don't branch anymore, there is only one path
            rename_if_body_variables(upon, syncvariables, iteration, 0)

def dead_code_elimination(codeast : c_ast.FileAST, phasevar):

    # Construct a theory using definitions and declarations
    theory = C99Theory(codeast)

    # Syntactic tree prune, everything after a phase increment is removed
    prune_after_phase_increment(codeast, phasevar)

    # Recursively explore the AST tree and cut the unfeasible branches
    prune_unreachable_branches(codeast, theory)

def prune_after_phase_increment(codeast : c_ast.FileAST, phasevar):

    typ = type(codeast) 
    
    if typ == c_ast.FileAST:
        for statement in codeast.ext:
            prune_after_phase_increment(statement, phasevar)
            
    elif typ == c_ast.If:
        prune_after_phase_increment(codeast.iftrue, phasevar)
        if codeast.iffalse:
            prune_after_phase_increment(codeast.iffalse, phasevar)
    
    elif typ == c_ast.While:
        prune_after_phase_increment(codeast.stmt, phasevar)

    elif typ == c_ast.Compound:
        to_delete = []
        start_deleting = False
        for statement in codeast.block_items:
            if start_deleting:
                to_delete.append(statement)
            else:
                prune_after_phase_increment(statement, phasevar)
                
            if is_var_increment(statement, phasevar):
                start_deleting = True
            
        for node in to_delete:
            codeast.block_items.remove(node)
        # recover continue after phase++
        if start_deleting:
            codeast.block_items.append(c_ast.Continue())

    elif typ == c_ast.FuncDef:
        prune_after_phase_increment(codeast.body, phasevar)

def prune_unreachable_branches(codeast : c_ast.FileAST, theory : C99Theory):
    
    typ = type(codeast) 
    
    if typ == c_ast.FileAST:
        for statement in codeast.ext:
            prune_unreachable_branches(statement, theory)
            
    elif typ == c_ast.If:
        prune_unreachable_branches(codeast.iftrue, theory)
        if codeast.iffalse:
            prune_unreachable_branches(codeast.iffalse)

    elif typ == c_ast.Assignment: 
        theory.handle_assigment(codeast)      
    elif typ == c_ast.While:
        prune_unreachable_branches(codeast.stmt, theory)

    elif typ == c_ast.Compound:
        to_delete = []
        for statement in codeast.block_items:
            if type(statement) == c_ast.If:
                if theory.is_sat(statement.cond):
                    new_context = copy.deepcopy(theory)
                    new_context.handle_if(statement)
                    prune_unreachable_branches(statement, new_context)
                else:
                    to_delete.append(statement)
            else:
                prune_unreachable_branches(statement, theory)
        for node in to_delete:
            codeast.block_items.remove(node)

    elif typ == c_ast.FuncDef:
        prune_unreachable_branches(codeast.body, theory)


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
                    ast.block_items.append(i)
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

def remove_declarations(codeast : c_ast.Node):
    typ = type(codeast) 

    if typ == c_ast.FileAST:
        to_delete = []
        for statement in codeast.ext:
            if is_var_declaration(statement):
                to_delete.append(statement)
            else:
                remove_declarations(statement)
        for node in to_delete:
            codeast.block_items.remove(node)

    elif typ == c_ast.If:
        remove_declarations(codeast.iftrue)

        if codeast.iffalse is not None:
            remove_declarations(codeast.iffalse)

    elif typ == c_ast.Compound:
        to_delete = []
        for statement in codeast.block_items:
            if is_var_declaration(statement):
                to_delete.append(statement)
            else:
                remove_declarations(statement)
        for node in to_delete:
            codeast.block_items.remove(node)

    elif typ == c_ast.FuncDef:
        remove_declarations(codeast.body)

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
        basename = re.sub(SYNCVAR_UNFOLD_REGEX, '', n.lvalue.name)
        return  n.op == '=' and basename == variable
    else:
        return False

def is_syncvar_assigned_to_value(n : c_ast.Node, variable, value):
    if type(n) == c_ast.Assignment:
        # we discard the unfolding index
        basename = re.sub(SYNCVAR_UNFOLD_REGEX, '', n.lvalue.name)
        return  n.op == '=' and basename == variable and n.rvalue.name == value
    else:
        return False

def is_var_increment(n : c_ast.Node, variable):
    return  type(n) == c_ast.UnaryOp and n.op == 'p++' and \
            n.expr.name == variable

def is_var_declaration(n : c_ast.Node):
    return  type(n) == c_ast.Decl

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
    def __init__(self, variables, iteration, path):
        self.variables = variables
        self.iteration = iteration
        self.path = path

    def visit_ID(self, node):
        if node.name in self.variables:
            node.name = rename_syncvar(node.name, self.iteration, self.path)
    
def rename_iterated_variables(ast, variables, iteration, path):
    v = RenameVariablesVisitor(variables, iteration, path)
    v.visit(ast)

class RenameIfBodyVisitor(c_ast.NodeVisitor):
    def __init__(self, variables, iteration, path):
        self.variables = variables
        self.iteration = iteration
        self.path = path

    def visit_If(self, node):
        rename_iterated_variables(node.iftrue, self.variables, self.iteration, self.path)
    
def rename_if_body_variables(ast, variables, iteration, path):
    v = RenameIfBodyVisitor(variables, iteration, path)
    v.visit(ast)

class RenameIfCondVisitor(c_ast.NodeVisitor):
    def __init__(self, variables, iteration, path):
        self.variables = variables
        self.iteration = iteration
        self.path = path

    def visit_If(self, node):
        rename_iterated_variables(node.cond, self.variables, self.iteration, self.path)
    
def rename_if_cond_variables(ast, variables, iteration, path):
    v = RenameIfCondVisitor(variables, iteration, path)
    v.visit(ast)

class DeclareIteratedVariablesVisitor(c_ast.NodeVisitor):
    def __init__(self, variables, iterations, paths):
        self.variables = variables
        self.paths = paths
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
                        for p in range(0,self.paths):
                            new_decl = copy.deepcopy(node)
                            new_decl.name = rename_syncvar(new_decl.name, i, p)
                            new_decl.type.declname = new_decl.name
                        
                            self.visited.append(new_decl)
                            self.current_parent.block_items.insert(0,new_decl)

        elif type(node.type) == c_ast.PtrDecl:
            if  node.type.type.declname in self.variables and \
                node not in self.visited:
                self.visited.append(node)
                for i in range(0,self.iterations):
                    for p in range(0,self.paths):
                        new_decl = copy.deepcopy(node)
                        new_decl.name = rename_syncvar(new_decl.name, i, p)
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

        

def declare_iterated_variables(ast, variables, iterations, paths):
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
    v = DeclareIteratedVariablesVisitor(variables, iterations, paths)
    v.visit(ast)