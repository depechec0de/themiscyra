import sys

sys.path.insert(0, '..')

from pycparser import c_parser, c_ast, parse_file, c_generator
from syntaxlib import ast
from semanticlib.c99theory import *

parser = c_parser.CParser()

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

test_evaluate_ast()
test_struct_dereference()
test_struct_dereference_complex()
test_struct_dereference_enum()