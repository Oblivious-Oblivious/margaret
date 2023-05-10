#ifndef __BOOLEANS_SPEC_H_
#define __BOOLEANS_SPEC_H_

#include "../_helpers.h"

module(booleans_spec, {
    it("parses boolean methods", {
        parse("(b = 2 == 3)", vector_new(FM_INTEGER, string_new("2"), FM_INTEGER, string_new("3"), FM_BINARY, string_new("=="), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = 2 dosth!)", vector_new(FM_INTEGER, string_new("2"), FM_UNARY, string_new("dosth!"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x != y)", vector_new(FM_LOCAL, string_new("x"), FM_LOCAL, string_new("y"), FM_BINARY, string_new("!="), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x === y)", vector_new(FM_LOCAL, string_new("x"), FM_LOCAL, string_new("y"), FM_BINARY, string_new("==="), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x !== y)", vector_new(FM_LOCAL, string_new("x"), FM_LOCAL, string_new("y"), FM_BINARY, string_new("!=="), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x > y)", vector_new(FM_LOCAL, string_new("x"), FM_LOCAL, string_new("y"), FM_BINARY, string_new(">"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x < y)", vector_new(FM_LOCAL, string_new("x"), FM_LOCAL, string_new("y"), FM_BINARY, string_new("<"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x >= y)", vector_new(FM_LOCAL, string_new("x"), FM_LOCAL, string_new("y"), FM_BINARY, string_new(">="), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x <= y)", vector_new(FM_LOCAL, string_new("x"), FM_LOCAL, string_new("y"), FM_BINARY, string_new("<="), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = b not)", vector_new(FM_LOCAL, string_new("b"), FM_UNARY, string_new("not"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = (x < 5) && (y > 1))", vector_new(FM_LOCAL, string_new("x"), FM_INTEGER, string_new("5"), FM_BINARY, string_new("<"), FM_LOCAL, string_new("y"), FM_INTEGER, string_new("1"), FM_BINARY, string_new(">"), FM_BINARY, string_new("&&"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = (x < 5) || (y > 1))", vector_new(FM_LOCAL, string_new("x"), FM_INTEGER, string_new("5"), FM_BINARY, string_new("<"), FM_LOCAL, string_new("y"), FM_INTEGER, string_new("1"), FM_BINARY, string_new(">"), FM_BINARY, string_new("||"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = (x < 5) and: (y > 1))", vector_new(FM_LOCAL, string_new("x"), FM_INTEGER, string_new("5"), FM_BINARY, string_new("<"), FM_LOCAL, string_new("y"), FM_INTEGER, string_new("1"), FM_BINARY, string_new(">"), FM_KEYWORD, string_new("and:"), string_new("1"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = (x < 5) or: (y > 1))", vector_new(FM_LOCAL, string_new("x"), FM_INTEGER, string_new("5"), FM_BINARY, string_new("<"), FM_LOCAL, string_new("y"), FM_INTEGER, string_new("1"), FM_BINARY, string_new(">"), FM_KEYWORD, string_new("or:"), string_new("1"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = (x < 5) eqv: (y > 1))", vector_new(FM_LOCAL, string_new("x"), FM_INTEGER, string_new("5"), FM_BINARY, string_new("<"), FM_LOCAL, string_new("y"), FM_INTEGER, string_new("1"), FM_BINARY, string_new(">"), FM_KEYWORD, string_new("eqv:"), string_new("1"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = (x < 5) xor: (y > 1))", vector_new(FM_LOCAL, string_new("x"), FM_INTEGER, string_new("5"), FM_BINARY, string_new("<"), FM_LOCAL, string_new("y"), FM_INTEGER, string_new("1"), FM_BINARY, string_new(">"), FM_KEYWORD, string_new("xor:"), string_new("1"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = 5 between: 3 and: 12)", vector_new(FM_INTEGER, string_new("5"), FM_INTEGER, string_new("3"), FM_INTEGER, string_new("12"), FM_KEYWORD, string_new("between:and:"), string_new("2"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = 123 is_kind_of: Number)", vector_new(FM_INTEGER, string_new("123"), FM_LOCAL, string_new("Number"), FM_KEYWORD, string_new("is_kind_of:"), string_new("1"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = 123 is_member_of: SmallInteger)", vector_new(FM_INTEGER, string_new("123"), FM_LOCAL, string_new("SmallInteger"), FM_KEYWORD, string_new("is_member_of:"), string_new("1"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = 123 responds_to: \"sqrt\")", vector_new(FM_INTEGER, string_new("123"), FM_STRING, string_new("sqrt"), FM_KEYWORD, string_new("responds_to:"), string_new("1"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x is_nil?)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("is_nil?"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x is_zero?)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("is_zero?"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x is_positive?)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("is_positive?"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x is_negative?)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("is_negative?"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x is_even?)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("is_even?"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x is_odd?)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("is_odd?"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x is_integer?)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("is_integer?"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x is_float?)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("is_float?"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = x is_number?)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("is_number?"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = 'a' is_uppercase?)", vector_new(FM_STRING, string_new("a"), FM_UNARY, string_new("is_uppercase?"), FM_STORE_LOCAL, string_new("b"), FM_POP));
        parse("(b = 'a' is_lowercase?)", vector_new(FM_STRING, string_new("a"), FM_UNARY, string_new("is_lowercase?"), FM_STORE_LOCAL, string_new("b"), FM_POP));
    });
})

#endif
