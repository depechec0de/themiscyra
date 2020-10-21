import copy
import itertools as it

import networkx as nx
import matplotlib.pyplot as plt

import cast_lib
from pycparser import c_parser, c_ast, parse_file, c_generator

class ControlFlowGraph(nx.DiGraph):
    """
    Placeholders AST nodes for delimitating the scope of c_ast.While and 
    c_ast.If in the CFG
    """
    class EntryNode(c_ast.EmptyStatement):
        def __init__(self, coord=None):
            super().__init__(coord)

    class ExitNode(c_ast.EmptyStatement):
        def __init__(self, coord=None):
            super().__init__(coord)

    def __init__(self, ast=None, data=None):
        super().__init__(data)

        if ast is not None:
            entrynode, exitnode = ast_to_cfg(self, ast)

            self.entry = entrynode
            self.exit = exitnode 

    def get_subgraph_between_nodes(self, start, end):
        """ Return the induced graph of the nodes in all paths from start to 
        end.
        """
        nodes = set()
        nodes.add(start)

        to_visit = set()
        to_visit.add(start)

        while len(to_visit) > 0:
            current_visit = copy.copy(to_visit)
            for tv in current_visit:
                to_visit.remove(tv)
                if tv is not end:
                    for s in self.successors(tv):
                        to_visit.add(s)
                        nodes.add(s)

        nodes.add(end)

        return self.subgraph(nodes) 
    
    def insert_graph(self, place, graph):
        """
        This method insert `graph` after `place`, connecting `place` to the 
        first node of `graph`.

        Parameters
        ----------
        graph : ControlFlowGraph()
        place : pycparser.c_ast.Node
        """
        if len(graph)>0:
            
            # Create and insert the graph
            graph_copy = copy.deepcopy(graph)
            augmented_graph = nx.union(self, graph_copy)

            self.update(augmented_graph.edges(), augmented_graph.nodes())

            # Connect the new graph in place
            graph_copy_nodes_ordered = list(nx.topological_sort(graph_copy))
            first_node_graph = graph_copy_nodes_ordered[0]
            last_node_graph = graph_copy_nodes_ordered[-1]

            # Disconnect old predecessors to the insertion place
            old_predecessors = copy.copy(self.predecessors(place))
            old_successors = copy.copy(self.successors(place))

            for s in old_successors:
                self.remove_edge(place, s)

            self.add_edge(place, first_node_graph)  

    def draw(self):
        labels = dict(self.nodes())
        for k in labels.keys():
            labels[k] = str(self.nodes[k]["label"])

        nx.draw_networkx(self, labels=labels, pos=nx.planar_layout(self))
        plt.show()

    def print_cfg(self):
        for n in self.nodes():
            print("############")
            print(str(type(n))+" "+str(n.coord)+" "+str(hex(id(n))))
            print("successors")
            for s in list(self.successors(n)):
                print(str(type(s))+" "+str(s.coord)+" "+str(hex(id(s))))
            print("")

