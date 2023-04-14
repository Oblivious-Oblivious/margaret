#ifndef __METHOD_DEFINITION_SPEC_H_
#define __METHOD_DEFINITION_SPEC_H_

#include "../_helpers.h"

module(method_definition_spec, {
    it("parses unary methods", {
        parse("#incr => self + 1", marg_vector_new( \
            OP_PUSH_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_PUSH_ANY_OBJECT, \
            OP_PUSH_STRING, marg_string_new("\"incr\""), \
            OP_START_PUSH_PROC,
                OP_PUSH_SELF, \
                OP_PUSH_TENSOR, marg_string_new("1"), \
                OP_PUSH_SELF, \
                OP_PUSH_1, \
                OP_BINARY, marg_string_new("+"), \
            OP_END_PUSH_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));
        parse("#  incr => self + 1", marg_vector_new( \
            OP_PUSH_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_PUSH_ANY_OBJECT, \
            OP_PUSH_STRING, marg_string_new("\"incr\""), \
            OP_START_PUSH_PROC,
                OP_PUSH_SELF, \
                OP_PUSH_TENSOR, marg_string_new("1"), \
                OP_PUSH_SELF, \
                OP_PUSH_1, \
                OP_BINARY, marg_string_new("+"), \
            OP_END_PUSH_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));
        parse("#is_empty? => true", marg_vector_new( \
            OP_PUSH_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_PUSH_ANY_OBJECT, \
            OP_PUSH_STRING, marg_string_new("\"is_empty?\""), \
            OP_START_PUSH_PROC,
                OP_PUSH_SELF, \
                OP_PUSH_TENSOR, marg_string_new("1"), \
                OP_PUSH_TRUE, \
            OP_END_PUSH_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));

        parse("# 0 fact => 1", marg_vector_new( \
            OP_PUSH_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_PUSH_0, \
            OP_PUSH_STRING, marg_string_new("\"fact\""), \
            OP_START_PUSH_PROC, \
                OP_PUSH_SELF, \
                OP_PUSH_TENSOR, marg_string_new("1"), \
                OP_PUSH_1, \
            OP_END_PUSH_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));

        // Method unary object: 0 message: "fact" method: -> { self | 1 }
        // Method unary object: _ message: "fact" method: -> { self | self * (self - 1) fact }
        parse("( \
            # 0 fact => 1, \
            # _ fact => self * (self-1) fact \
        )", marg_vector_new( \
            OP_PUSH_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_PUSH_0, \
            OP_PUSH_STRING, marg_string_new("\"fact\""), \
            OP_START_PUSH_PROC, \
                OP_PUSH_SELF, \
                OP_PUSH_TENSOR, marg_string_new("1"), \
                OP_PUSH_1, \
            OP_END_PUSH_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3"), \
            \
            OP_PUSH_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_PUSH_ANY_OBJECT, \
            OP_PUSH_STRING, marg_string_new("\"fact\""), \
            OP_START_PUSH_PROC, \
                OP_PUSH_SELF, \
                OP_PUSH_TENSOR, marg_string_new("1"), \
                OP_PUSH_SELF, \
                OP_PUSH_SELF, \
                OP_PUSH_1, \
                OP_BINARY, marg_string_new("-"), \
                OP_UNARY, marg_string_new("fact"), \
                OP_BINARY, marg_string_new("*"), \
            OP_END_PUSH_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));
    });

    it("parses binary methods", {
        parse("#** a_number => self raised_to: a_number", marg_vector_new(OP_START_PUSH_BINARY_METHOD, marg_string_new("\"**\""), OP_PUSH_VARIABLE, marg_string_new("a_number"), OP_PUSH_SELF, OP_PUSH_VARIABLE, marg_string_new("a_number"), OP_KEYWORD, marg_string_new("raised_to:"), marg_string_new("1"), OP_END_PUSH_BINARY_METHOD));
        // parse("# 0 ** a_number => 0", "");
        // parse("# 0 ** 0 => nil", "");
    });

    it("parses keyword methods", {
        parse("#add: element at: position => 42", marg_vector_new(OP_START_PUSH_KEYWORD_METHOD, marg_string_new("\"add:at:\""), OP_PUSH_VARIABLE, marg_string_new("element"), OP_PUSH_VARIABLE, marg_string_new("position"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_INTEGER, marg_string_new("42"), OP_END_PUSH_KEYWORD_METHOD));
        parse("#ok?: value1 otherwise!: value2 => 17", marg_vector_new(OP_START_PUSH_KEYWORD_METHOD, marg_string_new("\"ok?:otherwise!:\""), OP_PUSH_VARIABLE, marg_string_new("value1"), OP_PUSH_VARIABLE, marg_string_new("value2"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_INTEGER, marg_string_new("17"), OP_END_PUSH_KEYWORD_METHOD));
        // parse("# [] add: element at: position => 17");
        // parse("# [] add: 'a' at: 0 => ['a']");
        // parse("#add: 'a' at: 0 => ['a'] ++ self");

        parse("#times: a_block => ( \
            remaining = self, \
            ->{ (remaining = remaining - 1) >= 0 } while_true: ->{ a_block value } \
        )", marg_vector_new(OP_START_PUSH_KEYWORD_METHOD, marg_string_new("\"times:\""), OP_PUSH_VARIABLE, marg_string_new("a_block"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_SELF, OP_STORE, marg_string_new("remaining"), OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_VARIABLE, marg_string_new("remaining"), OP_PUSH_1, OP_BINARY, marg_string_new("-"), OP_STORE, marg_string_new("remaining"), OP_PUSH_0, OP_BINARY, marg_string_new(">="), OP_END_PUSH_PROC, OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_VARIABLE, marg_string_new("a_block"), OP_UNARY, marg_string_new("value"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("while_true:"), marg_string_new("1"), OP_END_PUSH_KEYWORD_METHOD));
    });
})

#endif
