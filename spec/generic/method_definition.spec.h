#ifndef __METHOD_DEFINITION_SPEC_H_
#define __METHOD_DEFINITION_SPEC_H_

#include "../_helpers.h"

module(method_definition_spec, {
    it("parses unary methods", {
        parse("# $true not => $false", vector_new( \
            FM_START_UNARY_METHOD, string_new("not"),
                FM_TRUE, FM_METHOD_RECEIVER, \
                FM_FALSE, \
                FM_POP, \
            FM_END_UNARY_METHOD, \
            FM_POP \
        ));

        parse("# $false neg => $nil", vector_new( \
            FM_START_UNARY_METHOD, string_new("neg"), \
                FM_FALSE, FM_METHOD_RECEIVER, \
                FM_NIL, \
                FM_POP, \
            FM_END_UNARY_METHOD, \
            FM_POP \
        ));

        parse("#incr => @self + 1", vector_new( \
            FM_START_UNARY_METHOD, string_new("incr"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_SELF, \
                FM_INTEGER, string_new("1"), \
                FM_BINARY, string_new("+"), \
                FM_POP, \
            FM_END_UNARY_METHOD, \
            FM_POP \
        ));
        parse("#  incr => @self + 1", vector_new( \
            FM_START_UNARY_METHOD, string_new("incr"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_SELF, \
                FM_INTEGER, string_new("1"), \
                FM_BINARY, string_new("+"), \
                FM_POP, \
            FM_END_UNARY_METHOD, \
            FM_POP \
        ));
        parse("#is_empty? => $true", vector_new( \
            FM_START_UNARY_METHOD, string_new("is_empty?"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_TRUE, \
                FM_POP, \
            FM_END_UNARY_METHOD, \
            FM_POP \
        ));

        parse("# 0 fact => 1", vector_new( \
            FM_START_UNARY_METHOD, string_new("fact"), \
                FM_INTEGER, string_new("0"), FM_METHOD_RECEIVER, \
                FM_INTEGER, string_new("1"), \
                FM_POP, \
            FM_END_UNARY_METHOD, \
            FM_POP \
        ));

        // Method unary object: 0 message: "fact" method: { 1 }
        // Method unary object: _ message: "fact" method: { @self * (@self - 1) fact }
        parse("( \
            # 0 fact => 1, \
            # _ fact => @self * (@self-1) fact \
        )", vector_new( \
            FM_START_UNARY_METHOD, string_new("fact"), \
                FM_INTEGER, string_new("0"), FM_METHOD_RECEIVER, \
                FM_INTEGER, string_new("1"), \
                FM_POP, \
            FM_END_UNARY_METHOD, \
            FM_POP, \
            \
            FM_START_UNARY_METHOD, string_new("fact"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_SELF, \
                FM_SELF, \
                FM_INTEGER, string_new("1"), \
                FM_BINARY, string_new("-"), \
                FM_UNARY, string_new("fact"), \
                FM_BINARY, string_new("*"), \
                FM_POP, \
            FM_END_UNARY_METHOD, \
            FM_POP \
        ));
    });

    it("parses binary methods", {
        // Method binary object: 0 message: "**" param: 0 method: { $nil }
        parse("# 0 ** 0 => $nil", vector_new( \
            FM_START_BINARY_METHOD, string_new("**"), \
                FM_INTEGER, string_new("0"), FM_METHOD_RECEIVER, \
                FM_INTEGER, string_new("0"), FM_METHOD_PARAMETER, \
                FM_NIL, \
                FM_POP, \
            FM_END_BINARY_METHOD, \
            FM_POP \
        ));

        // Method binary object: 0 message: "**" param: _ method: { 0 }
        parse("# 0 ** _ => 0", vector_new( \
            FM_START_BINARY_METHOD, string_new("**"), \
                FM_INTEGER, string_new("0"), FM_METHOD_RECEIVER, \
                FM_ANY_OBJECT, FM_METHOD_PARAMETER, \
                FM_INTEGER, string_new("0"), \
                FM_POP, \
            FM_END_BINARY_METHOD, \
            FM_POP \
        ));

        // Method binary object: _ message: "**" param: 0 method: { 1 }
        parse("# _ ** 0 => 1", vector_new( \
            FM_START_BINARY_METHOD, string_new("**"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_INTEGER, string_new("0"), FM_METHOD_PARAMETER, \
                FM_INTEGER, string_new("1"), \
                FM_POP, \
            FM_END_BINARY_METHOD, \
            FM_POP \
        ));

        // Method binary object: 0 message: "**" param: a_number method: { a_number | 0 }
        parse("# 0 ** a_number => 0", vector_new( \
            FM_START_BINARY_METHOD, string_new("**"), \
                FM_INTEGER, string_new("0"), FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("a_number"), FM_METHOD_PARAMETER, \
                FM_INTEGER, string_new("0"), \
                FM_POP, \
            FM_END_BINARY_METHOD, \
            FM_POP \
        ));

        // Method binary object: _ message: "**" param: a_number method: { a_number | @self raised_to: a_number }
        parse("# ** a_number => @self raised_to: a_number", vector_new( \
            FM_START_BINARY_METHOD, string_new("**"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("a_number"), FM_METHOD_PARAMETER, \
                FM_SELF, \
                FM_LOCAL, string_new("a_number"), \
                FM_KEYWORD, string_new("raised_to:"), string_new("1"), \
                FM_POP, \
            FM_END_BINARY_METHOD, \
            FM_POP \
        ));
    });

    it("parses keyword methods", {
        // Method keyword object: _ message: "add:at:" params: [element, position] method: { element, position | 42 }
        parse("#add: element at: position => 42", vector_new( \
            FM_START_KEYWORD_METHOD, string_new("add:at:"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("element"), FM_METHOD_PARAMETER, \
                FM_LOCAL, string_new("position"), FM_METHOD_PARAMETER, \
                FM_INTEGER, string_new("42"), \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_POP \
        ));

        // Method keyword object: _ message: "new:" params: [2] method: { 1 }
        parse("# _ new: 2 => 1", vector_new( \
            FM_START_KEYWORD_METHOD, string_new("new:"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_INTEGER, string_new("2"), FM_METHOD_PARAMETER, \
                FM_INTEGER, string_new("1"), \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_POP \
        ));

        // Method keyword object: 1 message: "add:" params: [$nil] method: { $nil }
        parse("# 1 add: $nil => $nil", vector_new( \
            FM_START_KEYWORD_METHOD, string_new("add:"), \
                FM_INTEGER, string_new("1"), FM_METHOD_RECEIVER, \
                FM_NIL, FM_METHOD_PARAMETER, \
                FM_NIL, \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_POP \
        ));

        // Method keyword object: 1 message: "add:" params: [2] method: { 3 }
        parse("# 1 add: 2 => 3", vector_new( \
            FM_START_KEYWORD_METHOD, string_new("add:"), \
                FM_INTEGER, string_new("1"), FM_METHOD_RECEIVER, \
                FM_INTEGER, string_new("2"), FM_METHOD_PARAMETER, \
                FM_INTEGER, string_new("3"), \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_POP \
        ));

        // Method keyword object: 1 message: "one:" params: [_, _] method: { 42 }
        parse("# 1 one: _ two: _ => 42", vector_new( \
            FM_START_KEYWORD_METHOD, string_new("one:two:"), \
                FM_INTEGER, string_new("1"), FM_METHOD_RECEIVER, \
                FM_ANY_OBJECT, FM_METHOD_PARAMETER, \
                FM_ANY_OBJECT, FM_METHOD_PARAMETER, \
                FM_INTEGER, string_new("42"), \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_POP \
        ));

        // Method keyword object: _ message: "ok?:otherwise!:" params: [value1, value2] method: { value1, value2 | 17 }
        parse("#ok?: value1 otherwise!: value2 => 17", vector_new( \
            FM_START_KEYWORD_METHOD, string_new("ok?:otherwise!:"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("value1"), FM_METHOD_PARAMETER, \
                FM_LOCAL, string_new("value2"), FM_METHOD_PARAMETER, \
                FM_INTEGER, string_new("17"), \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_POP \
        ));

        // Method keyword object: [] message: "add:at:" params: ["element", "position"] method: { element, position | 17 }
        parse("# [] add: element at: position => 17", vector_new( \
            FM_START_KEYWORD_METHOD, string_new("add:at:"), \
                FM_TENSOR, string_new("0"), FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("element"), FM_METHOD_PARAMETER, \
                FM_LOCAL, string_new("position"), FM_METHOD_PARAMETER, \
                FM_INTEGER, string_new("17"), \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_POP \
        ));

        // Method keyword object: [] message: "add:at:" params: ['a', 0] method: { ['a'] }
        parse("# [] add: 'a' at: 0 => ['a']", vector_new( \
            FM_START_KEYWORD_METHOD, string_new("add:at:"), \
                FM_TENSOR, string_new("0"), FM_METHOD_RECEIVER, \
                FM_STRING, string_new("a"), FM_METHOD_PARAMETER, \
                FM_INTEGER, string_new("0"), FM_METHOD_PARAMETER, \
                FM_STRING, string_new("a"), \
                FM_POP, \
                FM_TENSOR, string_new("1"), \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_POP \
        ));

        // Method keyword object: _ message: "add:at:" params: ['a', 0] method { ['a'] ++ @self }
        parse("#add: 'a' at: 0 => ['a'] ++ @self", vector_new( \
            FM_START_KEYWORD_METHOD, string_new("add:at:"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_STRING, string_new("a"), FM_METHOD_PARAMETER, \
                FM_INTEGER, string_new("0"), FM_METHOD_PARAMETER, \
                FM_STRING, string_new("a"), \
                FM_POP, \
                FM_TENSOR, string_new("1"), \
                FM_SELF, \
                FM_BINARY, string_new("++"), \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_POP \
        ));

        // Method keyword object: _ message: "times:" params: ["a_block"] method: { a_block | (
        //     remaining = @self,
        //     { (remaining = remaining - 1) >= 0 } while_true: { a_block value }
        // ) }
        parse("#times: a_block => ( \
            remaining = @self, \
            { (remaining = remaining - 1) >= 0 } while_true: { a_block value } \
        )", vector_new( \
            FM_START_KEYWORD_METHOD, string_new("times:"), \
                FM_ANY_OBJECT, FM_METHOD_RECEIVER, \
                FM_LOCAL, string_new("a_block"), FM_METHOD_PARAMETER, \
                FM_SELF, \
                FM_STORE_LOCAL, string_new("remaining"), \
                FM_POP, \
                FM_START_PROC, \
                    FM_LOCAL, string_new("remaining"), \
                    FM_INTEGER, string_new("1"), \
                    FM_BINARY, string_new("-"), \
                    FM_STORE_LOCAL, string_new("remaining"), \
                    FM_INTEGER, string_new("0"), \
                    FM_BINARY, string_new(">="), \
                    FM_POP, \
                FM_END_PROC, \
                FM_START_PROC, \
                    FM_LOCAL, string_new("a_block"), \
                    FM_UNARY, string_new("value"), \
                    FM_POP, \
                FM_END_PROC, \
                FM_KEYWORD, string_new("while_true:"), string_new("1"), \
                FM_POP, \
            FM_END_KEYWORD_METHOD, \
            FM_POP \
        ));
    });
})

#endif
