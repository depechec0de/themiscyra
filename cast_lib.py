import copy
import re

from typing import Type, List, Set, Dict, Tuple, Optional
from pycparser import c_parser, c_ast, parse_file, c_generator

import cfg

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
    
def is_recursive_node_type(node : c_ast.Node):
    recursive_types = {c_ast.FileAST, c_ast.Compound, c_ast.If, c_ast.While, c_ast.Compound, c_ast.FuncDef}

    return type(node) in recursive_types

def map_dfs(node : c_ast.Node, function, args):
    """ Perform a DFS walk in the AST and applies `function` to every node """
    typ = type(node) 

    continue_recursion = function(node, *args)

    if continue_recursion is None or continue_recursion:
        if typ == c_ast.FileAST:
            for statement in node.ext:
                map_dfs(statement, function, args)
                
        elif typ == c_ast.If:
            map_dfs(node.iftrue, function, args)
            if node.iffalse:
                map_dfs(node.iffalse, function, args)

        elif typ == c_ast.While:
            map_dfs(node.stmt, function, args)

        elif typ == c_ast.Compound:
            for statement in node.block_items:
                map_dfs(statement, function, args)

        elif typ == c_ast.FuncDef:
            map_dfs(node.body, function, args)

def removes_nodes_matching(n : c_ast.Node, filter_condition, *args):
    items = None
    if type(n) == c_ast.FileAST:
        items = n.ext
    elif type(n) == c_ast.Compound:
        items = n.block_items

    if items is not None: 
        to_delete = []
        for statement in items:
            if filter_condition(statement, *args):
                to_delete.append(statement)

        for node in to_delete:
            items.remove(node)

def filter_nodes(n : c_ast.Node, filter_condition, *filter_args):
    """ Filter nodes of the AST matching `filter_condition` """
    map_dfs(n, removes_nodes_matching, [filter_condition, *filter_args])

def find_nodes_matching(n : c_ast.Node, match_condition, matching):
    if match_condition(n):
        matching.append(n)

def find_nodes(n : c_ast.Node, match_condition):
    """ Find nodes of the AST matching `match_condition` """
    matching = []
    map_dfs(n, find_nodes_matching, [match_condition, matching])

    return matching

def unfold(ast, k: int):
    """This function assumes a C code with a unique `while` statement. The 
    result is the code unfolded `k` times, where unfolding means replacing 
    every occurrence of a `continue` statement with the original `while`
    body.

    Parameters
    ----------
    ast : pycparser.c_ast.Node
    k : number of unfoldings to perform
    """

    main_while = find_while_node(ast)
    while_statements = main_while.stmt.block_items

    while_body = copy.deepcopy(main_while.stmt.block_items)

    upons = [n for n in while_statements if type(n) == c_ast.If]

    for upon in upons:
        _unfold(upon.iftrue, while_body, iteration=0, unfoldings=k-1)


def _unfold(compound, while_body, iteration, unfoldings):

    new_body_iteration = copy.deepcopy(while_body)

    map_dfs(compound, insert_node_after_continue, [new_body_iteration])

    new_upons = [n for n in compound if type(n) == c_ast.If]

    # recursive calls or base cases
    for upon in new_upons:
        if unfoldings > iteration:
            _unfold(upon.iftrue, while_body, iteration=iteration+1, unfoldings=unfoldings)

def prune_after_phase_increment(codeast : c_ast.Node, phasevar):
    if type(codeast) == c_ast.Compound:
        to_delete = []
        start_deleting = False
        for statement in codeast.block_items:
            if start_deleting:
                to_delete.append(statement)
                
            if is_var_increment(statement, phasevar):
                start_deleting = True
            
        for node in to_delete:
            codeast.block_items.remove(node)
        # recover continue after phase++
        if start_deleting:
            codeast.block_items.append(c_ast.Continue())   

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
                    # uncomment this line to keep the old continue
                    #codeast.block_items.append(i)
                    codeast.block_items.append(c_ast.Break())

            return False
        
