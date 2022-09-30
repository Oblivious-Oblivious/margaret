#ifndef __CONDITIONALS_SPEC_H_
#define __CONDITIONALS_SPEC_H_

#include "../_helpers.h"

module(conditionals_spec, {
    it("parses conditional statements", {
        parse("(x > 10 + 42)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("10"), OP_BINARY, marg_string_new(">"), OP_PUSH_INTEGER, marg_string_new("42"), OP_BINARY, marg_string_new("+")));
        parse("(x > 10 if_true: 42)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("10"), OP_BINARY, marg_string_new(">"), OP_PUSH_INTEGER, marg_string_new("42"), OP_KEYWORD, marg_string_new("if_true:"), marg_string_new("1")));
        parse("(x > 10 if_false: 41)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("10"), OP_BINARY, marg_string_new(">"), OP_PUSH_INTEGER, marg_string_new("41"), OP_KEYWORD, marg_string_new("if_false:"), marg_string_new("1")));
        parse("(x > 10 \
                if_true: 42 \
                if_false: 41)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("10"), OP_BINARY, marg_string_new(">"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("41"), OP_KEYWORD, marg_string_new("if_true:if_false:"), marg_string_new("2")));
        parse("(x > 10 \
                if_true: ( \
                    x > 5 \
                        if_true: 1 \
                        if_false: 2 \
                ) \
                if_false: 3 \
        )", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("10"), OP_BINARY, marg_string_new(">"), OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new(">"), OP_PUSH_1, OP_PUSH_2, OP_KEYWORD, marg_string_new("if_true:if_false:"), marg_string_new("2"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("if_true:if_false:"), marg_string_new("2")));
        parse("(obj match: [ \
                    [1, 100], \
                    [2, 200], \
                    [3, 300], \
                ] \
        )", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_PUSH_1, OP_PUSH_INTEGER, marg_string_new("100"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("200"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_INTEGER, marg_string_new("3"), OP_PUSH_INTEGER, marg_string_new("300"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_TENSOR, marg_string_new("3"), OP_KEYWORD, marg_string_new("match:"), marg_string_new("1")));
        parse("obj match: {\"1\": 100, \"2\": 200, \"3\": 300}", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"1\""), OP_PUSH_INTEGER, marg_string_new("100"), OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"2\""), OP_PUSH_INTEGER, marg_string_new("200"), OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"3\""), OP_PUSH_INTEGER, marg_string_new("300"), OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_HASH, marg_string_new("3"), OP_KEYWORD, marg_string_new("match:"), marg_string_new("1")));
    });
})

#endif
