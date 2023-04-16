#ifndef __ITERATIONS_SPEC_H_
#define __ITERATIONS_SPEC_H_

#include "../_helpers.h"

module(iterations_spec, {
    it("parses iteration statements", {
        parse("(x > 0 while_true: (x = x - 1, y = y * 2))", marg_vector_new(OP_VARIABLE, marg_string_new("x"), OP_0, OP_BINARY, marg_string_new(">"), OP_VARIABLE, marg_string_new("x"), OP_1, OP_BINARY, marg_string_new("-"), OP_STORE, marg_string_new("x"), OP_VARIABLE, marg_string_new("y"), OP_2, OP_BINARY, marg_string_new("*"), OP_STORE, marg_string_new("y"), OP_KEYWORD, marg_string_new("while_true:"), marg_string_new("1")));
        parse("(x >= 0 while_false: (x = x + 1, y = y * 2))", marg_vector_new(OP_VARIABLE, marg_string_new("x"), OP_0, OP_BINARY, marg_string_new(">="), OP_VARIABLE, marg_string_new("x"), OP_1, OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("x"), OP_VARIABLE, marg_string_new("y"), OP_2, OP_BINARY, marg_string_new("*"), OP_STORE, marg_string_new("y"), OP_KEYWORD, marg_string_new("while_false:"), marg_string_new("1")));
        parse("(x times: (y = y * 2))", marg_vector_new(OP_VARIABLE, marg_string_new("x"), OP_VARIABLE, marg_string_new("y"), OP_2, OP_BINARY, marg_string_new("*"), OP_STORE, marg_string_new("y"), OP_KEYWORD, marg_string_new("times:"), marg_string_new("1")));
        parse("(1 to: 5 do: (y = y * 2))", marg_vector_new(OP_1, OP_INTEGER, marg_string_new("5"), OP_VARIABLE, marg_string_new("y"), OP_2, OP_BINARY, marg_string_new("*"), OP_STORE, marg_string_new("y"), OP_KEYWORD, marg_string_new("to:do:"), marg_string_new("2")));
        parse("(1 to: 5 by: 2 do: (y = y / 2))", marg_vector_new(OP_1, OP_INTEGER, marg_string_new("5"), OP_2, OP_VARIABLE, marg_string_new("y"), OP_2, OP_BINARY, marg_string_new("/"), OP_STORE, marg_string_new("y"), OP_KEYWORD, marg_string_new("to:by:do:"), marg_string_new("3")));
        parse("[1,2,3,4] each: { item | x = x + item }", marg_vector_new(OP_1, OP_2, OP_INTEGER, marg_string_new("3"), OP_INTEGER, marg_string_new("4"), OP_TENSOR, marg_string_new("4"), OP_START_PROC, OP_VARIABLE, marg_string_new("item"), OP_TENSOR, marg_string_new("1"), OP_VARIABLE, marg_string_new("x"), OP_VARIABLE, marg_string_new("item"), OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("x"), OP_END_PROC, OP_KEYWORD, marg_string_new("each:"), marg_string_new("1")));
    });
})

#endif
