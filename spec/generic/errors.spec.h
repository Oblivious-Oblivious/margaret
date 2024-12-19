#ifndef __ERRORS_SPEC_H_
#define __ERRORS_SPEC_H_

#include "../../src/errors.h"
#include "../../src/loader/Loader.h"
#include "_helpers.h"

module(errors_spec, {
  it("parses empty programs as NULL", {
    char **v = NULL;
    parse("", v);
  });

  it("validates syntax symbol errors", {
    error("(", "missing closing parenthesis on group.", "(");
    error(")", "reached end of program.", ")");
    error("(()", "missing closing parenthesis on group.", ")");
    error("())", "reached end of program.", ")");
    error("[", "missing closing bracket on tensor.", "[");
    error("]", "reached end of program.", "]");
    error("{", "missing closing curly on headless method.", "{");
    error("}", "reached end of program.", "}");
    error("#", "missing method body.", "#");
    error("##", "missing method body.", "#");
    error("###", "grouped items should be separated by commas.", "#");
    error("#x", "missing method body.", "#");
    error("##x", "missing method body.", "#");
    /* error("##x=>", "missing method body.", "=>"); */
    error(":", "grouped items should be separated by commas.", ":");
    error("::", "missing lhs message parameter.", ":");
    error(":::", "grouped items should be separated by commas.", ":");
    error(":::::::", "grouped items should be separated by commas.", ":");
    error("=1", "grouped items should be separated by commas.", "=");
    error("x = = 1", "grouped items should be separated by commas.", "=");
    error("x == = 1", "grouped items should be separated by commas.", "=");
    error("-, ++, --, +<><+", "missing lhs message parameter.", "+<><+");
    error("++", "missing lhs message parameter.", "++");

    error("'", "grouped items should be separated by commas.", "'");
    error("\"", "grouped items should be separated by commas.", "\"");
    error("\"\"\"", "grouped items should be separated by commas.", "");
    error("'''", "grouped items should be separated by commas.", "");

    /* TODO - Figure out why strings are in reverse */
    error("\"'", "grouped items should be separated by commas.", "'\"");
    error("'\"", "grouped items should be separated by commas.", "\"'");
  });

  it("does not load non-existing file", {
    VM *vm = vm_new("__this name does not exist__");
    loader_load(vm);
    assert_that_charptr(vm->error equals to ERROR_LOADER_FILE_NOT_FOUND);
    assert_that(vm->source is NULL);
  });

  it("validates special case errors", {
    error(
      "#-invalid-syntax-symbol",
      "missing '=>' on binary method definition.",
      "invalid"
    );
    error(
      "global$var", "grouped items should be separated by commas.", "global"
    );
    error(
      "# => l2 => [@self, l2]",
      "grouped items should be separated by commas.",
      "l2"
    );
    error("0000.000", "grouped items should be separated by commas.", "0");
  });

  it("other syntax errors", {
    VM *vm = vm_new("./examples/errors/e1.marg");
    loader_load(vm);
    lexer_make_tokens(vm);
    parser_analyze_syntax(vm);
  });

  it("tests weird edge cases", {
    char **v = NULL;
    parse("$", v);
    parse("$$", v);
    parse("$$$x", vector_new(FM_GLOBAL, string_new("$x")));
    parse("@", v);
    parse("@@", v);
    parse("@@@x", vector_new(FM_INSTANCE, string_new("@x")));

    parse(
      "***(not a valid operator sequence)",
      vector_new(
        FM_LOCAL,
        string_new("not"),
        FM_UNARY,
        string_new("a"),
        FM_UNARY,
        string_new("valid"),
        FM_UNARY,
        string_new("operator"),
        FM_UNARY,
        string_new("sequence"),
        FM_LHS,
        string_new("***")
      )
    );
    parse(
      "123.456.789",
      vector_new(
        FM_FLOAT,
        string_new("123.456"),
        FM_INTEGER,
        string_new("789"),
        FM_BINARY,
        string_new(".")
      )
    );
    parse(
      "0x", vector_new(FM_INTEGER, string_new("0"), FM_UNARY, string_new("x"))
    );
    parse(
      "@123variable",
      vector_new(
        FM_INTEGER, string_new("123"), FM_UNARY, string_new("variable")
      )
    );
    parse(
      "var!name",
      vector_new(FM_LOCAL, string_new("var!"), FM_UNARY, string_new("name"))
    );
    parse(
      "3.14e",
      vector_new(FM_FLOAT, string_new("3.14"), FM_UNARY, string_new("e"))
    );
    parse(
      ".startsWithDot",
      vector_new(FM_LOCAL, string_new("startsWithDot"), FM_LHS, string_new("."))
    );
    parse(
      "newline\ninside",
      vector_new(
        FM_LOCAL, string_new("newline"), FM_UNARY, string_new("inside")
      )
    );
    parse("\\", v);
    parse(
      "double--dash",
      vector_new(
        FM_LOCAL,
        string_new("double"),
        FM_LOCAL,
        string_new("dash"),
        FM_BINARY,
        string_new("--")
      )
    );
    parse(
      "@_leading_underscore",
      vector_new(FM_INSTANCE, string_new("@_leading_underscore"))
    );
    parse(
      "5e", vector_new(FM_INTEGER, string_new("5"), FM_UNARY, string_new("e"))
    );
    parse("0b_101010", vector_new(FM_INTEGER, string_new("42")));

    parse(
      "{ a | # | b => a + b }",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("a"),
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("b"),
        FM_METHOD_NAME,
        string_new("|"),
        FM_LOCAL,
        string_new("a"),
        FM_LOCAL,
        string_new("b"),
        FM_BINARY,
        string_new("+"),
        FM_METHOD_END,
        FM_METHOD_END
      )
    );

    parse(
      "{ # | a => a }",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("a"),
        FM_METHOD_NAME,
        string_new("|"),
        FM_LOCAL,
        string_new("a"),
        FM_METHOD_END,
        FM_METHOD_END
      )
    );

    parse(
      "{ # | a => a }",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("a"),
        FM_METHOD_NAME,
        string_new("|"),
        FM_LOCAL,
        string_new("a"),
        FM_METHOD_END,
        FM_METHOD_END
      )
    );

    parse(
      "# m => {{{}}}",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_NAME,
        string_new("m"),
        FM_METHOD_START,
        FM_METHOD_START,
        FM_NIL,
        FM_METHOD_END,
        FM_METHOD_END,
        FM_METHOD_END
      )
    );

    parse(
      "# m1 => { # m2 => { {} } }",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_NAME,
        string_new("m1"),
        FM_METHOD_START,
        FM_METHOD_NAME,
        string_new("m2"),
        FM_METHOD_START,
        FM_NIL,
        FM_METHOD_END,
        FM_METHOD_END,
        FM_METHOD_END
      )
    );

    parse(
      "{ # m1 => { # m2 => { {} } } }",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_START,
        FM_METHOD_NAME,
        string_new("m1"),
        FM_METHOD_START,
        FM_METHOD_NAME,
        string_new("m2"),
        FM_METHOD_START,
        FM_NIL,
        FM_METHOD_END,
        FM_METHOD_END,
        FM_METHOD_END,
        FM_METHOD_END
      )
    );

    parse(
      "42.param",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_LOCAL,
        string_new("param"),
        FM_BINARY,
        string_new(".")
      )
    );
  });
})

#endif
