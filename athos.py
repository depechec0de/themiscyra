import copy

from pycparser import c_parser, c_ast, parse_file, c_generator

import networkx as nx

import syntaxlib
import semanticlib

def async_to_sync(ast : c_ast.Node, config):
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
    main_ast = syntaxlib.get_funcdef_node(ast,'main')
    syntaxlib.remove_whiles(main_ast)

    cfg = syntaxlib.ControlFlowGraph(main_ast)
    
    # round variables assigments in the CFG
    map_label_to_cfgnodes = syntaxlib.variable_assigments_by_value(cfg, round_variable)
        
    # we search paths between every (monotonically increasing) assigment of round variables
    paths_by_label = {}
    for l in labels:
        paths_by_label[l] = []

    labels_intervals = generate_labels_intervals(labels)

    for label_start, label_end in labels_intervals:
        for first_label_assigment in map_label_to_cfgnodes[label_start]:
            for last_label_assigment in map_label_to_cfgnodes[label_end]:
                cfg_paths = get_cfg_paths_between_nodes(cfg, first_label_assigment, last_label_assigment)
                for p in cfg_paths:
                    if valid_intermediate_path(p, round_variable):        
                        paths_by_label[label_start].append(p)

    # all paths from round assigments to phase increments (ending paths)
    phase_increment_nodes = syntaxlib.variable_increments(cfg, phase_variable)

    for label in labels:
        for last_label_assigment in map_label_to_cfgnodes[label]:
            for phase_increment in phase_increment_nodes:
                cfg_paths = get_cfg_paths_between_nodes(cfg, last_label_assigment, phase_increment)
                for p in cfg_paths:        
                    if valid_end_path(p, round_variable):  
                        paths_by_label[label].append(p)
    
    # we calculate the complete path with the previous context (ifs conditions)
    complete_paths_by_label = {}
    start_node = list(nx.topological_sort(cfg))[0]

    for l in paths_by_label:
        complete_paths_by_label[l] = []
        for suffix_path in paths_by_label[l]:
            suffix_first_node = list(nx.topological_sort(suffix_path))[0]
            prefix_paths = get_cfg_paths_between_nodes( cfg, start_node, 
                                                        suffix_first_node)

            for prefix_path in prefix_paths:
                # we don't prefix with ended paths, i.e. with continues
                count_continues = syntaxlib.count_continues(prefix_path)
            
                if count_continues == 0:
                    cfg_end = suffix_path.copy()
                    # CFG path only containing ifs
                    #prefix_nodes = [n for n in list(nx.topological_sort(prefix_path)) if type(n)==c_ast.If]
                    prefix_nodes = list(nx.topological_sort(prefix_path))
                    # discard the node in common, the last
                    prefix_nodes = prefix_nodes[:-1]

                    valid_prefix_path = syntaxlib.ControlFlowGraph()
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

                    ast_path = syntaxlib.cfg_path_to_ast(path)
                    complete_paths_by_label[l].append(ast_path)

    return complete_paths_by_label

def get_cfg_paths_between_nodes(cfg, node_start, node_end):
    # all paths between start and end
    paths = []
    for path in nx.all_simple_paths(cfg, node_start, node_end): 
        path_cfg = cfg.subgraph(path)
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

def valid_intermediate_path(path, syncv):
    """ Returns true if `path` starts and ends in a `c_ast.Assigment` and there
    are no continues in the middle.
    """
    return syntaxlib.count_variable_assigments(path, syncv) == 2 and syntaxlib.count_continues(path) == 0

def valid_end_path(path, syncv):
    return syntaxlib.count_variable_assigments(path, syncv) == 1 and syntaxlib.count_continues(path) == 0