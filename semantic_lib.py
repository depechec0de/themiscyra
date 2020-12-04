from z3 import *
from typing import Type, List, Set, Dict, Tuple, Optional
from pycparser import c_parser, c_ast, parse_file, c_generator
import networkx as nx

import cast_lib
import cfg
from c99theory import *

def dead_code_elimination(codeast : c_ast.FileAST, config):

    # Syntactic tree prune, everything after a phase increment is removed
    main_while = cast_lib.find_while_node(codeast)

    if config is not None and hasattr(config, 'phase'):
        cast_lib.map_dfs(main_while, cast_lib.prune_after_phase_increment, [config['phase']])

    # Construct a theory using definitions and declarations
    theory = C99Theory(codeast)

    # Recursively explore the AST tree and cut the unfeasible branches
    cast_lib.map_dfs(codeast, prune_unsat_branches, [theory])


def prune_unsat_branches(node : c_ast.Node, theory : C99Theory): 
    
    if type(node) == c_ast.Compound:
        to_delete = []
        
        for i in node.block_items:   
            if type(i) == c_ast.If:
                cond_predicate = theory.evaluate_ast(i.cond)
                
                if theory.is_sat(cond_predicate):
                    new_context = copy.deepcopy(theory)
                    # uncomment to incorporate the if predicate to the solver
                    #new_context.handle_if(i)
                    # start a new dfs with the augmented context
                    cast_lib.map_dfs(i.iftrue, prune_unsat_branches, [new_context])
                else:
                    # delete this branch
                    to_delete.append(i)
            elif type(i) == c_ast.Assignment: 
                pred = theory.evaluate_ast(i)
                var_name = i.lvalue.name
                theory.add_var_predicate(var_name, pred)
            elif type(i) == c_ast.While:
                cast_lib.map_dfs(i.stmt, prune_unsat_branches, [theory])

        for i in to_delete:
            node.block_items.remove(i)

        # break dfs on this branch
        return False 

def phase_unfold(codeast : c_ast.Node, config):

    initial_state = C99Theory(codeast)

    initial_assignments = cast_lib.get_initial_assignments(codeast)

    phase_var = initial_state.get_var(config['phase'])
    predicate = phase_var > z3.IntVal(0)
    
    initial_state.add_var_predicate(config['phase'], predicate)

    for assignment in initial_assignments:
        if not cast_lib.is_var_assignment(assignment, config['phase']):
            predicate = initial_state.evaluate_ast(assignment)
            var_name = assignment.lvalue.name    
            initial_state.add_var_predicate(var_name, predicate)

    initial_states_changed = True
    initial_states = [initial_state]

    codeast_unfolded = codeast

    # unfold until we reach a fixpoint in the set of initial states
    while initial_states_changed:

        initial_states_changed = False
        final_states = []

        codeast_unfolded = copy.deepcopy(codeast)
        main_while = cast_lib.find_while_node(codeast_unfolded)
        while_body = main_while.stmt.block_items
        while_body_copy = copy.deepcopy(while_body)

        _phase_unfold(main_while.stmt, while_body_copy, initial_states, config['phase'], final_states)

        # if a new final state is not in initial_states we need to explore it
        for fstate in final_states:
            explored_state = False
            for istate in initial_states:
                if fstate.get_context() == istate.get_context():
                    explored_state = True

            if not explored_state:
                initial_states_changed = True
                initial_states.append(fstate)
            
    return codeast_unfolded

def _phase_unfold(compound : c_ast.Compound, while_body, initial_states, phase_var, final_states):

    to_delete = []

    upons = [n for n in compound if type(n) == c_ast.If]
    generator = c_generator.CGenerator()
    for upon in upons:

        sat_init_state = None

        for init in initial_states:
            cond_predicate = init.evaluate_ast(upon.cond)
            if init.is_sat(cond_predicate):
                sat_init_state = init
                break
 
        if sat_init_state is not None:

            new_context = copy.deepcopy(sat_init_state)
            path_end = False

            for n in upon.iftrue:
                if type(n) == c_ast.Assignment: 
                    pred = new_context.evaluate_ast(n)
                    var_name = n.lvalue.name
                    new_context.add_var_predicate(var_name, pred)
        
                if cast_lib.is_var_increment(n, phase_var):
                    path_end = True
            
            if not path_end:
                while_body_copy = copy.deepcopy(while_body)
                cast_lib.map_dfs(upon, cast_lib.insert_node_after_continue, [while_body_copy])
                _phase_unfold(upon.iftrue, while_body_copy, [new_context], phase_var, final_states)
            else:
                final_states.append(new_context)

        else:
            to_delete.append(upon)

    for upon in to_delete:
        compound.block_items.remove(upon)