def replace_while_with_body(codeast : c_ast.Node):
    if type(codeast) == c_ast.Compound:
        new_block_items = copy.deepcopy(codeast.block_items)
        for i in range(0,len(codeast.block_items)):
            if type(codeast.block_items[i]) == c_ast.While:
                # insert list in position i
                while_content = copy.deepcopy(codeast.block_items[i].stmt.block_items)
                del new_block_items[i]
                new_block_items[i:i] = while_content

        codeast.block_items = new_block_items
        
def is_funccall_with_name(node : c_ast.Node, name):
    return type(node) == c_ast.FuncCall and node.name.name == name

def count_inner_ifs(node : c_ast.Node) -> int:
    """ Visit the AST node and count how many nested c_ast.If it contains """
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

def variable_assigments_by_value(cfg : cfg.ControlFlowGraph, variable) -> Dict[str, List[c_ast.Assignment]]:
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

    variable_assigments = [node for node in cfg if is_var_assignment(node.astnode, variable)]

    for n in variable_assigments:
        value = get_assig_val(n.astnode)

        if not value in map_rvalue_nodes:
            map_rvalue_nodes[value] = []

        map_rvalue_nodes[value].append(n)

    return map_rvalue_nodes

def variable_increments(cfg, variable):
    return [node for node in cfg if is_var_increment(node, variable)]

def is_var_assignment(n : c_ast.Node, varname):
    if type(n) == c_ast.Assignment:
        return  n.op == '=' and n.lvalue.name == varname
    else:
        return False

def is_ghostvar_assignment(n : c_ast.Node):
    if type(n) == c_ast.Assignment:
        return  n.op == '=' and "__pred_" in n.lvalue.name
    else:
        return False

def is_var_assignment_to_value(n : c_ast.Node, varname, value):
    if type(n) == c_ast.Assignment:
        return is_var_assignment(n, varname) and n.rvalue.name == value
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
    #is_jump = type(n) == c_ast.Assignment and n.lvalue.name == variable
    return is_increment

def is_var_declaration(n : c_ast.Node):
    return  type(n) == c_ast.Decl

def get_assig_val(n : c_ast.Assignment):
    return str(n.rvalue.name)

def count_continues(path : List[c_ast.Node]):
    return len([1 for n in path if type(n) == c_ast.Continue])

def count_variable_assigments(path : List[c_ast.Node], var_name):
    return len([1 for n in path if is_var_assignment(n, var_name)])

def find_while_node(ast):
    """ Return the outer while of the AST """
    class MainWhileVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.result = None

        def visit_While(self, node):
            self.result = node

    v = MainWhileVisitor()
    v.visit(ast)
    return v.result

def find_funcdef_node(ast, funcname) -> c_ast.FuncDef:
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

def add_variable_assignment_version(ast):
    class RenameVariablesVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.assignment_counter = dict()

        def visit_Assignment(self, node):
            self.generic_visit(node.rvalue)

            var_name = node.lvalue.name
            if var_name in self.assignment_counter:
                self.assignment_counter[var_name] += 1
            else:
                self.assignment_counter[var_name] = 1

            node.lvalue.name = node.lvalue.name + "__" + str(self.assignment_counter[var_name])

        def visit_FuncCall(self, node):
            for arg in node.args:
                self.generic_visit(arg)
 
        def visit_ID(self, node):
            var_name = node.name
            if var_name in self.assignment_counter:
                node.name = var_name + "__" + str(self.assignment_counter[var_name])
            else: 
                node.name = var_name + "__0"

    v = RenameVariablesVisitor()
    v.visit(ast)

