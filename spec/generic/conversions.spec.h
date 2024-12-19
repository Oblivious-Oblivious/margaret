#ifndef __CONVERSIONS_SPEC_H_
#define __CONVERSIONS_SPEC_H_

#include "_helpers.h"

module(conversions_spec, {
  it("parses object conversion", {
    parse(
      "x = 3.99 to_int",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_FLOAT,
        string_new("3.99"),
        FM_UNARY,
        string_new("to_int"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = 3.99 to_fraction",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_FLOAT,
        string_new("3.99"),
        FM_UNARY,
        string_new("to_fraction"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = 3 to_float",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("to_float"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = 65 to_char",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("65"),
        FM_UNARY,
        string_new("to_char"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = \"A\" to_ascii",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("A"),
        FM_UNARY,
        string_new("to_ascii"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = 'b' to_ascii",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("b"),
        FM_UNARY,
        string_new("to_ascii"),
        FM_ASSIGNMENT
      )
    );
  });
})

#endif
