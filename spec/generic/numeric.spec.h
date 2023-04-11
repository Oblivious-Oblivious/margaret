#ifndef __NUMERIC_SPEC_H_
#define __NUMERIC_SPEC_H_

#include "../_helpers.h"

module(numeric_spec, {
    it("parses numeric expressions", {
        parse("(0)", marg_vector_new(OP_PUSH_0));
        parse("(0,0,0)", marg_vector_new(OP_PUSH_0, OP_PUSH_0, OP_PUSH_0));
        parse("(42)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42")));
        parse("(41, 42, 43)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("43")));
        parse("(41, (42), 43)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("43")));
        parse("(-41 - (-42))", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-41"), OP_PUSH_INTEGER, marg_string_new("-42"), OP_BINARY, marg_string_new("-")));
        parse("((-41), (-42))", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-41"), OP_PUSH_INTEGER, marg_string_new("-42")));
        parse("(42 - 41)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("41"), OP_BINARY, marg_string_new("-")));
    });

    it("parses integers literals", {
        parse("42", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42")));
        parse("-42", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-42")));
        parse("+42", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42")));

        parse("4_200", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("4200")));
        parse("-4_200", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-4200")));
    });

    it("parses float literals", {
        parse("42.0", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("42.0")));
        parse("-42.0", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("-42.0")));
        parse("986513.00056129", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("986513.00056129")));
        parse("-986513.00056129", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("-986513.00056129")));
        // TODO `E` floats
        // parse("1234e-2"), marg_string_new("12.34");
        // parse("1234E-2"), marg_string_new("12.34");
        // parse("1.234e1"), marg_string_new("12.34");
        // parse("1.234E1"), marg_string_new("12.34");
    });

    it("parses binary literals", {
        parse("0b0110", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("6")));
        parse("0B10", marg_vector_new(OP_PUSH_2));
        parse("-0b0110", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-6")));
        parse("-0B10", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-2")));
        parse("( \
            x = 0b0101 + 0b1011, \
            x to_int puts, \
        )", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_INTEGER, marg_string_new("11"), OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("to_int"), OP_UNARY, marg_string_new("puts")));
    });

    it("parses hexadecimal literals", {
        parse("0xbeef", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("48879")));
        parse("-0xbeEf", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-48879")));
        parse("0X0427", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("1063")));
        parse("-0X0427", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-1063")));
        parse("(x = 0xbeef to_bin to_int puts)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("48879"), OP_UNARY, marg_string_new("to_bin"), OP_UNARY, marg_string_new("to_int"), OP_UNARY, marg_string_new("puts"), OP_STORE, marg_string_new("x")));
        parse("(0xbeef - 0xabb2)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("48879"), OP_PUSH_INTEGER, marg_string_new("43954"), OP_BINARY, marg_string_new("-")));
    });

    it("parses octal literals", {
        parse("0o741", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("481")));
        parse("-0o741", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-481")));
        parse("0O0210", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("136")));
        parse("-0O0210", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-136")));
        parse("(x = 0o751 to_hex to_bin to_int puts)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("489"), OP_UNARY, marg_string_new("to_hex"), OP_UNARY, marg_string_new("to_bin"), OP_UNARY, marg_string_new("to_int"), OP_UNARY, marg_string_new("puts"), OP_STORE, marg_string_new("x")));
        parse("(0O541 + 0o777)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("353"), OP_PUSH_INTEGER, marg_string_new("511"), OP_BINARY, marg_string_new("+")));
    });

    it("parses negative characters", {
        parse("-'a'", marg_vector_new(OP_PUSH_CHAR, marg_string_new("-'a'")));
        parse("-'æ'", marg_vector_new(OP_PUSH_CHAR, marg_string_new("-'æ'")));
    });
})

#endif