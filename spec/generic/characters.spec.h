#ifndef __CHARACTERS_SPEC_H_
#define __CHARACTERS_SPEC_H_

#include "_helpers.h"

module(characters_spec, {
  it("parses character literals", {
    parse("'a'", vector_new(FM_STRING, string_new("a")));
    parse("'\n'", vector_new(FM_STRING, string_new("\n")));
    parse("'œ'", vector_new(FM_STRING, string_new("œ")));
  });

  it("parses character messages", {
    parse(
      "(x = 'a' is_lowercase?)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_UNARY,
        string_new("is_lowercase?"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 'a' is_uppercase?)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_UNARY,
        string_new("is_uppercase?"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 'a' is_letter?)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_UNARY,
        string_new("is_letter?"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 'a' is_digit?)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_UNARY,
        string_new("is_digit?"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 'a' is_alphanumeric?)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_UNARY,
        string_new("is_alphanumeric?"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 'a' is_separator?)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_UNARY,
        string_new("is_separator?"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 'a' is_vowel?)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_UNARY,
        string_new("is_vowel?"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 'a' to_digit)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_UNARY,
        string_new("to_digit"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 'a' to_lowercase)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_UNARY,
        string_new("to_lowercase"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 'a' to_uppercase)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_UNARY,
        string_new("to_uppercase"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 'a' to_ascii)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_UNARY,
        string_new("to_ascii"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = 'a' <= 'b')",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("a"),
        FM_STRING,
        string_new("b"),
        FM_BINARY,
        string_new("<="),
        FM_BINARY,
        string_new("=")
      )
    );
  });
})

#endif
