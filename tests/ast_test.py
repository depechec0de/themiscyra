import sys

sys.path.insert(0, '..')

from pycparser import c_parser, c_ast, parse_file, c_generator
from syntaxlib import ast

parser = c_parser.CParser()

def test_get_decl_type():
    src = "int a; _Bool b; struct c {int f1; struct c* f2;}; struct c* d; enum sometype e; struct c f;"
    srcast = parser.parse(src)

    decls = srcast.ext

    intdecl = decls[0]
    booldecl = decls[1]
    structdecl = decls[2]
    ptrstructvardecl = decls[3]
    sometypedecl = decls[4]
    structvardecl = decls[5]

    assert 'int' == ast.get_decl_type(intdecl)
    assert '_Bool' == ast.get_decl_type(booldecl)
    assert 'c' == ast.get_decl_type(structdecl)
    assert 'c' == ast.get_decl_type(ptrstructvardecl)
    assert 'sometype' == ast.get_decl_type(sometypedecl)
    assert 'c' == ast.get_decl_type(structvardecl)

    structfields = ast.get_struct_fields_decl(structdecl)

    assert 'int' == structfields['f1']
    assert 'c' == structfields['f2']


test_get_decl_type()