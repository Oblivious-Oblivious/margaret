#ifndef __BITSTRINGS_SPEC_H_
#define __BITSTRINGS_SPEC_H_

#include "_helpers.h"

module(bitstrings_spec, {
  it("parses bitstrings literals", {
    parse("%()", vector_new(FM_BITSTRING, string_new("0")));
    parse("(%())", vector_new(FM_BITSTRING, string_new("0")));
    parse(
      "%(%(), %())",
      vector_new(
        FM_BITSTRING,
        string_new("0"),
        FM_INTEGER,
        string_new("8"),
        FM_BITSTRING,
        string_new("0"),
        FM_INTEGER,
        string_new("8"),
        FM_BITSTRING,
        string_new("4")
      )
    );
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
      "(%(41, 42))",
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
      "%(42, \"str\", var)",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("8"),
        FM_STRING,
        string_new("str"),
        FM_INTEGER,
        string_new("8"),
        FM_LOCAL,
        string_new("var"),
        FM_INTEGER,
        string_new("8"),
        FM_BITSTRING,
        string_new("6")
      )
    );
    parse(
      "%(0::1, 0::1, 1::1, 1::1)",
      vector_new(
        FM_INTEGER,
        string_new("0"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("0"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("1"),
        FM_BITSTRING,
        string_new("8")
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
})

#endif
