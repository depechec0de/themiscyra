import sys
import argparse
import os.path 
import ast_tools
import smt_tools
from z3 import *

from pycparser import c_parser, c_ast, parse_file, c_generator

def prepare_for_pycparser(filename, header_prefix):

    types_filename = header_prefix + '_types.h'
    with open(types_filename) as f:
        types_h_str = f.read()

    decl_filename = header_prefix + '_decl.h'
    with open(decl_filename) as f:
        decl_h_str = f.read()
 
    with open(filename) as f:
        original_file_str = f.read()
        
    result_str = original_file_str.replace('#include "'+os.path.basename(decl_filename)+'"', '')
    result_str = result_str.replace('#include "'+os.path.basename(types_filename)+'"', types_h_str)

    result_str = ast_tools.remove_c99_comments(result_str)
    
    return result_str

"""
This function unifies the source code with its headers to obtain a complete source code used in tools like FRAMA-C
"""
def source_unique_file(input_str_unfolded, filename, header_prefix):

    types_filename = header_prefix + '_types.h'
    with open(types_filename) as f:
        types_h_str = f.read()

    decl_filename = header_prefix + '_decl.h'
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
    argparser.add_argument('--headers', help='Headers filename prefix, the default search for files called filename_decl.h and filename_types.h')
    args = argparser.parse_args()

    header_prefix = args.filename.replace('.c','')
    if args.headers:
      header_prefix = args.headers
    
    # Pycparser doesn't support directives, we replace them for its content
    input_str_pycparser = prepare_for_pycparser(args.filename, header_prefix)

    # Now we can use pycparser to obtain the AST
    parser = c_parser.CParser()

    ast = parser.parse(input_str_pycparser)
    ast_tools.unfold(ast, args.unfolds)

    # Dead code elimination
    config={'syncv': {'vround': Int('vround'), 'view': Int('view')}, 
            'labels': {'STARTVIEWCHANGE': 0, 'DOVIEWCHANGE': 1, 'STARTVIEW': 2 } }
    smt_tools.remove_unreachable_branches(ast, config, {})

    # Generate the C99 code
    generator = c_generator.CGenerator()
    input_str_unfolded = generator.visit(ast)
    
    # Now we insert the directives for a souce usable in Frama-C
    input_str_with_headers = source_unique_file(input_str_unfolded, args.filename, header_prefix)
    final_code = input_str_with_headers
    
    print(final_code)

    # frama-c-gui -val -main func examples/roundAtoB.unfold1.c


