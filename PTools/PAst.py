import sys

from antlr4 import *
from PTools.PLexer import PLexer
from PTools.PParser import PParser
from PTools.PParserVisitor import PParserVisitor

class PNode:  
    def show(self):
        lines = [self.__class__.__name__ + ':']
        for key, val in vars(self).items():
            lines += '{}: {}'.format(key, val).split('\n')
        return '\n    '.join(lines)

class ParentNode(PNode):
    def __init__(self, elements):
        self.elements = elements

    def __iter__(self):
        for el in (self.elements or []):
            yield el

    def __repr__(self):
        return str(self.elements)

class StateNode(ParentNode):
    def __init__(self, label, elements):
        super().__init__(elements)
        self.label = label
        self.eventDoAction = {}
        self.entryAction = []
        self.exitAction = []

        for e in elements:
            if type(e) == StateEntryNode:
                self.entryAction.extend(e.elements)
            elif type(e) == StateExitNode:
                self.exitAction.extend(e.elements)
            else:
                for event in e.events:
                    self.eventDoAction[event] = e.elements

    def __iter__(self):
        if self.label is not None:
            yield self.label
        if self.elements is not None:
            yield self.elements

    def __repr__(self):
        return str(self.label) + ':' + str(self.elements)

class IfStmtNode(PNode):
    def __init__(self, expresion, thenBranch : PParser.StatementContext, elseBranch : PParser.StatementContext = None):
        self.expresion = expresion
        self.thenBranch = thenBranch
        self.elseBranch = elseBranch

    def __repr__(self):
        strrepr = 'if (' + str(self.expresion) + '){' + str(self.thenBranch) + '}'
        if self.elseBranch is not None:
            strrepr += 'else{' + str(self.elseBranch) + '}'
        return strrepr

    def __iter__(self):
        yield self.expresion
        yield self.thenBranch
        if self.elseBranch is not None:
            yield self.elseBranch

class CompoundNode(ParentNode):
    def __init__(self, elements):
        super().__init__(elements)

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        repr = ''
        for e in (self.elements or []):
            repr = repr+str(e);
        return repr

class LeafNode(PNode):
    def __init__(self, content):
        self.content = content

    def __repr__(self):
        return self.__str__()

    def __str__(self):
        return str(self.content)

    def __iter__(self):
        return
        yield

class IdenNode(LeafNode):
    def __init__(self, name):
        super().__init__(name)

    def __repr__(self):
        return self.content

    def __str__(self):
        return self.content

class VarDeclNode(LeafNode):
    def __init__(self, idenList, r_type):
        self.idenList = idenList
        self.r_type = r_type

    def __repr__(self):
        return str(self.idenList.getText()) + ' : ' + str(self.r_type.getText())

class ProgramNode(ParentNode):
    def __init__(self, elements):
        super().__init__(elements)

class FunctionDeclNode(PNode):
    def __init__(self, name, params, type, body):
        self.name = name
        self.params = params
        self.type = type
        self.body = body

    def __iter__(self):
        yield self.name
        yield self.params
        if self.type is not None:
            yield self.type
        yield self.body

    def __str__(self):
        return str(self.name) + ' : ' + str(self.params)

    def __repr__(self):
        return self.__str__()
        

class MachineNode(ParentNode):
    def __init__(self, label: IdenNode, machineentries):
        super().__init__(machineentries)
        self.label = label
        self.states = dict()
        self.fundecl = []

        for e in machineentries:
            if type(e) == StateNode:
                self.states[str(e.label)] = e
            elif type(e) == FunctionDeclNode:
                self.fundecl.append(e)

    def states(self):
        return self.states

    def __iter__(self):
        if self.label is not None:
            yield self.label
        if self.elements is not None:
            yield self.elements

    def __str__(self):
        return str(self.label) + ': states: ' + str(self.states) + ' fundecls: ' + str(self.fundecl)

    def __repr__(self):
        return self.__str__()

class StateEntryNode(ParentNode):
    def __init__(self, elements):
        super().__init__(elements)

    def __str__(self):
        return 'entry :' + str(self.elements)

    def __repr__(self):
        return self.__str__()    

class StateExitNode(ParentNode):
    def __init__(self, elements):
        super().__init__(elements)

    def __str__(self):
        return 'exit :' + str(self.elements)

    def __repr__(self):
        return self.__str__() 

class StateEventNode(ParentNode):
    def __init__(self, events, elements):
        super().__init__(elements)
        self.events = events

    def __repr__(self):
        return self.__str__() 

    def __str__(self):
        return 'on event "'+ str(self.events) +'" :' + str(self.elements)

