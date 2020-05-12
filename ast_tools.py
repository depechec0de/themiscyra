import copy
import re

from pycparser import c_parser, c_ast, parse_file, c_generator
from ast_visitors import *


"""
This function assumes a C code with a unique "while" statement. The result is
the code unfolded "k" times, where unfolding means replacing every occurrence 
of a "continue" statement with the content of the "while" body.
"""
def unfold(ast, k: int):

    (main_while, while_parent) = get_main_while(ast)

    while_body = copy.deepcopy(main_while.stmt.block_items)

    for i in range(1,k):
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

def remove_c99_comments(text):
    """ remove c-style comments.
        text: blob of text with comments (can include newlines)
        returns: text with comments removed
    """
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