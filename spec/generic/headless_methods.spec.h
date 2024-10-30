#ifndef __HEADLESS_METHODS_SPEC_H_
#define __HEADLESS_METHODS_SPEC_H_

#include "_helpers.h"

module(headless_methods_spec, {
  it("parses headless methods", {
    parse(
      "{ x = (x = 1, y = 2) }",
      vector_new(
        FM_METHOD_START,
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("1"),
        FM_ASSIGNMENT,
        FM_LOCAL,
        string_new("y"),
        FM_INTEGER,
        string_new("2"),
        FM_ASSIGNMENT,
        FM_ASSIGNMENT,
        FM_METHOD_END
      )
    );
    parse(
      "x = { \
        v1, v2 | ( \
          v1 += 1, \
          v1 += 2, \
          v1 * v2 \
        ) \
      }",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_METHOD_START,
        FM_METHOD_PARAMETER,
        string_new("v1"),
        FM_METHOD_PARAMETER,
        string_new("v2"),
        FM_LOCAL,
        string_new("v1"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("+="),
        FM_LOCAL,
        string_new("v1"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("+="),
        FM_LOCAL,
        string_new("v1"),
        FM_LOCAL,
        string_new("v2"),
        FM_BINARY,
        string_new("*"),
        FM_METHOD_END,
        FM_ASSIGNMENT
      )
    );
  });

  it("parses headless methods that are parameterized returning literals", {
    parse("{}", vector_new(FM_METHOD_START, FM_NIL, FM_METHOD_END));
    parse(
      "{ 42 }",
      vector_new(FM_METHOD_START, FM_INTEGER, string_new("42"), FM_METHOD_END)
    );
    parse(
      "{ a | a puts }",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_PARAMETER,
        string_new("a"),
        FM_LOCAL,
        string_new("a"),
        FM_UNARY,
        string_new("puts"),
        FM_METHOD_END
      )
    );
    parse(
      "{ 2 + 3 }",
      vector_new(
        FM_METHOD_START,
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_BINARY,
        string_new("+"),
        FM_METHOD_END
      )
    );
    parse(
      "{ (x = 1, y = 2, x + y) }",
      vector_new(
        FM_METHOD_START,
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("1"),
        FM_ASSIGNMENT,
        FM_LOCAL,
        string_new("y"),
        FM_INTEGER,
        string_new("2"),
        FM_ASSIGNMENT,
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("y"),
        FM_BINARY,
        string_new("+"),
        FM_METHOD_END
      )
    );
    parse(
      "{ param | param puts }",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_PARAMETER,
        string_new("param"),
        FM_LOCAL,
        string_new("param"),
        FM_UNARY,
        string_new("puts"),
        FM_METHOD_END
      )
    );
    parse(
      "{ a | a }",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_PARAMETER,
        string_new("a"),
        FM_LOCAL,
        string_new("a"),
        FM_METHOD_END
      )
    );
    parse(
      "{ x = 2 } call",
      vector_new(
        FM_METHOD_START,
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("2"),
        FM_ASSIGNMENT,
        FM_METHOD_END,
        FM_UNARY,
        string_new("call")
      )
    );
    parse(
      "{ param | param puts } <- %[42]",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_PARAMETER,
        string_new("param"),
        FM_LOCAL,
        string_new("param"),
        FM_UNARY,
        string_new("puts"),
        FM_METHOD_END,
        FM_INTEGER,
        string_new("42"),
        FM_TUPLE,
        string_new("1"),
        FM_BINARY,
        string_new("<-")
      )
    );
    parse(
      "{ a | a * 2 } <- 42",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_PARAMETER,
        string_new("a"),
        FM_LOCAL,
        string_new("a"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("*"),
        FM_METHOD_END,
        FM_INTEGER,
        string_new("42"),
        FM_BINARY,
        string_new("<-")
      )
    );
    parse(
      "{a, b | a + b} <- %[2, 3]",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_PARAMETER,
        string_new("a"),
        FM_METHOD_PARAMETER,
        string_new("b"),
        FM_LOCAL,
        string_new("a"),
        FM_LOCAL,
        string_new("b"),
        FM_BINARY,
        string_new("+"),
        FM_METHOD_END,
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_TUPLE,
        string_new("2"),
        FM_BINARY,
        string_new("<-")
      )
    );
  });
})

#endif
