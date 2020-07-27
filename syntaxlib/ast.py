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

    declare_iterated_variables(ast, syncvariables, k, len(upons)+1)

    _unfold(while_statements, while_body, syncvariables, 0, 0, k-1)


def _unfold(ast, while_body, syncvariables, iteration, parent_path, unfoldings):

    upons = [n for n in ast if type(n) == c_ast.If]

    if unfoldings-iteration > 0:
        path = 0

        for upon in upons:
            
            if iteration>0:
                rename_iterated_variables(upon.cond, syncvariables, iteration-1, parent_path)

            rename_iterated_variables(upon.iftrue, syncvariables, iteration, path)
 
            call_recursively(upon, insert_node_after_continue, [copy.deepcopy(while_body)])

            _unfold(upon.iftrue, while_body, syncvariables, iteration+1, path, unfoldings)

            path=path+1
    else:
        for upon in upons:
            rename_iterated_variables(upon.cond, syncvariables, iteration-1, parent_path)
            # path is 0 because we don't branch anymore, there is only one path
            rename_iterated_variables(upon.iftrue, syncvariables, iteration, 0)

    # rename out of scope variables e.g. havoc, mbox
    if iteration>0:
        rename_iterated_variables(ast, syncvariables, iteration-1, parent_path)

def dead_code_elimination(codeast : c_ast.FileAST, phasevar):

    # Construct a theory using definitions and declarations
    theory = C99Theory(codeast)

    # Syntactic tree prune, everything after a phase increment is removed
    call_recursively(ast.get_main_while(codeast), prune_after_phase_increment, [phasevar])

    # Recursively explore the AST tree and cut the unfeasible branches
    to_delete = []
    call_recursively(codeast, get_unreachable_branches, [theory, to_delete])
    call_recursively(codeast, delete_nodes, [to_delete])

def call_recursively(node : c_ast.Node, function, args):
    
    typ = type(node) 
    
    if typ == c_ast.FileAST:
        for statement in node.ext:
            function(statement, *args)
            
    elif typ == c_ast.If:
        function(node.iftrue, *args)
        if node.iffalse:
            function(node.iffalse, *args)

    elif typ == c_ast.While:
        function(node.stmt, *args)

    elif typ == c_ast.Compound:
        for statement in node.block_items:
            function(statement, *args)

    elif typ == c_ast.FuncDef:
        function(node.body, *args)

def prune_after_phase_increment(codeast : c_ast.FileAST, phasevar):
    if type(codeast) == c_ast.Compound:
        to_delete = []
        start_deleting = False
        for statement in codeast.block_items:
            if start_deleting:
                to_delete.append(statement)
            else:
                call_recursively(statement, prune_after_phase_increment, [phasevar])
                
            if is_var_increment(statement, phasevar):
                start_deleting = True
            
        for node in to_delete:
            codeast.block_items.remove(node)
        # recover continue after phase++
        if start_deleting:
            codeast.block_items.append(c_ast.Continue())
    else:
        call_recursively(codeast, prune_after_phase_increment, [phasevar])

def get_unreachable_branches(codeast : c_ast.FileAST, theory : C99Theory, to_delete):   
    
    if type(codeast) == c_ast.Assignment: 
        theory.handle_assigment(codeast)
    elif type(codeast) == c_ast.If:
        if theory.is_sat(codeast):
            new_context = copy.deepcopy(theory)
            new_context.handle_if(codeast)
            call_recursively(codeast, get_unreachable_branches, [new_context, to_delete])
        else:
            to_delete.append(codeast)
    else:
        call_recursively(codeast, get_unreachable_branches, [theory, to_delete])

def delete_nodes(node, to_delete):
    if type(node) == c_ast.Compound:
        delete = []
        for i in node.block_items:
            if i in to_delete:
                delete.append(i)
            else:
                call_recursively(node, delete_nodes, [to_delete])
        for i in delete:
            node.block_items.remove(i)    
    else:
        call_recursively(node, delete_nodes, [to_delete])

def keep_nodes(node, to_keep):
    if type(node) == c_ast.Compound:
        delete = []
        for i in node.block_items:
            if str(i.coord) not in to_keep:
                delete.append(i)
            else:
                call_recursively(node, keep_nodes, [to_keep])
        for i in delete:
            node.block_items.remove(i)    
    else:
        call_recursively(node, keep_nodes, [to_keep])

def insert_node_after_continue(codeast, node):
    if type(codeast) == c_ast.Compound:
        continues = [n for n in codeast.block_items if type(n)==c_ast.Continue]
        
        if len(continues)>0:
            
            items = copy.copy(codeast.block_items)
            for i in items:
                if type(i) == c_ast.Continue:
                    codeast.block_items.remove(i)
                    body = copy.deepcopy(node)
                    for e in body:
                        codeast.block_items.append(e)
                    codeast.block_items.append(i)
        else:
            for i in codeast.block_items:
                call_recursively(i, insert_node_after_continue, [node])

    else:
        call_recursively(codeast, insert_node_after_continue, [node])

