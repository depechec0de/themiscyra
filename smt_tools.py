from pycparser import c_parser, c_ast, parse_file, c_generator
from typing import List, Set, Dict, Tuple, Optional
from z3 import *

def dead_code_elimination(ast : c_ast.Node, dict_enumtype_constants, dict_variable_enumtype):

    # All this mess is to generate the following dictionaries to handle Enum variables and constants:
    
    # Enum type -> z3 EnumSort
    dict_enumtype_smtsort = {}
    # variable name -> z3 constant declaration in their corresponding EnumSort domain
    dict_variable_smtvar = {}

    dict_const_smtconst = {}

    for enum_name, enum_constants in dict_enumtype_constants.items():
        smt_enum_sort, smt_constants = create_enum_sort(enum_name, enum_constants)
        dict_enumtype_smtsort[enum_name] = smt_enum_sort
        
        dict_const_smtconst = dict(dict_const_smtconst, **smt_constants)

    for var_name, smt_variable in dict_variable_enumtype.items():
        dict_variable_smtvar[var_name] = Const(var_name, dict_enumtype_smtsort[dict_variable_enumtype[var_name]])

    # Recursively explore the AST tree and cut the unfeasible branches
    remove_unreachable_branches(ast, dict_variable_smtvar, dict_const_smtconst, {})

def remove_unreachable_branches(ast : c_ast.Node, enum_variables, enum_constants, context : Dict[str, int]):
    
    typ = type(ast) 
    
    if typ == c_ast.FileAST:
        for statement in ast.ext:
            remove_unreachable_branches(statement, enum_variables, enum_constants, context)
            
    if typ == c_ast.If:
        remove_unreachable_branches(ast.iftrue, enum_variables, enum_constants, context)

    elif typ == c_ast.Assignment:
        constraint = ast_to_smt(ast, enum_variables, enum_constants)
        context[ast.lvalue.name] = constraint        
    elif typ == c_ast.While:
        remove_unreachable_branches(ast.stmt, enum_variables, enum_constants, context)

    elif typ == c_ast.Compound:
        to_delete = []
        for statement in ast.block_items:
            if type(statement) == c_ast.If:
                predicate = ast_to_smt(statement.cond, enum_variables, enum_constants)
                if is_sat(predicate, context):
                    new_context = copy.deepcopy(context)
                    remove_unreachable_branches(statement, enum_variables, enum_constants, new_context)
                else:
                    to_delete.append(statement)
            else:
                remove_unreachable_branches(statement, enum_variables, enum_constants, context)
        for node in to_delete:
            ast.block_items.remove(node)

    elif typ == c_ast.FuncDef:
        remove_unreachable_branches(ast.body, enum_variables, enum_constants, context)

# Asume a conjunctive normal form (CNF) in node.cond
def ast_to_smt(node: c_ast.Node, enum_variables=None, enum_constants=None):
    typ = type(node) 
    
    if typ == c_ast.BinaryOp:

        leftnode = ast_to_smt(node.left, enum_variables, enum_constants)
        rightnode = ast_to_smt(node.right, enum_variables, enum_constants) 

        if node.op == '&&':
            return And(leftnode, rightnode)
        elif node.op == '||':
            return Or(leftnode, rightnode)
        elif node.op == '==':
            return leftnode == rightnode 
        elif node.op == '<':
            return leftnode < rightnode
        elif node.op == '<=':
            return leftnode <= rightnode
        elif node.op == '>':
            return leftnode > rightnode
        elif node.op == '>=':
            return leftnode >= rightnode
        elif node.op == '!=':
            return leftnode != rightnode

    elif typ == c_ast.Assignment and node.op == '=':
        if type(node.rvalue) == c_ast.Constant or type(node.rvalue) == c_ast.ID:
            leftnode = ast_to_smt(node.lvalue, enum_variables, enum_constants)
            rightnode = ast_to_smt(node.rvalue, enum_variables, enum_constants) 
            return leftnode == rightnode
        else:
            return True
    elif typ == c_ast.Constant:
        return int(node.value)
    elif typ == c_ast.ID and node.name == 'false':
        return False
    elif typ == c_ast.ID and node.name == 'true':
        return True
    elif typ == c_ast.FuncCall:
        return ast_func_to_smt_func(node)
    elif typ == c_ast.ID:
        # The variable is an Enum
        if enum_variables is not None and node.name in enum_variables:
            return enum_variables[node.name]
        elif enum_constants is not None and node.name in enum_constants:
            return enum_constants[node.name]
        else:
            return Int(node.name)
    else:
        return True

def ast_func_to_smt_func(node: c_ast.Node):
    domain = []
    args = []
    if node.args is not None:
        for arg in node.args:
            args.append(Int(arg.name))
        domain = [IntSort()] * len(node.args.exprs)

    codomain = IntSort()

    f = Function(node.name.name, *domain, codomain)
    
    return f(*args)

def create_enum_sort(name, values):
    S, enum_values = EnumSort(name, values)

    map_enum = {}
    i = 0
    for e in enum_values:
        map_enum[values[i]] = e
        i=i+1

    return S, map_enum

def is_sat(predicate, context):

    solver = Solver()
    solver.add(predicate)

    for var in context:
        solver.add(context[var])
    #print(solver)
    #print(solver.check() == z3.sat)

    return solver.check() == z3.sat