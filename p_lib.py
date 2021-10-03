import copy

from PTools.PAst import *
from pycparser import c_ast, c_generator, c_parser
import cast_lib

def p_to_upon(p_program: ProgramNode, config):

    phase_var = config['phase']
    round_var = config['round']
    mbox_var = config['mbox']
    labels = config['labels']

    program_body = []

    main_func = build_main(p_program, config)

    roles = parse_roles(p_program)

    declarations = build_declarations(roles, config)

    for decl in declarations:
        program_body.append(decl)

    program_body.append(main_func)

    upon_program = c_ast.FileAST(program_body)
 
    return upon_program

def build_upon(cond, body):
    return c_ast.If(cond, body, iffalse=None)

def build_declarations(roles, config):
    declarations = []
    declarations.append(build_struct_decl('mbox', 'list'))
    declarations.append(build_var_decl(config['phase'], 'int'))
    declarations.append(build_round_decl(config['labels']))
    declarations.append(build_var_enum_decl(config['round'], 'round_type'))
    declarations.append(build_func_decl('non_deterministic_choice', '_Bool', None))
    declarations.append(build_func_decl('broadcast', 'void', None))

    for r in roles:
        args = c_ast.ParamList(params=[build_var_decl(config['phase'], 'int')])
        declarations.append(build_func_decl(r, '_Bool', args))

    return declarations

def build_struct_decl(name, type):
    return build_decl(  name=name,
                        type=c_ast.PtrDecl(quals=[],
                                            type=c_ast.TypeDecl(declname=name, quals=[], type=c_ast.Struct(name=type, decls=None))
                                            ),
                        )

def build_var_decl(name, type):
    return build_decl(  name=name,
                        type=c_ast.TypeDecl(declname=name, quals=[],
                                            type=c_ast.IdentifierType([type])
                                            ),
                        )

def build_var_enum_decl(name, type):
    return build_decl(  name=name,
                        type=c_ast.TypeDecl(declname=name, quals=[],
                                            type=c_ast.Enum(name=type, values=None)
                                            ),
                        )

def build_func_decl(name, type, args):
    return build_decl(name=name, type=c_ast.FuncDecl(args=args, 
                                            type=c_ast.TypeDecl(declname=name, 
                                                                quals=[],
                                                                type=c_ast.IdentifierType(names=[type])
                                                                )
                                            )
                        )

def build_round_decl(rounds):
    enumerators = []
    for r in rounds:
        enumerators.append(c_ast.Enumerator(name=r, value=None))

    return build_decl(name=None, type=c_ast.Enum(name='round_type', values=c_ast.EnumeratorList(enumerators)))

def build_decl(name, type):
    return c_ast.Decl(  name=name,
                        quals=[],
                        storage=[],
                        funcspec=[],
                        type=type,
                        init=None,
                        bitsize=None
                        )

def build_main(p_program: ProgramNode, config):
    init = build_init(p_program, config)
    main_loop = build_main_loop(p_program, config)

    main_body = []
    main_body.extend(init)
    main_body.append(main_loop)
    main_body_ast = c_ast.Compound(main_body)   

    parse_non_determinism(main_body)

    return c_ast.FuncDef(
                    decl=c_ast.Decl(
                            name='main',
                            quals=[], 
                            storage=[], 
                            funcspec=[], 
                            type=c_ast.FuncDecl(args=None,
                                                type=c_ast.TypeDecl(declname='main',
                                                    quals=[],
                                                    type=c_ast.IdentifierType(names=['int'])
                                                    )), 
                        init=None, 
                        bitsize=None), 
                    param_decls=None,
                    body=main_body_ast)

def parse_roles(p_program: ProgramNode):
    v = MachineVisitor()
    v.visit(p_program)

    roles = []

    for m in v.values:
        roles.append(m.label.getText())

    return roles

def build_init(p_program: ProgramNode, config):
    v = MachineVisitor()
    v.visit(p_program)

    init = []

    for m in v.values:
        ifcond = build_role_predicate(m.label.getText(), config['phase'])
        ifbody = parse_compound(m.states['Init'].entryAction)
        replace_goto(ifbody)
        ifstmt = build_upon(ifcond, ifbody)

        init.append(ifstmt)

    return init

