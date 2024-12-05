#ifndef __ASSIGNMENTS_SPEC_H_
#define __ASSIGNMENTS_SPEC_H_

#include "_helpers.h"

module(assignments_spec, {
  it("parses assignments", {
    parse(
      "(x = 4)",
      vector_new(
        FM_LOCAL, string_new("x"), FM_INTEGER, string_new("4"), FM_ASSIGNMENT
      )
    );
    parse(
      "(x = y = z = 6)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("y"),
        FM_LOCAL,
        string_new("z"),
        FM_INTEGER,
        string_new("6"),
        FM_ASSIGNMENT,
        FM_ASSIGNMENT,
        FM_ASSIGNMENT
      )
    );
    parse(
      "(x = (y = 6) + 1)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("y"),
        FM_INTEGER,
        string_new("6"),
        FM_ASSIGNMENT,
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("+"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "(x = Object new)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("Object"),
        FM_UNARY,
        string_new("new"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "var = 12",
      vector_new(
        FM_LOCAL, string_new("var"), FM_INTEGER, string_new("12"), FM_ASSIGNMENT
      )
    );
    parse(
      "arr = []",
      vector_new(
        FM_LOCAL, string_new("arr"), FM_TENSOR, string_new("0"), FM_ASSIGNMENT
      )
    );
    parse(
      "@x = x + 2",
      vector_new(
        FM_INSTANCE,
        string_new("@x"),
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("+"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "a = b",
      vector_new(
        FM_LOCAL, string_new("a"), FM_LOCAL, string_new("b"), FM_ASSIGNMENT
      )
    );
    parse(
      "a = b = c",
      vector_new(
        FM_LOCAL,
        string_new("a"),
        FM_LOCAL,
        string_new("b"),
        FM_LOCAL,
        string_new("c"),
        FM_ASSIGNMENT,
        FM_ASSIGNMENT
      )
    );
    parse(
      "@a = @b = @c",
      vector_new(
        FM_INSTANCE,
        string_new("@a"),
        FM_INSTANCE,
        string_new("@b"),
        FM_INSTANCE,
        string_new("@c"),
        FM_ASSIGNMENT,
        FM_ASSIGNMENT
      )
    );
    parse(
      "$a = $b = $c",
      vector_new(
        FM_GLOBAL,
        string_new("$a"),
        FM_GLOBAL,
        string_new("$b"),
        FM_GLOBAL,
        string_new("$c"),
        FM_ASSIGNMENT,
        FM_ASSIGNMENT
      )
    );
    parse(
      "a = b = c = d = 42",
      vector_new(
        FM_LOCAL,
        string_new("a"),
        FM_LOCAL,
        string_new("b"),
        FM_LOCAL,
        string_new("c"),
        FM_LOCAL,
        string_new("d"),
        FM_INTEGER,
        string_new("42"),
        FM_ASSIGNMENT,
        FM_ASSIGNMENT,
        FM_ASSIGNMENT,
        FM_ASSIGNMENT
      )
    );
    parse(
      "(a = 2, b = 3, c = a = b)",
      vector_new(
        FM_LOCAL,
        string_new("a"),
        FM_INTEGER,
        string_new("2"),
        FM_ASSIGNMENT,
        FM_LOCAL,
        string_new("b"),
        FM_INTEGER,
        string_new("3"),
        FM_ASSIGNMENT,
        FM_LOCAL,
        string_new("c"),
        FM_LOCAL,
        string_new("a"),
        FM_LOCAL,
        string_new("b"),
        FM_ASSIGNMENT,
        FM_ASSIGNMENT
      )
    );
    parse(
      "((a = 2), (b = 3), (c = a = b))",
      vector_new(
        FM_LOCAL,
        string_new("a"),
        FM_INTEGER,
        string_new("2"),
        FM_ASSIGNMENT,
        FM_LOCAL,
        string_new("b"),
        FM_INTEGER,
        string_new("3"),
        FM_ASSIGNMENT,
        FM_LOCAL,
        string_new("c"),
        FM_LOCAL,
        string_new("a"),
        FM_LOCAL,
        string_new("b"),
        FM_ASSIGNMENT,
        FM_ASSIGNMENT
      )
    );
    parse(
      "a = b = (c = 42) + 12",
      vector_new(
        FM_LOCAL,
        string_new("a"),
        FM_LOCAL,
        string_new("b"),
        FM_LOCAL,
        string_new("c"),
        FM_INTEGER,
        string_new("42"),
        FM_ASSIGNMENT,
        FM_INTEGER,
        string_new("12"),
        FM_BINARY,
        string_new("+"),
        FM_ASSIGNMENT,
        FM_ASSIGNMENT
      )
    );
    parse(
      "a = 12 + 3 * 4",
      vector_new(
        FM_LOCAL,
        string_new("a"),
        FM_INTEGER,
        string_new("12"),
        FM_INTEGER,
        string_new("3"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("4"),
        FM_BINARY,
        string_new("*"),
        FM_ASSIGNMENT
      )
    );
  });

  it("parses assignments as a plain message on non assignable values", {
    parse(
      "[a, b, c] = [1, 2, 3]",
      vector_new(
        FM_LOCAL,
        string_new("a"),
        FM_LOCAL,
        string_new("b"),
        FM_LOCAL,
        string_new("c"),
        FM_TENSOR,
        string_new("3"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_TENSOR,
        string_new("3"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "a = 3 + 4",
      vector_new(
        FM_LOCAL,
        string_new("a"),
        FM_INTEGER,
        string_new("3"),
        FM_INTEGER,
        string_new("4"),
        FM_BINARY,
        string_new("+"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "2 = 3 + 4",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_INTEGER,
        string_new("4"),
        FM_BINARY,
        string_new("+"),
        FM_ASSIGNMENT
      )
    );
  });
})

#endif
