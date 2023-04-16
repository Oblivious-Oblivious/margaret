#ifndef __ASSIGNMENTS_SPEC_H_
#define __ASSIGNMENTS_SPEC_H_

#include "../_helpers.h"

module(assignments_spec, {
    it("parses assignments", {
        parse("(x = 4)", marg_vector_new(OP_INTEGER, marg_string_new("4"), OP_STORE, marg_string_new("x")));
        parse("(x = y = z = 6)", marg_vector_new(OP_INTEGER, marg_string_new("6"), OP_STORE, marg_string_new("z"), OP_STORE, marg_string_new("y"), OP_STORE, marg_string_new("x")));
        parse("(x = (y = 6) + 1)", marg_vector_new(OP_INTEGER, marg_string_new("6"), OP_STORE, marg_string_new("y"), OP_1, OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("x")));
        parse("(x = Object new)", marg_vector_new(OP_VARIABLE, marg_string_new("Object"), OP_UNARY, marg_string_new("new"), OP_STORE, marg_string_new("x")));
        parse("var = 12", marg_vector_new(OP_INTEGER, marg_string_new("12"), OP_STORE, marg_string_new("var")));
        parse("arr = []", marg_vector_new(OP_TENSOR, marg_string_new("0"), OP_STORE, marg_string_new("arr")));
        parse("@x = x + 2", marg_vector_new(OP_VARIABLE, marg_string_new("x"), OP_2, OP_BINARY, marg_string_new("+"), OP_STORE_INSTANCE, marg_string_new("x")));
        parse("a = b", marg_vector_new(OP_VARIABLE, marg_string_new("b"), OP_STORE, marg_string_new("a")));
        parse("a = b = c", marg_vector_new(OP_VARIABLE, marg_string_new("c"), OP_STORE, marg_string_new("b"), OP_STORE, marg_string_new("a")));
        parse("a = b = c = d = 42", marg_vector_new(OP_INTEGER, marg_string_new("42"), OP_STORE, marg_string_new("d"), OP_STORE, marg_string_new("c"), OP_STORE, marg_string_new("b"), OP_STORE, marg_string_new("a")));
        parse("(a = 2, b = 3, c = a = b)", marg_vector_new(OP_2, OP_STORE, marg_string_new("a"), OP_INTEGER, marg_string_new("3"), OP_STORE, marg_string_new("b"), OP_VARIABLE, marg_string_new("b"), OP_STORE, marg_string_new("a"), OP_STORE, marg_string_new("c")));
        parse("((a = 2), (b = 3), (c = a = b))", marg_vector_new(OP_2, OP_STORE, marg_string_new("a"), OP_INTEGER, marg_string_new("3"), OP_STORE, marg_string_new("b"), OP_VARIABLE, marg_string_new("b"), OP_STORE, marg_string_new("a"), OP_STORE, marg_string_new("c")));
        parse("a = b = (c = 42) + 12", marg_vector_new(OP_INTEGER, marg_string_new("42"), OP_STORE, marg_string_new("c"), OP_INTEGER, marg_string_new("12"), OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("b"), OP_STORE, marg_string_new("a")));
        parse("a = 12 + 3 * 4", marg_vector_new(OP_INTEGER, marg_string_new("12"), OP_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_INTEGER, marg_string_new("4"), OP_BINARY, marg_string_new("*"), OP_STORE, marg_string_new("a")));
    });

    it("parses assignments as a plain message on non assignable values", {
        parse("[a, b, c] = [1, 2, 3]", marg_vector_new(OP_VARIABLE, marg_string_new("a"), OP_VARIABLE, marg_string_new("b"), OP_VARIABLE, marg_string_new("c"), OP_TENSOR, marg_string_new("3"), OP_1, OP_2, OP_INTEGER, marg_string_new("3"), OP_TENSOR, marg_string_new("3"), OP_BINARY, marg_string_new("=")));
        parse("a = 3 + 4", marg_vector_new(OP_INTEGER, marg_string_new("3"), OP_INTEGER, marg_string_new("4"), OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("a")));
        parse("2 = 3 + 4", marg_vector_new(OP_2, OP_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("="), OP_INTEGER, marg_string_new("4"), OP_BINARY, marg_string_new("+")));
    });
})

#endif
