import sys

sys.path.insert(0, '..')

from pycparser import c_parser, c_ast, parse_file, c_generator
import networkx as nx

from test_utils import *
import cast_lib
import cfg

def assert_degrees(codecfg, exit_in):
    for n in codecfg.nodes():
        if n != codecfg.entry and n != codecfg.exit:
            assert codecfg.degree(n) > 1
        elif n == codecfg.entry:
            assert codecfg.in_degree(n) == 0
            assert codecfg.out_degree(n) == 1
        elif n == codecfg.exit:
            assert codecfg.in_degree(n) == exit_in
            assert codecfg.out_degree(n) == 0

def test_parse_if_cfg():
    
    src_to_test =   """
                    int main(){
                        if(true){
                            test = 1;
                        }else{
                            test = 2;
                        }
                        var = 0;
                    }
                    """
        
    src_to_test_ast = parser.parse(src_to_test)
    main_ast = cast_lib.find_funcdef_node(src_to_test_ast,'main')

    codecfg = cfg.ControlFlowGraph(main_ast)

    assert len(codecfg.nodes()) == 9
    assert len(codecfg.edges()) == 9
    assert nx.is_directed_acyclic_graph(codecfg)
    assert_degrees(codecfg, 1)

def test_parse_simple_cfg():
    
    src_to_test =   """
                    int main(){
                        while(true){
                            if(true){
                                test = 2;
                            }
                            var = 0;
                        }
                    }
                    """
        
    src_to_test_ast = parser.parse(src_to_test)
    main_ast = cast_lib.find_funcdef_node(src_to_test_ast,'main')

    codecfg = cfg.ControlFlowGraph(main_ast)
    
    #codecfg.draw()

    assert len(codecfg.nodes()) == 10
    assert len(codecfg.edges()) == 11

    assert_degrees(codecfg, 1)

def test_parse_complex_cfg():
    
    src_to_test =   """
                    int main()
                    {
                        if(true){
                            test = 1;
                        }
                        var = 0;
                        if(true){
                            if(true){
                                test = 2;
                            }else{
                                test = 3;
                            }
                        }else{
                            test = 3;
                        }
                    }
                    """
        
    src_to_test_ast = parser.parse(src_to_test)
    main_ast = cast_lib.find_funcdef_node(src_to_test_ast,'main')

    codecfg = cfg.ControlFlowGraph(main_ast)

    #codecfg.draw()

    assert len(codecfg.nodes()) == 17
    assert len(codecfg.edges()) == 19
    assert nx.is_directed_acyclic_graph(codecfg)

    assert_degrees(codecfg, 3)

def test_parse_while_no_loop():
    
    src_to_test =   """
                    int main(){
                        while(true){
                            if(true){
                                test = 2;
                            }
                            var = 0;
                        }
                    }
                    """
        
    src_to_test_ast = parser.parse(src_to_test)
    main_ast = cast_lib.find_funcdef_node(src_to_test_ast,'main')

    codecfg = cfg.ControlFlowGraph(main_ast, loop=False)
    
    #codecfg.draw()

    assert len(codecfg.nodes()) == 10
    assert len(codecfg.edges()) == 11
    assert nx.is_directed_acyclic_graph(codecfg)

    assert_degrees(codecfg, 2)

print("test_parse_if_cfg")
test_parse_if_cfg()
print("test_parse_simple_cfg")
test_parse_simple_cfg()
print("test_parse_complex_cfg")
test_parse_complex_cfg()
print("test_parse_while_no_loop")
test_parse_while_no_loop()