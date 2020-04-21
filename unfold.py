import sys
import re
import argparse
import os.path 
import ast_tools

from pycparser import c_parser, c_ast, parse_file, c_generator

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

def prepare_for_pycparser(filename):

    types_filename = filename.replace('.c','') + '_types.h'
    with open(types_filename) as f:
        types_h_str = f.read()

    decl_filename = filename.replace('.c','') + '_decl.h'
    with open(decl_filename) as f:
        decl_h_str = f.read()
 
    with open(filename) as f:
        original_file_str = f.read()
        
    result_str = original_file_str.replace('#include "'+os.path.basename(decl_filename)+'"', '')
    result_str = result_str.replace('#include "'+os.path.basename(types_filename)+'"', types_h_str)

    result_str = remove_c99_comments(result_str)
    
    return result_str

"""
This function unifies the source code with its headers to obtain a complete source code used in tools like FRAMA-C
"""
def source_unique_file(input_str_unfolded, filename):

    types_filename = filename.replace('.c','') + '_types.h'
    with open(types_filename) as f:
        types_h_str = f.read()

    decl_filename = filename.replace('.c','') + '_decl.h'
    with open(decl_filename) as f:
        decl_h_str = f.read()

    code_str = input_str_unfolded.replace(types_h_str, '')

    code_str = decl_h_str+code_str

    return code_str

def check_positive(value):
    ivalue = int(value)
    if ivalue < 1:
        raise argparse.ArgumentTypeError("%s is an invalid positive int value" % value)
    return ivalue

if __name__ == "__main__":
    # Parse the program arguments
    argparser = argparse.ArgumentParser('Event driven async to sync')
    argparser.add_argument('filename', help='name of file to parse')
    argparser.add_argument('unfolds', help='number of unfolds to perform', type=check_positive)
    args = argparser.parse_args()
    
    # Pycparser doesn't support directives, we replace them for its content
    input_str_pycparser = prepare_for_pycparser(args.filename)

    # Now we can use pycparser to obtain the AST
    parser = c_parser.CParser()

    ast = parser.parse(input_str_pycparser)
    ast_tools.unfold(ast, args.unfolds)

    # Generate the C99 code
    generator = c_generator.CGenerator()
    input_str_unfolded = generator.visit(ast)
    
    # Now we insert the directives for a souce usable in Frama-C
    input_str_with_headers = source_unique_file(input_str_unfolded, args.filename)
    final_code = input_str_with_headers
    
    print(final_code)

    # frama-c-gui -val -main func examples/roundAtoB.unfold1.c