import sys
# insert at 1, 0 is the script path (or '' in REPL)
sys.path.insert(0, '..')

import networkx as nx
from semantic import *
from ast_visitors import *
from pycparser import c_parser, c_ast, parse_file

######################################

print("############ SIMPLEST ############")

ast = parse_file('examples/simplest.c', use_cpp=False)

# We search the main() function definition
node_main = get_funcdef_node(ast,'main')

cfg = ControlFlowGraph()
(start_node, exit_node) = cfg.from_ast(node_main)

assert( 2 == len(cfg))

test_edges = {("examples/simplest.c:1:5","examples/simplest.c:3:5")}

graph_edges = []

for e in cfg.edges():
    graph_edges.append((str(e[0].coord),str(e[1].coord)))
    #print(str(e[0].coord)+"->"+str(e[1].coord))

assert( len(graph_edges) == len(test_edges) )
assert( set(graph_edges) == test_edges )

paths = list(nx.all_simple_paths(cfg, start_node, exit_node))

assert( 1 == len(paths))

print("############ NESTED ############")

ast = parse_file('examples/nested.c', use_cpp=False)

# We search the main() function definition
node_main = get_funcdef_node(ast,'main')

cfg = ControlFlowGraph()
(start_node, exit_node) = cfg.from_ast(node_main)

assert( 10 == len(cfg))

test_edges = {('examples/nested.c:1:5', 'examples/nested.c:3:5'),('examples/nested.c:3:5', 'examples/nested.c:4:9'),('examples/nested.c:3:5', 'examples/nested.c:3:5:END'),('examples/nested.c:4:9', 'examples/nested.c:5:13'),('examples/nested.c:4:9', 'examples/nested.c:4:9:END'),('examples/nested.c:4:9:END', 'examples/nested.c:3:5:END'),('examples/nested.c:5:13', 'examples/nested.c:6:17'),('examples/nested.c:5:13', 'examples/nested.c:5:13:END'),('examples/nested.c:6:17', 'examples/nested.c:7:21'),('examples/nested.c:6:17', 'examples/nested.c:6:17:END'),('examples/nested.c:6:17:END', 'examples/nested.c:5:13:END'),('examples/nested.c:7:21', 'examples/nested.c:6:17:END'),('examples/nested.c:5:13:END', 'examples/nested.c:4:9:END'),('examples/nested.c:5:13:END', 'examples/nested.c:5:13'), ('examples/nested.c:3:5:END', 'examples/nested.c:3:5')}

graph_edges = []

for e in cfg.edges():
    graph_edges.append((str(e[0].coord),str(e[1].coord)))
    #print("('"+str(e[0].coord)+"', '"+str(e[1].coord)+"'),")

assert( len(graph_edges) == len(test_edges) )
assert( set(graph_edges) == test_edges )

paths = list(nx.all_simple_paths(cfg, start_node, exit_node))

assert( 5 == len(paths))

print("############ IFBRANCH ############")

ast = parse_file('examples/ifbranch.c', use_cpp=False)

# We search the main() function definition
node_main = get_funcdef_node(ast,'main')

cfg = ControlFlowGraph()
(start_node, exit_node) = cfg.from_ast(node_main)

assert( 5 == len(cfg))

test_edges = {('examples/ifbranch.c:1:5', 'examples/ifbranch.c:3:5'),('examples/ifbranch.c:3:5', 'examples/ifbranch.c:4:9'),('examples/ifbranch.c:3:5', 'examples/ifbranch.c:6:9'),('examples/ifbranch.c:4:9', 'examples/ifbranch.c:3:5:END'),('examples/ifbranch.c:6:9', 'examples/ifbranch.c:3:5:END')}

graph_edges = []

for e in cfg.edges():
    graph_edges.append((str(e[0].coord),str(e[1].coord)))
    #print("('"+str(e[0].coord)+"', '"+str(e[1].coord)+"'),")

assert( len(graph_edges) == len(test_edges) )
assert( set(graph_edges) == test_edges )

paths = list(nx.all_simple_paths(cfg, start_node, exit_node))

assert( 2 == len(paths))

print("############ TEST1 ############")

ast = parse_file('examples/test1.c', use_cpp=False)

# We search the main() function definition
node_main = get_funcdef_node(ast,'main')

cfg = ControlFlowGraph()
(start_node, exit_node) = cfg.from_ast(node_main)

test_edges = {('examples/test1.c:1:5','examples/test1.c:3:5'),('examples/test1.c:3:5','examples/test1.c:5:9'),('examples/test1.c:5:9','examples/test1.c:6:13'),('examples/test1.c:9:9','examples/test1.c:10:13'), ('examples/test1.c:6:13','examples/test1.c:5:9:END'), ('examples/test1.c:10:13', 'examples/test1.c:9:9:END'), ('examples/test1.c:5:9:END', 'examples/test1.c:9:9'), ('examples/test1.c:9:9:END', 'examples/test1.c:13:9'), ('examples/test1.c:13:9', 'examples/test1.c:3:5:END'), ('examples/test1.c:3:5', 'examples/test1.c:3:5:END'), ('examples/test1.c:5:9', 'examples/test1.c:5:9:END'), ('examples/test1.c:9:9', 'examples/test1.c:9:9:END'), ('examples/test1.c:3:5:END', 'examples/test1.c:3:5') }

assert( 10 == len(cfg))

graph_edges = []

for e in cfg.edges():
    graph_edges.append((str(e[0].coord),str(e[1].coord)))
    #print(str(e[0].coord)+"->"+str(e[1].coord))

#print(set(graph_edges).symmetric_difference(test_edges))
#print(len(graph_edges))

assert( len(graph_edges) == len(test_edges) )
assert( set(graph_edges) == test_edges )

paths = list(nx.all_simple_paths(cfg, start_node, exit_node))

#for path in paths:
#    for inst in path:
#        print(inst.coord)
#    print("")

assert( 5 == len(paths))
