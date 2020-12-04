import copy
from pycparser import c_ast
import networkx as nx
from pycparser import c_parser, c_ast, parse_file, c_generator

import semantic_lib
from cast_lib import *
import cfg

class SyncRound():

    def __init__(self, label, codecfg, ghost_variables, config):

        phase_var = config['phase']
        round_var = config['round']
        mbox_var = config['mbox']

        round_cfgs = self.round_subgraphs(codecfg, label, round_var)

        block_items = []
        
        for g in round_cfgs:
            nodes = list(nx.topological_sort(g))

            first_node = nodes[0]
            round_assig = [n for n in nodes if is_var_assignment_to_value(n.astnode, round_var, label)]

            g_block_items = []
            round_ast = c_ast.Compound(g_block_items)
            cfg.digraph_to_ast(g, first_node, g_block_items)

            context_round_ast = self.add_ast_context(round_ast, codecfg, round_assig[0], ghost_variables)

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

        self.update_ast = copy.deepcopy(result_compound)
        filter_nodes(self.update_ast, lambda n : is_funccall_with_name(n, 'send'))
        remove_empty_ifs(self.update_ast)
    
    def round_subgraphs(self, codecfg, label, round_var):

        # find all CFG nodes where round `label` starts
        round_init_nodes = [n for n in codecfg.nodes() if is_var_assignment_to_value(n.astnode, round_var, label)]
        
        # find all CFG's subtree of round `label`
        round_graphs = []

        for init in round_init_nodes:

            round_nodes = []

            paths_starting_from_round = semantic_lib.phase_paths(codecfg, init)
            
            for p in paths_starting_from_round:
                collect = True
                for n in p:
                    if is_var_assignment(n.astnode, round_var) and get_assig_val(n.astnode) != label:
                        collect = False
                    if collect:
                        round_nodes.append(n)
            
            subcfg = codecfg.subgraph(round_nodes)
            sg = nx.DiGraph(subcfg.edges())

            round_graphs.append(sg)

        return round_graphs

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

        return  "SEND: " + "\n" + generator.visit(self.send_ast) + "\n" + \
                "UPDATE: " + "\n" + generator.visit(self.update_ast)


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