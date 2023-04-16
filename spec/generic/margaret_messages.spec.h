#ifndef __MARGARET_MESSAGES_SPEC_H_
#define __MARGARET_MESSAGES_SPEC_H_

#include "../_helpers.h"

module(margaret_messages_spec, {
    it("parses messages without an object", {
        parse("if: true then: {|} else: {|}", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Margaret"), \
            FM_TRUE,
            FM_START_PROC, FM_TENSOR, marg_string_new("0"), FM_END_PROC,
            FM_START_PROC, FM_TENSOR, marg_string_new("0"), FM_END_PROC,
            FM_KEYWORD, marg_string_new("if:then:else:"), marg_string_new("3")
        ));

        parse("puts: \"Hello, World!\"", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Margaret"), \
            FM_STRING, marg_string_new("Hello, World!"), \
            FM_KEYWORD, marg_string_new("puts:"), marg_string_new("1") \
        ));
    });

    it("parses standalone identifiers as variables and not unary messages", {
        parse("myvar", marg_vector_new(FM_VARIABLE, marg_string_new("myvar")));
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
            FM_VARIABLE, marg_string_new("Margaret"), \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("while:do:"), \
            FM_METHOD_PARAMETER, marg_string_new("condition_block"), \
            FM_METHOD_PARAMETER, marg_string_new("block"), \
            FM_TENSOR, marg_string_new("2"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_VARIABLE, marg_string_new("condition_block"), \
                FM_VARIABLE, marg_string_new("block"), \
                FM_TENSOR, marg_string_new("3"), \
                FM_VARIABLE, marg_string_new("Margaret"), \
                FM_VARIABLE, marg_string_new("condition_block"), \
                FM_UNARY, marg_string_new("eval"), \
                FM_START_PROC, \
                    FM_TENSOR, marg_string_new("0"), \
                    FM_VARIABLE, marg_string_new("block"), \
                    FM_UNARY, marg_string_new("eval"), \
                    FM_VARIABLE, marg_string_new("Margaret"), \
                    FM_VARIABLE, marg_string_new("condition_block"), \
                    FM_VARIABLE, marg_string_new("block"), \
                    FM_KEYWORD, marg_string_new("while:do:"), marg_string_new("2"), \
                FM_END_PROC, \
                FM_KEYWORD, marg_string_new("if:then:"), marg_string_new("2"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4"), \
            FM_KEYWORD, marg_string_new("bind:"), marg_string_new("1") \
        ));
    });
})

#endif
