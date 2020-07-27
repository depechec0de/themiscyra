import copy

from pycparser import c_parser, c_ast, parse_file, c_generator

import networkx as nx

from syntaxlib import ast, cfg

def async_to_sync(async_ast : c_ast.Node, config):
    """ Given a c99 code in a AST form, returns the corresponding code of its
    synchronous equivalent program.

    Notes
    -----
    First step is calculate all code between round variables assigments, then
    we add all the context needed to reach that piece of code.

    Entry point     if  ... if ...      Current round            Next round
    * --------------------------------> *----------------------> *
                    A                               B
    
    The code we want to extract is in path B, but we need to collect all the
    conditions to reach this path, this is obtained collection all c_ast.If
    in path A.

    Path A and B can't contain c_ast.Continue nodes. Path B can't contain other
    round assigments in the middle.
    """
    phase_variable = config['phase']
    round_variable = config['round']
    labels = config['labels']
    
    # we discard what we won't use
    main_ast = ast.get_funcdef_node(async_ast,'main')
    ast.call_recursively(main_ast, ast.remove_whiles, [])
    ast.call_recursively(main_ast, ast.remove_declarations, [])

    codecfg = cfg.ControlFlowGraph(main_ast)
    
    # we search paths between every (monotonically increasing) assigment of round variables
    paths_between_rounds = paths_between_round_assignments(codecfg, labels, round_variable, phase_variable)

    # for every protocol's round we calculate all possible paths including its previous context (e.g., ifs conditions)
    start_node = list(nx.topological_sort(codecfg))[0]
    complete_paths_by_round = {}

    for label, suffix_paths in paths_between_rounds.items():
        complete_paths_by_round[label] = []

        for suffix_path in suffix_paths:
            suffix_first_node = list(nx.topological_sort(suffix_path))[0]
            prefix_paths = get_cfg_paths_between_nodes(codecfg, start_node, suffix_first_node)

            cp = complete_paths(suffix_path, prefix_paths)
            complete_paths_by_round[label].extend(cp)

    # the code of a round is the (graph) union of all the complete paths found to belong to that round
    # the easiest approach is to remove the nodes not included in those paths from the original code using the coord property
    sync_code = {}

    for label, paths in complete_paths_by_round.items():

        round_code_cfg = cfg.ControlFlowGraph()
        nodes_to_keep = set()
        
        for p in paths:
            for n in p.nodes():
                nodes_to_keep.add(str(n.coord))

        round_sync_code = copy.deepcopy(main_ast)
        
        ast.call_recursively(round_sync_code, ast.keep_nodes, [nodes_to_keep])

        sync_code[label] = round_sync_code

    # translate to CompHO
    compho = {}

    for label, ast_code in sync_code.items():
        compho[label] = {}
        compho[label]['send'] = ast.get_compho_send(copy.deepcopy(ast_code))
        compho[label]['update'] = ast.get_compho_update(copy.deepcopy(ast_code))


    return compho

def get_cfg_paths_between_nodes(codecfg, node_start, node_end):
    # all paths between start and end
    paths = []
    for path in nx.all_simple_paths(codecfg, node_start, node_end): 
        path_cfg = codecfg.subgraph(path)
        paths.append(path_cfg)

    return paths


def generate_labels_intervals(labels):
    """Generates all tuples `(x,y)` with `x` and `y` in `labels` where `x < y` 
    asuming `labels` to be a total order.
    """
    label_pairs = []

    for label_start_index in range(0, len(labels)):
        for label_end_index in range(label_start_index, len(labels)):
            label_start = labels[label_start_index]
            label_end = labels[label_end_index]
            if label_start != label_end:
                label_pairs.append( (label_start, label_end) )

    return label_pairs

def paths_between_round_assignments(codecfg, labels, round_variable, phase_variable):
    """ We find all possible paths between round assignments, taking into account the phase variable increment as a possible end of a path """
    paths_by_label = {}
    for l in labels:
        paths_by_label[l] = []

    labels_intervals = generate_labels_intervals(labels)

    # round variables assigments in the CFG
    map_label_to_cfgnodes = ast.variable_assigments_by_value(codecfg, round_variable)
    
    for label_start, label_end in labels_intervals:
        for first_label_assigment in map_label_to_cfgnodes[label_start]:
            for last_label_assigment in map_label_to_cfgnodes[label_end]:
                cfg_paths = get_cfg_paths_between_nodes(codecfg, first_label_assigment, last_label_assigment)
                for p in cfg_paths:
                    if valid_intermediate_path(p, round_variable):        
                        paths_by_label[label_start].append(p)
    
    # all paths from round assigments to phase increments (ending paths)
    phase_increment_nodes = ast.variable_increments(codecfg, phase_variable)
    
    for label in labels:
        for last_label_assigment in map_label_to_cfgnodes[label]:
            for phase_increment in phase_increment_nodes:
                cfg_paths = get_cfg_paths_between_nodes(codecfg, last_label_assigment, phase_increment)
                for p in cfg_paths:        
                    if valid_end_path(p, round_variable):  
                        paths_by_label[label].append(p)

    return paths_by_label

def complete_paths(suffix_path, prefix_paths):
    """ Generate all valid paths extending `prefix_paths` with `suffix path`"""

    complete_paths = []
    
    for prefix_path in prefix_paths:
        # we don't prefix with ended paths, i.e. with continues
        count_continues = ast.count_continues(prefix_path)
    
        if count_continues == 0:
            cfg_end = suffix_path.copy()
            # CFG path only containing ifs
            prefix_nodes = [n for n in list(nx.topological_sort(prefix_path)) if type(n)==c_ast.If or type(n)==c_ast.While]
            #prefix_nodes = list(nx.topological_sort(prefix_path))
            # discard the node in common, the last
            #prefix_nodes = prefix_nodes[:-1]
            #prefix_nodes.append(c_ast.Break())

            valid_prefix_path = cfg.ControlFlowGraph()
            nx.add_path(valid_prefix_path, prefix_nodes)

            # TODO: we could iterate the path and check if is SAT or
            # reduce redundant ifs

            if len(valid_prefix_path) > 0:
                nodes_beginning = list(nx.topological_sort(valid_prefix_path))
                nodes_end = list(nx.topological_sort(cfg_end))

                complete_path = nx.compose(valid_prefix_path, cfg_end)
                complete_path.add_edge(nodes_beginning[-1], nodes_end[0])
                
                path = complete_path
            else:
                path = cfg_end

            complete_paths.append(path)

    return complete_paths

def valid_intermediate_path(path, syncv):
    """ Returns true if `path` starts and ends in a `c_ast.Assigment` and there
    are no continues in the middle.
    """
    return ast.count_variable_assigments(path, syncv) == 2 and ast.count_continues(path) == 0

def valid_end_path(path, syncv):
    return ast.count_variable_assigments(path, syncv) == 1 and ast.count_continues(path) == 0