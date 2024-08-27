#ifndef __ERRORS_SPEC_H_
#define __ERRORS_SPEC_H_

#include "../../src/loader/Loader.h"
#include "_helpers.h"

module(errors_spec, {
  it("enumerable literal errors", {
    error("(", "missing closing parenthesis on group.");
    error(")", "missing opening parenthesis on group.");
    error("(()", "missing closing parenthesis on group.");
    error("())", "reached end of program.");
    error("[", "missing closing bracket on tensor.");
    error("]", "missing opening bracket on tensor.");
    error("{", "missing closing curly brace on hash.");
    error("}", "missing opening curly brace on hash.");
    error(
      "#-invalid-syntax-symbol", "missing '=>' on binary method definition."
    );
    error("global$var", "grouped items should be separated by commas.");
    error(
      "# => l2 => [@self, l2]", "grouped items should be separated by commas."
    );
  });

  it("other syntax errors", {
    VM *vm = vm_new("./examples/errors/e1.marg");
    loader_load(vm);
    lexer_make_tokens(vm);
    parser_analyze_syntax(vm);
  });

  context("on ignoring invalid and unknown characters", {
    it("skips non ascii characters", {
      parse(
        "©©42©,42©",
        vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("42"))
      );
      parse(
        "☺☺42☺,42☺",
        vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("42"))
      );
      parse(
        "😊😊42😊,42😊",
        vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("42"))
      );
      parse(
        "¤¤42¤,42¤",
        vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("42"))
      );
      parse(
        "ΩΩ42Ω,42Ω",
        vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("42"))
      );
      parse(
        "日日42日,42日",
        vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("42"))
      );
      parse(
        "𠜎𠜎42𠜎,42𠜎",
        vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("42"))
      );
      parse(
        "∆∆42∆,42∆",
        vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("42"))
      );
      parse(
        "🙂🙂42🙂,42🙂",
        vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("42"))
      );
      parse(
        "⚽⚽42⚽,42⚽",
        vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("42"))
      );
    });
  });

  it("tests weird edge cases", {
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
    parse("\\", vector_new(FM_LHS, string_new("\\")));
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
  });
})

#endif
