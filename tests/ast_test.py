import sys
import re

sys.path.insert(0, '..')

from pycparser import c_parser, c_ast, parse_file, c_generator
from syntaxlib import ast

parser = c_parser.CParser()

def assert_ast_equality(ast_to_test, ast_expected):
    g = c_generator.CGenerator()
    src_ast_expected = g.visit(ast_expected)
    src_ast_to_test = g.visit(ast_to_test)

    src_ast_expected_clean = re.sub(r"[\n\t\s]*", "", src_ast_expected)
    src_ast_to_test_clean = re.sub(r"[\n\t\s]*", "", src_ast_to_test)

    try:
        assert src_ast_expected_clean == src_ast_to_test_clean
    except AssertionError:
        print()
        print("AssertionError")
        print()
        print("Expected")
        print(src_ast_expected)
        print("Obtained")
        print(src_ast_to_test)
        print()

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
                        if(var_0 == 0){
                            var_0 = 1;
                            var_0 = 2;
                        }
                        foo = false;
                    }
                    """
    

    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    ast.rename_iterated_variables(src_to_test_ast, ['var'], 0)

    assert_ast_equality(src_to_test_ast, src_to_assert_ast)

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

    assert_ast_equality(src_to_test_ast, src_to_assert_ast)

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
    
    assert_ast_equality(src_to_test_ast, src_to_assert_ast)

def test_dce_func():
    src_to_test =   """
                    int main(){
                        int p;
                        p = 2;
                        _Bool func(int p);
                        if(!func(p)){
                            if(func(p)){
                                neverexecutes();
                            }
                            if(!func(p) && p == 2){
                                test();
                            }
                        }
                    }
                    """

    src_to_assert = """
                    int main(){
                        int p;
                        p = 2;
                        _Bool func(int p);
                        if(!func(p)){
                            if(!func(p) && p == 2){
                                test();
                            }
                        }
                    }
                    """

    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    ast.dead_code_elimination(src_to_test_ast, None)

    assert_ast_equality(src_to_test_ast, src_to_assert_ast)

def test_unfolding_simple():
    src_to_test =   """
int main(){
    while(1){
        mbox = havoc(phase, round);
        if(round==1){
            round=3;
            continue;
        }
        if(round==2){
            round=4;
            continue;
        }
    }
}
"""

    src_to_assert = """
int main()
{
    while(1){
        mbox = havoc(phase, round);
        if(round==1){
            round_0=3;

            mbox_0 = havoc(phase, round_0);
            if(round_0==1){
                round_1=3;
                continue;
            }
            if(round_0==2){
                round_1=4;
                continue;
            }
            continue;
        }
        if(round==2){
            round_0=4;

            mbox_0 = havoc(phase, round_0);
            if(round_0==1){
                round_1=3;
                continue;
            }
            if(round_0==2){
                round_1=4;
                continue;
            }
            continue;
        }
    }
}
"""
    
    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    ast.unfold(src_to_test_ast, 1, {'round':'round', 'mbox':'mbox'})
    
    assert_ast_equality(src_to_test_ast, src_to_assert_ast)

def test_unfolding():
    src_to_test =   """
int main(){
    while(1){
        mbox = havoc(phase, round);
        if(round == 1){
            round = 2;
            func1(phase, round, mbox);
            round = 3;
            continue;
        }
        if(round == 2){
            round = 4;
            func2(phase, round, mbox);
            round = 5;
            continue;
        }
    }
}
"""

    src_to_assert = """
int main()
{
    while (1)
    {
        mbox = havoc(phase, round);
        if (round == 1)
        {
            round_0 = 2;
            func1(phase, round_0, mbox);
            round_0 = 3;
            mbox_0 = havoc(phase, round_0);
            if (round_0 == 1)
            {
                round_1 = 2;
                func1(phase, round_1, mbox_0);
                round_1 = 3;
                mbox_1 = havoc(phase, round_1);
                if (round_1 == 1)
                {
                    round_2 = 2;
                    func1(phase, round_2, mbox_1);
                    round_2 = 3;
                    continue;
                }

                if (round_1 == 2)
                {
                    round_2 = 4;
                    func2(phase, round_2, mbox_1);
                    round_2 = 5;
                    continue;
                }

                continue;
            }

            if (round_0 == 2)
            {
                round_1 = 4;
                func2(phase, round_1, mbox_0);
                round_1 = 5;
                mbox_1 = havoc(phase, round_1);
                if (round_1 == 1)
                {
                    round_2 = 2;
                    func1(phase, round_2, mbox_1);
                    round_2 = 3;
                    continue;
                }

                if (round_1 == 2)
                {
                    round_2 = 4;
                    func2(phase, round_2, mbox_1);
                    round_2 = 5;
                    continue;
                }

                continue;
            }

            continue;
        }

        if (round == 2)
        {
            round_0 = 4;
            func2(phase, round_0, mbox);
            round_0 = 5;
            mbox_0 = havoc(phase, round_0);
            if (round_0 == 1)
            {
                round_1 = 2;
                func1(phase, round_1, mbox_0);
                round_1 = 3;
                mbox_1 = havoc(phase, round_1);
                if (round_1 == 1)
                {
                    round_2 = 2;
                    func1(phase, round_2, mbox_1);
                    round_2 = 3;
                    continue;
                }

                if (round_1 == 2)
                {
                    round_2 = 4;
                    func2(phase, round_2, mbox_1);
                    round_2 = 5;
                    continue;
                }

                continue;
            }

            if (round_0 == 2)
            {
                round_1 = 4;
                func2(phase, round_1, mbox_0);
                round_1 = 5;
                mbox_1 = havoc(phase, round_1);
                if (round_1 == 1)
                {
                    round_2 = 2;
                    func1(phase, round_2, mbox_1);
                    round_2 = 3;
                    continue;
                }

                if (round_1 == 2)
                {
                    round_2 = 4;
                    func2(phase, round_2, mbox_1);
                    round_2 = 5;
                    continue;
                }

                continue;
            }

            continue;
        }
    }
}
"""
    
    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    ast.unfold(src_to_test_ast, 2, {'round':'round', 'mbox':'mbox'})
    
    assert_ast_equality(src_to_test_ast, src_to_assert_ast)

def test_compho_send():
    src_to_test =   """
                    int main(){
                        send();
                        if(round==0){
                            int a = 2;
                            func();
                            send();
                            if(a == 2){
                                send();
                            }
                            bar();
                        }
                        test();
                    }
                    """

    src_to_assert = """
                    int main(){
                        send();
                        if(round==0){
                            send();
                            if(a == 2){
                                send();
                            }
                        }
                    }
                    """

    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    ast.get_compho_send(src_to_test_ast)

    assert_ast_equality(src_to_test_ast, src_to_assert_ast)

print("test_rename_variables")
test_rename_variables()
print("test_get_decl_type")
test_get_decl_type()
print("test_dce_simple")
test_dce_simple()
print("test_dce_path")
test_dce_path()
print("test_dce_func")
test_dce_func()
print("test_unfolding_simple")
test_unfolding_simple()
print("test_unfolding")
test_unfolding()
print("test_compho_send")
test_compho_send()