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
    class Node():
        def __str__(self):
            return self.label

        def __repr__(self):
                return self.__str__()

        def __init__(self, astnode=None):
            self.astnode = astnode
            self.update_label()

        def update_label(self):
            if self.astnode is not None:
                self.label = cast_lib.ast_to_str(self.astnode)

            if self.astnode.coord is not None:
                node_coords = str(self.astnode.coord).split(':')
                self.label = self.label + " @ "+node_coords[1]

    class IfNode(Node):
        def __init__(self, astnode=None):
            super().__init__(astnode)

    # Artificial CFG node to know wich IfNode branch I traversed
    class AssertNode(Node):
        def __init__(self, astpred):
            super().__init__(astpred)

        def update_label(self):
            self.label = "Assert " + cast_lib.ast_to_str(self.astnode)

    class ArtificialNode(Node):
        pass

    class EntryNode(ArtificialNode):
        def __init__(self):
            astnode = c_ast.EmptyStatement()
            super().__init__(astnode)
        
        def update_label(self):
            self.label = "entry"

    class ExitNode(ArtificialNode):
        def __init__(self):
            astnode = c_ast.EmptyStatement()
            super().__init__(astnode)

        def update_label(self):
            self.label = "exit"

    def __init__(self, ast, loop=True, iffalse=True):
        super().__init__()
        # If loop is true, we create an edge back from the end of the whiles 
        self.loop = loop
        # If iffalse is true, we create a negated AssertNode for the else conditions
        self.iffalse = iffalse
        entrynode, exitnode = self.ast_to_cfg(ast)

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
        labelsnodes = dict(self.nodes())
        for k in labelsnodes.keys():
            labelsnodes[k] = str(k)
        
        labelsedges = dict()
        for k in self.edges().keys():
            if "label" in self.edges[k]:
                labelsedges[k] = self.edges[k]["label"]

        #pos = nx.planar_layout(self)
        #pos = nx.circular_layout(self)
        pos = nx.spring_layout(self)

        nx.draw_networkx(self, labels=labelsnodes, pos=pos)
        nx.draw_networkx_edge_labels(self, edge_labels=labelsedges, pos=pos)

        plt.axis('off')
        plt.show()

    def paths(self):
        return nx.all_simple_paths(self, self.entry, self.exit)

    def add_node(self, node):
            super().add_node(node)

    def join_adjacents_and_merge(self, node, removed_node, **successor_data):
        """
        Removes `removed_node` and joins its adjacency into `node`.  

        Example
        -------
        {n0, ...} --->* removed_node --->* {m0, ...}
        {j0, ...} --->* node --->* {i0, ...}

        to

        {n0, ..., j0, ...} --->* node --->* {m0, ..., r0, ...} 
        """
        new_edges = []

        for predecessor in self.predecessors(removed_node):
            new_edges.append((predecessor, node, self.edges[predecessor, removed_node]))

        self.add_edges_from(new_edges)

        new_edges = []

        for succesor in self.successors(removed_node):
            new_edges.append((node, succesor, self.edges[removed_node, succesor]))

        self.add_edges_from(new_edges, **successor_data)

        self.remove_node(removed_node)

        # remove self loops
        if (node, node) in self.edges():
            self.remove_edge(node, node)

    def join_adjacents_and_remove(self, n1, n2):
        """
        Removes `n1` and `n2` but keeps connectivity of all paths between them (i.e. join).

        Example
        -------
        {n0, ...} --->* n1 --->* {m0, ...}
        {j0, ...} --->* n2 --->* {i0, ...}

        to

        {n0, ..., j0, ...} X {m0, ..., r0, ...}

        """

        new_edges = []

        for (u,v) in list(it.product(self.predecessors(n1), self.successors(n2))):
            new_edges.append((u, v, self.edges[u, n1]))

        self.add_edges_from(new_edges)

        self.remove_node(n1)   
        self.remove_node(n2)

    def ast_to_cfg(self, ast: c_ast.Node) -> (c_ast.Node, c_ast.Node):
        """Recursively compute the CFG from a AST. Given a AST node (can be any 
        complex structure) the function will return the first and last nodes of the
        CFG in a tuple and will modify `cfg` adding the corresponding nodes and 
        edges representing the final CFG.

        Parameters
        ----------
        ast : pycparser.c_ast.Node to be translated into a CFG
        
        Returns
        -------
        A tuple with references to the first and last element of the CFG
        """
        typ = type(ast) 

        entrynode = ControlFlowGraph.EntryNode()
        exitnode = ControlFlowGraph.ExitNode()
        
        self.add_node(entrynode)
        self.add_node(exitnode)

        # A c_ast.If in CFG is:
        #              cfg(body.true)
        #         /                      \
        # if(cond)                       endif*
        #         \                      /
        #          ----------------------
        #
        # returns (if(c), endif)

        if typ == c_ast.If:
            
            astif = c_ast.If(ast.cond, None, None, coord=ast.coord)
            if_start = ControlFlowGraph.IfNode(astif)

            self.add_node(if_start)

            self.add_edge(entrynode, if_start)

            true_branch_body_entry, true_branch_body_exit = self.ast_to_cfg(ast.iftrue)

            asserttrue = ControlFlowGraph.AssertNode(ast.cond)
            self.add_node(asserttrue)
            self.add_edge(if_start, asserttrue)
            self.add_edge(asserttrue, true_branch_body_entry)
            
            self.join_adjacents_and_merge(asserttrue, removed_node=true_branch_body_entry) 
            self.join_adjacents_and_merge(exitnode, removed_node=true_branch_body_exit)  

            if ast.iffalse is not None:
                false_branch_body_start, false_branch_body_last = self.ast_to_cfg(ast.iffalse)

                if self.iffalse:
                    assertfalse = ControlFlowGraph.AssertNode(c_ast.UnaryOp("!", ast.cond))
                    self.add_node(assertfalse)
                    self.add_edge(if_start, assertfalse)
                    self.add_edge(assertfalse, false_branch_body_start)
                else:
                    self.add_edge(if_start, false_branch_body_start)

                self.join_adjacents_and_merge(assertfalse, removed_node=false_branch_body_start) 
                self.join_adjacents_and_merge(exitnode, removed_node=false_branch_body_last) 
            else:
                if self.iffalse:
                    assertfalse = ControlFlowGraph.AssertNode(c_ast.UnaryOp("!", ast.cond))
                    self.add_node(assertfalse)
                    self.add_edge(if_start, assertfalse)
                    self.add_edge(assertfalse, exitnode)
                else:
                    self.add_edge(if_start, exitnode)

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

            while_body_entry, while_body_exit = self.ast_to_cfg(ast.stmt)
            
            astwhile = c_ast.While(ast.cond, None, coord=ast.coord)
            whilenode = ControlFlowGraph.Node(astwhile)
            self.add_node(whilenode)
            
            self.add_edge(whilenode, exitnode)
            self.add_edge(entrynode, whilenode)

            asserttrue = ControlFlowGraph.AssertNode(ast.cond)
            self.add_node(asserttrue)
            self.add_edge(whilenode, asserttrue)
            self.add_edge(asserttrue, while_body_entry)

            self.join_adjacents_and_merge(asserttrue, removed_node=while_body_entry) 
            # In a while the last statement return to the while condition
            if self.loop:
                self.join_adjacents_and_merge(whilenode, removed_node=while_body_exit) 
            else:
                self.join_adjacents_and_merge(exitnode, removed_node=while_body_exit)


        # A c_ast.Compound in CFG is:
        #
        # cfg(block(1)) --> cfg(block(2)) --> ... --> cfg(block(n))
        #
        # return (cfg(block(1)).first, cfg(block(n)).last)

        elif typ == c_ast.Compound:

            items = ast.block_items

            if items is not None:

                first_node = items[0]
                
                first_node_entry, prev_node_exit = self.ast_to_cfg(first_node)

                self.join_adjacents_and_merge(entrynode, removed_node=first_node_entry) 

                if len(items) > 1:
    
                    for i in items[1:-1]:
                        i_node_entry, i_node_exit = self.ast_to_cfg(i)
                        
                        self.join_adjacents_and_remove(prev_node_exit, i_node_entry)
                        
                        prev_node_exit = i_node_exit
                    
                    last_node = items[-1]

                    last_node_entry, last_node_exit = self.ast_to_cfg(last_node)

                    self.join_adjacents_and_remove(prev_node_exit, last_node_entry)

                else:
                    last_node = first_node
                    last_node_exit = prev_node_exit

                self.join_adjacents_and_merge(exitnode, removed_node=last_node_exit) 
                

            else:
                noopnode = ControlFlowGraph.Node(c_ast.EmptyStatement(coord=ast.coord))
                self.add_node(noopnode)

                self.add_edge(entrynode, noopnode)
                self.add_edge(noopnode, exitnode)


        # A c_ast.Compound in CFG is:
        #
        # function.name --> cfg(function.body).first
        #
        # return (function.name, cfg(function.body).last)

        elif typ == c_ast.FuncDef:

            (first_body, last_body) = self.ast_to_cfg(ast.body)

            astfuncdef = c_ast.FuncDef(ast.decl, ast.param_decls, None, coord=ast.coord)
            funcdefnode = ControlFlowGraph.Node(astfuncdef)

            self.add_node(funcdefnode)

            self.add_edge(entrynode, funcdefnode)
            self.add_edge(last_body, exitnode)

            # we insert the FuncDef body CFG discarding its entry and exit nodes
            self.join_adjacents_and_merge(funcdefnode, removed_node=first_body) 
            self.join_adjacents_and_merge(exitnode, removed_node=last_body)

        else:
            basicnode = ControlFlowGraph.Node(ast)
            self.add_node(basicnode)

            self.add_edge(entrynode, basicnode)
            self.add_edge(basicnode, exitnode)


        return entrynode, exitnode   

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