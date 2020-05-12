import sys

sys.path.insert(0, '..')

from pycparser import c_parser, c_ast, parse_file, c_generator
from smt_tools import *

parser = c_parser.CParser()

#############

src = "int main(void){if(round==0 && ballot==1){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): 1, Int('round'): 0}) 
assert value == True

src = "int main(void){if(0==round && 1==ballot){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): 1, Int('round'): 0}) 
assert value == True

src = "int main(void){if(0==round){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): 1, Int('round'): 0}) 
assert value == True

src = "int main(void){if(1==round){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): 1, Int('round'): 0}) 
assert value == False

src = "int main(void){if(round==0 && (other==20 && other2==10)){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): 1, Int('round'): 0}) 
assert value == True

src = "int main(void){if((round==0 && other==10) && (other==20 && ballot==1)){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): 1, Int('round'): 0}) 
assert value == False

src = "int main(void){if(((round==0 && test==3) && other==10) && (other2==20 && (ballot==1 && test2==10))){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): 1, Int('round'): 0}) 
assert value == True

src = "int main(void){if(((round==0 && test==3) && other==10) && (other==20 && (ballot==0 && test2==10))){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): 1, Int('round'): 0}) 
assert value == False

src = "int main(void){if(func()>n && ballot==1){}}"
parser = c_parser.CParser()
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): 1, Int('round'): 0}) 
assert value == True


src = "int main(void){if(func()>n && round==COMMIT){}}"
parser = c_parser.CParser()
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred, constants={'COMMIT':0})

value = is_sat(predicate, context={Int('ballot'): 1, Int('round'): 0}) 
assert value == True

src = "int main(void){if(vround == STARTVIEWCHANGE && p==primary(view,n) && count_messages(mbox, view, STARTVIEWCHANGE, NULL, NULL) > f){}}"
parser = c_parser.CParser()
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred, constants={'STARTVIEWCHANGE':0})

value = is_sat(predicate, context={Int('view'): 0, Int('vround'): 0}) 
assert value == True

###############

src = "int main(void){int phase; phase=1;}"
parser = c_parser.CParser()
ast = parser.parse(src)

decl_node = ast.ext[0].body.block_items[1]
context = {}
add_statement_to_context(decl_node, {}, context)

assert Int('phase') in context and context[Int('phase')] == 1


src = "int main(void){enum vround_typ{ STARTVIEWCHANGE, DOVIEWCHANGE, STARTVIEW};}"
parser = c_parser.CParser()
ast = parser.parse(src)
ast.show()