def remove_declarations(codeast : c_ast.Node):
    if type(codeast) == c_ast.FileAST:
        to_delete = []
        for statement in codeast.ext:
            if is_var_declaration(statement):
                to_delete.append(statement)
            else:
                call_recursively(statement, remove_declarations, [])
        for node in to_delete:
            codeast.block_items.remove(node)

    elif type(codeast) == c_ast.Compound:
        to_delete = []
        for statement in codeast.block_items:
            if is_var_declaration(statement):
                to_delete.append(statement)
            else:
                call_recursively(statement, remove_declarations, [])
        for node in to_delete:
            codeast.block_items.remove(node)

    else:
        call_recursively(codeast, remove_declarations, [])

def remove_whiles(codeast : c_ast.Node):
    if type(codeast) == c_ast.Compound:
        new_block_items = copy.deepcopy(codeast.block_items)
        for i in range(0,len(codeast.block_items)):
            if type(codeast.block_items[i]) == c_ast.While:
                # insert list in position i
                while_content = copy.deepcopy(codeast.block_items[i].stmt.block_items)
                del new_block_items[i]
                new_block_items[i:i] = while_content
            else:
                call_recursively(i, remove_whiles, [])

        codeast.block_items = new_block_items
        
    else:
        call_recursively(codeast, remove_whiles, [])

def keep_send_code(codeast : c_ast.Node, name):
    items = None
    if type(codeast) == c_ast.FileAST:
        items = codeast.ext

    elif type(codeast) == c_ast.Compound:
        items = codeast.block_items

    if items is not None: 
        to_delete = []
        for statement in items:

            if type(statement) == c_ast.If:
                call_recursively(statement, keep_send_code, [name])
            
            elif not is_funccall_with_name(statement, name):
                to_delete.append(statement) 

        for node in to_delete:
            items.remove(node)

    else:
        call_recursively(codeast, keep_send_code, [name])

def is_funccall_with_name(node : c_ast.Node, name):
    return type(node) == c_ast.FuncCall and node.name.name == name

def count_no_if_statements(node : c_ast.Node) -> int:
    class NonIfCounterVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.result = 0

        def visit_Compound(self, node):
            count_no_if_stm = len([n for n in node.block_items if type(n)!=c_ast.If])
            self.result = self.result + count_no_if_stm

            c_ast.NodeVisitor.generic_visit(self, node)

    v = NonIfCounterVisitor()
    v.visit(node)
    return v.result

def remove_empty_ifs(codeast : c_ast.Node):
    items = None
    if type(codeast) == c_ast.FileAST:
        items = codeast.ext

    elif type(codeast) == c_ast.Compound:
        items = codeast.block_items

    if items is not None: 
        to_delete = []
        for statement in items:

            if type(statement) == c_ast.If:                              
                if ast.count_no_if_statements(statement) == 0:
                    to_delete.append(statement) 
            else:
                call_recursively(statement, remove_empty_ifs, [])

        for node in to_delete:
            items.remove(node)

    else:
        call_recursively(codeast, remove_empty_ifs, [])

def get_compho_send(codeast : c_ast.Node) -> c_ast.Node:
    call_recursively(codeast, keep_send_code, ['send'])
    call_recursively(codeast, remove_empty_ifs, [])

    return codeast

def remove_send_mbox_code(codeast : c_ast.Node):
    items = None
    if type(codeast) == c_ast.FileAST:
        items = codeast.ext

    elif type(codeast) == c_ast.Compound:
        items = codeast.block_items

    if items is not None: 
        to_delete = []
        for statement in items:
            # TODO: is_var_assignment(statement, 'mbox') or not
            if is_funccall_with_name(statement, 'send'):
                to_delete.append(statement)
            else:
                call_recursively(statement, remove_send_mbox_code, [])

        for node in to_delete:
            items.remove(node)

    else:
        call_recursively(codeast, keep_send_code, [])

def get_compho_update(codeast : c_ast.Node) -> c_ast.Node:
    call_recursively(codeast, remove_send_mbox_code, [])

    return codeast

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

def is_var_assignment(n : c_ast.Node, varname):
    if type(n) == c_ast.Assignment:
        return  n.op == '=' and n.lvalue.name == varname
    else:
        return False

def get_decl_type(n : c_ast.Decl):
    if type(n.type) == c_ast.TypeDecl or type(n.type) == c_ast.PtrDecl:
        return get_decl_type(n.type)
    elif type(n.type) == c_ast.Enum or type(n.type) == c_ast.Struct:
        return n.type.name
    elif type(n.type) == c_ast.IdentifierType:
        return n.type.names[0]
    else:
        return '?'

def get_struct_fields_decl(n : c_ast.Decl):
    fields = {}
    for f in n.type.decls:
        fields[f.name] = get_decl_type(f)
    return fields

