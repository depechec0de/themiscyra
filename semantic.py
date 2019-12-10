import copy
import networkx as nx
import matplotlib.pyplot as plt

from pycparser import c_parser, c_ast, parse_file, c_generator

class Condition(object):
    def __init__(self, predicate, round, iteration):
        self.predicate = predicate
        self.round = round
        self.iteration = iteration

    def __str__(self):
        return self.predicate + " @ "+str(self.round)+" [Iteration "+str(self.iteration)+"]"

    def __repr__(self):
        return str(self)

    def __hash__(self):
        return hash(str(self))

    def __eq__(self, other):
        return (
            self.__class__ == other.__class__ and
            self.predicate == other.predicate and
            self.round == other.round and
            self.iteration == other.iteration
        )

class Context(object):
    def __init__(self, other_context=None):
        if other_context is None:
            self.conditions = set()
        else:
            self.conditions = copy.deepcopy(other_context.conditions)

    def __iter__(self):
        return iter(self.conditions)
    
    def __str__(self):
        return str(self.conditions)

    def __repr__(self):
        return str(self)

    def __hash__(self):
        return hash(str(self))

    def __eq__(self, other):
        return (
            self.__class__ == other.__class__ and
            self.conditions == other.conditions
        )
    def size(self):
        return len(self.conditions)

    def add_condition(self, cond):
        self.conditions.add(cond)


class AnotatedInstruction(object):
    def __init__(self, text, context, coord):
        self.text = text
        self.context = context
        self.coord = str(coord)

    def __str__(self):
        return str(self.coord) + " " + self.text

    def __repr__(self):
        return str(self)

    def __hash__(self):
        return hash(str(self))

    def __eq__(self, other):
        return (
            self.__class__ == other.__class__ and
            self.coord == other.coord and
            self.context == other.context and
            self.text == other.text
        )

"""
Placeholders AST nodes for delimitating the scope of "while"s and "if"s in the CFG
"""
class WhileEnd(c_ast.EmptyStatement):
    def __init__(self, coord=None):
        super().__init__(coord)

class IfEnd(c_ast.EmptyStatement):
    def __init__(self, coord=None):
        super().__init__(coord)

class ControlFlowGraph(nx.DiGraph):

    def __init__(self, data=None):
        super().__init__(data)
        self.start_node = None

        self.generator = c_generator.CGenerator()

    """
    Recursively compute the CFG from a AST. Given a AST node (can be any complex structure) the function will return 
    the first and last nodes of the CFG in a tuple and will modify de "cfg" parameter adding the corresponding nodes 
    and edges representing the final CFG.

    :param node: AST node to be translated into a CFG
    :param cfg: A ControlFlowGraph to be completed with nodes and edges
    :param arborescence: If it is set to False, the method add edges from the end of a While statement to condition, generating loops in the CFG. We also add an edge from the While condition to the end of the loop, breaking arborescence as defined in https://networkx.github.io/documentation/stable/reference/algorithms/tree.html#recognition-tests
    :type node: pycparser.c_ast.Node
    :type cfg: ControlFlowGraph
    :return: A tuple with references to the first and last element of the CFG
    :rtype: (first, last)
    """
    def from_ast(self, node: c_ast.Node, arborescence=False) -> (c_ast.Node, c_ast.Node):

        if self.start_node is None:
            self.start_node = node

        # Depending on the node type, we need to build a DiGraph and return its starting/ending nodes
        # We call from_ast = cfg in the comments
        # Nodes marqued with * are adhoc nodes to have only one end in the graph

        typ = type(node) 

        # A c_ast.If in CFG is:
        #        cfg(body.true)
        #       /               \
        # if(c)                  endif*
        #       \               /
        #        cfg(body.false)
        #
        # returns (if(c), endif)

        if typ == c_ast.If:

            self.add_node(node)

            last = IfEnd(coord=str(node.coord)+":END")
            self.add_node(last)
            
            (first_true, last_true) = self.from_ast(node.iftrue, arborescence)

            self.add_edge(node, first_true)
            self.add_edge(last_true, last)

            if node.iffalse is not None:
                (first_false, last_false) = self.from_ast(node.iffalse, arborescence)
                self.add_edge(node, first_false)
                self.add_edge(last_false, last)
            else:
                self.add_edge(node, last)

            return (node, last)

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

            last = WhileEnd(coord=str(node.coord)+":END")
            self.add_node(node, WhileEnd=last)
            self.add_node(last, While=node)

            (body_first, body_last) = self.from_ast(node.stmt, arborescence)

            self.add_edge(node, body_first)

            if not arborescence:
                self.add_edge(node, last)

            self.add_edge(body_last, last)

            if not arborescence:
                self.add_edge(last, node)
            
            return (node, last)

        # A c_ast.Compound in CFG is:
        #
        # cfg(block(1)) --> cfg(block(2)) --> ... --> cfg(block(n))
        #
        # return (cfg(block(1)).first, cfg(block(n)).last)

        elif typ == c_ast.Compound:
            items = node.block_items

            (first, last) = (None, None)

            old_i_last = None
            for i in items:
                (i_first, i_last) = self.from_ast(i, arborescence)

                if old_i_last is not None:
                    self.add_edge(old_i_last, i_first)

                if first is None:
                    first = i_first

                old_i_last = i_last
            
            last = old_i_last
            
            return (first, last)

        # A c_ast.Compound in CFG is:
        #
        # function.name --> cfg(function.body).first
        #
        # return (function.name, cfg(function.body).last)

        elif typ == c_ast.FuncDef:

            self.add_node(node)

            (first, last) = self.from_ast(node.body, arborescence)
            self.add_edge(node, first)

            return (node, last)
        else:
            self.add_node(node)
            return (node, node)   

    """
    For simplicity it requires the CFG to be acyclic (DAG)
    """
    def unfold(self, times: int):

        if not nx.is_directed_acyclic_graph(self):
            raise AssertionError('The unfolded CFG must be a DAG (e.g., calling from_ast method with arborescence=False)')

        # We search for all the continues in the CFG
        continue_nodes = [n for n in self.nodes() if type(n)==c_ast.Continue]

        # For every continue "c" we search the closer WhileEnd, the associated While is the scope of "c"
        continues_with_scope = self._get_while_scope(continue_nodes)
    
        continues_with_graph = []
        for (c, wend) in continues_with_scope:
            wstart = self.nodes[wend]['While']
            while_graph = self._get_subgraph(wstart, wend)
            continues_with_graph.append((c, while_graph))
        
        for i in range(0,times):
            for (c, while_graph) in continues_with_graph:
                self._insert_graph(c, while_graph)

    def _get_while_scope(self, nodes):
        # We search for all whiles in the CFG
        while_ends = [n for n in self.nodes() if type(n)==WhileEnd]
        
        while_scopes = []
        for n in nodes:
            shortest_path = None
            
            for wend in while_ends:
                path = nx.shortest_path(self, source=n, target=wend)
                
                if shortest_path is None or len(path) < len(shortest_path):
                    shortest_path = path

            # We map the continue with its corresponding WhileEnd
            while_scopes.append((n, shortest_path[-1]))

        return while_scopes   

    """
    Return the induced graph of the nodes in all paths from start to end
    """
    def _get_subgraph(self, start, end):
        nodes = set()

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

        nodes.remove(end)

        return self.subgraph(nodes) 
    
    """
    This method insert "graph" (a CFG) after "place" (a node), connecting "place" 
    to the first node of "graph"
    """
    def _insert_graph(self, place, graph):
        
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
            labels[k] = str(k.__class__.__name__)+" "+str(k.coord).split(":")[1]

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
            