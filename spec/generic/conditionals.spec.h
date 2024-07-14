#ifndef __CONDITIONALS_SPEC_H_
#define __CONDITIONALS_SPEC_H_

#include "_helpers.h"

module(conditionals_spec, {
  it("parses conditional statements", {
    parse(
      "(x > 10 + 42)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("10"),
        FM_BINARY,
        string_new(">"),
        FM_INTEGER,
        string_new("42"),
        FM_BINARY,
        string_new("+")
      )
    );
    parse(
      "(x > 10 if_true: 42)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("10"),
        FM_BINARY,
        string_new(">"),
        FM_INTEGER,
        string_new("42"),
        FM_KEYWORD,
        string_new("if_true:"),
        string_new("1")
      )
    );
    parse(
      "(x > 10 if_false: 41)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("10"),
        FM_BINARY,
        string_new(">"),
        FM_INTEGER,
        string_new("41"),
        FM_KEYWORD,
        string_new("if_false:"),
        string_new("1")
      )
    );
    parse(
      "x > 10 \
        if_true: 42 \
        if_false: 41",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("10"),
        FM_BINARY,
        string_new(">"),
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("41"),
        FM_KEYWORD,
        string_new("if_true:if_false:"),
        string_new("2")
      )
    );
    parse(
      "x > 10 \
        if_true: { \
          x > 5 \
            if_true: 1 \
            if_false: 2 \
        } \
        if_false: 3",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("10"),
        FM_BINARY,
        string_new(">"),
        FM_PROC_START,
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("5"),
        FM_BINARY,
        string_new(">"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_KEYWORD,
        string_new("if_true:if_false:"),
        string_new("2"),
        FM_PROC_END,
        FM_INTEGER,
        string_new("3"),
        FM_KEYWORD,
        string_new("if_true:if_false:"),
        string_new("2")
      )
    );
    parse(
      "(obj match: %[ \
        %[1, 100], \
        %[2, 200], \
        %[3, 300], \
      ])",
      vector_new(
        FM_LOCAL,
        string_new("obj"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("100"),
        FM_TUPLE,
        string_new("2"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("200"),
        FM_TUPLE,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_INTEGER,
        string_new("300"),
        FM_TUPLE,
        string_new("2"),
        FM_TUPLE,
        string_new("3"),
        FM_KEYWORD,
        string_new("match:"),
        string_new("1")
      )
    );
    parse(
      "obj match: %{\"1\": 100, \"2\": 200, \"3\": 300}",
      vector_new(
        FM_LOCAL,
        string_new("obj"),
        FM_STRING,
        string_new("1"),
        FM_INTEGER,
        string_new("100"),
        FM_STRING,
        string_new("2"),
        FM_INTEGER,
        string_new("200"),
        FM_STRING,
        string_new("3"),
        FM_INTEGER,
        string_new("300"),
        FM_HASH,
        string_new("6"),
        FM_KEYWORD,
        string_new("match:"),
        string_new("1")
      )
    );
  });
})

#endif
