#ifndef __CONSTANTS_SPEC_H_
#define __CONSTANTS_SPEC_H_

#include "_helpers.h"

module(constants_spec, {
  it("parses constants", {
    parse(
      "(b = $true)",
      vector_new(FM_LOCAL, string_new("b"), FM_TRUE, FM_BINARY, string_new("="))
    );
    parse(
      "(b = $false)",
      vector_new(
        FM_LOCAL, string_new("b"), FM_FALSE, FM_BINARY, string_new("=")
      )
    );
    parse(
      "(x = $nil)",
      vector_new(FM_LOCAL, string_new("x"), FM_NIL, FM_BINARY, string_new("="))
    );
    parse(
      "true = 123",
      vector_new(
        FM_LOCAL,
        string_new("true"),
        FM_INTEGER,
        string_new("123"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "false = 123",
      vector_new(
        FM_LOCAL,
        string_new("false"),
        FM_INTEGER,
        string_new("123"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "nil = 123",
      vector_new(
        FM_LOCAL,
        string_new("nil"),
        FM_INTEGER,
        string_new("123"),
        FM_BINARY,
        string_new("=")
      )
    );

    parse(
      "(x = 1)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = -1)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("1"),
        FM_LHS,
        string_new("-"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 3.14159)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_FLOAT,
        string_new("3.14159"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 0.42)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_FLOAT,
        string_new("0.42"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 0xbeef)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("48879"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 0b0101)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("5"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 0o741)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("481"),
        FM_BINARY,
        string_new("=")
      )
    );

    parse(
      "(x = \"Hello\")",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("Hello"),
        FM_BINARY,
        string_new("=")
      )
    );
  });
})

#endif
