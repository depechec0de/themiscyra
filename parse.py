import argparse
import sys

from pycparser import c_parser, c_ast, parse_file
from visitors import *

class bcolors:
    HEADER = '\033[95m'
    OKBLUE = '\033[94m'
    OKGREEN = '\033[92m'
    WARNING = '\033[93m'
    FAIL = '\033[91m'
    ENDC = '\033[0m'
    BOLD = '\033[1m'
    UNDERLINE = '\033[4m'

class Context(object):
    def __init__(self, other_context=None):
        if other_context is None:
            self.conditions = []
        else:
            self.conditions = copy.deepcopy(other_context.conditions)
    
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

    def add_condition(self, cond):
        self.conditions.append(cond)


class AnotatedInstruction(object):
    def __init__(self, text, context, coord):
        self.text = text
        self.context = context
        self.coord = coord

    def __str__(self):
        return self.instruction+" @ "+str(self.coord)+", "+str(self.context)

    def __repr__(self):
        return "("+self.instruction+" @ "+str(self.coord)+", "+str(self.context)+")"

    def __hash__(self):
        return hash(str(self))

    def __eq__(self, other):
        return (
            self.__class__ == other.__class__ and
            self.coord == other.coord and
            self.context == other.context and
            self.text == other.text
        )

def is_round_assigment(instruction, variable_name):
    if isinstance(instruction, c_ast.Assignment) and not isinstance(instruction.lvalue.name, c_ast.ID) and instruction.lvalue.name == variable_name:
        return True
    else:
        return False

def round_code(ast, phase_var, round_var, round, current_round, nextf, steps, debug):

    v = RoundCode(phase_var=phase_var, round_var=round_var, round=round, current_round=current_round, nextf=nextf, steps=steps, debug=debug)
    v.visit(ast)
    return v.collected_code


if __name__ == "__main__":
    argparser = argparse.ArgumentParser('Dump AST')
    argparser.add_argument('filename', help='name of file to parse')
    argparser.add_argument('--coord', help='show coordinates in the dump', action='store_true')
    args = argparser.parse_args()

    ast = parse_file(args.filename, use_cpp=False)

    # We search the main() function definition
    node_main = get_funcdef_node(ast,'main')

    if node_main is None:
        sys.exit("No main() declaration found.")

    variables = get_variables(node_main)

    # We get the rounds definitions
    rounds = get_rounds(ast)

    def nextround(ts):
        if ts['round']==1:
            return {'ballot': ts['ballot']+1, 'round': 0}
        else:
            return {'ballot': ts['ballot'], 'round': 1}

    def generate_code(collected_code):
        for context in collected_code.keys():
            print(context)
            for instruction in collected_code[context]:
                print("\t"+instruction.text)
    
    round = {'ballot': 0, 'round': 0}
    print("############### TRACE LOG ###############")
    collected_code = round_code(ast=node_main, phase_var='ballot', round_var='round', current_round={'ballot': 0, 'round': 0}, round=round, nextf=nextround, steps=2, debug=True)
    print("############### ROUND CODE "+str(round)+" ###############")
    generate_code(collected_code)
    print("")
    
    """
    round = {'ballot': 0, 'round': 1}
    print("############### CODE "+str(round)+" ###############")
    code = round_code(ast=node_main, phase_var='ballot', round_var='round', current_round={'ballot': 0, 'round': 0}, round=round, nextf=nextround, steps=2)
    for line in code:
        print(line)
    print("")

    round = {'ballot': 1, 'round': 0}
    print("############### CODE "+str(round)+" ###############")
    code = round_code(ast=node_main, phase_var='ballot', round_var='round', current_round={'ballot': 0, 'round': 0}, round=round, nextf=nextround, steps=2)
    for line in code:
        print(line)
    print("")
   
    round = {'ballot': 1, 'round': 1}
    print("############### CODE "+str(round)+" ###############")
    code = round_code(ast=node_main, phase_var='ballot', round_var='round', current_round={'ballot': 0, 'round': 0}, round=round, nextf=nextround, steps=2)
    print("")
    for line in code:
        print(line)
    print("")
    """

 
        

