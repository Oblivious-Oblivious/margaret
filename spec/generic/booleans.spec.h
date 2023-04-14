#ifndef __BOOLEANS_SPEC_H_
#define __BOOLEANS_SPEC_H_

#include "../_helpers.h"

module(booleans_spec, {
    it("parses boolean methods", {
        parse("(b = 2 == 3)", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("=="), OP_STORE, marg_string_new("b")));
        parse("(b = 2 dosth!)", marg_vector_new(OP_PUSH_2, OP_UNARY, marg_string_new("dosth!"), OP_STORE, marg_string_new("b")));
        parse("(b = x != y)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_BINARY, marg_string_new("!="), OP_STORE, marg_string_new("b")));
        parse("(b = x === y)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_BINARY, marg_string_new("==="), OP_STORE, marg_string_new("b")));
        parse("(b = x !== y)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_BINARY, marg_string_new("!=="), OP_STORE, marg_string_new("b")));
        parse("(b = x > y)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_BINARY, marg_string_new(">"), OP_STORE, marg_string_new("b")));
        parse("(b = x < y)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_BINARY, marg_string_new("<"), OP_STORE, marg_string_new("b")));
        parse("(b = x >= y)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_BINARY, marg_string_new(">="), OP_STORE, marg_string_new("b")));
        parse("(b = x <= y)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_BINARY, marg_string_new("<="), OP_STORE, marg_string_new("b")));
        parse("(b = b not)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("b"), OP_UNARY, marg_string_new("not"), OP_STORE, marg_string_new("b")));
        parse("(b = (x < 5) && (y > 1))", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("<"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_PUSH_1, OP_BINARY, marg_string_new(">"), OP_BINARY, marg_string_new("&&"), OP_STORE, marg_string_new("b")));
        parse("(b = (x < 5) || (y > 1))", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("<"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_PUSH_1, OP_BINARY, marg_string_new(">"), OP_BINARY, marg_string_new("||"), OP_STORE, marg_string_new("b")));
        parse("(b = (x < 5) and: (y > 1))", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("<"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_PUSH_1, OP_BINARY, marg_string_new(">"), OP_KEYWORD, marg_string_new("and:"), marg_string_new("1"), OP_STORE, marg_string_new("b")));
        parse("(b = (x < 5) or: (y > 1))", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("<"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_PUSH_1, OP_BINARY, marg_string_new(">"), OP_KEYWORD, marg_string_new("or:"), marg_string_new("1"), OP_STORE, marg_string_new("b")));
        parse("(b = (x < 5) eqv: (y > 1))", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("<"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_PUSH_1, OP_BINARY, marg_string_new(">"), OP_KEYWORD, marg_string_new("eqv:"), marg_string_new("1"), OP_STORE, marg_string_new("b")));
        parse("(b = (x < 5) xor: (y > 1))", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("<"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_PUSH_1, OP_BINARY, marg_string_new(">"), OP_KEYWORD, marg_string_new("xor:"), marg_string_new("1"), OP_STORE, marg_string_new("b")));
        parse("(b = 5 between: 3 and: 12)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_INTEGER, marg_string_new("3"), OP_PUSH_INTEGER, marg_string_new("12"), OP_KEYWORD, marg_string_new("between:and:"), marg_string_new("2"), OP_STORE, marg_string_new("b")));
        parse("(b = 123 is_kind_of: Number)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("123"), OP_PUSH_VARIABLE, marg_string_new("Number"), OP_KEYWORD, marg_string_new("is_kind_of:"), marg_string_new("1"), OP_STORE, marg_string_new("b")));
        parse("(b = 123 is_member_of: SmallInteger)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("123"), OP_PUSH_VARIABLE, marg_string_new("SmallInteger"), OP_KEYWORD, marg_string_new("is_member_of:"), marg_string_new("1"), OP_STORE, marg_string_new("b")));
        parse("(b = 123 responds_to: \"sqrt\")", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("123"), OP_PUSH_STRING, marg_string_new("sqrt"), OP_KEYWORD, marg_string_new("responds_to:"), marg_string_new("1"), OP_STORE, marg_string_new("b")));
        parse("(b = x is_nil?)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("is_nil?"), OP_STORE, marg_string_new("b")));
        parse("(b = x is_zero?)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("is_zero?"), OP_STORE, marg_string_new("b")));
        parse("(b = x is_positive?)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("is_positive?"), OP_STORE, marg_string_new("b")));
        parse("(b = x is_negative?)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("is_negative?"), OP_STORE, marg_string_new("b")));
        parse("(b = x is_even?)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("is_even?"), OP_STORE, marg_string_new("b")));
        parse("(b = x is_odd?)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("is_odd?"), OP_STORE, marg_string_new("b")));
        parse("(b = x is_integer?)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("is_integer?"), OP_STORE, marg_string_new("b")));
        parse("(b = x is_float?)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("is_float?"), OP_STORE, marg_string_new("b")));
        parse("(b = x is_number?)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("is_number?"), OP_STORE, marg_string_new("b")));
        parse("(b = 'a' is_uppercase?)", marg_vector_new(OP_PUSH_CHAR, marg_string_new("a"), OP_UNARY, marg_string_new("is_uppercase?"), OP_STORE, marg_string_new("b")));
        parse("(b = 'a' is_lowercase?)", marg_vector_new(OP_PUSH_CHAR, marg_string_new("a"), OP_UNARY, marg_string_new("is_lowercase?"), OP_STORE, marg_string_new("b")));
    });
})

#endif
