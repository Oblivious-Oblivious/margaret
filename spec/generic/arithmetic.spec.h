#ifndef __ARITHMETIC_SPEC_H_
#define __ARITHMETIC_SPEC_H_

#include "../_helpers.h"

module(arithmetic_spec, {
    it("parses arithmetic expressions", {
        parse("(x = 6 + 3)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("6"), OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("x")));
        parse("(x = 6 - 3)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("6"), OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("-"), OP_STORE, marg_string_new("x")));
        parse("(x = 6 * 3)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("6"), OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("*"), OP_STORE, marg_string_new("x")));
        parse("(x = 1 + 2 * 3)", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("*"), OP_STORE, marg_string_new("x")));
        parse("(x = 5 / 3)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("/"), OP_STORE, marg_string_new("x")));
        parse("(x = 5.0 / 3.0)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("5.0"), OP_PUSH_FLOAT, marg_string_new("3.0"), OP_BINARY, marg_string_new("/"), OP_STORE, marg_string_new("x")));
        parse("(x = 5.0 // 3.0)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("5.0"), OP_PUSH_FLOAT, marg_string_new("3.0"), OP_BINARY, marg_string_new("//"), OP_STORE, marg_string_new("x")));
        parse("(x = 5.0 rem: 3.0)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("5.0"), OP_PUSH_FLOAT, marg_string_new("3.0"), OP_KEYWORD, marg_string_new("rem:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = -5)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-5"), OP_STORE, marg_string_new("x")));
        parse("(x = 5 sign)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_UNARY, marg_string_new("sign"), OP_STORE, marg_string_new("x")));
        parse("(x = 5 negated)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_UNARY, marg_string_new("negated"), OP_STORE, marg_string_new("x")));
        parse("(x = 1.2 integer_part)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("1.2"), OP_UNARY, marg_string_new("integer_part"), OP_STORE, marg_string_new("x")));
        parse("(x = 1.2 fraction_part)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("1.2"), OP_UNARY, marg_string_new("fraction_part"), OP_STORE, marg_string_new("x")));
        parse("(x = 5 reciprocal)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_UNARY, marg_string_new("reciprocal"), OP_STORE, marg_string_new("x")));
        parse("(x = 6 * 3.1)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("6"), OP_PUSH_FLOAT, marg_string_new("3.1"), OP_BINARY, marg_string_new("*"), OP_STORE, marg_string_new("x")));
        parse("(x = 5 squared)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_UNARY, marg_string_new("squared"), OP_STORE, marg_string_new("x")));
        parse("(x = 25 sqrt)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("25"), OP_UNARY, marg_string_new("sqrt"), OP_STORE, marg_string_new("x")));
        parse("(x = 5 raised_to: 2)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_2, OP_KEYWORD, marg_string_new("raised_to:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 5 raised_to_integer: 2)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_2, OP_KEYWORD, marg_string_new("raised_to_integer:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 5 exp)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_UNARY, marg_string_new("exp"), OP_STORE, marg_string_new("x")));
        parse("(x = -5 abs)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-5"), OP_UNARY, marg_string_new("abs"), OP_STORE, marg_string_new("x")));
        parse("(x = 3.99 rounded)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("3.99"), OP_UNARY, marg_string_new("rounded"), OP_STORE, marg_string_new("x")));
        parse("(x = 3.99 truncated)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("3.99"), OP_UNARY, marg_string_new("truncated"), OP_STORE, marg_string_new("x")));
        parse("(x = 3.99 round_to: 1)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("3.99"), OP_PUSH_1, OP_KEYWORD, marg_string_new("round_to:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 3.99 truncate_to: 1)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("3.99"), OP_PUSH_1, OP_KEYWORD, marg_string_new("truncate_to:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 3.99 floor)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("3.99"), OP_UNARY, marg_string_new("floor"), OP_STORE, marg_string_new("x")));
        parse("(x = 3.99 ceiling)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("3.99"), OP_UNARY, marg_string_new("ceiling"), OP_STORE, marg_string_new("x")));
        parse("(x = 5 factorial)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_UNARY, marg_string_new("factorial"), OP_STORE, marg_string_new("x")));
        parse("(x = -5 quotient: 3)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-5"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("quotient:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = -5 rem: 3)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-5"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("rem:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 28 gcd: 12)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("28"), OP_PUSH_INTEGER, marg_string_new("12"), OP_KEYWORD, marg_string_new("gcd:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 28 lcm: 12)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("28"), OP_PUSH_INTEGER, marg_string_new("12"), OP_KEYWORD, marg_string_new("lcm:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 100 ln)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("100"), OP_UNARY, marg_string_new("ln"), OP_STORE, marg_string_new("x")));
        parse("(x = 100 log)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("100"), OP_UNARY, marg_string_new("log"), OP_STORE, marg_string_new("x")));
        parse("(x = 100 log: 10)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("100"), OP_PUSH_INTEGER, marg_string_new("10"), OP_KEYWORD, marg_string_new("log:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 180 deg_to_rad)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("180"), OP_UNARY, marg_string_new("deg_to_rad"), OP_STORE, marg_string_new("x")));
        parse("(x = 3.14 rad_to_deg)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("3.14"), OP_UNARY, marg_string_new("rad_to_deg"), OP_STORE, marg_string_new("x")));
        parse("(x = 0.7 sin)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("0.7"), OP_UNARY, marg_string_new("sin"), OP_STORE, marg_string_new("x")));
        parse("(x = 0.7 cos)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("0.7"), OP_UNARY, marg_string_new("cos"), OP_STORE, marg_string_new("x")));
        parse("(x = 0.7 tan)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("0.7"), OP_UNARY, marg_string_new("tan"), OP_STORE, marg_string_new("x")));
        parse("(x = 0.7 arcsin)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("0.7"), OP_UNARY, marg_string_new("arcsin"), OP_STORE, marg_string_new("x")));
        parse("(x = 0.7 arccos)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("0.7"), OP_UNARY, marg_string_new("arccos"), OP_STORE, marg_string_new("x")));
        parse("(x = 0.7 arctan)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("0.7"), OP_UNARY, marg_string_new("arctan"), OP_STORE, marg_string_new("x")));
        parse("(x = [10, 20] max)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("10"), OP_PUSH_INTEGER, marg_string_new("20"), OP_PUSH_TENSOR, marg_string_new("2"), OP_UNARY, marg_string_new("max"), OP_STORE, marg_string_new("x")));
        parse("(x = [10, 20] min)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("10"), OP_PUSH_INTEGER, marg_string_new("20"), OP_PUSH_TENSOR, marg_string_new("2"), OP_UNARY, marg_string_new("min"), OP_STORE, marg_string_new("x")));
        parse("(x = [0, 100] random)", marg_vector_new(OP_PUSH_0, OP_PUSH_INTEGER, marg_string_new("100"), OP_PUSH_TENSOR, marg_string_new("2"), OP_UNARY, marg_string_new("random"), OP_STORE, marg_string_new("x")));

        parse("(x = Float PI)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Float"), OP_UNARY, marg_string_new("PI"), OP_STORE, marg_string_new("x")));
        parse("(x = Float E)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Float"), OP_UNARY, marg_string_new("E"), OP_STORE, marg_string_new("x")));
        parse("(x = Float INF)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Float"), OP_UNARY, marg_string_new("INF"), OP_STORE, marg_string_new("x")));
        parse("(x = Float NAN)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Float"), OP_UNARY, marg_string_new("NAN"), OP_STORE, marg_string_new("x")));
    });
})

#endif
