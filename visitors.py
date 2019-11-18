from pycparser import c_parser, c_ast, parse_file
from z3 import *
from smttools import *
from parse import *
import copy

"""
Get the function definition node in the AST looking by its name
"""
class FuncDefVisitor(c_ast.NodeVisitor):
    def __init__(self, funcname):
        self.funcname = funcname
        self.result = None

    def visit_FuncDef(self, node):
        if node.decl.name == self.funcname:
            self.result = node
        elif hasattr(node, 'args'):
            self.visit(node.args)

def get_funcdef_node(ast, funcname):
    v = FuncDefVisitor(funcname)
    v.visit(ast)
    return v.result

"""
Find the declaration of the ROUNDS enum to know all the possible rounds
"""

class RoundsEnumVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.result = []

    def visit_Enum(self, node):
        if node.name == 'rounds' and node.values is not None:
            for enum in node.values.enumerators:
                self.result.append(enum.name)

def get_rounds(ast):
    v = RoundsEnumVisitor()
    v.visit(ast)
    return v.result

"""
Visit the AST and get all the int and bool variables definitions 
"""

class VariableDeclVisitor(c_ast.NodeVisitor):

    def __init__(self):
        self.variables = {}

    def visit_TypeDecl(self, node):
        if node.declname is None:
            return

        if isinstance(node.type, c_ast.IdentifierType):
            if node.type.names[0] == 'int':
                self.variables[node.declname] = Int(node.declname)
            elif node.type.names[0] == '_Bool':
                self.variables[node.declname] = Bool(node.declname)

def get_variables(ast):
    v = VariableDeclVisitor()
    v.visit(ast)
    return v.variables

"""
Traverse the AST and collect the code of a given round with its conditions
"""

class RoundCode(c_ast.NodeVisitor):
    def __init__(self, phase_var, round_var, round, current_round, nextf, steps, context=None, current_step=0, collected_code=None, restart_point=None, debug=False):
        
        if collected_code is None:
            self.collected_code = {}
        else:
            self.collected_code = collected_code

        self.context = Context(context)
        self.generator = c_generator.CGenerator()
        self.restart_point = None
        self.phase_var = phase_var
        self.round_var = round_var
        self.current_step = current_step
        self.steps = steps
        self.nextf = nextf
        self.round = round
        self.restart_point = restart_point
        self.current_round = current_round
        self.debug = debug
    
    def manage_instruction(self, instruction):

        collect = self.current_round == self.round
        code = ""

        if isinstance(instruction, c_ast.If):
            code = "if("+self.generator.visit(instruction.cond)+")"
            collect = False
        elif isinstance(instruction, c_ast.While):
            code = "while("+self.generator.visit(instruction.cond)+")"
            collect = False
        elif is_round_assigment(instruction, self.phase_var) or is_round_assigment(instruction, self.round_var):
            collect = False
            code = self.generator.visit(instruction)
        elif isinstance(instruction, c_ast.UnaryOp) and instruction.expr.name == self.phase_var:
            collect = False
            code = self.generator.visit(instruction)
        elif isinstance(instruction, c_ast.FuncDef):
            collect = False
            code = self.generator.visit(instruction.decl)
        else:
            code = self.generator.visit(instruction)

        if collect:
            
            inst = AnotatedInstruction(code, self.context, instruction.coord)

            if self.context not in self.collected_code:
                self.collected_code[self.context] = []

            self.collected_code[self.context].append(inst)

        if self.debug:
            #info = " | CROUND=" + str(self.current_round) +", CONTEXT="+str(self.context)+" "+str(instruction.coord)
            #info = "CONTEXT=" + str(self.context)+" "+str(instruction.coord)
            info = " | CROUND=" + str(self.current_round)
            
            color_info = info
            
            if collect:
                color_code = bcolors.OKGREEN +  code + bcolors.ENDC
            else:
                color_code = bcolors.OKBLUE + code + bcolors.ENDC

            if isinstance(instruction, c_ast.If):
                print("\t"*self.current_step + str(instruction.coord) + " " + color_code + " is_current_round? " + str(is_current_round(instruction.cond, self.round)) + color_info)
            elif isinstance(instruction, c_ast.While):
                print("\t"*self.current_step + str(instruction.coord) + " " + color_code + color_info)
            else:
                print("\t"*self.current_step + str(instruction.coord) + " " + color_code + color_info )
            

    def visit_FuncDef(self, node):
        self.manage_instruction(node)
        c_ast.NodeVisitor.generic_visit(self, node)

    def visit_If(self, node):
        self.manage_instruction(node)

        if is_current_round(node.cond, self.current_round) and (node.iftrue is not None):
            new_context = copy.deepcopy(self.context)
            new_context.add_condition("if("+self.generator.visit(node.cond)+") @ "+str(self.current_round))
            v = RoundCode(phase_var=self.phase_var, round_var=self.round_var, restart_point=self.restart_point, round=self.round, nextf=self.nextf, steps=self.steps, context=new_context, current_round=copy.deepcopy(self.current_round), current_step=self.current_step, collected_code=self.collected_code, debug=self.debug)
            v.visit(node.iftrue)

        if node.iffalse is not None:
            new_context = copy.deepcopy(self.context)
            new_context.add_condition("if(NOT("+self.generator.visit(node.cond)+")) @ "+str(self.current_round))
            v = RoundCode(phase_var=self.phase_var, round_var=self.round_var, restart_point=self.restart_point, round=self.round, nextf=self.nextf, steps=self.steps, context=new_context, current_round=copy.deepcopy(self.current_round), current_step=self.current_step, collected_code=self.collected_code, debug=self.debug)
            v.visit(node.iffalse)

    def visit_UnaryOp(self,node):   
         
        if node.op == 'p++' and node.expr.name == self.phase_var:
            self.current_round[self.phase_var] = self.current_round[self.phase_var]+1

        self.manage_instruction(node)
    
    def visit_While(self, node):
        self.manage_instruction(node)

        if is_sat(node.cond, {}, {}):
            self.restart_point = node
            c_ast.NodeVisitor.generic_visit(self, node)

    def visit_FuncCall(self, node):
        self.manage_instruction(node)   

    def visit_Continue(self, node):
        self.manage_instruction(node)

        if self.restart_point is not None and self.current_step < self.steps:
            next_round = copy.deepcopy(self.current_round)
            #next_round = self.nextf(new_round)
            v = RoundCode(phase_var=self.phase_var, round_var=self.round_var, round=self.round, current_round=next_round, nextf=self.nextf, steps=self.steps, current_step=self.current_step+1, context=self.context, restart_point=self.restart_point, collected_code=self.collected_code, debug=self.debug)
            v.visit(self.restart_point)

    def visit_Assignment(self, node):
        self.manage_instruction(node)

        if is_round_assigment(node, self.phase_var):
            self.current_round[self.phase_var] = int(node.rvalue.value)
            
        if is_round_assigment(node, self.round_var):
            self.current_round[self.round_var] = int(node.rvalue.value)    
    