class BuildAstVisitor(PParserVisitor):

    def visitProgram(self, ctx:PParser.ProgramContext):
        body = self._visitCompoundStatement(ctx.topDecl())

        return ProgramNode(body)

    def visitStateDecl(self, ctx:PParser.StateDeclContext):
        body = self._visitCompoundStatement(ctx.stateBodyItem())
        label = ctx.iden().getText()

        return StateNode(IdenNode(label), body)

    # def visitTopDecl(self, ctx:PParser.TopDeclContext):
    #     if(ctx.typeDefDecl() is not None):
    #         print(ctx.typeDefDecl().getText())
    #     else:
    #         self.visit(ctx)

    def visitPFunDecl(self, ctx:PParser.PFunDeclContext):
        params = []

        for e in ctx.funParamList().funParam():
            fp = (e.iden().getText(), e.r_type().getText())
            params.append(fp)

        ftype = None
        if ctx.r_type() is not None:
            ftype = ctx.r_type().getText()

        return FunctionDeclNode(IdenNode(ctx.iden().getText()), params, ftype, ctx.functionBody().getText())

    def visitCompoundStmt(self, ctx:PParser.CompoundStmtContext):
        return self._visitCompoundStatement(ctx.statement())

    def visitStateEntry(self, ctx:PParser.StateEntryContext):
        return StateEntryNode(self.visit(ctx.anonEventHandler()))

    def visitStateExit(self, ctx:PParser.StateExitContext):
        return StateExitNode(self.visit(ctx.noParamAnonEventHandler()))

    def visitOnEventDoAction(self, ctx:PParser.OnEventDoActionContext):
        return StateEventNode(ctx.eventList().getText().split(','), self.visit(ctx.anonEventHandler()))

    def visitAnonEventHandler(self, ctx:PParser.AnonEventHandlerContext):
        return self.visit(ctx.functionBody())

    def visitMachineBody(self, ctx:PParser.MachineBodyContext):
        return self._visitCompoundStatement(ctx.machineEntry())  

    def visitFunctionBody(self, ctx:PParser.FunctionBodyContext):
        return self._visitCompoundStatement(ctx.statement())

    def visitVarDecl(self, ctx:PParser.VarDeclContext):
        return VarDeclNode(ctx.idenList(), ctx.r_type())

    def visitIfStmt(self, ctx:PParser.IfStmtContext):
        thenBranch = CompoundNode(self.visit(ctx.thenBranch))
        elseBranch = None
        if ctx.elseBranch is not None:
            elseBranch = CompoundNode(self.visit(ctx.elseBranch))

        return IfStmtNode(LeafNode(ctx.expr().getText()), thenBranch, elseBranch)
    
    def visitReceiveStmt(self, ctx:PParser.ReceiveStmtContext):
        return None

    def visitImplMachineDecl(self, ctx:PParser.ImplMachineDeclContext):
        
        label = ctx.iden().getText()
        machineentries = self.visit(ctx.machineBody())

        m = MachineNode(IdenNode(label), machineentries)

        return m

    def _visitCompoundStatement(self, statement):
        body = []
        
        for el in statement:
            if el.__class__ == PParser.IfStmtContext:
                n = self.visit(el)  
            elif el.__class__ == PParser.AnnounceStmtContext:
                n = None
            elif el.__class__ == PParser.ReceiveStmtContext:
                n = self.visit(el)
            elif el.__class__ == PParser.SendStmtContext:
                params = []
                for e in el.expr():
                    params.append(e.getText())

                n = LeafNode('send(' + ','.join(params) + ');')
            elif issubclass(el.__class__, PParser.StatementContext):
                n = LeafNode(el.getText())
            else:
                n = self.visit(el)

            if n is not None:
                body.append(n)
                
        return body

class PNodeVisitor:

    _method_cache = None

    """ A base ParentNodeVisitor class for visiting P AST nodes.
        Subclass it and define your own visit_XXX methods, where
        XXX is the class name you want to visit with these
        methods.

        For example:

        class MachineVisitor(ParentNodeVisitor):
            def __init__(self):
                self.values = []

            def visit_ImplMachineDecl(self, node):
                self.values.append(node.value)

        Creates a list of values of all the machine nodes
        encountered below the given node. To use it:

        cv = MachineVisitor()
        cv.visit(node)

        Notes:

        *   generic_visit() will be called for AST nodes for which
            no visit_XXX method was defined.
        *   The children of nodes for which a visit_XXX was
            defined will not be visited - if you need this, call
            generic_visit() on the node.
            You can use:
                NodeVisitor.generic_visit(self, node)
        *   Modeled after Python's own AST visiting facilities
            (the ast module of Python 3.0)
    """
    def visit(self, node):
        """ Visit a node.
        """

        if self._method_cache is None:
            self._method_cache = {}

        visitor = self._method_cache.get(node.__class__.__name__, None)
        if visitor is None:
            method = 'visit_' + node.__class__.__name__
            visitor = getattr(self, method, self.generic_visit)
            self._method_cache[node.__class__.__name__] = visitor

        return visitor(node)

    def generic_visit(self, node):
        """ Called if no explicit visitor function exists for a
            node. Implements preorder visiting of the node.
        """
        for c in node:
            self.visit(c)