def ast_to_cfg(digraph, ast: c_ast.Node) -> (c_ast.Node, c_ast.Node):
    """Recursively compute the CFG from a AST. Given a AST node (can be any 
    complex structure) the function will return the first and last nodes of the
    CFG in a tuple and will modify `cfg` adding the corresponding nodes and 
    edges representing the final CFG.

    Parameters
    ----------
    digraph : networkx.DiGraph
    ast : pycparser.c_ast.Node to be translated into a CFG
    
    Returns
    -------
    A tuple with references to the first and last element of the CFG

    Notes
    -----
    Depending on the node type, we need to build a DiGraph and return its 
    starting/ending nodes.
    Nodes marqued with * in figures are adhoc nodes to have only one end in the
    graph.
    """
    typ = type(ast) 

    first = ControlFlowGraph.EntryNode()
    last = ControlFlowGraph.ExitNode()
    
    digraph.add_node(first, label="entry", type=str(type(ast)), coord=str(ast.coord))
    digraph.add_node(last, label="exit", type=str(type(ast)), coord=str(ast.coord))

    # A c_ast.If in CFG is:
    #              cfg(body.true)
    #         /                      \
    # if(cond)                       endif*
    #         \                      /
    #          ----------------------
    #
    # returns (if(c), endif)

    if typ == c_ast.If:
        
        if_start = c_ast.If(ast.cond, None, None, coord=ast.coord)
        digraph.add_node(if_start, label=cast_lib.ast_to_str(if_start))

        digraph.add_edge(first, if_start)

        true_branch_body_first, true_branch_body_last = ast_to_cfg(digraph, ast.iftrue)
        
        digraph.add_edges_from(it.product([if_start], digraph.successors(true_branch_body_first)))
        digraph.remove_node(true_branch_body_first)  

        digraph.add_edges_from(it.product(digraph.predecessors(true_branch_body_last), [last]))
        digraph.remove_node(true_branch_body_last)  

        if ast.iffalse is not None:
            false_branch_body_start, false_branch_body_last = ast_to_cfg(digraph, ast.iffalse)

            digraph.add_edges_from(it.product([if_start], digraph.successors(false_branch_body_start)))
            digraph.remove_node(false_branch_body_start)

            digraph.add_edges_from(it.product(digraph.predecessors(false_branch_body_last), [last]))
            digraph.remove_node(false_branch_body_last)
        else:
            digraph.add_edge(if_start, last)


    # A c_ast.While in CFG is:
    #           cfg(body)
    #          /         \
    # while(c)            endwhile* -->--+
    #       ^  \         /               |
    #       |   ---->----                |
    #       +----------------------------+
    #
    # returns (while(c), endwhile*)
    
    elif typ == c_ast.While:

        while_body_entry, while_body_exit = ast_to_cfg(digraph, ast.stmt)
        
        whilenode = c_ast.While(ast.cond, None, coord=ast.coord)
        digraph.add_node(whilenode, label=cast_lib.ast_to_str(whilenode))
        
        digraph.add_edge(first, whilenode)

        digraph.add_edges_from(it.product([whilenode], digraph.successors(while_body_entry)))
        digraph.add_edges_from(it.product(digraph.predecessors(while_body_exit), [last]))

        # In a while the last statement return to the while condition 
        digraph.add_edges_from(it.product(digraph.predecessors(while_body_exit), [whilenode]))
        
        digraph.remove_node(while_body_entry)
        digraph.remove_node(while_body_exit)


    # A c_ast.Compound in CFG is:
    #
    # cfg(block(1)) --> cfg(block(2)) --> ... --> cfg(block(n))
    #
    # return (cfg(block(1)).first, cfg(block(n)).last)

    elif typ == c_ast.Compound:

        items = ast.block_items

        if items is not None:

            first_node = items[0]
            
            first_node_entry, prev_node_exit = ast_to_cfg(digraph, first_node)

            digraph.add_edges_from(it.product([first], digraph.successors(first_node_entry)))
            digraph.add_edges_from(it.product(digraph.predecessors(first_node_entry),[first]))
            digraph.remove_node(first_node_entry)

            if len(items) > 1:
 
                for i in items[1:-1]:
                    i_node_entry, i_node_exit = ast_to_cfg(digraph, i)
                    
                    merge_nodes(digraph, prev_node_exit, i_node_entry)
                    
                    prev_node_exit = i_node_exit
                
                last_node = items[-1]

                last_node_entry, last_node_exit = ast_to_cfg(digraph, last_node)

                merge_nodes(digraph, prev_node_exit, last_node_entry)

            else:
                last_node = first_node
                last_node_exit = prev_node_exit

            digraph.add_edges_from(it.product([last],digraph.successors(last_node_exit)))
            digraph.add_edges_from(it.product(digraph.predecessors(last_node_exit),[last]))
            
            digraph.remove_node(last_node_exit)
            

        else:
            noopnode = c_ast.EmptyStatement(coord=ast.coord)
            digraph.add_node(noopnode, label=cast_lib.ast_to_str(noopnode))

            digraph.add_edge(first, noopnode)
            digraph.add_edge(noopnode, last)


    # A c_ast.Compound in CFG is:
    #
    # function.name --> cfg(function.body).first
    #
    # return (function.name, cfg(function.body).last)

    elif typ == c_ast.FuncDef:

        (first_body, last_body) = ast_to_cfg(digraph, ast.body)
        
        funcdefnode = c_ast.FuncDef(ast.decl, ast.param_decls, None, coord=ast.coord)
        digraph.add_node(funcdefnode, label=cast_lib.ast_to_str(funcdefnode))

        digraph.add_edge(first, funcdefnode)
        digraph.add_edge(last_body, last)

        # we insert the FuncDef body CFG discarding its entry and exit nodes
        digraph.add_edges_from(it.product([funcdefnode], digraph.successors(first_body)))
        digraph.add_edges_from(it.product(digraph.predecessors(last_body), [last]))
        
        digraph.remove_node(first_body)
        digraph.remove_node(last_body)

    else:
        digraph.add_node(ast, label=cast_lib.ast_to_str(ast))

        digraph.add_edge(first, ast)
        digraph.add_edge(ast, last)


    return first, last   



def merge_nodes(digraph, first_node, next_node):
    digraph.add_edges_from(it.product(digraph.predecessors(first_node), digraph.successors(next_node)))
    digraph.remove_node(first_node)   
    digraph.remove_node(next_node) 

def cfg_path_to_ast(cfg):
    """Generates a AST from a CFG path (No FileAST support, it handles 
    FuncDecl, If, While and no compound objects).

    Parameters
    ----------
    cfg : ControlFlowGraph
    """
    current_compound = c_ast.Compound([])
    ast = current_compound
    previous_compound = None

    nodes = list(nx.topological_sort(cfg))

    for n in nodes:

        if type(n) in {c_ast.FuncDef, c_ast.While, c_ast.If}:

            previous_compound = current_compound
            current_compound = c_ast.Compound([])

            if type(n) == c_ast.FuncDef:
                inner_ast = c_ast.FuncDef(n.decl, n.param_decls, current_compound)
            elif type(n) == c_ast.While:
                inner_ast = c_ast.While(n.cond, current_compound)
            elif type(n) == c_ast.If:
                inner_ast = c_ast.If(n.cond, current_compound, None)  

            previous_compound.block_items.append(inner_ast)

        elif type(n) != ControlFlowGraph.ExitNode:
            
            current_compound.block_items.append(n)

    return ast 

def get_if_path(path):
    nodes = [node for node in list(nx.topological_sort(path)) 
            if type(node)==c_ast.If]
    
    new_path = ControlFlowGraph()
    nx.add_path(new_path, nodes)

    return new_path