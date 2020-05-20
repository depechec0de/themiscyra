import copy
import re

from pycparser import c_parser, c_ast, parse_file, c_generator


"""
    This function assumes a C code with a unique "while" statement. The result is
    the code unfolded "k" times, where unfolding means replacing every occurrence 
    of a "continue" statement with the content of the "while" body.

    ast: a pycparser AST 
    k: number of unfoldings of the main loop
    returns: nothing, it alters the original "ast" object

"""
def unfold(ast, k: int):

    (main_while, while_parent) = get_main_while(ast)

    while_body = copy.deepcopy(main_while.stmt.block_items)

    for i in range(1,k):
        _insert_node_after_continue(main_while, while_body)

    # replace continues with returns
    #zero = c_ast.Constant(type=int, value='0')
    #return_ast = c_ast.Return(expr=zero)

    #_replace_node(while_parent, c_ast.Continue, return_ast)


def _insert_node_after_continue(ast, node):
    
    typ = type(ast) 

    if typ == c_ast.If:
        _insert_node_after_continue(ast.iftrue, node)

        if ast.iffalse is not None:
            _insert_node_after_continue(ast.iffalse, node)
        
    elif typ == c_ast.While:
        _insert_node_after_continue(ast.stmt, node)

    elif typ == c_ast.Compound:
        continues = [n for n in ast.block_items if type(n)==c_ast.Continue]
        
        if len(continues)>0:
            
            items = copy.copy(ast.block_items)
            for i in items:
                if type(i) == c_ast.Continue:
                    ast.block_items.remove(i)
                    body = copy.deepcopy(node)
                    for e in body:
                        ast.block_items.append(e)
        else:
            for i in ast.block_items:
                _insert_node_after_continue(i, node)

    elif typ == c_ast.FuncDef:
        _insert_node_after_continue(ast.body, node)

"""
    Replace every "continue;" statement with "returns 0;"

    ast: a pycparser AST 
    returns: nothing, it alters the original "ast" object 
"""
def _replace_node(ast, find_type, replace):

    typ = type(ast) 

    if typ == c_ast.If:
        _replace_node(ast.iftrue, find_type, replace)

        if ast.iffalse is not None:
            _replace_node(ast.iffalse, find_type, replace)
        
    elif typ == c_ast.While:
        _replace_node(ast.stmt, find_type, replace)

    elif typ == c_ast.Compound:
            
            for i in ast.block_items:
                if type(i) == find_type:
                    replace_copy = copy.deepcopy(replace)
                    index = ast.block_items.index(i)
                    ast.block_items.insert(index, replace_copy)
                    ast.block_items.remove(i)
                else:
                    _replace_node(i, find_type, replace)

    elif typ == c_ast.FuncDef:
        _replace_node(ast.body, find_type, replace)

""" 
    remove c-style comments.
    text: blob of text with comments (can include newlines)
    returns: text with comments removed
"""
def remove_c99_comments(text):

    pattern = r"""
                            ##  --------- COMMENT ---------
           //.*?$           ##  Start of // .... comment
         |                  ##
           /\*              ##  Start of /* ... */ comment
           [^*]*\*+         ##  Non-* followed by 1-or-more *'s
           (                ##
             [^/*][^*]*\*+  ##
           )*               ##  0-or-more things which don't start with /
                            ##    but do end with '*'
           /                ##  End of /* ... */ comment
         |                  ##  -OR-  various things which aren't comments:
           (                ##
                            ##  ------ " ... " STRING ------
             "              ##  Start of " ... " string
             (              ##
               \\.          ##  Escaped char
             |              ##  -OR-
               [^"\\]       ##  Non "\ characters
             )*             ##
             "              ##  End of " ... " string
           |                ##  -OR-
                            ##
                            ##  ------ ' ... ' STRING ------
             '              ##  Start of ' ... ' string
             (              ##
               \\.          ##  Escaped char
             |              ##  -OR-
               [^'\\]       ##  Non '\ characters
             )*             ##
             '              ##  End of ' ... ' string
           |                ##  -OR-
                            ##
                            ##  ------ ANYTHING ELSE -------
             .              ##  Anything other char
             [^/"'\\]*      ##  Chars which doesn't start a comment, string
           )                ##    or escape
    """
    regex = re.compile(pattern, re.VERBOSE|re.MULTILINE|re.DOTALL)
    noncomments = [m.group(2) for m in regex.finditer(text) if m.group(2)]

    return "".join(noncomments)

"""
    ast: A pycparser AST 
    returns: the outer while of the AST
"""
class MainWhileVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.current_parent = None
        self.result = None

    def visit_While(self, node):
        self.result = (node, self.current_parent)

    def generic_visit(self, node):
        oldparent = self.current_parent
        self.current_parent = node
        for c in node:
            self.visit(c)
        self.current_parent = oldparent

def get_main_while(ast):
    v = MainWhileVisitor()
    v.visit(ast)
    return v.result

"""
    ast: a pycparser AST 
    funcname: a function name to find
    returns: the corresponding FuncDef node in the AST defined as "funcname"
"""
class FuncDefVisitor(c_ast.NodeVisitor):
    def __init__(self, funcname):
        self.funcname = funcname
        self.result = None

    def visit_FuncDef(self, node):
        if node.decl.name == self.funcname:
            self.result = node
        elif hasattr(node, 'args'):
            self.visit(node.args)

def get_funcdef_node(ast, funcname):
    v = FuncDefVisitor(funcname)
    v.visit(ast)
    return v.result

"""
    ast: a pycparser AST 
    returns: enum definitions in the AST as a dictionary: {enum_type_name: [const1, ...]}
"""
class EnumDeclarationVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.result = {}

    def visit_Decl(self, node):
        if type(node.type) == c_ast.Enum:
            enum_name = node.type.name
            enum_constants = []
            for c in node.type.values.enumerators:
                enum_constants.append(c.name)

            self.result[enum_name] = enum_constants

def get_enum_declarations(ast):
    v = EnumDeclarationVisitor()
    v.visit(ast)
    return v.result

"""
    ast: a pycparser AST 
    returns: enum variable declarations as a dictionary {variable: enum_type_name}
"""
class EnumVariableDeclarationVisitor(c_ast.NodeVisitor):
    def __init__(self):
        self.result = {}

    def visit_Decl(self, node):
        if type(node.type) == c_ast.TypeDecl and type(node.type.type) == c_ast.Enum:
            self.result[node.name] = node.type.type.name


def get_declared_enum_vars(ast):
    v = EnumVariableDeclarationVisitor()
    v.visit(ast)
    return v.result

