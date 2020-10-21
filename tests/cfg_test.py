import sys

sys.path.insert(0, '..')

from pycparser import c_parser, c_ast, parse_file, c_generator

from test_utils import *
import cast_lib
import cfg

def test_parse_simple_cfg():
    src_to_test =   """
                    int main(){
                        while(true){
                            if(true){
                                test = 1;
                            }
                            var = 0;
                            if(true){
                                test = 2;
                            }else{
                                test = 3;
                            }
                        }
                    }
                    """
        
    src_to_test_ast = parser.parse(src_to_test)
    main_ast = cast_lib.find_funcdef_node(src_to_test_ast,'main')

    codecfg = cfg.ControlFlowGraph(main_ast)

    codecfg.draw()


print("test_parse_simple_cfg")
test_parse_simple_cfg()
