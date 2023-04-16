#ifndef __METHOD_DEFINITION_SPEC_H_
#define __METHOD_DEFINITION_SPEC_H_

#include "../_helpers.h"

module(method_definition_spec, {
    it("parses unary methods", {
        parse("#incr => self + 1", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("incr"), \
            FM_START_PROC,
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_SELF, \
                FM_1, \
                FM_BINARY, marg_string_new("+"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));
        parse("#  incr => self + 1", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("incr"), \
            FM_START_PROC,
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_SELF, \
                FM_1, \
                FM_BINARY, marg_string_new("+"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));
        parse("#is_empty? => true", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("is_empty?"), \
            FM_START_PROC,
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_TRUE, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));

        parse("# 0 fact => 1", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("unary"), \
            FM_0, \
            FM_STRING, marg_string_new("fact"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_1, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));

        // Method unary object: 0 message: "fact" method: { self | 1 }
        // Method unary object: _ message: "fact" method: { self | self * (self - 1) fact }
        parse("( \
            # 0 fact => 1, \
            # _ fact => self * (self-1) fact \
        )", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("unary"), \
            FM_0, \
            FM_STRING, marg_string_new("fact"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_1, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3"), \
            \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("unary"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("fact"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_SELF, \
                FM_SELF, \
                FM_1, \
                FM_BINARY, marg_string_new("-"), \
                FM_UNARY, marg_string_new("fact"), \
                FM_BINARY, marg_string_new("*"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));
    });

    it("parses binary methods", {
        // Method binary object: 0 message: "**" param: 0 method: { self | nil }
        parse("# 0 ** 0 => nil", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("binary"), \
            FM_0, \
            FM_STRING, marg_string_new("**"), \
            FM_0, \
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_NIL, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4") \
        ));

        // Method binary object: 0 message: "**" param: _ method: { self | 0 }
        parse("# 0 ** _ => 0", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("binary"), \
            FM_0, \
            FM_STRING, marg_string_new("**"), \
            FM_ANY_OBJECT, \
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_0, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4") \
        ));

        // Method binary object: _ message: "**" param: 0 method: { self | 1 }
        parse("# _ ** 0 => 1", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("binary"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("**"), \
            FM_0,
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_1, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4") \
        ));

        // Method binary object: 0 message: "**" param: a_number method: { self, a_number | 0 }
        parse("# 0 ** a_number => 0", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("binary"), \
            FM_0, \
            FM_STRING, marg_string_new("**"), \
            FM_METHOD_PARAMETER, marg_string_new("a_number"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_VARIABLE, marg_string_new("a_number"), \
                FM_TENSOR, marg_string_new("2"), \
                FM_0, \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4") \
        ));

        // Method binary object: _ message: "**" param: a_number method: { self, a_number | self raised_to: a_number }
        parse("# ** a_number => self raised_to: a_number", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("binary"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("**"), \
            FM_METHOD_PARAMETER, marg_string_new("a_number"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_VARIABLE, marg_string_new("a_number"), \
                FM_TENSOR, marg_string_new("2"), \
                FM_SELF, \
                FM_VARIABLE, marg_string_new("a_number"), \
                FM_KEYWORD, marg_string_new("raised_to:"), marg_string_new("1"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4") \
        ));
    });

    it("parses keyword methods", {
        // Method keyword object: _ message: "add:at:" params: ["element", "position"] method: { self, element, position | 42 }
        parse("#add: element at: position => 42", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("add:at:"), \
            FM_METHOD_PARAMETER, marg_string_new("element"), \
            FM_METHOD_PARAMETER, marg_string_new("position"), \
            FM_TENSOR, marg_string_new("2"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_VARIABLE, marg_string_new("element"), \
                FM_VARIABLE, marg_string_new("position"), \
                FM_TENSOR, marg_string_new("3"), \
                FM_INTEGER, marg_string_new("42"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: _ message: "new:" params: ["2"] method: { self | 1 }
        parse("# _ new: 2 => 1", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("new:"), \
            FM_2, \
            FM_TENSOR, marg_string_new("1"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_1,
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: 1 message: "add:" params: ["2"] method: { self | 3 }
        parse("# 1 add: 2 => 3", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_1, \
            FM_STRING, marg_string_new("add:"), \
            FM_2, \
            FM_TENSOR, marg_string_new("1"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_INTEGER, marg_string_new("3"),
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: 1 message: "one:" params: [_, _] method: { self | 42 }
        parse("# 1 one: _ two: _ => 42", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_1, \
            FM_STRING, marg_string_new("one:two:"), \
            FM_ANY_OBJECT, \
            FM_ANY_OBJECT, \
            FM_TENSOR, marg_string_new("2"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_INTEGER, marg_string_new("42"),
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: _ message: "ok?:otherwise!:" params: ["value1", "value2"] method: { self, value1, value2 | 17 }
        parse("#ok?: value1 otherwise!: value2 => 17", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("ok?:otherwise!:"), \
            FM_METHOD_PARAMETER, marg_string_new("value1"), \
            FM_METHOD_PARAMETER, marg_string_new("value2"), \
            FM_TENSOR, marg_string_new("2"), \
            FM_START_PROC, \
                FM_SELF,
                FM_VARIABLE, marg_string_new("value1"),
                FM_VARIABLE, marg_string_new("value2"),
                FM_TENSOR, marg_string_new("3"),
                FM_INTEGER, marg_string_new("17"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: [] message: "add:at:" params: ["element", "position"] method: { self, element, position | 17 }
        parse("# [] add: element at: position => 17", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_TENSOR, marg_string_new("0"), \
            FM_STRING, marg_string_new("add:at:"), \
            FM_METHOD_PARAMETER, marg_string_new("element"), \
            FM_METHOD_PARAMETER, marg_string_new("position"), \
            FM_TENSOR, marg_string_new("2"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_VARIABLE, marg_string_new("element"), \
                FM_VARIABLE, marg_string_new("position"), \
                FM_TENSOR, marg_string_new("3"), \
                FM_INTEGER, marg_string_new("17"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: [] message: "add:at:" params: ['a', 0] method: { self | ['a'] }
        parse("# [] add: 'a' at: 0 => ['a']", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_TENSOR, marg_string_new("0"), \
            FM_STRING, marg_string_new("add:at:"), \
            FM_CHAR, marg_string_new("a"), \
            FM_0,
            FM_TENSOR, marg_string_new("2"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_CHAR, marg_string_new("a"), \
                FM_TENSOR, marg_string_new("1"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: _ message: "add:at:" params: ['a', 0]
        parse("#add: 'a' at: 0 => ['a'] ++ self", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("add:at:"), \
            FM_CHAR, marg_string_new("a"), \
            FM_0,
            FM_TENSOR, marg_string_new("2"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_TENSOR, marg_string_new("1"), \
                FM_CHAR, marg_string_new("a"), \
                FM_TENSOR, marg_string_new("1"), \
                FM_SELF, \
                FM_BINARY, marg_string_new("++"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: _ message: "times:" params: ["a_block"] method: { self, a_block | (
        //     remaining = self,
        //     { (remaining = remaining - 1) >= 0 } while_true: { a_block value }
        // ) }
        parse("#times: a_block => ( \
            remaining = self, \
            { (remaining = remaining - 1) >= 0 } while_true: { a_block value } \
        )", marg_vector_new( \
            FM_VARIABLE, marg_string_new("Method"), \
            FM_UNARY, marg_string_new("keyword"), \
            FM_ANY_OBJECT, \
            FM_STRING, marg_string_new("times:"), \
            FM_METHOD_PARAMETER, marg_string_new("a_block"), \
            FM_TENSOR, marg_string_new("1"), \
            FM_START_PROC, \
                FM_SELF, \
                FM_VARIABLE, marg_string_new("a_block"), \
                FM_TENSOR, marg_string_new("2"), \
                FM_SELF, \
                FM_STORE, marg_string_new("remaining"), \
                FM_START_PROC, \
                    FM_TENSOR, marg_string_new("0"), \
                    FM_VARIABLE, marg_string_new("remaining"), \
                    FM_1, \
                    FM_BINARY, marg_string_new("-"), \
                    FM_STORE, marg_string_new("remaining"), \
                    FM_0, \
                    FM_BINARY, marg_string_new(">="), \
                FM_END_PROC, \
                FM_START_PROC, \
                    FM_TENSOR, marg_string_new("0"), \
                    FM_VARIABLE, marg_string_new("a_block"), \
                    FM_UNARY, marg_string_new("value"), \
                FM_END_PROC, \
                FM_KEYWORD, marg_string_new("while_true:"), marg_string_new("1"), \
            FM_END_PROC, \
            FM_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));
    });
})

#endif
