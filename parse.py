import argparse
import sys

from pycparser import c_parser, c_ast, parse_file
from visitors import *

def round_code(ast, phase_var, round_var, context, nextf, steps):

    v = RoundCode(phase_var, round_var, context, nextf, steps)
    v.visit(ast)


if __name__ == "__main__":
    argparser = argparse.ArgumentParser('Dump AST')
    argparser.add_argument('filename', help='name of file to parse')
    argparser.add_argument('--coord', help='show coordinates in the dump', action='store_true')
    args = argparser.parse_args()

    ast = parse_file(args.filename, use_cpp=False)

    # We search the main() function definition
    node_main = get_funcdef_node(ast,'main')

    if node_main is None:
        sys.exit("No main() declaration found.")

    variables = get_variables(node_main)

    # We get the rounds definitions
    rounds = get_rounds(ast)

    def nextround(ts):
        if ts['round']==1:
            return {'ballot': ts['ballot']+1, 'round': 0}
        else:
            return {'ballot': ts['ballot'], 'round': 1}

    round_code(node_main, 'ballot', 'round', context={'ballot': 0, 'round': 0}, nextf=nextround, steps=2)
 
        

