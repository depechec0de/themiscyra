import sys

sys.path.insert(0, '..')

from athos import *
from test_utils import *

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

print("test_compho_send")
test_compho_send()