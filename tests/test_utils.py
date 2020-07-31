import re

from pycparser import c_parser, c_ast, parse_file, c_generator

parser = c_parser.CParser()

def assert_ast_equality(ast_to_test, ast_expected):
    g = c_generator.CGenerator()
    src_ast_expected = g.visit(ast_expected)
    src_ast_to_test = g.visit(ast_to_test)

    src_ast_expected_clean = re.sub(r"[\n\t\s]*", "", src_ast_expected)
    src_ast_to_test_clean = re.sub(r"[\n\t\s]*", "", src_ast_to_test)

    try:
        assert src_ast_expected_clean == src_ast_to_test_clean
    except AssertionError:
        print()
        print("AssertionError")
        print()
        print("Expected")
        print(src_ast_expected)
        print("Obtained")
        print(src_ast_to_test)
        print()