def build_role_predicate(role, phasevar):
    return c_ast.FuncCall(name=c_ast.ID(role), args=c_ast.ExprList(exprs=[c_ast.ID(phasevar)]))

def build_main_loop(p_program: ProgramNode, config):
    entry_code = {}

    v = MachineVisitor()
    v.visit(p_program)

    # Entry events in P are executed when the round changes in an upon program
    # We replace every goto ROUND statement with a round assignment and the entry code
    # of that round
    
    for m in v.values:
        entry_code[m.label] = {}

        for statelabel, state_event in m.states.items():
            if statelabel != 'Init':
                if len(state_event.entryAction) > 0:
                    body = parse_compound(state_event.entryAction)
                    entry_code[m.label][statelabel] = body.block_items

    upons = []
    
    # An event in a P program is an upon
    for m in v.values:
        condrole = build_role_predicate(m.label.getText(), config['phase'])

        for statelabel, state_event in m.states.items():
            if statelabel != 'Init':
                for event, eventAction in state_event.eventDoAction.items():

                    condstate = c_ast.BinaryOp('==',c_ast.ID('round'), c_ast.ID(statelabel))
                    
                    uponpredicate = c_ast.BinaryOp('&&', condrole, condstate)
                    uponbody = parse_compound(eventAction)
                    add_entry_code(uponbody, entry_code[m.label])
                    del_goto(uponbody)
                    cast_lib.remove_empty_ifs(uponbody)

                    uponbody.block_items.append(c_ast.Continue())

                    # Add predicate over the mbox
                    count_mbox = contains_count_over_mbox(uponbody, config['mbox'], statelabel)

                    if count_mbox.countpred is not None:
                        uponpredicate = c_ast.BinaryOp('&&', uponpredicate, count_mbox.countpred)
                        uponbody = count_mbox.ifmbox.iftrue
                    else:
                        uponpredicate = c_ast.BinaryOp('&&', uponpredicate, build_mbox_predicate(statelabel, 1))

                    ifstmt = build_upon(uponpredicate, uponbody)

                    upons.append(ifstmt)

    while_body = c_ast.Compound(upons)

    return c_ast.While(c_ast.ID('1'), while_body)

def contains_count_over_mbox(ast: c_ast.Node, mboxvar, round):

    class MboxCountVisitor(c_ast.NodeVisitor):
        def __init__(self, mboxvar, round):
            self.mboxvar = mboxvar
            self.round = round
            # The if executed after collecting N messages
            self.ifmbox = None
            self.countpred = None

        def visit_If(self, node):
            countpred = get_mbox_count_pred(node.cond, mboxvar, round)
            
            if countpred != None:
                self.countpred = countpred
                self.ifmbox = node

            self.generic_visit(node.iftrue)
    
    v = MboxCountVisitor(mboxvar, round)
    v.visit(ast)  

    return v

def get_mbox_count_pred(cond, mboxvar, round):
    if type(cond) == c_ast.BinaryOp and (cond.op == '==' or cond.op == '<=' or cond.op == '>='):
        fun = None
        count = None
        
        if type(cond.left) == c_ast.UnaryOp and type(cond.right) == c_ast.ID:
            fun = cond.left
            count = cond.right
            
        elif type(cond.right) == c_ast.UnaryOp and type(cond.left) == c_ast.ID:
            fun = cond.right
            count = cond.left

        if fun == None:
            return None
        
        if fun.op == 'sizeof' and reads_mbox(fun, mboxvar):
            return build_mbox_predicate(round, count.name)
        else:
            return None
    else:
        return None

def reads_mbox(ast, mboxvar):
    class IDVisitor(c_ast.NodeVisitor):
        def __init__(self, mboxvar):
            self.result = False
            self.mboxvar = mboxvar

        def visit_ID(self, node):           
            if node.name == mboxvar:
                self.result = True
    
    v = IDVisitor(mboxvar)
    v.visit(ast)  

    return v.result

