#ifndef __ARITHMETIC_SPEC_H_
#define __ARITHMETIC_SPEC_H_

#include "../_helpers.h"

module(arithmetic_spec, {
    it("parses arithmetic expressions", {
        parse("(x = 6 + 3)", marg_vector_new(FM_INTEGER, marg_string_new("6"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("+"), FM_STORE, marg_string_new("x")));
        parse("(x = 6 - 3)", marg_vector_new(FM_INTEGER, marg_string_new("6"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("-"), FM_STORE, marg_string_new("x")));
        parse("(x = 6 * 3)", marg_vector_new(FM_INTEGER, marg_string_new("6"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("*"), FM_STORE, marg_string_new("x")));
        parse("(x = 1 + 2 * 3)", marg_vector_new(FM_INTEGER, marg_string_new("1"), FM_INTEGER, marg_string_new("2"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("*"), FM_STORE, marg_string_new("x")));
        parse("(x = 5 / 3)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("/"), FM_STORE, marg_string_new("x")));
        parse("(x = 5.0 / 3.0)", marg_vector_new(FM_FLOAT, marg_string_new("5.0"), FM_FLOAT, marg_string_new("3.0"), FM_BINARY, marg_string_new("/"), FM_STORE, marg_string_new("x")));
        parse("(x = 5.0 // 3.0)", marg_vector_new(FM_FLOAT, marg_string_new("5.0"), FM_FLOAT, marg_string_new("3.0"), FM_BINARY, marg_string_new("//"), FM_STORE, marg_string_new("x")));
        parse("(x = 5.0 rem: 3.0)", marg_vector_new(FM_FLOAT, marg_string_new("5.0"), FM_FLOAT, marg_string_new("3.0"), FM_KEYWORD, marg_string_new("rem:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = -5)", marg_vector_new(FM_INTEGER, marg_string_new("-5"), FM_STORE, marg_string_new("x")));
        parse("(x = 5 sign)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_UNARY, marg_string_new("sign"), FM_STORE, marg_string_new("x")));
        parse("(x = 5 negated)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_UNARY, marg_string_new("negated"), FM_STORE, marg_string_new("x")));
        parse("(x = 1.2 integer_part)", marg_vector_new(FM_FLOAT, marg_string_new("1.2"), FM_UNARY, marg_string_new("integer_part"), FM_STORE, marg_string_new("x")));
        parse("(x = 1.2 fraction_part)", marg_vector_new(FM_FLOAT, marg_string_new("1.2"), FM_UNARY, marg_string_new("fraction_part"), FM_STORE, marg_string_new("x")));
        parse("(x = 5 reciprocal)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_UNARY, marg_string_new("reciprocal"), FM_STORE, marg_string_new("x")));
        parse("(x = 6 * 3.1)", marg_vector_new(FM_INTEGER, marg_string_new("6"), FM_FLOAT, marg_string_new("3.1"), FM_BINARY, marg_string_new("*"), FM_STORE, marg_string_new("x")));
        parse("(x = 5 squared)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_UNARY, marg_string_new("squared"), FM_STORE, marg_string_new("x")));
        parse("(x = 25 sqrt)", marg_vector_new(FM_INTEGER, marg_string_new("25"), FM_UNARY, marg_string_new("sqrt"), FM_STORE, marg_string_new("x")));
        parse("(x = 5 raised_to: 2)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_INTEGER, marg_string_new("2"), FM_KEYWORD, marg_string_new("raised_to:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = 5 raised_to_integer: 2)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_INTEGER, marg_string_new("2"), FM_KEYWORD, marg_string_new("raised_to_integer:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = 5 exp)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_UNARY, marg_string_new("exp"), FM_STORE, marg_string_new("x")));
        parse("(x = -5 abs)", marg_vector_new(FM_INTEGER, marg_string_new("-5"), FM_UNARY, marg_string_new("abs"), FM_STORE, marg_string_new("x")));
        parse("(x = 3.99 rounded)", marg_vector_new(FM_FLOAT, marg_string_new("3.99"), FM_UNARY, marg_string_new("rounded"), FM_STORE, marg_string_new("x")));
        parse("(x = 3.99 truncated)", marg_vector_new(FM_FLOAT, marg_string_new("3.99"), FM_UNARY, marg_string_new("truncated"), FM_STORE, marg_string_new("x")));
        parse("(x = 3.99 round_to: 1)", marg_vector_new(FM_FLOAT, marg_string_new("3.99"), FM_INTEGER, marg_string_new("1"), FM_KEYWORD, marg_string_new("round_to:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = 3.99 truncate_to: 1)", marg_vector_new(FM_FLOAT, marg_string_new("3.99"), FM_INTEGER, marg_string_new("1"), FM_KEYWORD, marg_string_new("truncate_to:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = 3.99 floor)", marg_vector_new(FM_FLOAT, marg_string_new("3.99"), FM_UNARY, marg_string_new("floor"), FM_STORE, marg_string_new("x")));
        parse("(x = 3.99 ceiling)", marg_vector_new(FM_FLOAT, marg_string_new("3.99"), FM_UNARY, marg_string_new("ceiling"), FM_STORE, marg_string_new("x")));
        parse("(x = 5 factorial)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_UNARY, marg_string_new("factorial"), FM_STORE, marg_string_new("x")));
        parse("(x = -5 quotient: 3)", marg_vector_new(FM_INTEGER, marg_string_new("-5"), FM_INTEGER, marg_string_new("3"), FM_KEYWORD, marg_string_new("quotient:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = -5 rem: 3)", marg_vector_new(FM_INTEGER, marg_string_new("-5"), FM_INTEGER, marg_string_new("3"), FM_KEYWORD, marg_string_new("rem:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = 28 gcd: 12)", marg_vector_new(FM_INTEGER, marg_string_new("28"), FM_INTEGER, marg_string_new("12"), FM_KEYWORD, marg_string_new("gcd:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = 28 lcm: 12)", marg_vector_new(FM_INTEGER, marg_string_new("28"), FM_INTEGER, marg_string_new("12"), FM_KEYWORD, marg_string_new("lcm:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = 100 ln)", marg_vector_new(FM_INTEGER, marg_string_new("100"), FM_UNARY, marg_string_new("ln"), FM_STORE, marg_string_new("x")));
        parse("(x = 100 log)", marg_vector_new(FM_INTEGER, marg_string_new("100"), FM_UNARY, marg_string_new("log"), FM_STORE, marg_string_new("x")));
        parse("(x = 100 log: 10)", marg_vector_new(FM_INTEGER, marg_string_new("100"), FM_INTEGER, marg_string_new("10"), FM_KEYWORD, marg_string_new("log:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = 180 deg_to_rad)", marg_vector_new(FM_INTEGER, marg_string_new("180"), FM_UNARY, marg_string_new("deg_to_rad"), FM_STORE, marg_string_new("x")));
        parse("(x = 3.14 rad_to_deg)", marg_vector_new(FM_FLOAT, marg_string_new("3.14"), FM_UNARY, marg_string_new("rad_to_deg"), FM_STORE, marg_string_new("x")));
        parse("(x = 0.7 sin)", marg_vector_new(FM_FLOAT, marg_string_new("0.7"), FM_UNARY, marg_string_new("sin"), FM_STORE, marg_string_new("x")));
        parse("(x = 0.7 cos)", marg_vector_new(FM_FLOAT, marg_string_new("0.7"), FM_UNARY, marg_string_new("cos"), FM_STORE, marg_string_new("x")));
        parse("(x = 0.7 tan)", marg_vector_new(FM_FLOAT, marg_string_new("0.7"), FM_UNARY, marg_string_new("tan"), FM_STORE, marg_string_new("x")));
        parse("(x = 0.7 arcsin)", marg_vector_new(FM_FLOAT, marg_string_new("0.7"), FM_UNARY, marg_string_new("arcsin"), FM_STORE, marg_string_new("x")));
        parse("(x = 0.7 arccos)", marg_vector_new(FM_FLOAT, marg_string_new("0.7"), FM_UNARY, marg_string_new("arccos"), FM_STORE, marg_string_new("x")));
        parse("(x = 0.7 arctan)", marg_vector_new(FM_FLOAT, marg_string_new("0.7"), FM_UNARY, marg_string_new("arctan"), FM_STORE, marg_string_new("x")));
        parse("(x = [10, 20] max)", marg_vector_new(FM_INTEGER, marg_string_new("10"), FM_INTEGER, marg_string_new("20"), FM_TENSOR, marg_string_new("2"), FM_UNARY, marg_string_new("max"), FM_STORE, marg_string_new("x")));
        parse("(x = [10, 20] min)", marg_vector_new(FM_INTEGER, marg_string_new("10"), FM_INTEGER, marg_string_new("20"), FM_TENSOR, marg_string_new("2"), FM_UNARY, marg_string_new("min"), FM_STORE, marg_string_new("x")));
        parse("(x = [0, 100] random)", marg_vector_new(FM_INTEGER, marg_string_new("0"), FM_INTEGER, marg_string_new("100"), FM_TENSOR, marg_string_new("2"), FM_UNARY, marg_string_new("random"), FM_STORE, marg_string_new("x")));

        parse("(x = Float PI)", marg_vector_new(FM_VARIABLE, marg_string_new("Float"), FM_UNARY, marg_string_new("PI"), FM_STORE, marg_string_new("x")));
        parse("(x = Float E)", marg_vector_new(FM_VARIABLE, marg_string_new("Float"), FM_UNARY, marg_string_new("E"), FM_STORE, marg_string_new("x")));
        parse("(x = Float INF)", marg_vector_new(FM_VARIABLE, marg_string_new("Float"), FM_UNARY, marg_string_new("INF"), FM_STORE, marg_string_new("x")));
        parse("(x = Float NAN)", marg_vector_new(FM_VARIABLE, marg_string_new("Float"), FM_UNARY, marg_string_new("NAN"), FM_STORE, marg_string_new("x")));
    });
})

#endif
