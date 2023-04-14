#ifndef __MARGARET_MESSAGES_SPEC_H_
#define __MARGARET_MESSAGES_SPEC_H_

#include "../_helpers.h"

module(margaret_messages_spec, {
    it("parses messages without an object", {
        parse("if: true then: {|} else: {|}", marg_vector_new( \
            OP_PUSH_VARIABLE, marg_string_new("Margaret"), \
            OP_PUSH_TRUE,
            OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_END_PUSH_PROC,
            OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_END_PUSH_PROC,
            OP_KEYWORD, marg_string_new("if:then:else:"), marg_string_new("3")
        ));

        parse("puts: \"Hello, World!\"", marg_vector_new( \
            OP_PUSH_VARIABLE, marg_string_new("Margaret"), \
            OP_PUSH_STRING, marg_string_new("Hello, World!"), \
            OP_KEYWORD, marg_string_new("puts:"), marg_string_new("1") \
        ));
    });

    it("parses standalone identifiers as variables and not unary messages", {
        parse("myvar", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("myvar")));
    });

    it("fails on parsing standalone binary messages", {
        error("++", "");
    });

    it("binds to the Margaret object using standalone margaret messages", {
        parse("Margaret bind: # while: condition_block do: block => \
            if: condition_block eval then: {(\
                block eval, \
                while: condition_block do: block \
            )} \
        ", marg_vector_new( \
            OP_PUSH_VARIABLE, marg_string_new("Margaret"), \
            OP_PUSH_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_PUSH_ANY_OBJECT, \
            OP_PUSH_STRING, marg_string_new("while:do:"), \
            OP_PUSH_METHOD_PARAMETER, marg_string_new("condition_block"), \
            OP_PUSH_METHOD_PARAMETER, marg_string_new("block"), \
            OP_PUSH_TENSOR, marg_string_new("2"), \
            OP_START_PUSH_PROC, \
                OP_PUSH_SELF, \
                OP_PUSH_VARIABLE, marg_string_new("condition_block"), \
                OP_PUSH_VARIABLE, marg_string_new("block"), \
                OP_PUSH_TENSOR, marg_string_new("3"), \
                OP_PUSH_VARIABLE, marg_string_new("Margaret"), \
                OP_PUSH_VARIABLE, marg_string_new("condition_block"), \
                OP_UNARY, marg_string_new("eval"), \
                OP_START_PUSH_PROC, \
                    OP_PUSH_TENSOR, marg_string_new("0"), \
                    OP_PUSH_VARIABLE, marg_string_new("block"), \
                    OP_UNARY, marg_string_new("eval"), \
                    OP_PUSH_VARIABLE, marg_string_new("Margaret"), \
                    OP_PUSH_VARIABLE, marg_string_new("condition_block"), \
                    OP_PUSH_VARIABLE, marg_string_new("block"), \
                    OP_KEYWORD, marg_string_new("while:do:"), marg_string_new("2"), \
                OP_END_PUSH_PROC, \
                OP_KEYWORD, marg_string_new("if:then:"), marg_string_new("2"), \
            OP_END_PUSH_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4"), \
            OP_KEYWORD, marg_string_new("bind:"), marg_string_new("1") \
        ));
    });
})

#endif
