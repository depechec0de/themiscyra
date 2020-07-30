from z3 import *
from typing import Type, List, Set, Dict, Tuple, Optional

from pycparser import c_parser, c_ast, parse_file, c_generator
from syntaxlib import ast

class SemanticError(Exception):
    pass

class C99Theory():

    def __init__(self, fileast : c_ast.FileAST):

        ### z3 solver
        self.solver = Solver()

        ### Context
        self.var_assigments = dict()

        ### Declarations ###
        # variables
        self.dict_variable_smtvar = {}
        # enum constants
        self.dict_const_smtconst = {}
        # enum sorts
        self.dict_enumtype_smtsort = {}
        self.dict_const_smtsort = {}
        # functions
        self.dict_funcname_smtfunc = {}
        # struct sorts
        self.dict_structtype_smtsort = {}
        
        # Aux structures
        self.dict_variable_type = ast.get_declared_vars(fileast)
        self.dict_enumtype_constants = ast.get_enum_declarations(fileast)
        self.dict_funcname_astfunc = ast.get_func_declarations(fileast)
        self.dict_structtype_fields = ast.get_struct_declarations(fileast)
        self.dict_structvariable_structdecl = ast.get_struct_vars_declarations(fileast)

        for structtype, decl in self.dict_structtype_fields.items(): 
            self.dict_structtype_smtsort[structtype] = DeclareSort(structtype)
        
        for enum_name, enum_constants in self.dict_enumtype_constants.items():
            smt_enum_sort, smt_constants = self.declare_enum_sort(enum_name, enum_constants)

            for const in enum_constants:
                self.dict_const_smtsort[const] = smt_enum_sort

            self.dict_enumtype_smtsort[enum_name] = smt_enum_sort
            # dictionary union
            self.dict_const_smtconst = dict(self.dict_const_smtconst, **smt_constants)

        for var_name, var_type in self.dict_variable_type.items():
            self.dict_variable_smtvar[var_name] = self.declare_variable(var_name, var_type)    
        
        for funcname, astfuncdecl in self.dict_funcname_astfunc.items():
            self.dict_funcname_smtfunc[funcname] = self.declare_func(funcname, astfuncdecl)
        
    def __repr__(self):

        funcs = []
        for fname, f in self.dict_funcname_smtfunc.items():
            fdomain = []
            for i in range(0,f.arity()):
                fdomain.append( str(f.domain(i)))
            fstr = f.name() + "(" + ", ".join(fdomain) + ") -> " + str(f.range())
            funcs.append(fstr)

        enums = []
        for ename, e in self.dict_enumtype_smtsort.items():
            econsts = []
            for i in range(0,e.num_constructors()):
                econsts.append( str(e.constructor(i)))
            estr = str(e) + " = [" + ", ".join(econsts) + "]"
            enums.append(estr)

        vardecls = []
        for vname, v in self.dict_variable_smtvar.items():
            vardecls.append(vname)

        structdecls = self.dict_structtype_fields
           
        structvardecls = []
        for vname, v in self.dict_structvariable_structdecl.items():
            structvardecls.append(vname)

        structsorts = self.dict_structtype_smtsort

        return  "enum sorts: {" + ", ".join(enums) + "}, \
structs sorts: " + str(structsorts) + ", \
enum vars: {" + ", ".join(vardecls) + "}, \
function defs: { " + ", ".join(funcs) + " }, \
structs decls: { " + str(structdecls) + " }, \
declared struct vars: {" + ", ".join(structvardecls) + "}, \
var assigments: { " + str(self.var_assigments) + " }"
    
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
                sort = self.get_sort(arg_type)
                domain.append(sort)
        
        freturntype = ast.get_decl_type(fdecl)
        codomain = self.get_sort(freturntype)

        f = Function(name, *domain, codomain)

        return f

    def handle_if(self, node : c_ast.If):
        constraint = self.evaluate_ast(node.cond)
        self.solver.add(constraint) 

    def handle_assigment(self, node : c_ast.Assignment):
        constraint = self.evaluate_ast(node)
        self.var_assigments[node.lvalue.name] = constraint 

    def get_sort(self, asttype):
        if asttype in self.dict_enumtype_smtsort:
            return self.dict_enumtype_smtsort[asttype]
        elif asttype == '_Bool':
            return BoolSort()
        elif asttype == 'int':
            return IntSort()
        elif asttype in self.dict_structtype_smtsort:
            return self.dict_structtype_smtsort[asttype]
        else: 
            raise SemanticError('No Sort found for '+asttype)

    def evaluate_structref(self, node):
        
        # We declare a `varname`, we look for its domain
        varname = ast.get_structref_name(node)

        # amount of derefs, the first one manually
        derefs = varname.split('->')
        basename = derefs[0]
        field = derefs[1]

        if basename not in self.dict_structvariable_structdecl:
            raise SemanticError('An error ocurred trying to dereference StructRef')
        
        structdecl = self.dict_structvariable_structdecl[basename]
        structref_type = self.dict_structtype_fields[structdecl][field]

        del derefs[0:2]

        if len(derefs)>0:
            for f in derefs:
                if structref_type not in self.dict_structtype_fields:
                    raise SemanticError('An error ocurred trying to dereference StructRef')

                structref_type = self.dict_structtype_fields[structref_type][f]

        v = self.declare_variable(varname, structref_type)

        return v

    def declare_variable(self, idname, vtype):
        if vtype == 'int':
            return Int(idname)
        elif vtype in self.dict_variable_smtvar:
            return Const(idname, self.dict_variable_smtvar[vtype])
        elif vtype in self.dict_structtype_smtsort:
            return Const(idname, self.dict_structtype_smtsort[vtype])
        elif vtype in self.dict_enumtype_smtsort:
            return Const(idname, self.dict_enumtype_smtsort[vtype])
        elif vtype == '_Bool':
            return Bool(idname)
        else:
            raise SemanticError('invalid vtype '+vtype)

    def evaluate_variable(self, id_name):
        if id_name == 'false':
            return BoolVal(False)
        elif id_name == 'true':
            return BoolVal(True)
        elif id_name in self.dict_variable_smtvar:
            return self.dict_variable_smtvar[id_name]
        elif id_name in self.dict_const_smtconst:
            return self.dict_const_smtconst[id_name]
        else:
            raise SemanticError('not declared variable '+id_name)

    def evaluate_ast(self, node: c_ast.Node):
        """Translates a c_ast.Node to a z3 predicate."""
        typ = type(node) 

        if typ == c_ast.UnaryOp:

            if node.op == '!':
                return Not(self.evaluate_ast(node.expr))
            else:
                raise SemanticError('Variable evaluation not possible: '+node)

        elif typ == c_ast.BinaryOp:
            leftnode = self.evaluate_ast(node.left)
            rightnode = self.evaluate_ast(node.right) 
            
            if node.op == '&&':
                return And(leftnode, rightnode)
            elif node.op == '||':
                return Or(leftnode, rightnode)
            elif node.op == '==':
                return And(leftnode == rightnode)
            elif node.op == '<':
                return And(leftnode < rightnode)
            elif node.op == '<=':
                return And(leftnode <= rightnode)
            elif node.op == '>':
                return And(leftnode > rightnode)
            elif node.op == '>=':
                return And(leftnode >= rightnode)
            elif node.op == '!=':
                return And(leftnode != rightnode)
            elif node.op == '/':
                return leftnode / rightnode
            elif node.op == '+':
                return leftnode + rightnode

        elif typ == c_ast.Assignment and node.op == '=':
            leftnode = self.evaluate_ast(node.lvalue)
            rightnode = self.evaluate_ast(node.rvalue) 
            
            return leftnode == rightnode
        elif typ == c_ast.Constant:
            if node.type == 'int':
                return IntVal(int(node.value))
            else:
                raise SemanticError('Variable evaluation not possible: '+node)
        elif typ == c_ast.FuncCall:
            args = []
            if node.args is not None:
                for arg in ast.get_funccall_args(node):
                    smtarg = self.evaluate_ast(arg)   
                    args.append(smtarg)

            fname = ast.get_funccall_name(node)
            f = self.dict_funcname_smtfunc[fname]

            return f(*args)
        elif typ == c_ast.ID:
            return self.evaluate_variable(node.name)
        elif typ == c_ast.StructRef:
            return self.evaluate_structref(node)
        else:
            raise SemanticError('Variable evaluation not possible: '+node)

    def is_sat(self, astif : c_ast.If) -> Bool:
        
        predicate = self.evaluate_ast(astif.cond)

        assertions = []
        assertions.append(predicate)

        for var in self.var_assigments:
            assertions.append(self.var_assigments[var])
        
        return self.solver.check(assertions) == z3.sat