from z3 import *
from typing import Type, List, Set, Dict, Tuple, Optional

from pycparser import c_parser, c_ast, parse_file, c_generator
from syntaxlib import ast

class C99Theory():

    def __init__(self, fileast : c_ast.FileAST):

        # z3 solver
        self.solver = Solver()

        # Declarations
        # variable name : str -> corresponding SMT variable : z3.Const
        self.dict_variable_smtvar = {}
        # constant name : str -> corresponding SMT const : z3.Const
        self.dict_const_smtconst = {}
        # c99 enum type name : str -> corresponding SMT sort : z3.EnumSort
        self.dict_enumtype_smtsort = {}
        self.dict_const_smtsort = {}
        self.dict_funcname_smtfunc = {}

        # Context
        self.var_assigments = dict()
        
        # We gather every enum definitions and variables and obtain their SMT 
        # counterpart
        self.dict_variable_enumtype = ast.get_declared_enum_vars(fileast)
        self.dict_enumtype_constants = ast.get_enum_declarations(fileast)
        self.dict_funcname_astfunc = ast.get_func_declarations(fileast)
        
        for enum_name, enum_constants in self.dict_enumtype_constants.items():
            smt_enum_sort, smt_constants = self.declare_enum_sort(enum_name, enum_constants)

            for const in enum_constants:
                self.dict_const_smtsort[const] = smt_enum_sort

            self.dict_enumtype_smtsort[enum_name] = smt_enum_sort
            # dictionary union
            self.dict_const_smtconst = dict(self.dict_const_smtconst, **smt_constants)

        for var_name, smt_variable in self.dict_variable_enumtype.items():
            self.dict_variable_smtvar[var_name] = \
            z3.Const(var_name, 
                    self.dict_enumtype_smtsort[self.dict_variable_enumtype[var_name]])    

        for funcname, astfuncdecl in self.dict_funcname_astfunc.items():
            self.dict_funcname_smtfunc[funcname] = self.declare_func(funcname, astfuncdecl)

    def declare_enum_sort(self, name, values) -> (z3.DatatypeSortRef, Dict[str, z3.DatatypeRef]):
        S, enum_values = EnumSort(name, values)

        map_enum = {}
        i = 0
        for e in enum_values:
            map_enum[values[i]] = e
            i=i+1

        return S, map_enum

    def declare_func(self, name, fdecl : c_ast.FuncDecl):
        domain = []
        if fdecl.args is not None:
            for arg in fdecl.args.params:
                arg_type = ast.get_decl_type(arg)
                if arg_type in self.dict_enumtype_smtsort:
                    domain.append(self.dict_enumtype_smtsort[arg_type])
                else:
                    domain.append(IntSort())
        
        freturntype = ast.get_decl_type(fdecl)
        codomain = IntSort()
        if freturntype in self.dict_enumtype_smtsort:
            codomain = self.dict_enumtype_smtsort[freturntype]

        f = Function(name, *domain, codomain)

        return f

    def handle_if(self, node : c_ast.If):
        constraint = self.evaluate_ast(node.cond)
        self.var_assigments[node] = constraint 

    def handle_assigment(self, node : c_ast.Assignment):
        constraint = self.evaluate_ast(node)
        self.var_assigments[node.lvalue.name] = constraint 

    def evaluate_sort(self, var_name):
        if var_name in self.dict_variable_enumtype:
            return self.dict_enumtype_smtsort[self.dict_variable_enumtype[var_name]]
        if var_name in self.dict_const_smtsort:
            return self.dict_const_smtsort[var_name]
        else:
            return IntSort()

    def evaluate_variable(self, id_name):
        if id_name == 'false':
            return Bool(False)
        elif id_name == 'true':
            return Bool(True)
        elif id_name in self.dict_variable_smtvar:
            return self.dict_variable_smtvar[id_name]
        elif id_name in self.dict_const_smtconst:
            return self.dict_const_smtconst[id_name]
        else:
            return Int(id_name)

    def evaluate_ast(self, node: c_ast.Node):
        """Translates a c_ast.Node to a z3 predicate."""
        typ = type(node) 
        
        if typ == c_ast.BinaryOp:
            leftnode = self.evaluate_ast(node.left)
            rightnode = self.evaluate_ast(node.right) 
            
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
            leftnode = self.evaluate_ast(node.lvalue)
            rightnode = self.evaluate_ast(node.rvalue) 

            return leftnode == rightnode
        elif typ == c_ast.Constant:
            return int(node.value)
        elif typ == c_ast.FuncCall:
            args = []
            if node.args is not None:
                for arg in node.args.exprs:
                    smtarg = self.evaluate_ast(arg)   
                    args.append(smtarg)

            fname = node.name.name
            f = self.dict_funcname_smtfunc[fname]
            return f(*args)
        elif typ == c_ast.ID:
            return self.evaluate_variable(node.name)
        elif typ == c_ast.StructRef:
            # TODO: consider structs types
            return Int(ast.get_structref_name(node))
        else:
            return Bool(True)

    def is_sat(self, astif : c_ast.If) -> Bool:
        
        predicate = self.evaluate_ast(astif.cond)

        assertions = []
        assertions.append(predicate)

        for var in self.var_assigments:
            assertions.append(self.var_assigments[var])
        
        return self.solver.check(assertions) == z3.sat