def get_funccall_args(n : c_ast.FuncCall):
    return n.args.exprs

def get_funccall_name(n : c_ast.FuncCall):
    return n.name.name   

def get_structref_basename(n : c_ast.StructRef):
    """ A StructRef name can contain several dereferences e.g. var->foo->bar
    should return `var`
    """
    if type(n) == c_ast.StructRef:
        return get_structref_basename(n.name)
    elif type(n) == c_ast.ID:
        return n.name

def get_structref_name(n : c_ast.StructRef):
    """ A StructRef name can contain several dereferences e.g. var->foo->bar
    """
    if type(n.name) == c_ast.StructRef:
        return get_structref_name(n.name) + n.type + n.field.name
    else:
        return n.name.name + n.type + n.field.name

def get_structref_firstref_field(n : c_ast.StructRef):
    if type(n) == c_ast.StructRef:
        if type(n.name) == c_ast.ID:
            return n.field.name
        else:
            return get_structref_firstref_field(n.name)

def is_var_increment(n : c_ast.Node, variable):
    is_increment = type(n) == c_ast.UnaryOp and n.op == 'p++' and n.expr.name == variable
    is_jump = type(n) == c_ast.Assignment and n.lvalue.name == variable
    return is_increment or is_jump

def is_var_declaration(n : c_ast.Node):
    return  type(n) == c_ast.Decl

def get_assigment_value(n : c_ast.Assignment):
    return str(n.rvalue.name)

def count_variable_assigments(path, variable):
    i = 0
    for n in path:
        if is_syncvar_assignment(n, variable):
            i=i+1
    return i

def count_continues(path : List[c_ast.Node]):
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

def get_main_while(ast):
    """ Return the outer while of the AST """
    class MainWhileVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.result = None

        def visit_While(self, node):
            self.result = node

    v = MainWhileVisitor()
    v.visit(ast)
    return v.result

def get_funcdef_node(ast, funcname) -> c_ast.FuncDef:
    """ Returns  the corresponding FuncDef node in the AST defined as 
    `funcname`.

    Parameters
    ----------
    ast : a pycparser AST 
    funcname : a function name to find
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

    v = FuncDefVisitor(funcname)
    v.visit(ast)
    return v.result

def get_enum_declarations(ast) -> Dict[str, List[str]]:
    """ Returns enum definitions in the AST as a dictionary: {enum_type_name: [const1, ...]}

    Parameters
    ----------
    ast : pycparser.c_ast.Node 
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

    v = EnumDeclarationVisitor()
    v.visit(ast)
    return v.result

def get_func_declarations(ast) -> Dict[str, c_ast.FuncDecl]:
    class FuncDeclarationVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.result = {}

        def visit_Decl(self, node):
            if type(node.type) == c_ast.FuncDecl:
                self.result[node.name] = node.type

    v = FuncDeclarationVisitor()
    v.visit(ast)
    return v.result

def get_struct_vars_declarations(ast) -> Dict[str,str]:
    class StructVariableDeclarationVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.result = {}

        def visit_Decl(self, node):
            if type(node.type) == c_ast.PtrDecl and type(node.type.type.type) == c_ast.Struct:
                self.result[node.name] = node.type.type.type.name
            elif type(node.type) == c_ast.TypeDecl and type(node.type.type) == c_ast.Struct:
                self.result[node.name] = node.type.type.name

    v = StructVariableDeclarationVisitor()
    v.visit(ast)
    return v.result

def get_struct_declarations(ast) -> Dict[str, Dict[str,str]]:
    class StructVariableDeclarationVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.result = {}

        def visit_Decl(self, node):
            if type(node.type) == c_ast.Struct:
                self.result[node.type.name] = get_struct_fields_decl(node)

    v = StructVariableDeclarationVisitor()
    v.visit(ast)
    return v.result

def get_declared_vars(ast):
    """ Returns variable declarations as a dictionary {variable: type}

    Parameters
    ----------
    ast: a pycparser AST 
    """
    class VariableDeclarationVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.result = {}

        def visit_Decl(self, node):
            if type(node.type) == c_ast.TypeDecl or type(node.type) == c_ast.PtrDecl:
                self.result[node.name] = get_decl_type(node)

    v = VariableDeclarationVisitor()
    v.visit(ast)
    return v.result
    
def rename_iterated_variables(ast, variables, iteration, path):
    class RenameVariablesVisitor(c_ast.NodeVisitor):
        def __init__(self, variables, iteration, path):
            self.variables = variables
            self.iteration = iteration
            self.path = path

        def visit_ID(self, node):
            if node.name in self.variables:
                node.name = rename_syncvar(node.name, self.iteration, self.path)

    v = RenameVariablesVisitor(variables, iteration, path)
    v.visit(ast)  

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

    v = DeclareIteratedVariablesVisitor(variables, iterations, paths)
    v.visit(ast)