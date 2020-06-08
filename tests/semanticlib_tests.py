import sys

sys.path.insert(0, '..')

from pycparser import c_parser, c_ast, parse_file, c_generator
from semanticlib import *

parser = c_parser.CParser()

RoundsSort, (STARTVIEWCHANGE, DOVIEWCHANGE, STARTVIEW) = EnumSort('rounds', ['STARTVIEWCHANGE','DOVIEWCHANGE','STARTVIEW'])

round = Const('round', RoundsSort)

#############

src = "int main(void){if(round==0 && ballot==1){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): Int('ballot') == 1, Int('round'): Int('round') == 0}) 
assert value == True

src = "int main(void){if(0==round && 1==ballot){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): Int('ballot') == 1, Int('round'): Int('round') == 0}) 
assert value == True

src = "int main(void){if(0==round){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): Int('ballot') == 1, Int('round'): Int('round') == 0}) 
assert value == True

src = "int main(void){if(1==round){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): Int('ballot') == 1, Int('round'): Int('round') == 0}) 
assert value == False

src = "int main(void){if(round==0 && (other==20 && other2==10)){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): Int('ballot') == 1, Int('round'): Int('round') == 0}) 
assert value == True

src = "int main(void){if((round==0 && other==10) && (other==20 && ballot==1)){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): Int('ballot') == 1, Int('round'): Int('round') == 0}) 
assert value == False

src = "int main(void){if(((round==0 && test==3) && other==10) && (other2==20 && (ballot==1 && test2==10))){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): Int('ballot') == 1, Int('round'): Int('round') == 0}) 
assert value == True

src = "int main(void){if(((round==0 && test==3) && other==10) && (other==20 && (ballot==0 && test2==10))){}}"
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): Int('ballot') == 1, Int('round'): Int('round') == 0}) 
assert value == False

src = "int main(void){if(func(a,b,c)>n && ballot==1){}}"
parser = c_parser.CParser()
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): Int('ballot') == 1, Int('round'): Int('round') == 0}) 
assert value == True

src = "int main(void){if(func()>n && round==DOVIEWCHANGE){}}"
parser = c_parser.CParser()
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={Int('ballot'): Int('ballot') == 1, 'round': round == DOVIEWCHANGE}) 
assert value == True

src = "int main(void){if(round==STARTVIEWCHANGE){}}"
parser = c_parser.CParser()
ast = parser.parse(src)
ast_pred = ast.ext[0].body.block_items[0].cond
predicate = ast_to_smt(ast_pred)

value = is_sat(predicate, context={'round': round == STARTVIEWCHANGE}) 
assert value == True

