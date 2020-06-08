import copy

from pycparser import c_parser, c_ast, parse_file, c_generator

import networkx as nx

import syntaxlib

def async_to_sync(ast : c_ast.Node, syncv, labels):

    generator = c_generator.CGenerator()

    main_ast = syntaxlib.get_funcdef_node(ast,'main')

    cfg = syntaxlib.ControlFlowGraph(main_ast)

    assigment_nodes = round_assigments(cfg, syncv)

    labels_intervals = generate_labels_intervals(labels)
    
    # The list of all CFG's paths that start from a label to a greater one
    # TODO: we need to consider the paths from the last round!!! STARTVIEW->view++
    # TODO: all paths needs to be prefixed with all the possible paths that leads to the initial node (without syncv assigments)
    paths = []
    
    for p in labels_intervals:

        label_start = p[0]
        label_end = p[1]

        for assigment_start in assigment_nodes[label_start]:
            for assigment_end in assigment_nodes[label_end]:
                cfg_paths = get_cfg_paths_between_nodes(cfg, assigment_start, assigment_end)
                for p in cfg_paths:
                    if valid_path(p, syncv):          
                        paths.append(p)

    for p in paths:
        print("################Path######################")
        path_ast = syntaxlib.cfg_path_to_ast(p)
        code = generator.visit(path_ast)
        print(code)
        #path_cfg.draw()
        print("##########################################")

    #print(paths)


def get_cfg_paths_between_nodes(cfg, node_start, node_end):
    # all paths between start and end
    paths = []
    for path in nx.all_simple_paths(cfg, node_start, node_end): 
        path_cfg = cfg.subgraph(path)
        paths.append(path_cfg)

    return paths

"""
Tuples (x,y) of labels where x < y asuming labels to be a total order
"""
def generate_labels_intervals(labels):
    label_pairs = []

    for label_start_index in range(0, len(labels)):
        for label_end_index in range(label_start_index, len(labels)):
            label_start = labels[label_start_index]
            label_end = labels[label_end_index]
            if label_start != label_end:
                label_pairs.append( (label_start, label_end) )

    return label_pairs

"""
Calculate a dictionary where given a label it returns the list of CFG's nodes where the label is assigned to the syncvariable
"""
def round_assigments(cfg, syncv):
    round_assigments = {}

    syncv_assigments = [node for node in cfg if syntaxlib.is_var_assigment(node, syncv)]

    # Map label -> all cfg nodes where that label is assigned
    for n in syncv_assigments:
        label = syntaxlib.get_assigment_value(n)

        if not label in round_assigments:
            round_assigments[label] = []

        round_assigments[label].append(n)

    return round_assigments

"""
The input path starts and ends in a c_ast.Assigment where lvalue is syncv
A valid path is one with no assigments or continues in the middle
"""
def valid_path(path, syncv):
    return syntaxlib.count_variable_assigments(path, syncv) == 2 and syntaxlib.count_continues(path) == 0