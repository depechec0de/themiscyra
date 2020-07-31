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

    rename_iterated_variables(src_to_test_ast, ['var'], 0)

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

    unfold(src_to_test_ast, 1, {'round':'round', 'mbox':'mbox'})
    
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

    unfold(src_to_test_ast, 2, {'round':'round', 'mbox':'mbox'})
    
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

    get_compho_send(src_to_test_ast)

    assert_ast_equality(src_to_test_ast, src_to_assert_ast)

print("test_rename_variables")
test_rename_variables()
print("test_get_decl_type")
test_get_decl_type()
print("test_unfolding_simple")
test_unfolding_simple()
print("test_unfolding")
test_unfolding()
print("test_compho_send")
test_compho_send()