#ifndef __NUMERIC_SPEC_H_
#define __NUMERIC_SPEC_H_

#include "../_helpers.h"

module(numeric_spec, {
    it("parses numeric expressions", {
        parse("(0)", marg_vector_new(FM_INTEGER, marg_string_new("0")));
        parse("(0,0,0)", marg_vector_new(FM_INTEGER, marg_string_new("0"), FM_INTEGER, marg_string_new("0"), FM_INTEGER, marg_string_new("0")));
        parse("(42)", marg_vector_new(FM_INTEGER, marg_string_new("42")));
        parse("(41, 42, 43)", marg_vector_new(FM_INTEGER, marg_string_new("41"), FM_INTEGER, marg_string_new("42"), FM_INTEGER, marg_string_new("43")));
        parse("(41, (42), 43)", marg_vector_new(FM_INTEGER, marg_string_new("41"), FM_INTEGER, marg_string_new("42"), FM_INTEGER, marg_string_new("43")));
        parse("(-41 - (-42))", marg_vector_new(FM_INTEGER, marg_string_new("-41"), FM_INTEGER, marg_string_new("-42"), FM_BINARY, marg_string_new("-")));
        parse("((-41), (-42))", marg_vector_new(FM_INTEGER, marg_string_new("-41"), FM_INTEGER, marg_string_new("-42")));
        parse("(42 - 41)", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_INTEGER, marg_string_new("41"), FM_BINARY, marg_string_new("-")));
    });

    it("parses integers literals", {
        parse("42", marg_vector_new(FM_INTEGER, marg_string_new("42")));
        parse("-42", marg_vector_new(FM_INTEGER, marg_string_new("-42")));
        parse("+42", marg_vector_new(FM_INTEGER, marg_string_new("42")));

        parse("4_200", marg_vector_new(FM_INTEGER, marg_string_new("4200")));
        parse("-4_200", marg_vector_new(FM_INTEGER, marg_string_new("-4200")));
    });

    it("parses float literals", {
        parse("42.0", marg_vector_new(FM_FLOAT, marg_string_new("42.0")));
        parse("-42.0", marg_vector_new(FM_FLOAT, marg_string_new("-42.0")));
        parse("986513.00056129", marg_vector_new(FM_FLOAT, marg_string_new("986513.00056129")));
        parse("-986513.00056129", marg_vector_new(FM_FLOAT, marg_string_new("-986513.00056129")));
        parse("1234 e: -2", marg_vector_new(FM_INTEGER, marg_string_new("1234"), FM_INTEGER, marg_string_new("-2"), FM_KEYWORD, marg_string_new("e:"), marg_string_new("1")));
        parse("1234 E: -2", marg_vector_new(FM_INTEGER, marg_string_new("1234"), FM_INTEGER, marg_string_new("-2"), FM_KEYWORD, marg_string_new("E:"), marg_string_new("1")));
        parse("1.234 e: 1", marg_vector_new(FM_FLOAT, marg_string_new("1.234"), FM_INTEGER, marg_string_new("1"), FM_KEYWORD, marg_string_new("e:"), marg_string_new("1")));
        parse("1.234 E: 1", marg_vector_new(FM_FLOAT, marg_string_new("1.234"), FM_INTEGER, marg_string_new("1"), FM_KEYWORD, marg_string_new("E:"), marg_string_new("1")));
    });

    it("parses binary literals", {
        parse("0b0110", marg_vector_new(FM_INTEGER, marg_string_new("6")));
        parse("0B10", marg_vector_new(FM_INTEGER, marg_string_new("2")));
        parse("-0b0110", marg_vector_new(FM_INTEGER, marg_string_new("-6")));
        parse("-0B10", marg_vector_new(FM_INTEGER, marg_string_new("-2")));
        parse("( \
            x = 0b0101 + 0b1011, \
            x to_int puts, \
        )", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_INTEGER, marg_string_new("11"), FM_BINARY, marg_string_new("+"), FM_STORE, marg_string_new("x"), FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("to_int"), FM_UNARY, marg_string_new("puts")));
    });

    it("parses hexadecimal literals", {
        parse("0xbeef", marg_vector_new(FM_INTEGER, marg_string_new("48879")));
        parse("-0xbeEf", marg_vector_new(FM_INTEGER, marg_string_new("-48879")));
        parse("0X0427", marg_vector_new(FM_INTEGER, marg_string_new("1063")));
        parse("-0X0427", marg_vector_new(FM_INTEGER, marg_string_new("-1063")));
        parse("(x = 0xbeef to_bin to_int puts)", marg_vector_new(FM_INTEGER, marg_string_new("48879"), FM_UNARY, marg_string_new("to_bin"), FM_UNARY, marg_string_new("to_int"), FM_UNARY, marg_string_new("puts"), FM_STORE, marg_string_new("x")));
        parse("(0xbeef - 0xabb2)", marg_vector_new(FM_INTEGER, marg_string_new("48879"), FM_INTEGER, marg_string_new("43954"), FM_BINARY, marg_string_new("-")));
    });

    it("parses octal literals", {
        parse("0o741", marg_vector_new(FM_INTEGER, marg_string_new("481")));
        parse("-0o741", marg_vector_new(FM_INTEGER, marg_string_new("-481")));
        parse("0O0210", marg_vector_new(FM_INTEGER, marg_string_new("136")));
        parse("-0O0210", marg_vector_new(FM_INTEGER, marg_string_new("-136")));
        parse("(x = 0o751 to_hex to_bin to_int puts)", marg_vector_new(FM_INTEGER, marg_string_new("489"), FM_UNARY, marg_string_new("to_hex"), FM_UNARY, marg_string_new("to_bin"), FM_UNARY, marg_string_new("to_int"), FM_UNARY, marg_string_new("puts"), FM_STORE, marg_string_new("x")));
        parse("(0O541 + 0o777)", marg_vector_new(FM_INTEGER, marg_string_new("353"), FM_INTEGER, marg_string_new("511"), FM_BINARY, marg_string_new("+")));
    });

    it("parses negative characters", {
        parse("-'a'", marg_vector_new(FM_CHAR, marg_string_new("-a")));
        parse("-'æ'", marg_vector_new(FM_CHAR, marg_string_new("-æ")));
    });
})

#endif
