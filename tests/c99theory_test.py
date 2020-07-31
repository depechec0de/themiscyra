import sys

sys.path.insert(0, '..')

from c99theory import *
from test_utils import *

def test_evaluate_ast():
    src = "main(){if(false){}}"
    srcast = parser.parse(src)

    t = C99Theory(srcast)

    boolstm = srcast.ext[0].body.block_items[0].cond

    evaluation = t.evaluate_ast(boolstm)
    
    assert evaluation == False

def test_struct_dereference():
    src = """
    struct A {
        struct A* next;
        int val;
    };

    struct A* var;
    """

    srcast = parser.parse(src)
    t = C99Theory(srcast)

    evalstruct_ast = parser.parse("main(){if(var->val){}}")
    evalstruct = t.evaluate_ast(evalstruct_ast.ext[0].body.block_items[0].cond)

    assert evalstruct.sort() == IntSort()

def test_struct_dereference_complex():
    src = """
    struct A {
        struct A* nextA;
        struct B* nextB;
        int val;
    };
    struct B {
        struct A* nextA;
        struct B* nextB;
        _Bool val;
    };

    struct A* var;
    """

    srcast = parser.parse(src)
    t = C99Theory(srcast)

    evalstruct_ast = parser.parse("main(){if(var->nextA->nextA->nextB->nextB->nextA->val){}}")
    evalstruct = t.evaluate_ast(evalstruct_ast.ext[0].body.block_items[0].cond)

    assert evalstruct.sort() == IntSort()

def test_struct_dereference_enum():
    src = """
    struct msg {
        int phase;
        _Bool decided;
        enum round_typ round;
        struct msg* next;
    };
    enum round_typ {FIRST_ROUND, SECOND_ROUND, THIRD_ROUND, FOURTH_ROUND};
    int a;
    struct msg* m;
    struct msg* m2;
    int func(int a, _Bool b);
    """

    srcast = parser.parse(src)

    t = C99Theory(srcast)

    evalstruct_ast = parser.parse("main(){if(m->next->next->next->round){}}")
    evalstruct = t.evaluate_ast(evalstruct_ast.ext[0].body.block_items[0].cond)

    assert evalstruct.sort() == t.dict_enumtype_smtsort['round_typ']

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

    dead_code_elimination(src_to_test_ast, None)

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
                                int c;
                                c = 3;
                                if(c == 0){
                                    neverexecutes();
                                }
                                if(c == 3){
                                    func();
                                }
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
                                int c;
                                c = 3;
                                if(c == 3){
                                    func();
                                }
                            }
                        }
                        exit(0);
                    }
                    """
    
    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    dead_code_elimination(src_to_test_ast, None)
    
    assert_ast_equality(src_to_test_ast, src_to_assert_ast)

def test_dce_nested_info():
    src_to_test =   """
                    int main(){
                        int a;
                        int a_0;
                        a = 1;
                        if(a == 1){
                            a_0 = 2;
                            if(a_0 == 2){
                                a = 3;
                            }
                            if(a_0 == 1){
                                a = 2;
                            }
                        }
                    }
                    """

    src_to_assert = """
                    int main(){
                        int a;
                        int a_0;
                        a = 1;
                        if(a == 1){
                            a_0 = 2;
                            if(a_0 == 2){
                                a = 3;
                            }
                        }
                    }
                    """
    
    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    dead_code_elimination(src_to_test_ast, None)
    
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

    dead_code_elimination(src_to_test_ast, None)

    assert_ast_equality(src_to_test_ast, src_to_assert_ast)

print("test_evaluate_ast")
test_evaluate_ast()
print("test_struct_dereference")
test_struct_dereference()
print("test_struct_dereference_complex")
test_struct_dereference_complex()
print("test_struct_dereference_enum")
test_struct_dereference_enum()
print("test_dce_simple")
test_dce_simple()
print("test_dce_path")
test_dce_path()
print("test_dce_nested_info")
test_dce_nested_info()
print("test_dce_func")
test_dce_func()