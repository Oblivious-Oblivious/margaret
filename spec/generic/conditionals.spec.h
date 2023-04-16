#ifndef __CONDITIONALS_SPEC_H_
#define __CONDITIONALS_SPEC_H_

#include "../_helpers.h"

module(conditionals_spec, {
    it("parses conditional statements", {
        parse("(x > 10 + 42)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("10"), FM_BINARY, marg_string_new(">"), FM_INTEGER, marg_string_new("42"), FM_BINARY, marg_string_new("+")));
        parse("(x > 10 if_true: 42)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("10"), FM_BINARY, marg_string_new(">"), FM_INTEGER, marg_string_new("42"), FM_KEYWORD, marg_string_new("if_true:"), marg_string_new("1")));
        parse("(x > 10 if_false: 41)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("10"), FM_BINARY, marg_string_new(">"), FM_INTEGER, marg_string_new("41"), FM_KEYWORD, marg_string_new("if_false:"), marg_string_new("1")));
        parse("(x > 10 \
                if_true: 42 \
                if_false: 41)", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("10"), FM_BINARY, marg_string_new(">"), FM_INTEGER, marg_string_new("42"), FM_INTEGER, marg_string_new("41"), FM_KEYWORD, marg_string_new("if_true:if_false:"), marg_string_new("2")));
        parse("(x > 10 \
                if_true: ( \
                    x > 5 \
                        if_true: 1 \
                        if_false: 2 \
                ) \
                if_false: 3 \
        )", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("10"), FM_BINARY, marg_string_new(">"), FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("5"), FM_BINARY, marg_string_new(">"), FM_1, FM_2, FM_KEYWORD, marg_string_new("if_true:if_false:"), marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_KEYWORD, marg_string_new("if_true:if_false:"), marg_string_new("2")));
        parse("(obj match: [ \
                    [1, 100], \
                    [2, 200], \
                    [3, 300], \
                ] \
        )", marg_vector_new(FM_VARIABLE, marg_string_new("obj"), FM_1, FM_INTEGER, marg_string_new("100"), FM_TENSOR, marg_string_new("2"), FM_2, FM_INTEGER, marg_string_new("200"), FM_TENSOR, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_INTEGER, marg_string_new("300"), FM_TENSOR, marg_string_new("2"), FM_TENSOR, marg_string_new("3"), FM_KEYWORD, marg_string_new("match:"), marg_string_new("1")));
        parse("obj match: {\"1\": 100, \"2\": 200, \"3\": 300}", marg_vector_new(FM_VARIABLE, marg_string_new("obj"), FM_VARIABLE, marg_string_new("Association"), FM_STRING, marg_string_new("1"), FM_INTEGER, marg_string_new("100"), FM_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("Association"), FM_STRING, marg_string_new("2"), FM_INTEGER, marg_string_new("200"), FM_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("Association"), FM_STRING, marg_string_new("3"), FM_INTEGER, marg_string_new("300"), FM_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), FM_HASH, marg_string_new("3"), FM_KEYWORD, marg_string_new("match:"), marg_string_new("1")));
    });
})

#endif
