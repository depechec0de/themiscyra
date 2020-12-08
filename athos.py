import copy
from pycparser import c_ast
import networkx as nx
from pycparser import c_parser, c_ast, parse_file, c_generator

import semantic_lib
from cast_lib import *
import cfg

class SyncRound():

    def __init__(self, label, pug : cfg.PhaseUnfoldGraph, ghost_variables, config):

        phase_var = config['phase']
        round_var = config['round']
        mbox_var = config['mbox']

        round_forest = compute_round_forest(pug, label, round_var)

        block_items = []
        
        for round_tree in round_forest:
            nodes = list(nx.topological_sort(round_tree))

            first_node = nodes[0]
            round_assig = [n for n in nodes if is_var_assignment_to_value(n.astnode, round_var, label)]

            g_block_items = []
            round_ast = c_ast.Compound(g_block_items)
            cfg.digraph_to_ast(round_tree, first_node, g_block_items)

            context_round_ast = self.add_ast_context(round_ast, pug, round_assig[0], ghost_variables)

            if type(context_round_ast) == c_ast.Compound:
                block_items.extend(context_round_ast.block_items)
            else:
                block_items.append(context_round_ast)

        result_compound = c_ast.Compound(block_items)

        # cleaning
        filter_nodes(result_compound, lambda n, rv=round_var : is_var_assignment(n, rv))
        filter_nodes(result_compound, lambda n, mb=mbox_var : is_var_assignment(n, mb))
        filter_nodes(result_compound, lambda n, pv=phase_var : is_var_increment(n, pv))
        filter_nodes(result_compound, lambda n : type(n) == c_ast.Continue)

        self.send_ast = copy.deepcopy(result_compound)
        filter_nodes(self.send_ast, lambda n : type(n) != c_ast.If and type(n) != c_ast.Compound and not is_funccall_with_name(n, 'send'))
        remove_empty_ifs(self.send_ast)
        # unify ifs to conserve upon's mutual exclusion
        chain_ifs(self.send_ast)

        self.update_ast = copy.deepcopy(result_compound)
        filter_nodes(self.update_ast, lambda n : is_funccall_with_name(n, 'send'))
        remove_empty_ifs(self.update_ast)
        # unify ifs to conserve upon's mutual exclusion
        chain_ifs(self.update_ast)
    
    def add_ast_context(self, astnode, codecfg, round_init, ghost_variables):

        paths_to_init = nx.all_simple_paths(codecfg, codecfg.entry, round_init)

        path = list(paths_to_init)[0]
        context_path = [ghost_variables[str(n.astnode.cond.coord)] for n in path if type(n) == cfg.ControlFlowGraph.IfNode]

        if len(context_path)>0:
            return c_ast.If(unify_if_predicates(context_path), iftrue=astnode, iffalse=None)
        else:
            return astnode
    
    def __repr__(self):
        generator = c_generator.CGenerator()

        return  "SEND(PHASE, ROUND): " + "\n" + generator.visit(self.send_ast) + "\n" + \
                "UPDATE(MBOX, PHASE, ROUND): " + "\n" + generator.visit(self.update_ast)


def async_to_sync(async_ast: c_ast.Node, config):

    phase_var = config['phase']
    round_var = config['round']
    mbox_var = config['mbox']
    labels = config['labels']

    main_ast = find_funcdef_node(async_ast,'main')
    map_dfs(main_ast, replace_while_with_body, [])
    filter_nodes(main_ast, lambda n : is_var_declaration(n))

    ghost_variables = create_ghost_variables(main_ast)
    map_dfs(main_ast, add_ghost_variables, [ghost_variables])
    map_dfs(main_ast, prune_after_phase_increment, [phase_var])
    filter_nodes(main_ast, lambda n : type(n) == c_ast.Break)

    #generator = c_generator.CGenerator()
    # code = generator.visit(main_ast)
    # print(code)

    codecfg = cfg.PhaseUnfoldGraph(main_ast)

    compho = {}

    for label in labels:
        sr = SyncRound(label, codecfg, ghost_variables, config)
        compho[label] = sr

    return compho

def compute_round_forest(pug : cfg.PhaseUnfoldGraph, label, round_var):
    """
    Given a PUG `pug` and a round `label` we return a forest where each tree is a slice
    of `pug` starting with a round assignment to `label` and every leaf ends with a 
    round or phase change.
    """

    # find all CFG nodes where round `label` starts
    round_init_nodes = [n for n in pug.nodes() if is_var_assignment_to_value(n.astnode, round_var, label)]
    continue_nodes = [n for n in pug.nodes() if type(n.astnode) == c_ast.Continue]
    
    # find all CFG's subtree of round `label`
    round_graphs = []

    for init in round_init_nodes:
        
        round_paths = []
        
        for continue_node in continue_nodes:
            paths_to_continue = nx.all_simple_paths(pug, init, continue_node)

            for p in paths_to_continue:
                round_paths.append(p)

        round_nodes = []

        for p in round_paths:
            for n in p:
                if is_var_assignment(n.astnode, round_var) and get_assig_val(n.astnode) != label:
                    break

                round_nodes.append(n)
        
        subcfg = pug.subgraph(round_nodes)
        sg = nx.DiGraph(subcfg.edges())

        round_graphs.append(sg)

    return round_graphs