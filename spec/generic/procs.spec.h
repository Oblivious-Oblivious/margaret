#ifndef __PROCS_SPEC_H_
#define __PROCS_SPEC_H_

#include "../_helpers.h"

module(procs_spec, {
    it("parses procs", {
        parse("{ x = (x = 1, y = 2) }", marg_vector_new(FM_START_PROC, FM_TENSOR, marg_string_new("0"), FM_INTEGER, marg_string_new("1"), FM_STORE, marg_string_new("x"), FM_INTEGER, marg_string_new("2"), FM_STORE, marg_string_new("y"), FM_STORE, marg_string_new("x"), FM_END_PROC)); // x = 2
        parse("x =  { \
            v1, v2 | ( \
                v1 += 1, \
                v1 += 2, \
                v1 * v2 \
            ) \
        }", marg_vector_new(FM_START_PROC, FM_VARIABLE, marg_string_new("v1"), FM_VARIABLE, marg_string_new("v2"), FM_TENSOR, marg_string_new("2"), FM_VARIABLE, marg_string_new("v1"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new("+="), FM_VARIABLE, marg_string_new("v1"), FM_INTEGER, marg_string_new("2"), FM_BINARY, marg_string_new("+="), FM_VARIABLE, marg_string_new("v1"), FM_VARIABLE, marg_string_new("v2"), FM_BINARY, marg_string_new("*"), FM_END_PROC, FM_STORE, marg_string_new("x"))); // v1 * v2
    });

    it("parses parameterized procs and procs returning literals", {
        parse("{|}", marg_vector_new(FM_START_PROC, FM_TENSOR, marg_string_new("0"), FM_END_PROC));
        parse("{ 42 }", marg_vector_new(FM_START_PROC, FM_TENSOR, marg_string_new("0"), FM_INTEGER, marg_string_new("42"), FM_END_PROC));
        parse("{ a | a puts }", marg_vector_new(FM_START_PROC, FM_VARIABLE, marg_string_new("a"), FM_TENSOR, marg_string_new("1"), FM_VARIABLE, marg_string_new("a"), FM_UNARY, marg_string_new("puts"), FM_END_PROC));
        parse("{ 2 + 3 }", marg_vector_new(FM_START_PROC, FM_TENSOR, marg_string_new("0"), FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("+"), FM_END_PROC));
        parse("{ (x = 1, y = 2, x + y) }", marg_vector_new(FM_START_PROC, FM_TENSOR, marg_string_new("0"), FM_INTEGER, marg_string_new("1"), FM_STORE, marg_string_new("x"), FM_INTEGER, marg_string_new("2"), FM_STORE, marg_string_new("y"), FM_VARIABLE, marg_string_new("x"), FM_VARIABLE, marg_string_new("y"), FM_BINARY, marg_string_new("+"), FM_END_PROC));
        parse("{ param | param puts }", marg_vector_new(FM_START_PROC, FM_VARIABLE, marg_string_new("param"), FM_TENSOR, marg_string_new("1"), FM_VARIABLE, marg_string_new("param"), FM_UNARY, marg_string_new("puts"), FM_END_PROC));
        parse("{ a | a }", marg_vector_new(FM_START_PROC, FM_VARIABLE, marg_string_new("a"), FM_TENSOR, marg_string_new("1"), FM_VARIABLE, marg_string_new("a"), FM_END_PROC));
        parse("{ x = 2 } eval", marg_vector_new(FM_START_PROC, FM_TENSOR, marg_string_new("0"), FM_INTEGER, marg_string_new("2"), FM_STORE, marg_string_new("x"), FM_END_PROC, FM_UNARY, marg_string_new("eval")));
        parse("{ param | param puts } value: 42", marg_vector_new(FM_START_PROC, FM_VARIABLE, marg_string_new("param"), FM_TENSOR, marg_string_new("1"), FM_VARIABLE, marg_string_new("param"), FM_UNARY, marg_string_new("puts"), FM_END_PROC, FM_INTEGER, marg_string_new("42"), FM_KEYWORD, marg_string_new("value:"), marg_string_new("1")));
    });
})

#endif