def rename_variable(ast, dict_rename):

    class RenameVariablesVisitor(c_ast.NodeVisitor):
        def __init__(self, original_ast, dict_rename):
            self.original_ast = original_ast
            self.dict_rename = dict_rename

        def visit_FuncCall(self, node):
            for arg in node.args:
                self.visit(arg)

        def visit_ID(self, node):
            for var_origname, var_newname in self.dict_rename.items():
                if node.name == var_origname:
                    node.name = var_newname

    v = RenameVariablesVisitor(ast, dict_rename)
    v.visit(ast)  
    
def get_initial_assignments(ast):

    class InitialAssignmentsVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.assignments = []

        def visit_Assignment(self, node):
            self.assignments.append(node)

        # We don't enter the main loop
        def visit_While(self, node):
            pass
 
    v = InitialAssignmentsVisitor()
    v.visit(ast)

    return v.assignments

def ast_to_str(node : c_ast.Node):
    generator = c_generator.CGenerator()
    nodestr = generator.visit(node)

    return nodestr.replace('\n' , '').strip()

def unify_if_predicates(predicates):

    if len(predicates)==1:
        return predicates[0]
    else:
        return c_ast.BinaryOp('&&', predicates[0], unify_if_predicates(predicates[1:]))

def create_ghost_variables(ast : c_ast.Node) -> Dict[str, c_ast.ID]:

    class IfsVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.ghost_variables = dict()
            self.counter = 0

        def visit_If(self, node):
            self.ghost_variables[str(node.cond.coord)] = c_ast.ID("__pred_" + str(self.counter))
            self.counter += 1

            self.visit(node.iftrue)
            if node.iffalse is not None:
                self.visit(node.iffalse)
 
    v = IfsVisitor()
    v.visit(ast)

    return v.ghost_variables

def add_ghost_variables(codeast : c_ast.Node, ghost_variables):

    if type(codeast) == c_ast.Compound:

        items = codeast.block_items

        for n in items:
            if type(n) == c_ast.If:
                ghost_idx = str(n.cond.coord)

                var = ghost_variables[ghost_idx]
                pred = copy.deepcopy(n.cond)
  
                #ghost_declaration = c_ast.Assignment('=', var, pred)
                ghost_declaration = c_ast.Assignment('=', var, c_ast.ID('true'))
                n.iftrue.block_items.insert(0, ghost_declaration)

def has_elements(node):

    class CountVisitor(c_ast.NodeVisitor):
        def __init__(self):
            self.result = True

        def visit_Compound(self, node):
            for n in node.block_items:
                if type(n) != c_ast.If:
                    self.result = False
                else:
                    self.visit(n)

    v = CountVisitor()
    v.visit(node)

    return v.result

def remove_empty_ifs(node):

    class CompoundVisitor(c_ast.NodeVisitor):

        def visit_Compound(self, node):
            to_delete = []
            for n in node.block_items:
                if type(n) == c_ast.If:
                    if has_elements(n.iftrue):
                        to_delete.append(n)
                    else:
                        self.visit(n)

            for n in to_delete:
                node.block_items.remove(n)

    v = CompoundVisitor()
    v.visit(node)

def chain_ifs(node):
    class CompoundVisitor(c_ast.NodeVisitor):

        def visit_Compound(self, node):
            to_chain = []
            
            for n in node.block_items:
                if type(n) == c_ast.If:
                    to_chain.append(n)
                    #print(n)

                    self.visit(n)

            if len(to_chain)>1:
                for n in to_chain:
                    node.block_items.remove(n)

                first_if = to_chain[0]
                chained_if = c_ast.If(first_if.cond, iftrue=first_if.iftrue, iffalse=None)
                prev_if = chained_if
                node.block_items.append(chained_if)

                for n in to_chain[1:-1]:
                    new_if = c_ast.If(n.cond, iftrue=n.iftrue, iffalse=None)
                    prev_if.iffalse = new_if
                    prev_if = new_if
                    
                last_if = to_chain[-1]
                prev_if.iffalse = c_ast.If(last_if.cond, iftrue=last_if.iftrue, iffalse=None)
                

    v = CompoundVisitor()
    v.visit(node)