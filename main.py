import sys
import re
import argparse
import os.path 
import importlib
import yaml

from pycparser import c_parser, c_ast, parse_file, c_generator
from typing import List, Set, Dict, Tuple, Optional
from antlr4 import *
from PTools.PLexer import PLexer
from PTools.PParser import PParser
from PTools.PParserVisitor import PParserVisitor
from PTools.PAst import BuildAstVisitor, PNodeVisitor

import cast_lib
import athos
import semantic_lib
import p_lib

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
    argparser.add_argument('--phaseunfold', help='execute the phaseunfold algorithm', action='store_true')
    argparser.add_argument('--ptoupon', help='transform a P program to the expected async input', action='store_true')
    args = argparser.parse_args()

    # Read config file
    config = yaml.safe_load(open(args.configfile))

    generator = c_generator.CGenerator()

    if args.ptoupon:
        
        inf = FileStream(args.filename)

        lexer = PLexer(inf)
        tokens = CommonTokenStream(lexer)
        parser = PParser(tokens)
        tree = parser.program()

        #print(tree.toStringTree(recog=parser))
        
        v = BuildAstVisitor()
        past = v.visit(tree)
        #print(past)
        cast = p_lib.p_to_upon(past, config)
        #print(cast)
        code = generator.visit(cast)
        print(code)

    else:

        # Pycparser doesn't support directives, we replace them for its content
        input_str_pycparser = prepare_for_pycparser(args.filename)

        # Now we can use pycparser to obtain the AST
        parser = c_parser.CParser()
        
        codeast = parser.parse(input_str_pycparser)

        if args.unfold:
            
            cast_lib.unfold(codeast, args.unfold)

            code = generator.visit(codeast)
            print(code)

        elif args.athos:
            
            compho = athos.async_to_sync(codeast, config)      
            print(compho)

        elif args.deadcode:

            semantic_lib.dead_code_elimination(codeast, config)

            code = generator.visit(codeast)
            print(code)

        elif args.phaseunfold:

            codeast_unfolded = semantic_lib.phase_unfold(codeast, config)

            code = generator.visit(codeast_unfolded)
            print(code)
    