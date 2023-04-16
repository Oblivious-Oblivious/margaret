#ifndef __PROCS_SPEC_H_
#define __PROCS_SPEC_H_

#include "../_helpers.h"

module(procs_spec, {
    it("parses procs", {
        parse("{ x = (x = 1, y = 2) }", marg_vector_new(OP_START_PROC, OP_TENSOR, marg_string_new("0"), OP_1, OP_STORE, marg_string_new("x"), OP_2, OP_STORE, marg_string_new("y"), OP_STORE, marg_string_new("x"), OP_END_PROC)); // x = 2
        parse("x =  { \
            v1, v2 | ( \
                v1 += 1, \
                v1 += 2, \
                v1 * v2 \
            ) \
        }", marg_vector_new(OP_START_PROC, OP_VARIABLE, marg_string_new("v1"), OP_VARIABLE, marg_string_new("v2"), OP_TENSOR, marg_string_new("2"), OP_VARIABLE, marg_string_new("v1"), OP_1, OP_BINARY, marg_string_new("+="), OP_VARIABLE, marg_string_new("v1"), OP_2, OP_BINARY, marg_string_new("+="), OP_VARIABLE, marg_string_new("v1"), OP_VARIABLE, marg_string_new("v2"), OP_BINARY, marg_string_new("*"), OP_END_PROC, OP_STORE, marg_string_new("x"))); // v1 * v2
    });

    it("parses parameterized procs and procs returning literals", {
        parse("{|}", marg_vector_new(OP_START_PROC, OP_TENSOR, marg_string_new("0"), OP_END_PROC));
        parse("{ 42 }", marg_vector_new(OP_START_PROC, OP_TENSOR, marg_string_new("0"), OP_INTEGER, marg_string_new("42"), OP_END_PROC));
        parse("{ a | a puts }", marg_vector_new(OP_START_PROC, OP_VARIABLE, marg_string_new("a"), OP_TENSOR, marg_string_new("1"), OP_VARIABLE, marg_string_new("a"), OP_UNARY, marg_string_new("puts"), OP_END_PROC));
        parse("{ 2 + 3 }", marg_vector_new(OP_START_PROC, OP_TENSOR, marg_string_new("0"), OP_2, OP_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_END_PROC));
        parse("{ (x = 1, y = 2, x + y) }", marg_vector_new(OP_START_PROC, OP_TENSOR, marg_string_new("0"), OP_1, OP_STORE, marg_string_new("x"), OP_2, OP_STORE, marg_string_new("y"), OP_VARIABLE, marg_string_new("x"), OP_VARIABLE, marg_string_new("y"), OP_BINARY, marg_string_new("+"), OP_END_PROC));
        parse("{ param | param puts }", marg_vector_new(OP_START_PROC, OP_VARIABLE, marg_string_new("param"), OP_TENSOR, marg_string_new("1"), OP_VARIABLE, marg_string_new("param"), OP_UNARY, marg_string_new("puts"), OP_END_PROC));
        parse("{ a | a }", marg_vector_new(OP_START_PROC, OP_VARIABLE, marg_string_new("a"), OP_TENSOR, marg_string_new("1"), OP_VARIABLE, marg_string_new("a"), OP_END_PROC));
        parse("{ x = 2 } eval", marg_vector_new(OP_START_PROC, OP_TENSOR, marg_string_new("0"), OP_2, OP_STORE, marg_string_new("x"), OP_END_PROC, OP_UNARY, marg_string_new("eval")));
        parse("{ param | param puts } value: 42", marg_vector_new(OP_START_PROC, OP_VARIABLE, marg_string_new("param"), OP_TENSOR, marg_string_new("1"), OP_VARIABLE, marg_string_new("param"), OP_UNARY, marg_string_new("puts"), OP_END_PROC, OP_INTEGER, marg_string_new("42"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1")));
    });
})

#endif
