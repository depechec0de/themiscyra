from pycparser import c_parser, c_ast, parse_file, c_generator
from typing import List, Set, Dict, Tuple, Optional
from z3 import *

# Asume a conjunctive normal form (CNF) in node.cond
def ast_to_smt(node: c_ast.Node, variables: Dict[str, z3.Int]):
    if isinstance(node, c_ast.BinaryOp):
        
        if isinstance(node.left, c_ast.ID) and node.left.name not in variables:
            return True
        else:
            leftnode = ast_to_smt(node.left, variables)

        if isinstance(node.right, c_ast.ID) and node.right.name not in variables:
            return True
        else:
            rightnode = ast_to_smt(node.right, variables)

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
    elif isinstance(node, c_ast.Constant):
        return True
    elif isinstance(node,c_ast.Assignment) and isinstance(node.rvalue, c_ast.ID) and not isinstance(node.rvalue.name, c_ast.ID):
        if variables[node.lvalue.name] is not None:
            return variables[node.lvalue.name] == node.rvalue.name
        else:
            return True
    else:
        if node.name == 'false':
            return False
        elif node.name == 'true':
            return True
        else:
            return True

# Check if the predicate round variables satisfy the context
def is_current_round(predicate: c_ast.Node, context: Dict[str, int]) -> bool:

    if isinstance(predicate, c_ast.BinaryOp):

        if isinstance(predicate.left, c_ast.ID) and isinstance(predicate.right, c_ast.Constant) and predicate.left.name in context:
            return context[predicate.left.name] == int(predicate.right.value)
        elif isinstance(predicate.left, c_ast.ID) and isinstance(predicate.right, c_ast.Constant) and predicate.left.name not in context:
            return True
        else:
            leftpredicate = is_current_round(predicate.left, context)

        if isinstance(predicate.right, c_ast.ID) and isinstance(predicate.left, c_ast.Constant) and predicate.right.name in context:
            return context[predicate.right.name] == int(predicate.left.value)
        elif isinstance(predicate.right, c_ast.ID) and isinstance(predicate.left, c_ast.Constant) and predicate.right.name not in context:
            return True
        else:
            rightpredicate = is_current_round(predicate.right, context)

        if leftpredicate is None:
            leftpredicate = True
        
        if rightpredicate is None:
            rightpredicate = True

        return leftpredicate and rightpredicate

    else:
        return True

def is_sat(ast_predicate, variables, context):

    solver = Solver()
    predicate = ast_to_smt(ast_predicate,variables)

    solver.add(predicate)

    for var in context:
        solver.add(variables[var] == context[var])

    return solver.check() == z3.sat