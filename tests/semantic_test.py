import sys

sys.path.insert(0, '..')

from semantic_lib import *
from cast_lib import *
from test_utils import *
import cfg

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

def test_dce_var_func():
    src_to_test =   """
                    int main()
                    {
                        int round;
                        int view;
                        view = 0;
                        round = 1;
                        while (1)
                        {

                            if ((round == 1))
                            {
                            round = 2;
                            
                            if (round == 2)
                            {
                                view++;
                                round = 1;
                                continue;
                            }

                            break;
                            }

                        }

                    }

                    """

    src_to_assert = src_to_test

    src_to_assert_ast = parser.parse(src_to_assert)
    src_to_test_ast = parser.parse(src_to_test)

    dead_code_elimination(src_to_test_ast, None)

    assert_ast_equality(src_to_test_ast, src_to_assert_ast)

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

def path_to_formula(src, theory):

    src1_path_ast = parser.parse(cast_lib.remove_c99_comments(src))
    main_ast = cast_lib.find_funcdef_node(src1_path_ast,'main')
    srccfg = cfg.ControlFlowGraph(main_ast)

    path = list(srccfg.paths())[0]
    phi = PhaseFormula(theory, path)

    return phi

def test_path_formula_distinct():

    decl = "int a;"

    src1 = "int main(){a = 1;}"
    src2 = "int main(){a = 2;}"

    decl_ast = parser.parse(decl)
    theory = C99Theory(decl_ast)
    
    phi1 = path_to_formula(src1, theory)
    phi2 = path_to_formula(src2, theory)

    #z3.prove(phi1.formula == phi2.formula)

    assert(phi1 != phi2)

def test_path_formula_history():

    decl = "int a;"

    src1 = "int main(){a = 1; a = 2;}"
    src2 = "int main(){a = 1; a = 3;}"

    decl_ast = parser.parse(decl)
    theory = C99Theory(decl_ast)
    
    phi1 = path_to_formula(src1, theory)
    phi2 = path_to_formula(src2, theory)

    #z3.prove(phi1.formula == phi2.formula)

    assert(phi1 != phi2)    

def test_path_formula_dependencies():

    decl = "int a; int b;"

    src1 = "int main(){a = 1; b = a+1;}"
    src2 = "int main(){a = 1; b = 2;}"

    decl_ast = parser.parse(decl)
    theory = C99Theory(decl_ast)
    
    phi1 = path_to_formula(src1, theory)
    phi2 = path_to_formula(src2, theory)

    #z3.prove(phi1.formula == phi2.formula)

    assert(phi1 == phi2)

def test_path_formula_asserts():

    decl = "int a; int b; int c;"

    src1 = "int main(){a = 1; (c > 100 && a == 1); b = a+1;}"
    src2 = "int main(){a = 1; (c > 100 && a > 0); b = 2;}"

    decl_ast = parser.parse(decl)
    theory = C99Theory(decl_ast)

    phi1 = path_to_formula(src1, theory)
    phi2 = path_to_formula(src2, theory)

    #z3.prove(phi1.formula == phi2.formula)

    assert(phi1 == phi2)
    
def test_cfg_abstract_paths():

    decl = """
            enum round_label {FIRST_ROUND, SECOND_ROUND};

            int n;
            int p;
            enum round_label r;
            _Bool func1(int);
            _Bool func2(int, enum round_label);
            int mbox(int, enum round_label);
            """

    src1 =   """ int main(){
                    p = 0;
                    func1(p);
                    r = FIRST_ROUND;
                    r = SECOND_ROUND;
                    r == SECOND_ROUND && (mbox(p, r) > (2*n)/3);
                    func2(p, r);
                    p = p + 1; 
                }       
            """
    src2 =   """ int main(){
                    p = 0;
                    r = FIRST_ROUND;
                    func1(p);
                    r = SECOND_ROUND;
                    r == SECOND_ROUND && (mbox(p, r) > (2*n)/3);
                    func2(p, r);
                    p = p + 1;
                }
            """

    decl_ast = parser.parse(decl)
    theory = C99Theory(decl_ast)

    phi1 = path_to_formula(src1, theory)
    phi2 = path_to_formula(src2, theory)
    
    assert(phi1 == phi2)

print("test_evaluate_ast")
test_evaluate_ast()
print("test_struct_dereference")
test_struct_dereference()
print("test_struct_dereference_complex")
test_struct_dereference_complex()
print("test_struct_dereference_enum")
test_struct_dereference_enum()
print("test_dce_var_func")
test_dce_var_func()
print("test_dce_simple")
test_dce_simple()
print("test_dce_path")
test_dce_path()
print("test_dce_nested_info")
test_dce_nested_info()
print("test_path_formula_distinct")
test_path_formula_distinct()
print("test_path_formula_history")
test_path_formula_history()
print("test_path_formula_dependencies")
test_path_formula_dependencies()
print("test_path_formula_asserts")
test_path_formula_asserts()
print("test_cfg_abstract_paths")
test_cfg_abstract_paths()