class PhaseFormula():

    def __init__(self, theory : C99Theory, path : List[cfg.ControlFlowGraph.Node]):
        self.theory = theory
        self.formula = z3.Bool(False)
        self.path = copy.deepcopy(path)
        variable_rename = dict()
        variable_counter = dict()
        
        # We declare aux variables to keep the historial of assigments
        for n in self.path:
            if type(n.astnode) == c_ast.Assignment:

                # Rename variables with the last version in rvalue
                cast_lib.rename_variable(n.astnode.rvalue, variable_rename)

                var_basename = n.astnode.lvalue.name

                if var_basename not in variable_counter:
                    variable_counter[var_basename] = 0
                else:
                    variable_counter[var_basename] += 1

                var_version = variable_counter[var_basename]
                var_fullname = var_basename + '__' + str(var_version)
                variable_rename[var_basename] = var_fullname

                var_type = theory.get_variable_type(var_basename)

                if not theory.is_var_declared(var_fullname):
                    # We augment the theory with the new history variable
                    smt_var = theory.generate_smt_variable(var_fullname, var_type)
                    theory.declare_variable(var_fullname, smt_var)

                # Rename the variable with the history version and evaluate
                n.astnode.lvalue.name = var_fullname

            else:
                # Rename variables with the last version
                cast_lib.rename_variable(n.astnode, variable_rename)

        to_evaluate = {c_ast.FuncCall, c_ast.Assignment, c_ast.BinaryOp, c_ast.UnaryOp}

        predicates = []

        for n in self.path:
            
            # update the label
            n.update_label()

            if type(n) == cfg.ControlFlowGraph.AssertNode:
                predicate = theory.evaluate_ast(n.astnode)
                predicates.append(predicate)
                
            elif type(n) == cfg.ControlFlowGraph.Node and type(n.astnode) in to_evaluate:

                if type(n.astnode) == c_ast.Assignment: 
                    predicate = theory.evaluate_ast(n.astnode)
                elif type(n.astnode) == c_ast.FuncCall:
                    predicate = theory.evaluate_ast(n.astnode) == z3.Bool(True)
                else:
                    predicate = theory.evaluate_ast(n.astnode)

                predicates.append(predicate)

        self.formula = z3.And(predicates)

    def __repr__(self):
        return str(self.formula)

    def __eq__(self, other):
        if isinstance(other, PhaseFormula):
            if other.theory == self.theory:
                return self.theory.is_unsat(Not(other.formula == self.formula))
            else:
                raise SemanticError('Theories are different')

        raise SemanticError('other is not a PathFormula')

def phase_paths(code_cfg : cfg.ControlFlowGraph, init=None):

    if init is None:
        init = code_cfg.entry
        
    continue_nodes = [n for n in code_cfg.nodes() if type(n.astnode) == c_ast.Continue]
    paths = []
    
    for continue_node in continue_nodes:
        paths_to_continue = nx.all_simple_paths(code_cfg, init, continue_node)

        for p in paths_to_continue:
            paths.append(p)
        
    return paths

def prune_equivalent_paths(ast : c_ast.Node):

    theory = C99Theory(ast)

    code_ast = cast_lib.find_funcdef_node(ast, 'main')
    code_cfg = cfg.ControlFlowGraph(code_ast, loop=False)

    # collect the paths
    to_visit = phase_paths(code_cfg)

    # we split paths between mbox assignments and phase changes
    splitted_paths = []

    for p in to_visit:

        splitted_path = []
        chunk = []
    
        for n_index, node in enumerate(p):

            chunk.append(node)

            phase_incremented = cast_lib.is_var_increment(node.astnode, 'view') 
            phase_jump = cast_lib.is_var_assignment(node.astnode, 'view')
            path_end = type(node.astnode) == c_ast.Continue

            if (phase_incremented or phase_jump or path_end) and len(chunk)>0:
                # add context from previous chunk
                if len(splitted_path)>0: 
                    previous_chunk = splitted_path[-1]

                    context_chunk = []
                    # we look for all asserts from the last elemento to the first mbox assignment
                    for n_prev in previous_chunk[::-1]:
                        if cast_lib.is_var_assignment(n_prev.astnode, 'mbox'):
                            break

                        if type(n_prev) == cfg.ControlFlowGraph.AssertNode:
                            context_chunk.insert(0, n_prev)

                    context_chunk.extend(chunk)
                    chunk = context_chunk
                        
                splitted_path.append(chunk)
                chunk = []      

        splitted_paths.append(splitted_path)

    # search for equivalent paths respecting the phase
    final_paths = [path[1] for path in splitted_paths]

    # BFS search of chunk equivalence
    max_splitted_path = max(splitted_paths, key = lambda i: len(i)) 
    max_splitted_path_length = len(max_splitted_path) 

    for depth in range(0, max_splitted_path_length):
        for path_split in splitted_paths:
            if len(path_split) > depth:
                chunk = path_split[depth]
                # look for an equivalent phase
                phi = PhaseFormula(theory, chunk)
                unique = True

                for p in final_paths:
                    if p != chunk:
                        phi_prime = PhaseFormula(theory,p)
                        if phi == phi_prime:
                            unique = False
                            break

                if unique:
                    final_paths.append(chunk)