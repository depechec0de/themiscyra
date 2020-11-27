import sys

sys.path.insert(0, '..')

from cast_lib import *
from test_utils import *

def test_rename_variables():
    src_to_test =   """
                    int main(){
                        if(var == 0){
                            var = 1;
                            var = 2;
                            foo = func(var, test);
                            bar = var + 2;
                            foo = func(func(1,2,exec(var)), test);
                            var = var;
                        }
                        foo = false;
                    }
                    """
    src_to_assert = """
                    int main(){
                        if(var__0 == 0){
                            var__0 = 1;
                            var__0 = 2;
                            foo = func(var__0, test);
                            bar = var__0 + 2;
                            foo = func(func(1,2,exec(var__0)), test);
                            var__0 = var__0;
                        }
                        foo = false;
                    }
                    """
    
    
    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)
    dict_rename = {'var': 'var__0'}
    rename_variable(src_to_test_ast, dict_rename)

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

    assert 'int' == get_decl_type(intdecl)
    assert '_Bool' == get_decl_type(booldecl)
    assert 'c' == get_decl_type(structdecl)
    assert 'c' == get_decl_type(ptrstructvardecl)
    assert 'sometype' == get_decl_type(sometypedecl)
    assert 'c' == get_decl_type(structvardecl)

    structfields = get_struct_fields_decl(structdecl)

    assert 'int' == structfields['f1']
    assert 'c' == structfields['f2']

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
            round=3;
            mbox = havoc(phase, round);
            if(round==1){
                round=3;
                continue;
            }
            if(round==2){
                round=4;
                continue;
            }
            break;
        }
        if(round==2){
            round=4;
            mbox = havoc(phase, round);
            if(round==1){
                round=3;
                continue;
            }
            if(round==2){
                round=4;
                continue;
            }
            break;
        }
    }
}
"""
    
    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    unfold(src_to_test_ast, 1)
    
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
            round = 2;
            func1(phase, round, mbox);
            round = 3;
            mbox = havoc(phase, round);
            if (round == 1)
            {
                round = 2;
                func1(phase, round, mbox);
                round = 3;
                mbox = havoc(phase, round);
                if (round == 1)
                {
                    round = 2;
                    func1(phase, round, mbox);
                    round = 3;
                    continue;
                }

                if (round == 2)
                {
                    round = 4;
                    func2(phase, round, mbox);
                    round = 5;
                    continue;
                }
                break;
            }

            if (round == 2)
            {
                round = 4;
                func2(phase, round, mbox);
                round = 5;
                mbox = havoc(phase, round);
                if (round == 1)
                {
                    round = 2;
                    func1(phase, round, mbox);
                    round = 3;
                    continue;
                }

                if (round == 2)
                {
                    round = 4;
                    func2(phase, round, mbox);
                    round = 5;
                    continue;
                }
                break;
            }
            break;
        }

        if (round == 2)
        {
            round = 4;
            func2(phase, round, mbox);
            round = 5;
            mbox = havoc(phase, round);
            if (round == 1)
            {
                round = 2;
                func1(phase, round, mbox);
                round = 3;
                mbox = havoc(phase, round);
                if (round == 1)
                {
                    round = 2;
                    func1(phase, round, mbox);
                    round = 3;
                    continue;
                }

                if (round == 2)
                {
                    round = 4;
                    func2(phase, round, mbox);
                    round = 5;
                    continue;
                }
                break;
            }

            if (round == 2)
            {
                round = 4;
                func2(phase, round, mbox);
                round = 5;
                mbox = havoc(phase, round);
                if (round == 1)
                {
                    round = 2;
                    func1(phase, round, mbox);
                    round = 3;
                    continue;
                }

                if (round == 2)
                {
                    round = 4;
                    func2(phase, round, mbox);
                    round = 5;
                    continue;
                }
                break;
            }
            break;
        }
    }
}
"""
    
    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    unfold(src_to_test_ast, 2)
    
    assert_ast_equality(src_to_test_ast, src_to_assert_ast)


print("test_rename_variables")
test_rename_variables()
print("test_get_decl_type")
test_get_decl_type()
print("test_unfolding_simple")
test_unfolding_simple()
print("test_unfolding")
test_unfolding()