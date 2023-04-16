#ifndef __METHOD_DEFINITION_SPEC_H_
#define __METHOD_DEFINITION_SPEC_H_

#include "../_helpers.h"

module(method_definition_spec, {
    it("parses unary methods", {
        parse("#incr => self + 1", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("incr"), \
            OP_START_PROC,
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_SELF, \
                OP_1, \
                OP_BINARY, marg_string_new("+"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));
        parse("#  incr => self + 1", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("incr"), \
            OP_START_PROC,
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_SELF, \
                OP_1, \
                OP_BINARY, marg_string_new("+"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));
        parse("#is_empty? => true", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("is_empty?"), \
            OP_START_PROC,
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_TRUE, \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));

        parse("# 0 fact => 1", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_0, \
            OP_STRING, marg_string_new("fact"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_1, \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));

        // Method unary object: 0 message: "fact" method: { self | 1 }
        // Method unary object: _ message: "fact" method: { self | self * (self - 1) fact }
        parse("( \
            # 0 fact => 1, \
            # _ fact => self * (self-1) fact \
        )", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_0, \
            OP_STRING, marg_string_new("fact"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_1, \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3"), \
            \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("unary"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("fact"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_SELF, \
                OP_SELF, \
                OP_1, \
                OP_BINARY, marg_string_new("-"), \
                OP_UNARY, marg_string_new("fact"), \
                OP_BINARY, marg_string_new("*"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:method:"), marg_string_new("3") \
        ));
    });

    it("parses binary methods", {
        // Method binary object: 0 message: "**" param: 0 method: { self | nil }
        parse("# 0 ** 0 => nil", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("binary"), \
            OP_0, \
            OP_STRING, marg_string_new("**"), \
            OP_0, \
            OP_START_PROC, \
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_NIL, \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4") \
        ));

        // Method binary object: 0 message: "**" param: _ method: { self | 0 }
        parse("# 0 ** _ => 0", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("binary"), \
            OP_0, \
            OP_STRING, marg_string_new("**"), \
            OP_ANY_OBJECT, \
            OP_START_PROC, \
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_0, \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4") \
        ));

        // Method binary object: _ message: "**" param: 0 method: { self | 1 }
        parse("# _ ** 0 => 1", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("binary"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("**"), \
            OP_0,
            OP_START_PROC, \
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_1, \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4") \
        ));

        // Method binary object: 0 message: "**" param: a_number method: { self, a_number | 0 }
        parse("# 0 ** a_number => 0", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("binary"), \
            OP_0, \
            OP_STRING, marg_string_new("**"), \
            OP_METHOD_PARAMETER, marg_string_new("a_number"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_VARIABLE, marg_string_new("a_number"), \
                OP_TENSOR, marg_string_new("2"), \
                OP_0, \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4") \
        ));

        // Method binary object: _ message: "**" param: a_number method: { self, a_number | self raised_to: a_number }
        parse("# ** a_number => self raised_to: a_number", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("binary"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("**"), \
            OP_METHOD_PARAMETER, marg_string_new("a_number"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_VARIABLE, marg_string_new("a_number"), \
                OP_TENSOR, marg_string_new("2"), \
                OP_SELF, \
                OP_VARIABLE, marg_string_new("a_number"), \
                OP_KEYWORD, marg_string_new("raised_to:"), marg_string_new("1"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:param:method:"), marg_string_new("4") \
        ));
    });

    it("parses keyword methods", {
        // Method keyword object: _ message: "add:at:" params: ["element", "position"] method: { self, element, position | 42 }
        parse("#add: element at: position => 42", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("add:at:"), \
            OP_METHOD_PARAMETER, marg_string_new("element"), \
            OP_METHOD_PARAMETER, marg_string_new("position"), \
            OP_TENSOR, marg_string_new("2"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_VARIABLE, marg_string_new("element"), \
                OP_VARIABLE, marg_string_new("position"), \
                OP_TENSOR, marg_string_new("3"), \
                OP_INTEGER, marg_string_new("42"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: _ message: "new:" params: ["2"] method: { self | 1 }
        parse("# _ new: 2 => 1", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("new:"), \
            OP_2, \
            OP_TENSOR, marg_string_new("1"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_1,
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: 1 message: "add:" params: ["2"] method: { self | 3 }
        parse("# 1 add: 2 => 3", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_1, \
            OP_STRING, marg_string_new("add:"), \
            OP_2, \
            OP_TENSOR, marg_string_new("1"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_INTEGER, marg_string_new("3"),
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: 1 message: "one:" params: [_, _] method: { self | 42 }
        parse("# 1 one: _ two: _ => 42", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_1, \
            OP_STRING, marg_string_new("one:two:"), \
            OP_ANY_OBJECT, \
            OP_ANY_OBJECT, \
            OP_TENSOR, marg_string_new("2"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_INTEGER, marg_string_new("42"),
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: _ message: "ok?:otherwise!:" params: ["value1", "value2"] method: { self, value1, value2 | 17 }
        parse("#ok?: value1 otherwise!: value2 => 17", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("ok?:otherwise!:"), \
            OP_METHOD_PARAMETER, marg_string_new("value1"), \
            OP_METHOD_PARAMETER, marg_string_new("value2"), \
            OP_TENSOR, marg_string_new("2"), \
            OP_START_PROC, \
                OP_SELF,
                OP_VARIABLE, marg_string_new("value1"),
                OP_VARIABLE, marg_string_new("value2"),
                OP_TENSOR, marg_string_new("3"),
                OP_INTEGER, marg_string_new("17"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: [] message: "add:at:" params: ["element", "position"] method: { self, element, position | 17 }
        parse("# [] add: element at: position => 17", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_TENSOR, marg_string_new("0"), \
            OP_STRING, marg_string_new("add:at:"), \
            OP_METHOD_PARAMETER, marg_string_new("element"), \
            OP_METHOD_PARAMETER, marg_string_new("position"), \
            OP_TENSOR, marg_string_new("2"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_VARIABLE, marg_string_new("element"), \
                OP_VARIABLE, marg_string_new("position"), \
                OP_TENSOR, marg_string_new("3"), \
                OP_INTEGER, marg_string_new("17"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: [] message: "add:at:" params: ['a', 0] method: { self | ['a'] }
        parse("# [] add: 'a' at: 0 => ['a']", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_TENSOR, marg_string_new("0"), \
            OP_STRING, marg_string_new("add:at:"), \
            OP_CHAR, marg_string_new("a"), \
            OP_0,
            OP_TENSOR, marg_string_new("2"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_CHAR, marg_string_new("a"), \
                OP_TENSOR, marg_string_new("1"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: _ message: "add:at:" params: ['a', 0]
        parse("#add: 'a' at: 0 => ['a'] ++ self", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("add:at:"), \
            OP_CHAR, marg_string_new("a"), \
            OP_0,
            OP_TENSOR, marg_string_new("2"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_TENSOR, marg_string_new("1"), \
                OP_CHAR, marg_string_new("a"), \
                OP_TENSOR, marg_string_new("1"), \
                OP_SELF, \
                OP_BINARY, marg_string_new("++"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));

        // Method keyword object: _ message: "times:" params: ["a_block"] method: { self, a_block | (
        //     remaining = self,
        //     { (remaining = remaining - 1) >= 0 } while_true: { a_block value }
        // ) }
        parse("#times: a_block => ( \
            remaining = self, \
            { (remaining = remaining - 1) >= 0 } while_true: { a_block value } \
        )", marg_vector_new( \
            OP_VARIABLE, marg_string_new("Method"), \
            OP_UNARY, marg_string_new("keyword"), \
            OP_ANY_OBJECT, \
            OP_STRING, marg_string_new("times:"), \
            OP_METHOD_PARAMETER, marg_string_new("a_block"), \
            OP_TENSOR, marg_string_new("1"), \
            OP_START_PROC, \
                OP_SELF, \
                OP_VARIABLE, marg_string_new("a_block"), \
                OP_TENSOR, marg_string_new("2"), \
                OP_SELF, \
                OP_STORE, marg_string_new("remaining"), \
                OP_START_PROC, \
                    OP_TENSOR, marg_string_new("0"), \
                    OP_VARIABLE, marg_string_new("remaining"), \
                    OP_1, \
                    OP_BINARY, marg_string_new("-"), \
                    OP_STORE, marg_string_new("remaining"), \
                    OP_0, \
                    OP_BINARY, marg_string_new(">="), \
                OP_END_PROC, \
                OP_START_PROC, \
                    OP_TENSOR, marg_string_new("0"), \
                    OP_VARIABLE, marg_string_new("a_block"), \
                    OP_UNARY, marg_string_new("value"), \
                OP_END_PROC, \
                OP_KEYWORD, marg_string_new("while_true:"), marg_string_new("1"), \
            OP_END_PROC, \
            OP_KEYWORD, marg_string_new("object:message:params:method:"), marg_string_new("4") \
        ));
    });
})

#endif
