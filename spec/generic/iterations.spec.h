#ifndef __ITERATIONS_SPEC_H_
#define __ITERATIONS_SPEC_H_

#include "../_helpers.h"

module(iterations_spec, {
    it("parses iteration statements", {
        parse("(x > 0 while_true: (x = x - 1, y = y * 2))", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_0, FM_BINARY, marg_string_new(">"), FM_VARIABLE, marg_string_new("x"), FM_1, FM_BINARY, marg_string_new("-"), FM_STORE, marg_string_new("x"), FM_VARIABLE, marg_string_new("y"), FM_2, FM_BINARY, marg_string_new("*"), FM_STORE, marg_string_new("y"), FM_KEYWORD, marg_string_new("while_true:"), marg_string_new("1")));
        parse("(x >= 0 while_false: (x = x + 1, y = y * 2))", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_0, FM_BINARY, marg_string_new(">="), FM_VARIABLE, marg_string_new("x"), FM_1, FM_BINARY, marg_string_new("+"), FM_STORE, marg_string_new("x"), FM_VARIABLE, marg_string_new("y"), FM_2, FM_BINARY, marg_string_new("*"), FM_STORE, marg_string_new("y"), FM_KEYWORD, marg_string_new("while_false:"), marg_string_new("1")));
        parse("(x times: (y = y * 2))", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_VARIABLE, marg_string_new("y"), FM_2, FM_BINARY, marg_string_new("*"), FM_STORE, marg_string_new("y"), FM_KEYWORD, marg_string_new("times:"), marg_string_new("1")));
        parse("(1 to: 5 do: (y = y * 2))", marg_vector_new(FM_1, FM_INTEGER, marg_string_new("5"), FM_VARIABLE, marg_string_new("y"), FM_2, FM_BINARY, marg_string_new("*"), FM_STORE, marg_string_new("y"), FM_KEYWORD, marg_string_new("to:do:"), marg_string_new("2")));
        parse("(1 to: 5 by: 2 do: (y = y / 2))", marg_vector_new(FM_1, FM_INTEGER, marg_string_new("5"), FM_2, FM_VARIABLE, marg_string_new("y"), FM_2, FM_BINARY, marg_string_new("/"), FM_STORE, marg_string_new("y"), FM_KEYWORD, marg_string_new("to:by:do:"), marg_string_new("3")));
        parse("[1,2,3,4] each: { item | x = x + item }", marg_vector_new(FM_1, FM_2, FM_INTEGER, marg_string_new("3"), FM_INTEGER, marg_string_new("4"), FM_TENSOR, marg_string_new("4"), FM_START_PROC, FM_VARIABLE, marg_string_new("item"), FM_TENSOR, marg_string_new("1"), FM_VARIABLE, marg_string_new("x"), FM_VARIABLE, marg_string_new("item"), FM_BINARY, marg_string_new("+"), FM_STORE, marg_string_new("x"), FM_END_PROC, FM_KEYWORD, marg_string_new("each:"), marg_string_new("1")));
    });
})

#endif
