#ifndef __RATIONAL_SPEC_H_
#define __RATIONAL_SPEC_H_

#include "_helpers.h"

module(rational_spec, {
  it("parses rational literals", {
    parse(
      "1r", vector_new(FM_INTEGER, string_new("1"), FM_UNARY, string_new("r"))
    );
    parse(
      "2/3r",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("r"),
        FM_BINARY,
        string_new("/")
      )
    );
    parse(
      "-1r",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_LHS,
        string_new("-"),
        FM_UNARY,
        string_new("r")
      )
    );
    parse(
      "-2/3r",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_LHS,
        string_new("-"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("r"),
        FM_BINARY,
        string_new("/")
      )
    );
    parse(
      "2/(-3r)",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_LHS,
        string_new("-"),
        FM_UNARY,
        string_new("r"),
        FM_BINARY,
        string_new("/")
      )
    );
    parse(
      "-2/(-3r)",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_LHS,
        string_new("-"),
        FM_INTEGER,
        string_new("3"),
        FM_LHS,
        string_new("-"),
        FM_UNARY,
        string_new("r"),
        FM_BINARY,
        string_new("/")
      )
    );
    parse(
      "+1 / (+3r)",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_LHS,
        string_new("+"),
        FM_INTEGER,
        string_new("3"),
        FM_LHS,
        string_new("+"),
        FM_UNARY,
        string_new("r"),
        FM_BINARY,
        string_new("/")
      )
    );
    parse(
      "1.2r", vector_new(FM_FLOAT, string_new("1.2"), FM_UNARY, string_new("r"))
    );
    parse(
      "1_1/2_2r",
      vector_new(
        FM_INTEGER,
        string_new("11"),
        FM_INTEGER,
        string_new("22"),
        FM_UNARY,
        string_new("r"),
        FM_BINARY,
        string_new("/")
      )
    );
    parse(
      "2/4r",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("4"),
        FM_UNARY,
        string_new("r"),
        FM_BINARY,
        string_new("/")
      )
    );
  });

  it(
    "parses rational literal messages",
    {
      // TODO -
    }
  );
})

#endif
