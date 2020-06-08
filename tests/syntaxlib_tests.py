import sys
import re

# insert at 1, 0 is the script path (or '' in REPL)
sys.path.insert(0, '..')

import networkx as nx
import syntaxlib

from pycparser import c_parser, c_ast, parse_file, c_generator

ast = parse_file('examples/test1.c', use_cpp=False)
node_main = syntaxlib.get_funcdef_node(ast,'main')

cfg = syntaxlib.ControlFlowGraph(node_main)
cfg.draw()
"""
node_main_from_cfg = syntaxlib.cfg_to_ast(cfg)

generator = c_generator.CGenerator()

string1 = generator.visit(node_main).replace('\n', '').replace('\r', '').replace(' ', '')
string2 = generator.visit(node_main_from_cfg).replace('\n', '').replace('\r', '').replace(' ', '')

print(string1)
print(string2)
assert( string1 == string2 )
"""