def build_mbox_predicate(round, number):
    return c_ast.BinaryOp(  '==',
                            c_ast.FuncCall(  name=c_ast.ID('count'), 
                                                args=c_ast.ExprList(exprs=[ c_ast.ID('phase'), 
                                                                            c_ast.ID(round),
                                                                            c_ast.ID('mbox')])), 
                            c_ast.Constant('int',str(number)))

def parse_compound(statements):
    body = []

    for stm in statements:
        stm_ast = str_to_ast(str(stm))
        body.append(stm_ast)

    return c_ast.Compound(body)

def add_entry_code(ast, entry_code_dict):
    class AddEntryCodeVisitor(c_ast.NodeVisitor):

        def visit_Compound(self, node):
            new_block_items = copy.deepcopy(node.block_items)
            for i in range(0,len(node.block_items)):
                n = node.block_items[i]

                if type(n) == c_ast.ID and n.name.startswith('goto'):
                    round = n.name.replace('goto','')
                    roundAssignment = c_ast.Assignment('=', c_ast.ID('round'), c_ast.ID(round))
                    new_block_items.insert(i, roundAssignment)

                    if round in entry_code_dict:
                        for n_entry in entry_code_dict[round]:
                            if not(type(n_entry) == c_ast.ID and n.name.startswith('goto')):
                                new_block_items.append(n_entry)
                            else:
                                round_entry = n_entry.name.replace('goto','')
                                roundAssignment_entry = c_ast.Assignment('=', c_ast.ID('round'), c_ast.ID(round_entry))
                                new_block_items.append(roundAssignment_entry)

            node.block_items = new_block_items

            for n in node.block_items:
                self.generic_visit(n)

    v = AddEntryCodeVisitor()
    v.visit(ast)

def del_goto(ast):
    class RemoveGotoCodeVisitor(c_ast.NodeVisitor):

        def visit_Compound(self, node):
            new_block_items = copy.deepcopy(node.block_items)
            for i in range(0,len(node.block_items)):
                n = node.block_items[i]

                if type(n) == c_ast.ID and n.name.startswith('goto'):
                    del new_block_items[i]

            node.block_items = new_block_items

            for n in node.block_items:
                self.generic_visit(n)

    v = RemoveGotoCodeVisitor()
    v.visit(ast)

def replace_goto(ast):
    class ReplaceGotoCodeVisitor(c_ast.NodeVisitor):

        def visit_Compound(self, node):
            new_block_items = copy.deepcopy(node.block_items)
            for i in range(0,len(node.block_items)):
                n = node.block_items[i]

                if type(n) == c_ast.ID and n.name.startswith('goto'):
                    del new_block_items[i]
                    round_entry = n.name.replace('goto','')
                    roundAssignment_entry = c_ast.Assignment('=', c_ast.ID('round'), c_ast.ID(round_entry))
                    new_block_items.append(roundAssignment_entry)

            node.block_items = new_block_items

            for n in node.block_items:
                self.generic_visit(n)

    v = ReplaceGotoCodeVisitor()
    v.visit(ast)

def parse_non_determinism(ast):
    class NonDeterminismVisitor(c_ast.NodeVisitor):

        def visit_If(self, node):
            if type(node.cond) == c_ast.ID and node.cond.name == '$':
                node.cond = c_ast.FuncCall(c_ast.ID('non_deterministic_choice'), args=None)

            self.generic_visit(node.iftrue)

            if node.iffalse is not None:
                self.generic_visit(node.iffalse)

    v = NonDeterminismVisitor()
    v.visit(ast)

def str_to_ast(stm):
    text = "int main(){" + stm +" }"

    parser = c_parser.CParser()
    ast = parser.parse(text, filename='<none>')

    return ast.ext[0].body.block_items[0]

class MachineVisitor(PNodeVisitor):
    def __init__(self):
        self.values = []

    def visit_MachineNode(self, node : MachineNode):
        self.values.append(node)