#ifndef __ITERATIONS_SPEC_H_
#define __ITERATIONS_SPEC_H_

#include "_helpers.h"

module(iterations_spec, {
  it("parses iteration statements", {
    parse(
      "(x > 0 while_true: {x = x - 1, y = y * 2})",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("0"),
        FM_BINARY,
        string_new(">"),
        FM_METHOD_START,
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("-"),
        FM_ASSIGNMENT,
        FM_LOCAL,
        string_new("y"),
        FM_LOCAL,
        string_new("y"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("*"),
        FM_ASSIGNMENT,
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("while_true:"),
        string_new("1")
      )
    );
    parse(
      "(x >= 0 while_false: {x = x + 1, y = y * 2})",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("0"),
        FM_BINARY,
        string_new(">="),
        FM_METHOD_START,
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("+"),
        FM_ASSIGNMENT,
        FM_LOCAL,
        string_new("y"),
        FM_LOCAL,
        string_new("y"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("*"),
        FM_ASSIGNMENT,
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("while_false:"),
        string_new("1")
      )
    );
    parse(
      "(x times: {y = y * 2})",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_METHOD_START,
        FM_LOCAL,
        string_new("y"),
        FM_LOCAL,
        string_new("y"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("*"),
        FM_ASSIGNMENT,
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("times:"),
        string_new("1")
      )
    );
    parse(
      "(1 to: 5 do: {y = y * 2})",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("5"),
        FM_METHOD_START,
        FM_LOCAL,
        string_new("y"),
        FM_LOCAL,
        string_new("y"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("*"),
        FM_ASSIGNMENT,
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("to:do:"),
        string_new("2")
      )
    );
    parse(
      "(1 to: 5 by: 2 do: {y = y / 2})",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("5"),
        FM_INTEGER,
        string_new("2"),
        FM_METHOD_START,
        FM_LOCAL,
        string_new("y"),
        FM_LOCAL,
        string_new("y"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("/"),
        FM_ASSIGNMENT,
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("to:by:do:"),
        string_new("3")
      )
    );
    parse(
      "[1,2,3,4] each: { item | x = x + item }",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_INTEGER,
        string_new("4"),
        FM_TENSOR,
        string_new("4"),
        FM_METHOD_START,
        FM_LOCAL,
        string_new("item"),
        FM_METHOD_PARAMETER,
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("item"),
        FM_BINARY,
        string_new("+"),
        FM_ASSIGNMENT,
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("each:"),
        string_new("1")
      )
    );
  });
})

#endif
