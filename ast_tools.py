import copy

from pycparser import c_parser, c_ast, parse_file, c_generator
from ast_visitors import *


"""
This function assumes a C code with a unique "while" iteration. The result is
the code unfolded "times" times, where unfolding means replacing every occurrence 
of a "continue" statement with the content of the "while" body.
"""
def unfold(ast, times: int):

    (main_while, while_parent) = get_main_while(ast)

    while_body = copy.deepcopy(main_while.stmt.block_items)

    for i in range(0,times):
        _insert_node_after_continue(main_while, while_body)

    # Remove the main while
    new_while_code = copy.deepcopy(main_while.stmt)

    # We move the content of the unfolded "while" outside of it
    index =  while_parent.block_items.index(main_while) 
    while_parent.block_items[index:index] = new_while_code.block_items

    # Remove the old "while"
    while_parent.block_items.remove(main_while)

    _replace_continue_for_return(while_parent)


def _insert_node_after_continue(ast, node):
    
    typ = type(ast) 

    if typ == c_ast.If:
        _insert_node_after_continue(ast.iftrue, node)

        if ast.iffalse is not None:
            _insert_node_after_continue(ast.iffalse, node)
        
    elif typ == c_ast.While:
        _insert_node_after_continue(ast.stmt, node)

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
                _insert_node_after_continue(i, node)

    elif typ == c_ast.FuncDef:
        _insert_node_after_continue(ast.body, node)


def _replace_continue_for_return(ast):

    typ = type(ast) 

    if typ == c_ast.If:
        _replace_continue_for_return(ast.iftrue)

        if ast.iffalse is not None:
            _replace_continue_for_return(ast.iffalse)
        
    elif typ == c_ast.While:
        _replace_continue_for_return(ast.stmt)

    elif typ == c_ast.Compound:
            
            for i in ast.block_items:
                if type(i) == c_ast.Continue:
                    zero = c_ast.Constant(type=int, value='0')
                    return_ast = c_ast.Return(expr=zero)
                    index = ast.block_items.index(i)
                    ast.block_items.insert(index, return_ast)
                    ast.block_items.remove(i)
                else:
                    _replace_continue_for_return(i)

    elif typ == c_ast.FuncDef:
        _replace_continue_for_return(ast.body)