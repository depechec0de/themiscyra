from pycparser import c_parser, c_ast, parse_file
from z3 import *
from smt_tools import *
from parser import *
from termcolor import colored
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

class MainWhileVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.current_parent = None
        self.result = None

    def visit_While(self, node):
        self.result = (node, self.current_parent)

    def generic_visit(self, node):
        oldparent = self.current_parent
        self.current_parent = node
        for c in node:
            self.visit(c)
        self.current_parent = oldparent

def get_main_while(ast):
    v = MainWhileVisitor()
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


class FileLinesNumberVisitor(c_ast.NodeVisitor):

    def __init__(self):
        self.lines_nr = set()

    def visit_FuncDef(self, node):
        self.add_line(node)
        c_ast.NodeVisitor.generic_visit(self, node)

    def visit_If(self, node):
        self.add_line(node)
        c_ast.NodeVisitor.generic_visit(self, node)

    def visit_UnaryOp(self,node):   
        self.add_line(node)             
    
    def visit_While(self, node):
        self.add_line(node)
        c_ast.NodeVisitor.generic_visit(self, node)

    def visit_FuncCall(self, node):
        self.add_line(node)  

    def visit_Continue(self, node):
        self.add_line(node)         

    def visit_Assignment(self, node):
        self.add_line(node)

    def add_line(self, node):
        line_nr = int(str(node.coord).split(':')[1])
        self.lines_nr.add(line_nr)

"""
Traverse the AST and collect the code of a given round with its conditions
"""

class UnfoldVisitor(c_ast.NodeVisitor):
    def __init__(self, phase_var, round_var, goal_round, initial_round, steps, context=None, current_step=0, collected_code=None, current_path_code=None, restart_point=None, stop=False, debug=False):
        
        if collected_code is None:
            self.collected_code = []
        else:
            self.collected_code = collected_code

        if current_path_code is None:
            self.current_path_code = []
        else:
            self.current_path_code = current_path_code

        if context is None:
            self.context = Context()
        else:
            self.context = context

        
        self.stop = stop
 
        self.generator = c_generator.CGenerator()
        self.restart_point = None
        self.phase_var = phase_var
        self.round_var = round_var
        self.current_step = current_step
        self.steps = steps
        self.goal_round = goal_round
        self.restart_point = restart_point
        self.current_round = initial_round
        self.debug = debug
    
    def manage_instruction(self, instruction):

        collect = (self.current_round == self.goal_round) and (not self.stop)
        code = ""

        typ = type(instruction) 

        if typ == c_ast.If:
            collect = False
            code = "if("+self.generator.visit(instruction.cond)+")"
        elif typ == c_ast.While:
            collect = False
            code = "while("+self.generator.visit(instruction.cond)+")"
        elif is_round_assigment(instruction, self.phase_var) or is_round_assigment(instruction, self.round_var):
            collect = False
            code = self.generator.visit(instruction)
        elif typ == c_ast.UnaryOp and instruction.expr.name == self.phase_var:
            collect = False
            code = self.generator.visit(instruction)
        elif typ == c_ast.FuncDef:
            collect = False
            code = self.generator.visit(instruction.decl)
        elif typ == c_ast.Continue:
            collect = False
            code = self.generator.visit(instruction)
        else:
            code = self.generator.visit(instruction)

        if collect:
            inst = AnotatedInstruction(code, self.context, instruction.coord)
            self.current_path_code.append(inst)

        if self.debug:
            #info = " | CROUND=" + str(self.current_round) +", CONTEXT="+str(self.context)
            #info = "CONTEXT=" + str(self.context)+" "+str(instruction.coord)
            info = " | CROUND=" + str(self.current_round) + " Stop:" + str(self.stop)+" ID: "+str(hash(id(self)))
            
            color_info = info
            
            if collect:
                color_code = colored(code, 'green')
            else:
                color_code = colored(code, 'blue')

            if typ == c_ast.If:
                print("\t"*self.current_step + str(instruction.coord) + " " + color_code + " is_current_round? " + str(is_current_round(instruction.cond, self.goal_round)) + color_info)
            elif typ == c_ast.While:
                print("\t"*self.current_step + str(instruction.coord) + " " + color_code + color_info)
            else:
                print("\t"*self.current_step + str(instruction.coord) + " " + color_code + color_info )
            

    def visit_FuncDef(self, node):
        self.manage_instruction(node)
        c_ast.NodeVisitor.generic_visit(self, node)

    def visit_If(self, node):
        self.manage_instruction(node)

        if is_current_round(node.cond, self.current_round) and (node.iftrue is not None):
            #new_context = Context(self.context)
            condition = Condition("if("+self.generator.visit(node.cond)+")", self.current_round, self.current_step)
            self.context.add_condition(condition)
            #new_context.add_condition(condition)
            #v = UnfoldVisitor(phase_var=self.phase_var, round_var=self.round_var, restart_point=self.restart_point, goal_round=self.goal_round, steps=self.steps, context=new_context, initial_round=copy.deepcopy(self.current_round), current_step=self.current_step, collected_code=self.collected_code, current_path_code=self.current_path_code, stop=self.stop, debug=self.debug)
            #v.visit(node.iftrue)
            c_ast.NodeVisitor.generic_visit(self, node.iftrue)
        else:
            self.stop = True

    def visit_UnaryOp(self,node):   
        self.manage_instruction(node)
        
        if node.op == 'p++' and node.expr.name == self.phase_var:
            self.current_round[self.phase_var] = self.current_round[self.phase_var]+1               
    
    def visit_While(self, node):
        self.manage_instruction(node)

        if is_sat(node.cond, {}, {}):
            self.restart_point = node
            c_ast.NodeVisitor.generic_visit(self, node)

    def visit_FuncCall(self, node):
        self.manage_instruction(node)   

    def visit_Continue(self, node):
        self.manage_instruction(node)

        if self.current_step == self.steps:
            self.collected_code.append(copy.deepcopy(self.current_path_code))
            self.stop = True
            
        if self.restart_point is not None and not self.stop:
            next_round = copy.deepcopy(self.current_round)
            new_current_path_code = copy.deepcopy(self.current_path_code)
            v = UnfoldVisitor(phase_var=self.phase_var, round_var=self.round_var, goal_round=self.goal_round, initial_round=next_round, steps=self.steps, current_step=self.current_step+1, context=self.context, restart_point=self.restart_point, collected_code=self.collected_code, current_path_code=new_current_path_code, stop=self.stop, debug=self.debug)
            v.visit(self.restart_point)            
        

    def visit_Assignment(self, node):
        self.manage_instruction(node)

        if is_round_assigment(node, self.phase_var):
            self.current_round[self.phase_var] = int(node.rvalue.value)
            
        if is_round_assigment(node, self.round_var):
            self.current_round[self.round_var] = int(node.rvalue.value)    
            

def is_round_assigment(instruction, variable_name):
    if isinstance(instruction, c_ast.Assignment) and not isinstance(instruction.lvalue.name, c_ast.ID) and instruction.lvalue.name == variable_name:
        return True
    else:
        return False