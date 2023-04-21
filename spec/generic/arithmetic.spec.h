#ifndef __ARITHMETIC_SPEC_H_
#define __ARITHMETIC_SPEC_H_

#include "../_helpers.h"

module(arithmetic_spec, {
    it("parses arithmetic expressions", {
        parse("(x = 6 + 3)", vector_new(FM_INTEGER, string_new("6"), FM_INTEGER, string_new("3"), FM_BINARY, string_new("+"), FM_STORE, string_new("x")));
        parse("(x = 6 - 3)", vector_new(FM_INTEGER, string_new("6"), FM_INTEGER, string_new("3"), FM_BINARY, string_new("-"), FM_STORE, string_new("x")));
        parse("(x = 6 * 3)", vector_new(FM_INTEGER, string_new("6"), FM_INTEGER, string_new("3"), FM_BINARY, string_new("*"), FM_STORE, string_new("x")));
        parse("(x = 1 + 2 * 3)", vector_new(FM_INTEGER, string_new("1"), FM_INTEGER, string_new("2"), FM_BINARY, string_new("+"), FM_INTEGER, string_new("3"), FM_BINARY, string_new("*"), FM_STORE, string_new("x")));
        parse("(x = 5 / 3)", vector_new(FM_INTEGER, string_new("5"), FM_INTEGER, string_new("3"), FM_BINARY, string_new("/"), FM_STORE, string_new("x")));
        parse("(x = 5.0 / 3.0)", vector_new(FM_FLOAT, string_new("5.0"), FM_FLOAT, string_new("3.0"), FM_BINARY, string_new("/"), FM_STORE, string_new("x")));
        parse("(x = 5.0 // 3.0)", vector_new(FM_FLOAT, string_new("5.0"), FM_FLOAT, string_new("3.0"), FM_BINARY, string_new("//"), FM_STORE, string_new("x")));
        parse("(x = 5.0 rem: 3.0)", vector_new(FM_FLOAT, string_new("5.0"), FM_FLOAT, string_new("3.0"), FM_KEYWORD, string_new("rem:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = -5)", vector_new(FM_INTEGER, string_new("-5"), FM_STORE, string_new("x")));
        parse("(x = 5 sign)", vector_new(FM_INTEGER, string_new("5"), FM_UNARY, string_new("sign"), FM_STORE, string_new("x")));
        parse("(x = 5 negated)", vector_new(FM_INTEGER, string_new("5"), FM_UNARY, string_new("negated"), FM_STORE, string_new("x")));
        parse("(x = 1.2 integer_part)", vector_new(FM_FLOAT, string_new("1.2"), FM_UNARY, string_new("integer_part"), FM_STORE, string_new("x")));
        parse("(x = 1.2 fraction_part)", vector_new(FM_FLOAT, string_new("1.2"), FM_UNARY, string_new("fraction_part"), FM_STORE, string_new("x")));
        parse("(x = 5 reciprocal)", vector_new(FM_INTEGER, string_new("5"), FM_UNARY, string_new("reciprocal"), FM_STORE, string_new("x")));
        parse("(x = 6 * 3.1)", vector_new(FM_INTEGER, string_new("6"), FM_FLOAT, string_new("3.1"), FM_BINARY, string_new("*"), FM_STORE, string_new("x")));
        parse("(x = 5 squared)", vector_new(FM_INTEGER, string_new("5"), FM_UNARY, string_new("squared"), FM_STORE, string_new("x")));
        parse("(x = 25 sqrt)", vector_new(FM_INTEGER, string_new("25"), FM_UNARY, string_new("sqrt"), FM_STORE, string_new("x")));
        parse("(x = 5 raised_to: 2)", vector_new(FM_INTEGER, string_new("5"), FM_INTEGER, string_new("2"), FM_KEYWORD, string_new("raised_to:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = 5 raised_to_integer: 2)", vector_new(FM_INTEGER, string_new("5"), FM_INTEGER, string_new("2"), FM_KEYWORD, string_new("raised_to_integer:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = 5 exp)", vector_new(FM_INTEGER, string_new("5"), FM_UNARY, string_new("exp"), FM_STORE, string_new("x")));
        parse("(x = -5 abs)", vector_new(FM_INTEGER, string_new("-5"), FM_UNARY, string_new("abs"), FM_STORE, string_new("x")));
        parse("(x = 3.99 rounded)", vector_new(FM_FLOAT, string_new("3.99"), FM_UNARY, string_new("rounded"), FM_STORE, string_new("x")));
        parse("(x = 3.99 truncated)", vector_new(FM_FLOAT, string_new("3.99"), FM_UNARY, string_new("truncated"), FM_STORE, string_new("x")));
        parse("(x = 3.99 round_to: 1)", vector_new(FM_FLOAT, string_new("3.99"), FM_INTEGER, string_new("1"), FM_KEYWORD, string_new("round_to:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = 3.99 truncate_to: 1)", vector_new(FM_FLOAT, string_new("3.99"), FM_INTEGER, string_new("1"), FM_KEYWORD, string_new("truncate_to:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = 3.99 floor)", vector_new(FM_FLOAT, string_new("3.99"), FM_UNARY, string_new("floor"), FM_STORE, string_new("x")));
        parse("(x = 3.99 ceiling)", vector_new(FM_FLOAT, string_new("3.99"), FM_UNARY, string_new("ceiling"), FM_STORE, string_new("x")));
        parse("(x = 5 factorial)", vector_new(FM_INTEGER, string_new("5"), FM_UNARY, string_new("factorial"), FM_STORE, string_new("x")));
        parse("(x = -5 quotient: 3)", vector_new(FM_INTEGER, string_new("-5"), FM_INTEGER, string_new("3"), FM_KEYWORD, string_new("quotient:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = -5 rem: 3)", vector_new(FM_INTEGER, string_new("-5"), FM_INTEGER, string_new("3"), FM_KEYWORD, string_new("rem:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = 28 gcd: 12)", vector_new(FM_INTEGER, string_new("28"), FM_INTEGER, string_new("12"), FM_KEYWORD, string_new("gcd:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = 28 lcm: 12)", vector_new(FM_INTEGER, string_new("28"), FM_INTEGER, string_new("12"), FM_KEYWORD, string_new("lcm:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = 100 ln)", vector_new(FM_INTEGER, string_new("100"), FM_UNARY, string_new("ln"), FM_STORE, string_new("x")));
        parse("(x = 100 log)", vector_new(FM_INTEGER, string_new("100"), FM_UNARY, string_new("log"), FM_STORE, string_new("x")));
        parse("(x = 100 log: 10)", vector_new(FM_INTEGER, string_new("100"), FM_INTEGER, string_new("10"), FM_KEYWORD, string_new("log:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = 180 deg_to_rad)", vector_new(FM_INTEGER, string_new("180"), FM_UNARY, string_new("deg_to_rad"), FM_STORE, string_new("x")));
        parse("(x = 3.14 rad_to_deg)", vector_new(FM_FLOAT, string_new("3.14"), FM_UNARY, string_new("rad_to_deg"), FM_STORE, string_new("x")));
        parse("(x = 0.7 sin)", vector_new(FM_FLOAT, string_new("0.7"), FM_UNARY, string_new("sin"), FM_STORE, string_new("x")));
        parse("(x = 0.7 cos)", vector_new(FM_FLOAT, string_new("0.7"), FM_UNARY, string_new("cos"), FM_STORE, string_new("x")));
        parse("(x = 0.7 tan)", vector_new(FM_FLOAT, string_new("0.7"), FM_UNARY, string_new("tan"), FM_STORE, string_new("x")));
        parse("(x = 0.7 arcsin)", vector_new(FM_FLOAT, string_new("0.7"), FM_UNARY, string_new("arcsin"), FM_STORE, string_new("x")));
        parse("(x = 0.7 arccos)", vector_new(FM_FLOAT, string_new("0.7"), FM_UNARY, string_new("arccos"), FM_STORE, string_new("x")));
        parse("(x = 0.7 arctan)", vector_new(FM_FLOAT, string_new("0.7"), FM_UNARY, string_new("arctan"), FM_STORE, string_new("x")));
        parse("(x = [10, 20] max)", vector_new(FM_INTEGER, string_new("10"), FM_INTEGER, string_new("20"), FM_TENSOR, string_new("2"), FM_UNARY, string_new("max"), FM_STORE, string_new("x")));
        parse("(x = [10, 20] min)", vector_new(FM_INTEGER, string_new("10"), FM_INTEGER, string_new("20"), FM_TENSOR, string_new("2"), FM_UNARY, string_new("min"), FM_STORE, string_new("x")));
        parse("(x = [0, 100] random)", vector_new(FM_INTEGER, string_new("0"), FM_INTEGER, string_new("100"), FM_TENSOR, string_new("2"), FM_UNARY, string_new("random"), FM_STORE, string_new("x")));

        parse("(x = Float PI)", vector_new(FM_VARIABLE, string_new("Float"), FM_UNARY, string_new("PI"), FM_STORE, string_new("x")));
        parse("(x = Float E)", vector_new(FM_VARIABLE, string_new("Float"), FM_UNARY, string_new("E"), FM_STORE, string_new("x")));
        parse("(x = Float INF)", vector_new(FM_VARIABLE, string_new("Float"), FM_UNARY, string_new("INF"), FM_STORE, string_new("x")));
        parse("(x = Float NAN)", vector_new(FM_VARIABLE, string_new("Float"), FM_UNARY, string_new("NAN"), FM_STORE, string_new("x")));
    });
})

#endif
