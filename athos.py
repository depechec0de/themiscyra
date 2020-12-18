import copy
from pycparser import c_ast
import networkx as nx
from pycparser import c_parser, c_ast, parse_file, c_generator

import semantic_lib
from cast_lib import *
from c99theory import *
import cfg

class CompHO():
    def __init__(self, init_ast, rounds, jump_map, config):
        self.init_ast = init_ast
        self.rounds = rounds
        self.jump_map = jump_map

        for r in self.rounds:
            round_jumps = jump_map[r.label]
            r.add_jumps(round_jumps)

            chain_ifs(r.send_ast)
            chain_ifs(r.update_ast)

            r.send_ast = add_jump_guard(r.send_ast, config['phase'], config['round'], r.label)
            r.update_ast = add_jump_guard(r.update_ast, config['phase'], config['round'], r.label)

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

    def __init__(self, label, code_ast, ghost_variables, config, theory, jump_map):

        self.label = label
        self.jump_map = jump_map

        phase_var = config['phase']
        round_var = config['round']
        mbox_var = config['mbox']
        labels = config['labels']

        theory.add_var_predicate(round_var, theory.evaluate_variable(round_var) == theory.evaluate_variable(label))

        # Remove all code from other rounds and keep If structure
        round_slice(code_ast, round_var, label, ghost_variables)

        # Clean all async variables
        #filter_nodes(code_ast, lambda n, rv=round_var : is_var_assignment_to_value(n, rv, label))
        filter_nodes(code_ast, lambda n, mb=mbox_var : is_var_assignment(n, mb))
        filter_nodes(code_ast, lambda n, pv=phase_var : is_var_increment(n, pv))
        filter_nodes(code_ast, lambda n : type(n) == c_ast.Continue)

        # Compute SEND
        self.send_ast = copy.deepcopy(code_ast)
        filter_nodes(self.send_ast, lambda n : type(n) != c_ast.If and type(n) != c_ast.Compound and not is_funccall_with_name(n, 'send'))
        remove_empty_ifs(self.send_ast)
        # dead code elimination, phase unfold could end with several initial states that confuse the procedure
        filter_nodes(self.send_ast, lambda n : type(n) == c_ast.If and theory.is_unsat(theory.evaluate_ast(n.cond)))
        
        # Compute UPDATE
        self.update_ast = copy.deepcopy(code_ast)
        filter_nodes(self.update_ast, lambda n : is_funccall_with_name(n, 'send'))
        remove_empty_ifs(self.update_ast)
        # dead code elimination, phase unfold could end with several initial states that confuse the procedure
        filter_nodes(self.update_ast, lambda n : type(n) == c_ast.If and theory.is_unsat(theory.evaluate_ast(n.cond)))

        # Look for jumps
        parse_jumps(self.jump_map, self.update_ast, label, config)

    def get_jumps(self):
        return self.jumps

    def add_jumps(self, jump_map : Dict[str, c_ast.Node]):

        for ghost_var, code in jump_map.items():
            #print(ghost_var)
            ghost_var_ast = c_ast.ID(ghost_var)
            self.update_ast.block_items.append(c_ast.If(ghost_var_ast, code, None))
            #add_code_inside_matching_if(self.update_ast, ghost_var_ast, code)

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
    
    ghost_variables = create_ghost_variables(main_ast)
    map_dfs(main_ast, add_ghost_variables, [ghost_variables])
    map_dfs(main_ast, prune_after_phase_increment, [phase_var, round_var])
    filter_nodes(main_ast, lambda n : type(n) == c_ast.Break)
    # generator = c_generator.CGenerator()
    # print(generator.visit(main_ast))
    theory = C99Theory(async_ast)

    filter_nodes(main_ast, lambda n : is_var_declaration(n))
    init_ast = get_init_code(copy.deepcopy(main_ast), config)

    rounds = []

    jump_map = dict()

    for l in labels:
        jump_map[l] = dict()

    for label in labels:
        round_ast = copy.deepcopy(main_ast)
        sr = SyncRound(label, round_ast, ghost_variables, config, theory, jump_map)

        rounds.append(sr)

    compho = CompHO(init_ast, rounds, jump_map, config)

    return compho

def get_init_code(node : c_ast.Compound, config):
    result = node
    filter_nodes(result, lambda n : type(n) != c_ast.Assignment)
    filter_nodes(result, lambda n, mb=config['mbox'] : is_var_assignment(n, mb))
    filter_nodes(result, lambda n, rv=config['round'] : is_var_assignment(n, rv))

    return result

def add_jump_guard(ast_to_guard, phase_var, round_var, label):

    guarded_ast = c_ast.If( c_ast.BinaryOp('&&',
                        c_ast.BinaryOp('==',c_ast.ID(phase_var), c_ast.ID('PHASE')),
                        c_ast.BinaryOp('==',c_ast.ID(round_var), c_ast.ID(label))), 
                    ast_to_guard, None)

    return c_ast.Compound([guarded_ast])
