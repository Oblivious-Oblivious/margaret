#ifndef __CONSTANTS_SPEC_H_
#define __CONSTANTS_SPEC_H_

#include "_helpers.h"

module(constants_spec, {
  it("parses constants", {
    parse(
      "b = $true", vector_new(FM_LOCAL, string_new("b"), FM_TRUE, FM_ASSIGNMENT)
    );
    parse(
      "b = $false",
      vector_new(FM_LOCAL, string_new("b"), FM_FALSE, FM_ASSIGNMENT)
    );
    parse(
      "x = $nil", vector_new(FM_LOCAL, string_new("x"), FM_NIL, FM_ASSIGNMENT)
    );
    parse(
      "true = 123",
      vector_new(
        FM_LOCAL,
        string_new("true"),
        FM_INTEGER,
        string_new("123"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "false = 123",
      vector_new(
        FM_LOCAL,
        string_new("false"),
        FM_INTEGER,
        string_new("123"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "nil = 123",
      vector_new(
        FM_LOCAL,
        string_new("nil"),
        FM_INTEGER,
        string_new("123"),
        FM_ASSIGNMENT
      )
    );

    parse(
      "x = 1",
      vector_new(
        FM_LOCAL, string_new("x"), FM_INTEGER, string_new("1"), FM_ASSIGNMENT
      )
    );
    parse(
      "x = -1",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("1"),
        FM_LHS,
        string_new("-"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = 3.14159",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_FLOAT,
        string_new("3.14159"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = 0.42",
      vector_new(
        FM_LOCAL, string_new("x"), FM_FLOAT, string_new("0.42"), FM_ASSIGNMENT
      )
    );
    parse(
      "x = 0xbeef",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("48879"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = 0b0101",
      vector_new(
        FM_LOCAL, string_new("x"), FM_INTEGER, string_new("5"), FM_ASSIGNMENT
      )
    );
    parse(
      "x = 0o741",
      vector_new(
        FM_LOCAL, string_new("x"), FM_INTEGER, string_new("481"), FM_ASSIGNMENT
      )
    );

    parse(
      "x = \"Hello\"",
      vector_new(
        FM_LOCAL, string_new("x"), FM_STRING, string_new("Hello"), FM_ASSIGNMENT
      )
    );
  });
})

#endif
