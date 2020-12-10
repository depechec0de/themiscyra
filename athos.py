import copy
from pycparser import c_ast
import networkx as nx
from pycparser import c_parser, c_ast, parse_file, c_generator

import semantic_lib
from cast_lib import *
import cfg

class CompHO():
    def __init__(self, init_ast, rounds):
        self.init_ast = init_ast
        self.rounds = rounds

    def __repr__(self):
        result = "INIT()\n"

        generator = c_generator.CGenerator()
        code = generator.visit(self.init_ast)
        result += code + "\n"

        for syncround in self.rounds:
            result += str(syncround)
            result += "\n"

        return result

class SyncRound():

    def __init__(self, label, code_ast, ghost_variables, config):

        self.label = label

        phase_var = config['phase']
        round_var = config['round']
        mbox_var = config['mbox']
        labels = config['labels']

        # Remove all code from other rounds and keep If structure
        start_round_predicate = lambda n, se, es, rv=round_var, l=label : round_start_predicate(n, se, es, rv, l)
        end_round_predicate = lambda n, se, es, rv=round_var, l=label : round_end_predicate(n, se, es, rv, l)
        delete_predicate_label = lambda n, se, es, rv=round_var, l=label: round_slice_delete_predicate(n, se, es, rv, l)

        ast_slice(code_ast, start_round_predicate, end_round_predicate, delete_predicate_label)

        # Replace previous If predicates with ghost variables
        replace_context_with_ghost_vars(code_ast, round_var, label, ghost_variables)

        result_compound = code_ast

        # Clean all async variables
        #filter_nodes(result_compound, lambda n, rv=round_var : is_var_assignment(n, rv))
        filter_nodes(result_compound, lambda n, mb=mbox_var : is_var_assignment(n, mb))
        filter_nodes(result_compound, lambda n, pv=phase_var : is_var_increment(n, pv))
        filter_nodes(result_compound, lambda n : type(n) == c_ast.Continue)

        # Compute SEND
        self.send_ast = copy.deepcopy(result_compound)
        filter_nodes(self.send_ast, lambda n : type(n) != c_ast.If and type(n) != c_ast.Compound and not is_funccall_with_name(n, 'send'))
        remove_empty_ifs(self.send_ast)
        # unify ifs to conserve upon's mutual exclusion
        chain_ifs(self.send_ast)
        self.send_ast = add_jump_guard(self.send_ast, phase_var, round_var)
        
        # Compute UPDATE
        self.update_ast = copy.deepcopy(result_compound)
        filter_nodes(self.update_ast, lambda n : is_funccall_with_name(n, 'send'))
        remove_empty_ifs(self.update_ast)
        # unify ifs to conserve upon's mutual exclusion
        chain_ifs(self.update_ast)
        self.update_ast = add_jump_guard(self.update_ast, phase_var, round_var)
    
    def __repr__(self):
        generator = c_generator.CGenerator()

        send_code = generator.visit(self.send_ast)
        send_code = send_code.replace('\n', '\n\t')
        send_code = "\tSEND(PHASE, ROUND)\n\t" + send_code

        update_code = generator.visit(self.update_ast)
        update_code = update_code.replace('\n', '\n\t')
        update_code = "\tUPDATE(MBOX, PHASE, ROUND)\n\t" + update_code
        
        return  self.label+"{\n\n" + send_code + "\n" + update_code + "\n" + "}\n"


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

    # codecfg = cfg.PhaseUnfoldGraph(main_ast)
    init_ast = get_init_code(copy.deepcopy(main_ast), config)

    rounds = []

    for label in labels:
        round_ast = copy.deepcopy(main_ast)
        sr = SyncRound(label, round_ast, ghost_variables, config)
        rounds.append(sr)

    compho = CompHO(init_ast, rounds)

    return compho

def get_init_code(node : c_ast.Compound, config):
    result = node
    filter_nodes(result, lambda n : type(n) != c_ast.Assignment)
    filter_nodes(result, lambda n, mb=config['mbox'] : is_var_assignment(n, mb))
    filter_nodes(result, lambda n, rv=config['round'] : is_var_assignment(n, rv))

    return result

def add_jump_guard(ast_to_guard, phase_var, round_var):

    guarded_ast = c_ast.If( c_ast.BinaryOp('&&',
                        c_ast.BinaryOp('==',c_ast.ID(phase_var), c_ast.ID('PHASE')),
                        c_ast.BinaryOp('==',c_ast.ID(round_var), c_ast.ID('ROUND'))), 
                    ast_to_guard, None)

    return c_ast.Compound([guarded_ast])
