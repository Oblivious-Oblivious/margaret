#ifndef __TENSORS_SPEC_H_
#define __TENSORS_SPEC_H_

#include "_helpers.h"

module(tensors_spec, {
  it("parses tensor literals", {
    parse("[]", vector_new(FM_TENSOR, string_new("0")));
    parse("([])", vector_new(FM_TENSOR, string_new("0")));
    parse(
      "[[], []]",
      vector_new(
        FM_TENSOR,
        string_new("0"),
        FM_TENSOR,
        string_new("0"),
        FM_TENSOR,
        string_new("2")
      )
    );
    parse(
      "[41, 42]",
      vector_new(
        FM_INTEGER,
        string_new("41"),
        FM_INTEGER,
        string_new("42"),
        FM_TENSOR,
        string_new("2")
      )
    );
    parse(
      "([41, 42])",
      vector_new(
        FM_INTEGER,
        string_new("41"),
        FM_INTEGER,
        string_new("42"),
        FM_TENSOR,
        string_new("2")
      )
    );
    parse(
      "[42, \"str\", var]",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_STRING,
        string_new("str"),
        FM_LOCAL,
        string_new("var"),
        FM_TENSOR,
        string_new("3")
      )
    );
    parse(
      "[42, \"Hello\", v1, v2]",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_STRING,
        string_new("Hello"),
        FM_LOCAL,
        string_new("v1"),
        FM_LOCAL,
        string_new("v2"),
        FM_TENSOR,
        string_new("4")
      )
    );
    parse(
      "[42, \"Hello\", v1, v2, (), [], %{}, x = 1]",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_STRING,
        string_new("Hello"),
        FM_LOCAL,
        string_new("v1"),
        FM_LOCAL,
        string_new("v2"),
        FM_NIL,
        FM_TENSOR,
        string_new("0"),
        FM_TABLE,
        string_new("0"),
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("="),
        FM_TENSOR,
        string_new("8")
      )
    );
  });
})

#endif
