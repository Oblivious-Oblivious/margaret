#ifndef __COMPLEX_SPEC_H_
#define __COMPLEX_SPEC_H_

#include "_helpers.h"

module(complex_spec, {
  it("parses complex literals", {
    parse(
      "1i", vector_new(FM_INTEGER, string_new("1"), FM_UNARY, string_new("i"))
    );
    parse(
      "1i * 1i",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_UNARY,
        string_new("i"),
        FM_INTEGER,
        string_new("1"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("*")
      )
    );
    parse(
      "12.3r i",
      vector_new(
        FM_FLOAT,
        string_new("12.3"),
        FM_UNARY,
        string_new("r"),
        FM_UNARY,
        string_new("i")
      )
    );

    parse(
      "12.3ri",
      vector_new(FM_FLOAT, string_new("12.3"), FM_UNARY, string_new("ri"))
    );
  });

  it("parses complex literal messages", {
    parse(
      "$Complex polar_form: 3 arg: 0",
      vector_new(
        FM_GLOBAL,
        string_new("$Complex"),
        FM_INTEGER,
        string_new("3"),
        FM_INTEGER,
        string_new("0"),
        FM_KEYWORD,
        string_new("polar_form:arg:"),
        string_new("2")
      )
    );

    parse(
      "$Complex rect_form: 1 imag: 2",
      vector_new(
        FM_GLOBAL,
        string_new("$Complex"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_KEYWORD,
        string_new("rect_form:imag:"),
        string_new("2")
      )
    );

    parse(
      "(2 + 3i) * (2 + 3i)",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_BINARY,
        string_new("*")
      )
    );

    parse(
      "1i ** 2",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_UNARY,
        string_new("i"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("**")
      )
    );

    parse(
      "(2 + 3i) + (2 + 3i)",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_BINARY,
        string_new("+")
      )
    );

    parse(
      "(2 + 3i) - (2 + 3i)",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_BINARY,
        string_new("-")
      )
    );

    parse(
      "(2 + 3i) * (2 + 3i)",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_BINARY,
        string_new("*")
      )
    );

    parse(
      "-(2 + 3i)",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_LHS,
        string_new("-")
      )
    );

    parse(
      "(2 + 3i) / (2 + 3i)",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_BINARY,
        string_new("/")
      )
    );

    parse(
      "(2 + 3i) == (2 + 3i)",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_BINARY,
        string_new("==")
      )
    );

    parse(
      "(3 + 4i) abs",
      vector_new(
        FM_INTEGER,
        string_new("3"),
        FM_INTEGER,
        string_new("4"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_UNARY,
        string_new("abs")
      )
    );

    parse(
      "(3 + $Float PI i) angle",
      vector_new(
        FM_INTEGER,
        string_new("3"),
        FM_GLOBAL,
        string_new("$Float"),
        FM_UNARY,
        string_new("PI"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("+"),
        FM_UNARY,
        string_new("angle")
      )
    );
  });
})

#endif
