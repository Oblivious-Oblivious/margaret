#ifndef __ASSIGNMENTS_SPEC_H_
#define __ASSIGNMENTS_SPEC_H_

#include "../_helpers.h"

module(assignments_spec, {
    it("parses assignments", {
        parse("(x = 4)", marg_vector_new(FM_INTEGER, marg_string_new("4"), FM_STORE, marg_string_new("x")));
        parse("(x = y = z = 6)", marg_vector_new(FM_INTEGER, marg_string_new("6"), FM_STORE, marg_string_new("z"), FM_STORE, marg_string_new("y"), FM_STORE, marg_string_new("x")));
        parse("(x = (y = 6) + 1)", marg_vector_new(FM_INTEGER, marg_string_new("6"), FM_STORE, marg_string_new("y"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new("+"), FM_STORE, marg_string_new("x")));
        parse("(x = Object new)", marg_vector_new(FM_VARIABLE, marg_string_new("Object"), FM_UNARY, marg_string_new("new"), FM_STORE, marg_string_new("x")));
        parse("var = 12", marg_vector_new(FM_INTEGER, marg_string_new("12"), FM_STORE, marg_string_new("var")));
        parse("arr = []", marg_vector_new(FM_TENSOR, marg_string_new("0"), FM_STORE, marg_string_new("arr")));
        parse("@x = x + 2", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("2"), FM_BINARY, marg_string_new("+"), FM_STORE_INSTANCE, marg_string_new("x")));
        parse("a = b", marg_vector_new(FM_VARIABLE, marg_string_new("b"), FM_STORE, marg_string_new("a")));
        parse("a = b = c", marg_vector_new(FM_VARIABLE, marg_string_new("c"), FM_STORE, marg_string_new("b"), FM_STORE, marg_string_new("a")));
        parse("a = b = c = d = 42", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_STORE, marg_string_new("d"), FM_STORE, marg_string_new("c"), FM_STORE, marg_string_new("b"), FM_STORE, marg_string_new("a")));
        parse("(a = 2, b = 3, c = a = b)", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_STORE, marg_string_new("a"), FM_INTEGER, marg_string_new("3"), FM_STORE, marg_string_new("b"), FM_VARIABLE, marg_string_new("b"), FM_STORE, marg_string_new("a"), FM_STORE, marg_string_new("c")));
        parse("((a = 2), (b = 3), (c = a = b))", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_STORE, marg_string_new("a"), FM_INTEGER, marg_string_new("3"), FM_STORE, marg_string_new("b"), FM_VARIABLE, marg_string_new("b"), FM_STORE, marg_string_new("a"), FM_STORE, marg_string_new("c")));
        parse("a = b = (c = 42) + 12", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_STORE, marg_string_new("c"), FM_INTEGER, marg_string_new("12"), FM_BINARY, marg_string_new("+"), FM_STORE, marg_string_new("b"), FM_STORE, marg_string_new("a")));
        parse("a = 12 + 3 * 4", marg_vector_new(FM_INTEGER, marg_string_new("12"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("4"), FM_BINARY, marg_string_new("*"), FM_STORE, marg_string_new("a")));
    });

    it("parses assignments as a plain message on non assignable values", {
        parse("[a, b, c] = [1, 2, 3]", marg_vector_new(FM_VARIABLE, marg_string_new("a"), FM_VARIABLE, marg_string_new("b"), FM_VARIABLE, marg_string_new("c"), FM_TENSOR, marg_string_new("3"), FM_INTEGER, marg_string_new("1"), FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_TENSOR, marg_string_new("3"), FM_BINARY, marg_string_new("=")));
        parse("a = 3 + 4", marg_vector_new(FM_INTEGER, marg_string_new("3"), FM_INTEGER, marg_string_new("4"), FM_BINARY, marg_string_new("+"), FM_STORE, marg_string_new("a")));
        parse("2 = 3 + 4", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("="), FM_INTEGER, marg_string_new("4"), FM_BINARY, marg_string_new("+")));
    });
})

#endif
