from pycparser import c_parser, c_ast, parse_file, c_generator
from typing import List, Set, Dict, Tuple, Optional
from z3 import *


def remove_unreachable_branches(ast : c_ast.Node, config, context : Dict[str, int]):
    
    typ = type(ast) 
    
    if typ == c_ast.FileAST:
        for statement in ast.ext:
            remove_unreachable_branches(statement, config, context)
            
    if typ == c_ast.If:
        remove_unreachable_branches(ast.iftrue, config, context)

    elif typ == c_ast.Assignment:
        add_statement_to_context(ast, config, context)
        
    elif typ == c_ast.While:
        remove_unreachable_branches(ast.stmt, config, context)

    elif typ == c_ast.Compound:
        to_delete = []
        for statement in ast.block_items:
            if type(statement) == c_ast.If:
                if is_current_round(statement.cond, config, context):
                    new_context = copy.deepcopy(context)
                    remove_unreachable_branches(statement, config, new_context)
                else:
                    to_delete.append(statement)
            else:
                remove_unreachable_branches(statement, config, context)
        for node in to_delete:
            ast.block_items.remove(node)

    elif typ == c_ast.FuncDef:
        remove_unreachable_branches(ast.body, config, context)

def add_statement_to_context(node: c_ast.Node, config, context : Dict[str, int]):
    if node.op == '=':
        if type(node.rvalue) == c_ast.Constant:
            context[str(node.lvalue.name)] = int(node.rvalue.value)
        elif type(node.rvalue) == c_ast.ID:
            context[str(node.lvalue.name)] = config['labels'][node.rvalue.name]

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
def is_current_round(predicate: c_ast.Node, config, context: Dict[str, int]) -> bool:

    if isinstance(predicate, c_ast.BinaryOp):

        right_is_constant = isinstance(predicate.right, c_ast.Constant)
        right_is_id = isinstance(predicate.right, c_ast.ID)

        left_is_constant = isinstance(predicate.left, c_ast.Constant)
        left_is_id = isinstance(predicate.left, c_ast.ID)

        if left_is_id and right_is_id:
            variable = None
            constant = None

            if predicate.right.name in config['labels']:
                constant = config['labels'][predicate.right.name]
                variable = str(predicate.left.name)

            if predicate.left.name in config['labels']:
                constant = config['labels'][predicate.left.name]
                variable = str(predicate.right.name)

            if variable in context:
                return context[variable] == constant
            else:
                return True

        elif (left_is_id and right_is_constant) or (left_is_constant and right_is_id):

            variable = None
            constant = None

            if left_is_id:
                variable = str(predicate.left.name)
                constant = int(predicate.right.value)

            if right_is_id:
                variable = str(predicate.right.name)
                constant = int(predicate.left.value)

            if variable in context:
                return context[variable] == constant
            else:
                return True
        
        else:
            
            leftpredicate = is_current_round(predicate.left, config, context)
            rightpredicate = is_current_round(predicate.right, config, context)

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