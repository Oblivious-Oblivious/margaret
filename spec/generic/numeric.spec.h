#ifndef __NUMERIC_SPEC_H_
#define __NUMERIC_SPEC_H_

#include "_helpers.h"

module(numeric_spec, {
  it("parses numeric expressions", {
    parse("(0)", vector_new(FM_INTEGER, string_new("0")));
    parse(
      "(0,0,0)",
      vector_new(
        FM_INTEGER,
        string_new("0"),
        FM_INTEGER,
        string_new("0"),
        FM_INTEGER,
        string_new("0")
      )
    );
    parse("(42)", vector_new(FM_INTEGER, string_new("42")));
    parse(
      "(41, 42, 43)",
      vector_new(
        FM_INTEGER,
        string_new("41"),
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("43")
      )
    );
    parse(
      "(41, (42), 43)",
      vector_new(
        FM_INTEGER,
        string_new("41"),
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("43")
      )
    );
    parse(
      "(-41 - (-42))",
      vector_new(
        FM_INTEGER,
        string_new("41"),
        FM_LHS,
        string_new("-"),
        FM_INTEGER,
        string_new("42"),
        FM_LHS,
        string_new("-"),
        FM_BINARY,
        string_new("-")
      )
    );
    parse(
      "((-41), (-42))",
      vector_new(
        FM_INTEGER,
        string_new("41"),
        FM_LHS,
        string_new("-"),
        FM_INTEGER,
        string_new("42"),
        FM_LHS,
        string_new("-")
      )
    );
    parse(
      "(42 - 41)",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("41"),
        FM_BINARY,
        string_new("-")
      )
    );
  });

  it("parses integers literals", {
    parse("42", vector_new(FM_INTEGER, string_new("42")));
    parse(
      "-42", vector_new(FM_INTEGER, string_new("42"), FM_LHS, string_new("-"))
    );
    parse(
      "+42", vector_new(FM_INTEGER, string_new("42"), FM_LHS, string_new("+"))
    );

    parse("4_200", vector_new(FM_INTEGER, string_new("4200")));
    parse(
      "-4_200",
      vector_new(FM_INTEGER, string_new("4200"), FM_LHS, string_new("-"))
    );
  });

  it("parses float literals", {
    parse("42.0", vector_new(FM_FLOAT, string_new("42.0")));
    parse(
      "-42.0", vector_new(FM_FLOAT, string_new("42.0"), FM_LHS, string_new("-"))
    );
    parse(
      "986513.00056129", vector_new(FM_FLOAT, string_new("986513.00056129"))
    );
    parse(
      "-986513.00056129",
      vector_new(
        FM_FLOAT, string_new("986513.00056129"), FM_LHS, string_new("-")
      )
    );
    parse(
      "1234 e: -2",
      vector_new(
        FM_INTEGER,
        string_new("1234"),
        FM_INTEGER,
        string_new("2"),
        FM_LHS,
        string_new("-"),
        FM_KEYWORD,
        string_new("e:"),
        string_new("1")
      )
    );
    parse(
      "1234 E: -2",
      vector_new(
        FM_INTEGER,
        string_new("1234"),
        FM_INTEGER,
        string_new("2"),
        FM_LHS,
        string_new("-"),
        FM_KEYWORD,
        string_new("E:"),
        string_new("1")
      )
    );
    parse(
      "1.234 e: 1",
      vector_new(
        FM_FLOAT,
        string_new("1.234"),
        FM_INTEGER,
        string_new("1"),
        FM_KEYWORD,
        string_new("e:"),
        string_new("1")
      )
    );
    parse(
      "1.234 E: 1",
      vector_new(
        FM_FLOAT,
        string_new("1.234"),
        FM_INTEGER,
        string_new("1"),
        FM_KEYWORD,
        string_new("E:"),
        string_new("1")
      )
    );
  });

  it("parses binary literals", {
    parse("0b0110", vector_new(FM_INTEGER, string_new("6")));
    parse("0B10", vector_new(FM_INTEGER, string_new("2")));
    parse(
      "-0b0110",
      vector_new(FM_INTEGER, string_new("6"), FM_LHS, string_new("-"))
    );
    parse(
      "-0B10", vector_new(FM_INTEGER, string_new("2"), FM_LHS, string_new("-"))
    );
    parse(
      "( \
        x = 0b0101 + 0b1011, \
        x to_int puts, \
      )",
      vector_new(
        FM_INTEGER,
        string_new("5"),
        FM_INTEGER,
        string_new("11"),
        FM_BINARY,
        string_new("+"),
        FM_LOCAL,
        string_new("x"),
        FM_BINARY,
        string_new("="),
        FM_LOCAL,
        string_new("x"),
        FM_UNARY,
        string_new("to_int"),
        FM_UNARY,
        string_new("puts")
      )
    );
  });

  it("parses hexadecimal literals", {
    parse("0xbeef", vector_new(FM_INTEGER, string_new("48879")));
    parse(
      "-0xbeEf",
      vector_new(FM_INTEGER, string_new("48879"), FM_LHS, string_new("-"))
    );
    parse("0X0427", vector_new(FM_INTEGER, string_new("1063")));
    parse(
      "-0X0427",
      vector_new(FM_INTEGER, string_new("1063"), FM_LHS, string_new("-"))
    );
    parse(
      "(x = 0xbeef to_bin to_int puts)",
      vector_new(
        FM_INTEGER,
        string_new("48879"),
        FM_UNARY,
        string_new("to_bin"),
        FM_UNARY,
        string_new("to_int"),
        FM_UNARY,
        string_new("puts"),
        FM_LOCAL,
        string_new("x"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(0xbeef - 0xabb2)",
      vector_new(
        FM_INTEGER,
        string_new("48879"),
        FM_INTEGER,
        string_new("43954"),
        FM_BINARY,
        string_new("-")
      )
    );
  });

  it("parses octal literals", {
    parse("0o741", vector_new(FM_INTEGER, string_new("481")));
    parse(
      "-0o741",
      vector_new(FM_INTEGER, string_new("481"), FM_LHS, string_new("-"))
    );
    parse("0O0210", vector_new(FM_INTEGER, string_new("136")));
    parse(
      "-0O0210",
      vector_new(FM_INTEGER, string_new("136"), FM_LHS, string_new("-"))
    );
    parse(
      "(x = 0o751 to_hex to_bin to_int puts)",
      vector_new(
        FM_INTEGER,
        string_new("489"),
        FM_UNARY,
        string_new("to_hex"),
        FM_UNARY,
        string_new("to_bin"),
        FM_UNARY,
        string_new("to_int"),
        FM_UNARY,
        string_new("puts"),
        FM_LOCAL,
        string_new("x"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(0O541 + 0o777)",
      vector_new(
        FM_INTEGER,
        string_new("353"),
        FM_INTEGER,
        string_new("511"),
        FM_BINARY,
        string_new("+")
      )
    );
  });

  it("parses negative characters", {
    parse(
      "-'a'", vector_new(FM_STRING, string_new("a"), FM_LHS, string_new("-"))
    );
    parse(
      "-'æ'", vector_new(FM_STRING, string_new("æ"), FM_LHS, string_new("-"))
    );
  });
})

#endif
