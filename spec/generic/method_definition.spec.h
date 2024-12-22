#ifndef __METHOD_DEFINITION_SPEC_H_
#define __METHOD_DEFINITION_SPEC_H_

#include "_helpers.h"

module(method_definition_spec, {
  it("parses subscript methods", {
    parse(
      "#[param] => 42.param",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("param"),
        FM_METHOD_NAME,
        string_new("[]_SUBSCRIPT"),
        FM_INTEGER,
        string_new("42"),
        FM_LOCAL,
        string_new("param"),
        FM_BINARY,
        string_new("."),
        FM_METHOD_END
      )
    );
  });

  it("parses lhs methods", {
    parse(
      "# - => 42",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_NAME,
        string_new("-_LHS"),
        FM_INTEGER,
        string_new("42"),
        FM_METHOD_END
      )
    );
  });

  it("parses unary methods", {
    parse(
      "#incr => @self + 1",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_NAME,
        string_new("incr_UNARY"),
        FM_SELF,
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("+"),
        FM_METHOD_END
      )
    );
    parse(
      "#  incr => @self + 1",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_NAME,
        string_new("incr_UNARY"),
        FM_SELF,
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("+"),
        FM_METHOD_END
      )
    );
    parse(
      "#is_empty? => $true",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_NAME,
        string_new("is_empty?_UNARY"),
        FM_TRUE,
        FM_METHOD_END
      )
    );
  });

  it("parses binary methods", {
    parse(
      "# ** a_number => @self raised_to: a_number",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("a_number"),
        FM_METHOD_NAME,
        string_new("**_BINARY"),
        FM_SELF,
        FM_LOCAL,
        string_new("a_number"),
        FM_KEYWORD,
        string_new("raised_to:"),
        string_new("1"),
        FM_METHOD_END
      )
    );
  });

  it("parses keyword methods", {
    parse(
      "#add: element at: position => 42",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("element"),
        FM_METHOD_ARGUMENT,
        string_new("position"),
        FM_METHOD_NAME,
        string_new("add:at:_KEYWORD"),
        FM_INTEGER,
        string_new("42"),
        FM_METHOD_END
      )
    );

    parse(
      "#ok?: value1 otherwise!: value2 => 17",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("value1"),
        FM_METHOD_ARGUMENT,
        string_new("value2"),
        FM_METHOD_NAME,
        string_new("ok?:otherwise!:_KEYWORD"),
        FM_INTEGER,
        string_new("17"),
        FM_METHOD_END
      )
    );

    parse(
      "#add: element at: position => 17",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("element"),
        FM_METHOD_ARGUMENT,
        string_new("position"),
        FM_METHOD_NAME,
        string_new("add:at:_KEYWORD"),
        FM_INTEGER,
        string_new("17"),
        FM_METHOD_END
      )
    );

    parse(
      "#times: a_block => { \
        remaining = @self, \
        { (remaining = remaining - 1) >= 0 } while_true: { a_block value } \
      }",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("a_block"),
        FM_METHOD_NAME,
        string_new("times:_KEYWORD"),
        FM_LOCAL,
        string_new("remaining"),
        FM_SELF,
        FM_ASSIGNMENT,
        FM_METHOD_START,
        FM_LOCAL,
        string_new("remaining"),
        FM_LOCAL,
        string_new("remaining"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("-"),
        FM_ASSIGNMENT,
        FM_INTEGER,
        string_new("0"),
        FM_BINARY,
        string_new(">="),
        FM_METHOD_END,
        FM_METHOD_START,
        FM_LOCAL,
        string_new("a_block"),
        FM_UNARY,
        string_new("value"),
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("while_true:"),
        string_new("1"),
        FM_METHOD_END
      )
    );
  });
})

#endif
