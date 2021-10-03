# Generated from PParser.g4 by ANTLR 4.9.2
from antlr4 import *
if __name__ is not None and "." in __name__:
    from .PParser import PParser
else:
    from PParser import PParser

# This class defines a complete generic visitor for a parse tree produced by PParser.

class PParserVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by PParser#program.
    def visitProgram(self, ctx:PParser.ProgramContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#iden.
    def visitIden(self, ctx:PParser.IdenContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#r_int.
    def visitR_int(self, ctx:PParser.R_intContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#SeqType.
    def visitSeqType(self, ctx:PParser.SeqTypeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#SetType.
    def visitSetType(self, ctx:PParser.SetTypeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#MapType.
    def visitMapType(self, ctx:PParser.MapTypeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#TupleType.
    def visitTupleType(self, ctx:PParser.TupleTypeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#NamedTupleType.
    def visitNamedTupleType(self, ctx:PParser.NamedTupleTypeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#PrimitiveType.
    def visitPrimitiveType(self, ctx:PParser.PrimitiveTypeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#NamedType.
    def visitNamedType(self, ctx:PParser.NamedTypeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#idenTypeList.
    def visitIdenTypeList(self, ctx:PParser.IdenTypeListContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#idenType.
    def visitIdenType(self, ctx:PParser.IdenTypeContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#funParamList.
    def visitFunParamList(self, ctx:PParser.FunParamListContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#funParam.
    def visitFunParam(self, ctx:PParser.FunParamContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#topDecl.
    def visitTopDecl(self, ctx:PParser.TopDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#ForeignTypeDef.
    def visitForeignTypeDef(self, ctx:PParser.ForeignTypeDefContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#PTypeDef.
    def visitPTypeDef(self, ctx:PParser.PTypeDefContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#enumTypeDefDecl.
    def visitEnumTypeDefDecl(self, ctx:PParser.EnumTypeDefDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#enumElemList.
    def visitEnumElemList(self, ctx:PParser.EnumElemListContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#enumElem.
    def visitEnumElem(self, ctx:PParser.EnumElemContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#numberedEnumElemList.
    def visitNumberedEnumElemList(self, ctx:PParser.NumberedEnumElemListContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#numberedEnumElem.
    def visitNumberedEnumElem(self, ctx:PParser.NumberedEnumElemContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#eventDecl.
    def visitEventDecl(self, ctx:PParser.EventDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#cardinality.
    def visitCardinality(self, ctx:PParser.CardinalityContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#eventSetDecl.
    def visitEventSetDecl(self, ctx:PParser.EventSetDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#eventSetLiteral.
    def visitEventSetLiteral(self, ctx:PParser.EventSetLiteralContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#interfaceDecl.
    def visitInterfaceDecl(self, ctx:PParser.InterfaceDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#implMachineDecl.
    def visitImplMachineDecl(self, ctx:PParser.ImplMachineDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#idenList.
    def visitIdenList(self, ctx:PParser.IdenListContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#MachineReceive.
    def visitMachineReceive(self, ctx:PParser.MachineReceiveContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#MachineSend.
    def visitMachineSend(self, ctx:PParser.MachineSendContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#specMachineDecl.
    def visitSpecMachineDecl(self, ctx:PParser.SpecMachineDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#machineBody.
    def visitMachineBody(self, ctx:PParser.MachineBodyContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#machineEntry.
    def visitMachineEntry(self, ctx:PParser.MachineEntryContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#varDecl.
    def visitVarDecl(self, ctx:PParser.VarDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#ForeignFunDecl.
    def visitForeignFunDecl(self, ctx:PParser.ForeignFunDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#PFunDecl.
    def visitPFunDecl(self, ctx:PParser.PFunDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#group.
    def visitGroup(self, ctx:PParser.GroupContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#groupItem.
    def visitGroupItem(self, ctx:PParser.GroupItemContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#stateDecl.
    def visitStateDecl(self, ctx:PParser.StateDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#StateEntry.
    def visitStateEntry(self, ctx:PParser.StateEntryContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#StateExit.
    def visitStateExit(self, ctx:PParser.StateExitContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#StateDefer.
    def visitStateDefer(self, ctx:PParser.StateDeferContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#StateIgnore.
    def visitStateIgnore(self, ctx:PParser.StateIgnoreContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#OnEventDoAction.
    def visitOnEventDoAction(self, ctx:PParser.OnEventDoActionContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#OnEventPushState.
    def visitOnEventPushState(self, ctx:PParser.OnEventPushStateContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#OnEventGotoState.
    def visitOnEventGotoState(self, ctx:PParser.OnEventGotoStateContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#nonDefaultEventList.
    def visitNonDefaultEventList(self, ctx:PParser.NonDefaultEventListContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#nonDefaultEvent.
    def visitNonDefaultEvent(self, ctx:PParser.NonDefaultEventContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#eventList.
    def visitEventList(self, ctx:PParser.EventListContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#eventId.
    def visitEventId(self, ctx:PParser.EventIdContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#stateName.
    def visitStateName(self, ctx:PParser.StateNameContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#functionBody.
    def visitFunctionBody(self, ctx:PParser.FunctionBodyContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#CompoundStmt.
    def visitCompoundStmt(self, ctx:PParser.CompoundStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#PopStmt.
    def visitPopStmt(self, ctx:PParser.PopStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#AssertStmt.
    def visitAssertStmt(self, ctx:PParser.AssertStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#PrintStmt.
    def visitPrintStmt(self, ctx:PParser.PrintStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#ReturnStmt.
    def visitReturnStmt(self, ctx:PParser.ReturnStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#BreakStmt.
    def visitBreakStmt(self, ctx:PParser.BreakStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#ContinueStmt.
    def visitContinueStmt(self, ctx:PParser.ContinueStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#AssignStmt.
    def visitAssignStmt(self, ctx:PParser.AssignStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#InsertStmt.
    def visitInsertStmt(self, ctx:PParser.InsertStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#AddStmt.
    def visitAddStmt(self, ctx:PParser.AddStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#RemoveStmt.
    def visitRemoveStmt(self, ctx:PParser.RemoveStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#WhileStmt.
    def visitWhileStmt(self, ctx:PParser.WhileStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#IfStmt.
    def visitIfStmt(self, ctx:PParser.IfStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#CtorStmt.
    def visitCtorStmt(self, ctx:PParser.CtorStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#FunCallStmt.
    def visitFunCallStmt(self, ctx:PParser.FunCallStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#RaiseStmt.
    def visitRaiseStmt(self, ctx:PParser.RaiseStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#SendStmt.
    def visitSendStmt(self, ctx:PParser.SendStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#AnnounceStmt.
    def visitAnnounceStmt(self, ctx:PParser.AnnounceStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#GotoStmt.
    def visitGotoStmt(self, ctx:PParser.GotoStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#ReceiveStmt.
    def visitReceiveStmt(self, ctx:PParser.ReceiveStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#NoStmt.
    def visitNoStmt(self, ctx:PParser.NoStmtContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#TupleLvalue.
    def visitTupleLvalue(self, ctx:PParser.TupleLvalueContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#NamedTupleLvalue.
    def visitNamedTupleLvalue(self, ctx:PParser.NamedTupleLvalueContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#MapOrSeqLvalue.
    def visitMapOrSeqLvalue(self, ctx:PParser.MapOrSeqLvalueContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#VarLvalue.
    def visitVarLvalue(self, ctx:PParser.VarLvalueContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#recvCase.
    def visitRecvCase(self, ctx:PParser.RecvCaseContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#anonEventHandler.
    def visitAnonEventHandler(self, ctx:PParser.AnonEventHandlerContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#noParamAnonEventHandler.
    def visitNoParamAnonEventHandler(self, ctx:PParser.NoParamAnonEventHandlerContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#StringExpr.
    def visitStringExpr(self, ctx:PParser.StringExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#KeywordExpr.
    def visitKeywordExpr(self, ctx:PParser.KeywordExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#ChooseExpr.
    def visitChooseExpr(self, ctx:PParser.ChooseExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#SeqAccessExpr.
    def visitSeqAccessExpr(self, ctx:PParser.SeqAccessExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#NamedTupleAccessExpr.
    def visitNamedTupleAccessExpr(self, ctx:PParser.NamedTupleAccessExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#PrimitiveExpr.
    def visitPrimitiveExpr(self, ctx:PParser.PrimitiveExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#BinExpr.
    def visitBinExpr(self, ctx:PParser.BinExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#UnaryExpr.
    def visitUnaryExpr(self, ctx:PParser.UnaryExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#TupleAccessExpr.
    def visitTupleAccessExpr(self, ctx:PParser.TupleAccessExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#UnnamedTupleExpr.
    def visitUnnamedTupleExpr(self, ctx:PParser.UnnamedTupleExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#FunCallExpr.
    def visitFunCallExpr(self, ctx:PParser.FunCallExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#CastExpr.
    def visitCastExpr(self, ctx:PParser.CastExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#CtorExpr.
    def visitCtorExpr(self, ctx:PParser.CtorExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#ParenExpr.
    def visitParenExpr(self, ctx:PParser.ParenExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#NamedTupleExpr.
    def visitNamedTupleExpr(self, ctx:PParser.NamedTupleExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#formatedString.
    def visitFormatedString(self, ctx:PParser.FormatedStringContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#primitive.
    def visitPrimitive(self, ctx:PParser.PrimitiveContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#DecimalFloat.
    def visitDecimalFloat(self, ctx:PParser.DecimalFloatContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#ExpFloat.
    def visitExpFloat(self, ctx:PParser.ExpFloatContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#unnamedTupleBody.
    def visitUnnamedTupleBody(self, ctx:PParser.UnnamedTupleBodyContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#namedTupleBody.
    def visitNamedTupleBody(self, ctx:PParser.NamedTupleBodyContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#rvalueList.
    def visitRvalueList(self, ctx:PParser.RvalueListContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#rvalue.
    def visitRvalue(self, ctx:PParser.RvalueContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#ParenModuleExpr.
    def visitParenModuleExpr(self, ctx:PParser.ParenModuleExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#PrimitiveModuleExpr.
    def visitPrimitiveModuleExpr(self, ctx:PParser.PrimitiveModuleExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#NamedModule.
    def visitNamedModule(self, ctx:PParser.NamedModuleContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#ComposeModuleExpr.
    def visitComposeModuleExpr(self, ctx:PParser.ComposeModuleExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#UnionModuleExpr.
    def visitUnionModuleExpr(self, ctx:PParser.UnionModuleExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#HideEventsModuleExpr.
    def visitHideEventsModuleExpr(self, ctx:PParser.HideEventsModuleExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#HideInterfacesModuleExpr.
    def visitHideInterfacesModuleExpr(self, ctx:PParser.HideInterfacesModuleExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#AssertModuleExpr.
    def visitAssertModuleExpr(self, ctx:PParser.AssertModuleExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#RenameModuleExpr.
    def visitRenameModuleExpr(self, ctx:PParser.RenameModuleExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#MainMachineModuleExpr.
    def visitMainMachineModuleExpr(self, ctx:PParser.MainMachineModuleExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#bindExpr.
    def visitBindExpr(self, ctx:PParser.BindExprContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#namedModuleDecl.
    def visitNamedModuleDecl(self, ctx:PParser.NamedModuleDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#SafetyTestDecl.
    def visitSafetyTestDecl(self, ctx:PParser.SafetyTestDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#RefinementTestDecl.
    def visitRefinementTestDecl(self, ctx:PParser.RefinementTestDeclContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by PParser#implementationDecl.
    def visitImplementationDecl(self, ctx:PParser.ImplementationDeclContext):
        return self.visitChildren(ctx)



del PParser