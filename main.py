import sys
import argparse
import os.path 
import ast_tools

from pycparser import c_parser, c_ast, parse_file, c_generator


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
    
    return result_str

def prepare_for_framac(input_str_unfolded, filename):

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
    input_str_framac = prepare_for_framac(input_str_unfolded, args.filename)
    final_code = input_str_framac
    
    print(final_code)

    # frama-c-gui -val -main func examples/roundAtoB.unfold1.c