#ifndef __LITERAL_MODULE_SPEC_H_
#define __LITERAL_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "association_list.module.spec.h"
#include "bit_list.module.spec.h"
#include "method_definition.module.spec.h"
#include "param_list.module.spec.h"
#include "scalar.module.spec.h"

module(literal, {
  it("parses groups", {
    parse("()", vector_new(FM_NIL));
    parse("(42)", vector_new(FM_INTEGER, string_new("42")));
    parse(
      "(42, 43)",
      vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("43"))
    );
    parse(
      "(42, 43, 44)",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("43"),
        FM_INTEGER,
        string_new("44")
      )
    );
  });

  it("parses tensors", {
    parse("[]", vector_new(FM_TENSOR, string_new("0")));
    parse(
      "[42]",
      vector_new(FM_INTEGER, string_new("42"), FM_TENSOR, string_new("1"))
    );
    parse(
      "[42, 43]",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("43"),
        FM_TENSOR,
        string_new("2")
      )
    );
    parse(
      "[42, 43, 44]",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("43"),
        FM_INTEGER,
        string_new("44"),
        FM_TENSOR,
        string_new("3")
      )
    );
  });

  it("parses headless methods", {
    parse("{}", vector_new(FM_METHOD_START, FM_NIL, FM_METHOD_END));
    parse("{|}", vector_new(FM_METHOD_START, FM_NIL, FM_METHOD_END));
    parse(
      "{ 42 }",
      vector_new(FM_METHOD_START, FM_INTEGER, string_new("42"), FM_METHOD_END)
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
  });

  it("parses bitstrings", {
    parse("%()", vector_new(FM_BITSTRING, string_new("0")));
    parse(
      "%(41, 42)",
      vector_new(
        FM_INTEGER,
        string_new("41"),
        FM_INTEGER,
        string_new("8"),
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("8"),
        FM_BITSTRING,
        string_new("4")
      )
    );
    parse(
      "%(3::4)",
      vector_new(
        FM_INTEGER,
        string_new("3"),
        FM_INTEGER,
        string_new("4"),
        FM_BITSTRING,
        string_new("2")
      )
    );
  });

  it("parses tuples", {
    parse("%[]", vector_new(FM_TUPLE, string_new("0")));
    parse(
      "%[%[], %[]]",
      vector_new(
        FM_TUPLE,
        string_new("0"),
        FM_TUPLE,
        string_new("0"),
        FM_TUPLE,
        string_new("2")
      )
    );
    parse(
      "%[1, 2, 3]",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_TUPLE,
        string_new("3")
      )
    );
  });

  it("parses tables", {
    parse("%{}", vector_new(FM_TABLE, string_new("0")));
    parse(
      "%{\"a\": %{}, \"b\": %{}}",
      vector_new(
        FM_STRING,
        string_new("a"),
        FM_TABLE,
        string_new("0"),
        FM_STRING,
        string_new("b"),
        FM_TABLE,
        string_new("0"),
        FM_TABLE,
        string_new("4")
      )
    );
    parse(
      "%{a: 2, b: 3, \"c\": 5}",
      vector_new(
        FM_STRING,
        string_new("a"),
        FM_INTEGER,
        string_new("2"),
        FM_STRING,
        string_new("b"),
        FM_INTEGER,
        string_new("3"),
        FM_STRING,
        string_new("c"),
        FM_INTEGER,
        string_new("5"),
        FM_TABLE,
        string_new("6")
      )
    );
  });

  it("parses method definitions", {
    parse(
      "# 0 fact => 1",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_RECEIVER,
        FM_INTEGER,
        string_new("0"),
        FM_METHOD_NAME,
        string_new("fact"),
        FM_INTEGER,
        string_new("1"),
        FM_METHOD_END
      )
    );
  });

  param_list();
  bit_list();
  association_list();
  method_definition();
  scalar();
})

#endif
