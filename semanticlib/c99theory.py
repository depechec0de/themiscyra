from z3 import *
from typing import Type, List, Set, Dict, Tuple, Optional

from pycparser import c_parser, c_ast, parse_file, c_generator
from syntaxlib import ast

class C99Theory():

    def __init__(self, fileast : c_ast.FileAST):

        # Declarations
        # variable name : str -> corresponding SMT variable : z3.Const
        self.dict_variable_smtvar = {}
        # constant name : str -> corresponding SMT const : z3.Const
        self.dict_const_smtconst = {}
        # c99 enum type name : str -> corresponding SMT sort : z3.EnumSort
        self.dict_enumtype_smtsort = {}

        self.dict_variable_enumtype = {}
        self.dict_enumtype_constants = {}
        self.dict_const_smtsort = {}

        # Context
        self.context = dict()
        
        # We gather every enum definitions and variables and obtain their SMT 
        # counterpart
        self.dict_variable_enumtype = ast.get_declared_enum_vars(fileast)
        self.dict_enumtype_constants = ast.get_enum_declarations(fileast)
        
        for enum_name, enum_constants in self.dict_enumtype_constants.items():
            smt_enum_sort, smt_constants = self.create_enum_sort(enum_name, enum_constants)

            for const in enum_constants:
                self.dict_const_smtsort[const] = smt_enum_sort

            self.dict_enumtype_smtsort[enum_name] = smt_enum_sort
            # dictionary union
            self.dict_const_smtconst = dict(self.dict_const_smtconst, **smt_constants)

        for var_name, smt_variable in self.dict_variable_enumtype.items():
            self.dict_variable_smtvar[var_name] = \
            z3.Const(var_name, 
                    self.dict_enumtype_smtsort[self.dict_variable_enumtype[var_name]])    

    def create_enum_sort(self, name, values) -> (z3.DatatypeSortRef, Dict[str, z3.DatatypeRef]):
        S, enum_values = EnumSort(name, values)

        map_enum = {}
        i = 0
        for e in enum_values:
            map_enum[values[i]] = e
            i=i+1

        return S, map_enum

    def handle_if(self, node : c_ast.If):
        constraint = self.ast_to_smt(node.cond)
        self.context[node] = constraint 

    def handle_assigment(self, node : c_ast.Assignment):
        constraint = self.ast_to_smt(node)
        self.context[node.lvalue.name] = constraint 

    def get_sort(self, var_name):
        if var_name in self.dict_variable_enumtype:
            return self.dict_enumtype_smtsort[self.dict_variable_enumtype[var_name]]
        if var_name in self.dict_const_smtsort:
            return self.dict_const_smtsort[var_name]
        else:
            return IntSort()

    def get_variable(self, id_name):
        if id_name == 'false':
            return False
        elif id_name == 'true':
            return True
        elif id_name in self.dict_variable_smtvar:
            return self.dict_variable_smtvar[id_name]
        elif id_name in self.dict_const_smtconst:
            return self.dict_const_smtconst[id_name]
        else:
            return Int(id_name)

    def ast_to_smt(self, node: c_ast.Node):
        """Translates a pycparser c_ast.Node to a z3 predicate."""
        typ = type(node) 
        
        if typ == c_ast.BinaryOp:
            
            leftnode = self.ast_to_smt(node.left)
            rightnode = self.ast_to_smt(node.right) 

            if node.op == '&&':
                return And(leftnode, rightnode)
            elif node.op == '||':
                return Or(leftnode, rightnode)
            elif node.op == '==':
                return leftnode == rightnode 
            elif node.op == '<':
                return leftnode < rightnode
            elif node.op == '<=':
                return leftnode <= rightnode
            elif node.op == '>':
                return leftnode > rightnode
            elif node.op == '>=':
                return leftnode >= rightnode
            elif node.op == '!=':
                return leftnode != rightnode
            elif node.op == '/':
                return leftnode / rightnode
            elif node.op == '+':
                return leftnode + rightnode

        elif typ == c_ast.Assignment and node.op == '=':
            leftnode = self.ast_to_smt(node.lvalue)
            rightnode = self.ast_to_smt(node.rvalue) 

            return leftnode == rightnode
        elif typ == c_ast.Constant:
            return int(node.value)
        elif typ == c_ast.FuncCall:
            domain = []
            args = []
            if node.args is not None:
                for arg in node.args.exprs:
                    smtarg = self.ast_to_smt(arg)
                    args.append(smtarg)
                    domain.append(self.get_sort(arg.name))
         
            codomain = IntSort()

            f = Function(node.name.name, *domain, codomain)

            return f(*args)
        elif typ == c_ast.ID:
            return self.get_variable(node.name)
        else:
            return True

    def is_sat(self, astcond) -> Bool:
        
        predicate = self.ast_to_smt(astcond)
        
        solver = Solver()

        solver.add(predicate)

        for var in self.context:
            solver.add(self.context[var])
        
        return solver.check() == z3.sat