from pycparser import c_parser, c_ast, parse_file, c_generator
from typing import List, Set, Dict, Tuple, Optional
from z3 import *


def remove_unreachable_branches(ast : c_ast.Node, constants, context : Dict[str, int]):
    
    typ = type(ast) 
    
    if typ == c_ast.FileAST:
        for statement in ast.ext:
            remove_unreachable_branches(statement, constants, context)
            
    if typ == c_ast.If:
        remove_unreachable_branches(ast.iftrue, constants, context)

    elif typ == c_ast.Assignment:
        add_statement_to_context(ast, constants, context)
        
    elif typ == c_ast.While:
        remove_unreachable_branches(ast.stmt, constants, context)

    elif typ == c_ast.Compound:
        to_delete = []
        for statement in ast.block_items:
            if type(statement) == c_ast.If:
                predicate = ast_to_smt(statement.cond, constants)
                if is_sat(predicate, context):
                    new_context = copy.deepcopy(context)
                    remove_unreachable_branches(statement, constants, new_context)
                else:
                    to_delete.append(statement)
            else:
                remove_unreachable_branches(statement, constants, context)
        for node in to_delete:
            ast.block_items.remove(node)

    elif typ == c_ast.FuncDef:
        remove_unreachable_branches(ast.body, constants, context)

def add_statement_to_context(node: c_ast.Node, constants, context : Dict[str, int]):
    if node.op == '=':
        val = None
        if type(node.rvalue) == c_ast.Constant:
            val = int(node.rvalue.value)
        elif type(node.rvalue) == c_ast.ID and node.rvalue.name in constants:
            val = constants[node.rvalue.name]
        elif type(node.rvalue) == c_ast.FuncCall:
            val = Int(node.rvalue.name.name)

        context[Int(node.lvalue.name)] = val

# Asume a conjunctive normal form (CNF) in node.cond
def ast_to_smt(node: c_ast.Node, constants={}):
    typ = type(node) 
    
    if typ == c_ast.BinaryOp:

        leftnode = ast_to_smt(node.left, constants)
        rightnode = ast_to_smt(node.right, constants)            

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

    elif typ == c_ast.Constant:
        return int(node.value)
    elif typ == c_ast.ID and node.name == 'false':
        return False
    elif typ == c_ast.ID and node.name == 'true':
        return True
    elif typ == c_ast.FuncCall:
        return Int(node.name.name)
    elif typ == c_ast.ID and node.name in constants:
        return constants[node.name]
    elif typ == c_ast.ID:
        return Int(node.name)

def is_sat(predicate, context):

    solver = Solver()
    solver.add(predicate)

    for var in context:
        solver.add(var == context[var])

    return solver.check() == z3.sat