#ifndef __BOOLEANS_SPEC_H_
#define __BOOLEANS_SPEC_H_

#include "../_helpers.h"

module(booleans_spec, {
    it("parses boolean methods", {
        parse("(b = 2 == 3)", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("=="), FM_STORE, marg_string_new("b")));
        parse("(b = 2 dosth!)", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_UNARY, marg_string_new("dosth!"), FM_STORE, marg_string_new("b")));
        parse("(b = x != y)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_VARIABLE, marg_string_new("y"), FM_BINARY, marg_string_new("!="), FM_STORE, marg_string_new("b")));
        parse("(b = x === y)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_VARIABLE, marg_string_new("y"), FM_BINARY, marg_string_new("==="), FM_STORE, marg_string_new("b")));
        parse("(b = x !== y)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_VARIABLE, marg_string_new("y"), FM_BINARY, marg_string_new("!=="), FM_STORE, marg_string_new("b")));
        parse("(b = x > y)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_VARIABLE, marg_string_new("y"), FM_BINARY, marg_string_new(">"), FM_STORE, marg_string_new("b")));
        parse("(b = x < y)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_VARIABLE, marg_string_new("y"), FM_BINARY, marg_string_new("<"), FM_STORE, marg_string_new("b")));
        parse("(b = x >= y)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_VARIABLE, marg_string_new("y"), FM_BINARY, marg_string_new(">="), FM_STORE, marg_string_new("b")));
        parse("(b = x <= y)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_VARIABLE, marg_string_new("y"), FM_BINARY, marg_string_new("<="), FM_STORE, marg_string_new("b")));
        parse("(b = b not)", marg_vector_new(FM_VARIABLE, marg_string_new("b"), FM_UNARY, marg_string_new("not"), FM_STORE, marg_string_new("b")));
        parse("(b = (x < 5) && (y > 1))", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("5"), FM_BINARY, marg_string_new("<"), FM_VARIABLE, marg_string_new("y"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new(">"), FM_BINARY, marg_string_new("&&"), FM_STORE, marg_string_new("b")));
        parse("(b = (x < 5) || (y > 1))", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("5"), FM_BINARY, marg_string_new("<"), FM_VARIABLE, marg_string_new("y"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new(">"), FM_BINARY, marg_string_new("||"), FM_STORE, marg_string_new("b")));
        parse("(b = (x < 5) and: (y > 1))", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("5"), FM_BINARY, marg_string_new("<"), FM_VARIABLE, marg_string_new("y"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new(">"), FM_KEYWORD, marg_string_new("and:"), marg_string_new("1"), FM_STORE, marg_string_new("b")));
        parse("(b = (x < 5) or: (y > 1))", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("5"), FM_BINARY, marg_string_new("<"), FM_VARIABLE, marg_string_new("y"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new(">"), FM_KEYWORD, marg_string_new("or:"), marg_string_new("1"), FM_STORE, marg_string_new("b")));
        parse("(b = (x < 5) eqv: (y > 1))", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("5"), FM_BINARY, marg_string_new("<"), FM_VARIABLE, marg_string_new("y"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new(">"), FM_KEYWORD, marg_string_new("eqv:"), marg_string_new("1"), FM_STORE, marg_string_new("b")));
        parse("(b = (x < 5) xor: (y > 1))", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("5"), FM_BINARY, marg_string_new("<"), FM_VARIABLE, marg_string_new("y"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new(">"), FM_KEYWORD, marg_string_new("xor:"), marg_string_new("1"), FM_STORE, marg_string_new("b")));
        parse("(b = 5 between: 3 and: 12)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_INTEGER, marg_string_new("3"), FM_INTEGER, marg_string_new("12"), FM_KEYWORD, marg_string_new("between:and:"), marg_string_new("2"), FM_STORE, marg_string_new("b")));
        parse("(b = 123 is_kind_of: Number)", marg_vector_new(FM_INTEGER, marg_string_new("123"), FM_VARIABLE, marg_string_new("Number"), FM_KEYWORD, marg_string_new("is_kind_of:"), marg_string_new("1"), FM_STORE, marg_string_new("b")));
        parse("(b = 123 is_member_of: SmallInteger)", marg_vector_new(FM_INTEGER, marg_string_new("123"), FM_VARIABLE, marg_string_new("SmallInteger"), FM_KEYWORD, marg_string_new("is_member_of:"), marg_string_new("1"), FM_STORE, marg_string_new("b")));
        parse("(b = 123 responds_to: \"sqrt\")", marg_vector_new(FM_INTEGER, marg_string_new("123"), FM_STRING, marg_string_new("sqrt"), FM_KEYWORD, marg_string_new("responds_to:"), marg_string_new("1"), FM_STORE, marg_string_new("b")));
        parse("(b = x is_nil?)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("is_nil?"), FM_STORE, marg_string_new("b")));
        parse("(b = x is_zero?)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("is_zero?"), FM_STORE, marg_string_new("b")));
        parse("(b = x is_positive?)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("is_positive?"), FM_STORE, marg_string_new("b")));
        parse("(b = x is_negative?)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("is_negative?"), FM_STORE, marg_string_new("b")));
        parse("(b = x is_even?)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("is_even?"), FM_STORE, marg_string_new("b")));
        parse("(b = x is_odd?)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("is_odd?"), FM_STORE, marg_string_new("b")));
        parse("(b = x is_integer?)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("is_integer?"), FM_STORE, marg_string_new("b")));
        parse("(b = x is_float?)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("is_float?"), FM_STORE, marg_string_new("b")));
        parse("(b = x is_number?)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("is_number?"), FM_STORE, marg_string_new("b")));
        parse("(b = 'a' is_uppercase?)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("is_uppercase?"), FM_STORE, marg_string_new("b")));
        parse("(b = 'a' is_lowercase?)", marg_vector_new(FM_CHAR, marg_string_new("a"), FM_UNARY, marg_string_new("is_lowercase?"), FM_STORE, marg_string_new("b")));
    });
})

#endif
