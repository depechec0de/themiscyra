from pycparser import c_parser, c_ast, parse_file
from z3 import *
from smttools import *
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
Traverse the AST and collect the code depending on the context
"""

class ParseCode(c_ast.NodeVisitor):
    def __init__(self, phase_var, round_var, context, nextf, steps, current_step=0):
        self.generator = c_generator.CGenerator()
        self.restart_point = None
        self.variables = {phase_var: Int(phase_var), round_var: Int(round_var)}
        self.phase_var = phase_var
        self.round_var = round_var
        self.current_step = current_step
        self.steps = steps
        self.nextf = nextf
        self.context = context

        print("\t"*self.current_step+"========== INIT OF UNFOLDING ============")
    
    def manage_instruction(self, instruction):
        if isinstance(instruction, c_ast.If):
            print("\t"*self.current_step + "if("+self.generator.visit(instruction.cond)+") is_current_round? " + str(is_current_round(instruction.cond, self.context)) + " | ROUND=[" + str(self.context[self.phase_var]) + ", " + str(self.context[self.round_var]) + "] " +str(instruction.coord))
        elif isinstance(instruction, c_ast.While):
            print("\t"*self.current_step + "while("+self.generator.visit(instruction.cond)+") " + " | ROUND=[" + str(self.context[self.phase_var]) + ", " + str(self.context[self.round_var]) + "] " +str(instruction.coord))
        else:
            print("\t"*self.current_step + self.generator.visit(instruction) + " | ROUND=[" + str(self.context[self.phase_var]) + ", " + str(self.context[self.round_var]) + "] " +str(instruction.coord))

    def visit_FuncDef(self, node):
        self.manage_instruction(node.decl)
        c_ast.NodeVisitor.generic_visit(self, node)

    def visit_If(self, node):
        self.manage_instruction(node)

        if is_current_round(node.cond, self.context) and (node.iftrue is not None):
            #c_ast.NodeVisitor.generic_visit(self, node.iftrue)
            v = ParseCodeIf(self.phase_var, self.round_var, self.restart_point, self.context, self.nextf, self.steps, self.current_step)
            v.visit(node.iftrue)

        if node.iffalse is not None:
            #c_ast.NodeVisitor.generic_visit(self, node.iffalse)
            v = ParseCodeIf(self.phase_var, self.round_var, self.restart_point, self.context, self.nextf, self.steps, self.current_step)
            v.visit(node.iffalse)

    
    def visit_While(self, node):
        self.manage_instruction(node)

        if is_sat(node.cond, {}, {}):
            self.restart_point = node
            c_ast.NodeVisitor.generic_visit(self, self.restart_point)
        


class ParseCodeIf(c_ast.NodeVisitor):
    def __init__(self, phase_var, round_var, restart_point, context, nextf, steps, current_step):
        self.generator = c_generator.CGenerator()
        self.context = context
        self.phase_var = phase_var
        self.round_var = round_var
        self.current_step = current_step
        self.steps = steps
        self.nextf = nextf
        self.restart_point = restart_point
        self.stop = False

    def manage_instruction(self, instruction):
        if not self.stop:

            if isinstance(instruction, c_ast.If):
                print("\t"*self.current_step + "if("+self.generator.visit(instruction.cond)+") is_current_round? " + str(is_current_round(instruction.cond, self.context)) + " | ROUND=[" + str(self.context[self.phase_var]) + ", " + str(self.context[self.round_var]) + "] " +str(instruction.coord))
            else:
                print("\t"*self.current_step + self.generator.visit(instruction) + " | ROUND=[" + str(self.context[self.phase_var]) + ", " + str(self.context[self.round_var]) + "] " +str(instruction.coord))

    def visit_UnaryOp(self,node):   
        if not self.stop:
            self.manage_instruction(node) 

            if node.op == 'p++' and node.expr.name == self.phase_var:
                print("\t"*self.current_step+"ROUND CHANGE "+str(node.coord))
                self.stop = True
            

    def visit_FuncCall(self, node):
        self.manage_instruction(node)

    def visit_Continue(self, node):
        self.manage_instruction(node)

        if self.restart_point is not None and self.current_step < self.steps:
            v = ParseCode(self.phase_var, self.round_var, self.nextf(self.context), self.nextf, self.steps, self.current_step+1)
            v.visit(self.restart_point)
        
        else:
            print("\t"*self.current_step+"========== END OF STEPS ============")

    def visit_If(self, node):
        if not self.stop:
            self.manage_instruction(node)

            if is_current_round(node.cond, self.context) and (node.iftrue is not None):
                #c_ast.NodeVisitor.generic_visit(self, node.iftrue)
                v = ParseCodeIf(self.phase_var, self.round_var, self.restart_point, self.context, self.nextf, self.steps, self.current_step)
                v.visit(node.iftrue)

            if node.iffalse is not None:
                #c_ast.NodeVisitor.generic_visit(self, node.iffalse)
                v = ParseCodeIf(self.phase_var, self.round_var, self.restart_point, self.context, self.nextf, self.steps, self.current_step)
                v.visit(node.iffalse)

    def visit_Assignment(self, node):
        if not self.stop:
            if not isinstance(node.lvalue.name, c_ast.ID):
                if node.lvalue.name == self.phase_var:
                    if self.context[self.phase_var]==int(node.rvalue.value): 
                        self.manage_instruction(node)
                    else:
                        print("\t"*self.current_step+"ROUND CHANGE "+str(node.coord))
                        self.stop = True

                if node.lvalue.name == self.round_var:
                    if self.context[self.round_var]==int(node.rvalue.value): 
                        self.manage_instruction(node)
                    else:
                        print("\t"*self.current_step+"ROUND CHANGE "+str(node.coord))
                        self.stop = True