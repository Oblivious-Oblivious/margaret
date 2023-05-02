#ifndef __METHOD_DEFINITION_SPEC_H_
#define __METHOD_DEFINITION_SPEC_H_

#include "../_helpers.h"

module(method_definition_spec, {
    it("parses unary methods", {
        parse("#incr => self + 1", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("incr"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_SELF, \
                FM_INTEGER, string_new("1"), \
                FM_BINARY, string_new("+"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:method:"), string_new("3") \
        ));
        parse("#  incr => self + 1", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("incr"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_SELF, \
                FM_INTEGER, string_new("1"), \
                FM_BINARY, string_new("+"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:method:"), string_new("3") \
        ));
        parse("#is_empty? => $true", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("is_empty?"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_TRUE, \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:method:"), string_new("3") \
        ));

        parse("# 0 fact => 1", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("unary"), \
            FM_INTEGER, string_new("0"), \
            FM_STRING, string_new("fact"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_INTEGER, string_new("1"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:method:"), string_new("3") \
        ));

        // Method unary object: 0 message: "fact" method: { self | 1 }
        // Method unary object: _ message: "fact" method: { self | self * (self - 1) fact }
        parse("( \
            # 0 fact => 1, \
            # _ fact => self * (self-1) fact \
        )", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("unary"), \
            FM_INTEGER, string_new("0"), \
            FM_STRING, string_new("fact"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_INTEGER, string_new("1"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:method:"), string_new("3"), \
            \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("fact"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_SELF, \
                FM_SELF, \
                FM_INTEGER, string_new("1"), \
                FM_BINARY, string_new("-"), \
                FM_UNARY, string_new("fact"), \
                FM_BINARY, string_new("*"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:method:"), string_new("3") \
        ));
    });

    it("parses binary methods", {
        // Method binary object: 0 message: "**" param: 0 method: { self | $nil }
        parse("# 0 ** 0 => $nil", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("binary"), \
            FM_INTEGER, string_new("0"), \
            FM_STRING, string_new("**"), \
            FM_INTEGER, string_new("0"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_NIL, \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:param:method:"), string_new("4") \
        ));

        // Method binary object: 0 message: "**" param: _ method: { self | 0 }
        parse("# 0 ** _ => 0", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("binary"), \
            FM_INTEGER, string_new("0"), \
            FM_STRING, string_new("**"), \
            FM_ANY_OBJECT, \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_INTEGER, string_new("0"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:param:method:"), string_new("4") \
        ));

        // Method binary object: _ message: "**" param: 0 method: { self | 1 }
        parse("# _ ** 0 => 1", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("binary"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("**"), \
            FM_INTEGER, string_new("0"),
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_INTEGER, string_new("1"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:param:method:"), string_new("4") \
        ));

        // Method binary object: 0 message: "**" param: a_number method: { self, a_number | 0 }
        parse("# 0 ** a_number => 0", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("binary"), \
            FM_INTEGER, string_new("0"), \
            FM_STRING, string_new("**"), \
            FM_METHOD_PARAMETER, string_new("a_number"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_PROC_PARAMETER, string_new("a_number"), \
                FM_INTEGER, string_new("0"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:param:method:"), string_new("4") \
        ));

        // Method binary object: _ message: "**" param: a_number method: { self, a_number | self raised_to: a_number }
        parse("# ** a_number => self raised_to: a_number", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("binary"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("**"), \
            FM_METHOD_PARAMETER, string_new("a_number"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_PROC_PARAMETER, string_new("a_number"), \
                FM_SELF, \
                FM_LOCAL, string_new("a_number"), \
                FM_KEYWORD, string_new("raised_to:"), string_new("1"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:param:method:"), string_new("4") \
        ));
    });

    it("parses keyword methods", {
        // Method keyword object: _ message: "add:at:" params: [element, position] method: { self, element, position | 42 }
        parse("#add: element at: position => 42", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("add:at:"), \
            FM_METHOD_PARAMETER, string_new("element"), \
            FM_METHOD_PARAMETER, string_new("position"), \
            FM_TENSOR, string_new("2"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_PROC_PARAMETER, string_new("element"), \
                FM_PROC_PARAMETER, string_new("position"), \
                FM_INTEGER, string_new("42"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4") \
        ));

        // Method keyword object: _ message: "new:" params: [2] method: { self | 1 }
        parse("# _ new: 2 => 1", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("new:"), \
            FM_INTEGER, string_new("2"), \
            FM_TENSOR, string_new("1"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_INTEGER, string_new("1"),
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4") \
        ));

        // Method keyword object: 1 message: "add:" params: [$nil] method: { self | $nil }
        parse("# 1 add: $nil => $nil", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_INTEGER, string_new("1"), \
            FM_STRING, string_new("add:"), \
            FM_NIL, \
            FM_TENSOR, string_new("1"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_NIL, \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4") \
        ));

        // Method keyword object: 1 message: "add:" params: [2] method: { self | 3 }
        parse("# 1 add: 2 => 3", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_INTEGER, string_new("1"), \
            FM_STRING, string_new("add:"), \
            FM_INTEGER, string_new("2"), \
            FM_TENSOR, string_new("1"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_INTEGER, string_new("3"),
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4") \
        ));

        // Method keyword object: 1 message: "one:" params: [_, _] method: { self | 42 }
        parse("# 1 one: _ two: _ => 42", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_INTEGER, string_new("1"), \
            FM_STRING, string_new("one:two:"), \
            FM_ANY_OBJECT, \
            FM_ANY_OBJECT, \
            FM_TENSOR, string_new("2"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_INTEGER, string_new("42"),
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4") \
        ));

        // Method keyword object: _ message: "ok?:otherwise!:" params: [value1, value2] method: { self, value1, value2 | 17 }
        parse("#ok?: value1 otherwise!: value2 => 17", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("ok?:otherwise!:"), \
            FM_METHOD_PARAMETER, string_new("value1"), \
            FM_METHOD_PARAMETER, string_new("value2"), \
            FM_TENSOR, string_new("2"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_PROC_PARAMETER, string_new("value1"), \
                FM_PROC_PARAMETER, string_new("value2"), \
                FM_INTEGER, string_new("17"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4") \
        ));

        // Method keyword object: [] message: "add:at:" params: ["element", "position"] method: { self, element, position | 17 }
        parse("# [] add: element at: position => 17", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_TENSOR, string_new("0"), \
            FM_STRING, string_new("add:at:"), \
            FM_METHOD_PARAMETER, string_new("element"), \
            FM_METHOD_PARAMETER, string_new("position"), \
            FM_TENSOR, string_new("2"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_PROC_PARAMETER, string_new("element"), \
                FM_PROC_PARAMETER, string_new("position"), \
                FM_INTEGER, string_new("17"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4") \
        ));

        // Method keyword object: [] message: "add:at:" params: ['a', 0] method: { self | ['a'] }
        parse("# [] add: 'a' at: 0 => ['a']", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_TENSOR, string_new("0"), \
            FM_STRING, string_new("add:at:"), \
            FM_STRING, string_new("a"), \
            FM_INTEGER, string_new("0"),
            FM_TENSOR, string_new("2"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_STRING, string_new("a"), \
                FM_TENSOR, string_new("1"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4") \
        ));

        // Method keyword object: _ message: "add:at:" params: ['a', 0]
        parse("#add: 'a' at: 0 => ['a'] ++ self", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("add:at:"), \
            FM_STRING, string_new("a"), \
            FM_INTEGER, string_new("0"),
            FM_TENSOR, string_new("2"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_STRING, string_new("a"), \
                FM_TENSOR, string_new("1"), \
                FM_SELF, \
                FM_BINARY, string_new("++"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4") \
        ));

        // Method keyword object: _ message: "times:" params: ["a_block"] method: { self, a_block | (
        //     remaining = self,
        //     { (remaining = remaining - 1) >= 0 } while_true: { a_block value }
        // ) }
        parse("#times: a_block => ( \
            remaining = self, \
            { (remaining = remaining - 1) >= 0 } while_true: { a_block value } \
        )", vector_new( \
            FM_LOCAL, string_new("Method"), \
            FM_UNARY, string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, string_new("times:"), \
            FM_METHOD_PARAMETER, string_new("a_block"), \
            FM_TENSOR, string_new("1"), \
            FM_START_PROC, \
                FM_PROC_PARAMETER, FM_SELF, \
                FM_PROC_PARAMETER, string_new("a_block"), \
                FM_SELF, \
                FM_STORE_LOCAL, string_new("remaining"), \
                FM_START_PROC, \
                    FM_LOCAL, string_new("remaining"), \
                    FM_INTEGER, string_new("1"), \
                    FM_BINARY, string_new("-"), \
                    FM_STORE_LOCAL, string_new("remaining"), \
                    FM_INTEGER, string_new("0"), \
                    FM_BINARY, string_new(">="), \
                FM_END_PROC, \
                FM_START_PROC, \
                    FM_LOCAL, string_new("a_block"), \
                    FM_UNARY, string_new("value"), \
                FM_END_PROC, \
                FM_KEYWORD, string_new("while_true:"), string_new("1"), \
            FM_END_PROC, \
            FM_KEYWORD, string_new("object:message:params:method:"), string_new("4") \
        ));
    });
})

#endif
