import sys
import re

sys.path.insert(0, '..')

from pycparser import c_parser, c_ast, parse_file, c_generator
from syntaxlib import ast

parser = c_parser.CParser()

def ast_equality(ast1, ast2):
    g = c_generator.CGenerator()
    src_ast1 = g.visit(ast1)
    src_ast2 = g.visit(ast2)

    src_ast1 = re.sub(r"[\n\t\s]*", "", src_ast1)
    src_ast2 = re.sub(r"[\n\t\s]*", "", src_ast2)

    print(src_ast1)
    print(src_ast2)

    return src_ast1 == src_ast2

def test_rename_variables():
    src_to_test =   """
                    int main(){
                        if(var == 0){
                            var = 1;
                            var = 2;
                        }
                        foo = false;
                    }
                    """
    src_to_assert = """
                    int main(){
                        if(var_0_0 == 0){
                            var_0_0 = 1;
                            var_0_0 = 2;
                        }
                        foo = false;
                    }
                    """
    

    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    ast.rename_iterated_variables(src_to_test_ast, ['var'], 0, 0)

    assert ast_equality(src_to_test_ast, src_to_assert_ast)

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

def test_dce_simple():
    src_to_test =   """
                    int main(){
                        if(1==0){
                            neverexecutes();
                        }
                        if(false){
                            neverexecutes();
                        }
                        if(0>1){
                            neverexecutes();
                        }
                        int a;
                        a = 1;
                        if(a == 0){
                            neverexecutes();
                        }
                        exit(0);
                    }
                    """

    src_to_assert = """
                    int main(){
                        int a;
                        a = 1;
                        exit(0);
                    }
                    """

    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    ast.dead_code_elimination(src_to_test_ast, None)

    assert ast_equality(src_to_test_ast, src_to_assert_ast)

def test_dce_path():
    src_to_test =   """
                    int main(){
                        int a;
                        a = 1;
                        if(a == 1){
                            int b;
                            b = 2;
                            if(b == 1){
                                neverexecutes();
                            }
                            if(b == 2){
                                func();
                            }
                        }
                        if(a == 2){
                            neverexecutes();
                        }
                        exit(0);
                    }
                    """

    src_to_assert = """
                    int main(){
                        int a;
                        a = 1;
                        if(a == 1){
                            int b;
                            b = 2;
                            if(b == 2){
                                func();
                            }
                        }
                        exit(0);
                    }
                    """
    
    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    ast.dead_code_elimination(src_to_test_ast, None)
    
    assert ast_equality(src_to_test_ast, src_to_assert_ast)

test_rename_variables()
test_get_decl_type()
test_dce_simple()
test_dce_path()