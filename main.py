import sys
import argparse
import os.path 
import importlib
import yaml

from pycparser import c_parser, c_ast, parse_file, c_generator
from typing import List, Set, Dict, Tuple, Optional

import cast_lib
import athos
import c99theory

def prepare_for_pycparser(filename):

    with open(filename) as f:
        original_file_str = f.read()

    result_str = cast_lib.remove_c99_comments(original_file_str)
    
    return result_str

def check_positive(value):
    ivalue = int(value)
    if ivalue < 1:
      raise argparse.ArgumentTypeError("%s is an invalid positive int value" % value)
    return ivalue

if __name__ == "__main__":
    # Parse the program arguments
    argparser = argparse.ArgumentParser('Event driven async to sync')
    argparser.add_argument('filename', help='name of file to parse')
    argparser.add_argument('configfile', help='configuration file with syncvars and labels')
    argparser.add_argument('--unfold', help='number of unfolds to perform', type=check_positive)
    argparser.add_argument('--athos', help='perform async to sync translation', action='store_true')
    argparser.add_argument('--deadcode', help='perform a deadcode elimination', action='store_true')
    args = argparser.parse_args()

    # Pycparser doesn't support directives, we replace them for its content
    input_str_pycparser = prepare_for_pycparser(args.filename)

    # Read config file
    config = yaml.safe_load(open(args.configfile))

    # Now we can use pycparser to obtain the AST
    parser = c_parser.CParser()
    generator = c_generator.CGenerator()
    codeast = parser.parse(input_str_pycparser)

    if args.unfold:
        
        cast_lib.unfold(codeast, args.unfold, config)

        code = generator.visit(codeast)
        print(code)

    elif args.athos:
        
        compho = athos.async_to_sync(codeast, config)      
        
        for label, compho in compho.items():
            print("################## "+label+" ######################")
            for step, step_code_ast in compho.items():
                print("############ "+step+" ############") 
                code = generator.visit(step_code_ast)
                print(code)

    elif args.deadcode:

        c99theory.dead_code_elimination(codeast, config['phase'])

        code = generator.visit(codeast)
        print(code)
    