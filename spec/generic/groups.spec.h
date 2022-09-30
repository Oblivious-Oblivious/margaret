#ifndef __GROUPS_SPEC_H_
#define __GROUPS_SPEC_H_

#include "../_helpers.h"

module(groups_spec, {
    it("parses an empty group as a first unit", {
        parse("()", marg_vector_new_empty());
    });

    it("parses multiple groups as translation units", {
        parse("(())", marg_vector_new_empty());
        parse("((()))", marg_vector_new_empty());
        parse("((), (), (), ())", marg_vector_new_empty());
        parse("((()), ())", marg_vector_new_empty());
    });
    
    it("parses infinite groups of groups", {
        parse("(42)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42")));
        parse("(42, 43, 44)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("43"), OP_PUSH_INTEGER, marg_string_new("44")));
        parse("(42, (), 43, ())", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("43")));
        parse("(42, (43), 44, ())", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("43"), OP_PUSH_INTEGER, marg_string_new("44")));
        parse("((((()))))", marg_vector_new_empty());
        parse("(1, 2, (10, 20, 30), 3)", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("10"), OP_PUSH_INTEGER, marg_string_new("20"), OP_PUSH_INTEGER, marg_string_new("30"), OP_PUSH_INTEGER, marg_string_new("3")));
    });
        
    it("parses list messages", {
        parse("(arr = [1, 2, 3, 4])", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_PUSH_INTEGER, marg_string_new("4"), OP_PUSH_TENSOR, marg_string_new("4"), OP_STORE, marg_string_new("arr")));
        parse("arr << 1 << 2 << 3", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_1, OP_BINARY, marg_string_new("<<"), OP_PUSH_2, OP_BINARY, marg_string_new("<<"), OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("<<")));
        parse("arr add: 1 add: 2 add: 3", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_1, OP_KEYWORD, marg_string_new("add:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_2, OP_KEYWORD, marg_string_new("add:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("add:"), marg_string_new("1")));
        parse("(arr at: 1 put: 5, arr at: 2 put: 6)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_1, OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("at:put:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("6"), OP_KEYWORD, marg_string_new("at:put:"), marg_string_new("2")));
        parse("(b = arr is_empty?)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_UNARY, marg_string_new("is_empty?"), OP_STORE, marg_string_new("b")));
        parse("(x = arr size)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_UNARY, marg_string_new("size"), OP_STORE, marg_string_new("x")));
        parse("(x = arr at: 4)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_INTEGER, marg_string_new("4"), OP_KEYWORD, marg_string_new("at:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = arr includes?: 3)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("includes?:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = arr includes: 3)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("includes:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = arr copy_from: 2 to: 4)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("4"), OP_KEYWORD, marg_string_new("copy_from:to:"), marg_string_new("2"), OP_STORE, marg_string_new("x")));
        parse("(x = arr index_of: 3 if_absent: -1)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_INTEGER, marg_string_new("3"), OP_PUSH_MINUS_1, OP_KEYWORD, marg_string_new("index_of:if_absent:"), marg_string_new("2"), OP_STORE, marg_string_new("x")));
        parse("(x = arr occurrences_of: 3)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("occurrences_of:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(arr each: ->{ a | a puts })", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_UNARY, marg_string_new("puts"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("each:"), marg_string_new("1")));
        parse("(b = arr conform: ->{ a | (a >= 1) && (a <= 4) })", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_1, OP_BINARY, marg_string_new(">="), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_INTEGER, marg_string_new("4"), OP_BINARY, marg_string_new("<="), OP_BINARY, marg_string_new("&&"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("conform:"), marg_string_new("1"), OP_STORE, marg_string_new("b")));
        parse("(x = arr select: ->{ a | a > 2 })", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_2, OP_BINARY, marg_string_new(">"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("select:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = arr reject: ->{ a | a < 2 })", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_2, OP_BINARY, marg_string_new("<"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("reject:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = arr collect: ->{ a | a + a })", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_BINARY, marg_string_new("+"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("collect:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = arr detect: ->{ a | a > 3 } if_none: ())", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new(">"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("detect:if_none:"), marg_string_new("2"), OP_STORE, marg_string_new("x")));
        parse("( \
            arr = [1, 2, 3, 4], \
            sum = 0, \
            arr each: ->{ a | sum += a }, \
            sum \
        )", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_PUSH_INTEGER, marg_string_new("4"), OP_PUSH_TENSOR, marg_string_new("4"), OP_STORE, marg_string_new("arr"), OP_PUSH_0, OP_STORE, marg_string_new("sum"), OP_PUSH_VARIABLE, marg_string_new("arr"), OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("sum"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_BINARY, marg_string_new("+="), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("each:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("sum")));
        parse("(sum = arr inject: 0 into: ->{ a, c | a + c })", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_0, OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("c"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("c"), OP_BINARY, marg_string_new("+"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("inject:into:"), marg_string_new("2"), OP_STORE, marg_string_new("sum")));
        parse("(sum = arr fold: 0 into: ->{ a, c | a + c })", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_0, OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("c"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("c"), OP_BINARY, marg_string_new("+"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("fold:into:"), marg_string_new("2"), OP_STORE, marg_string_new("sum")));
        parse("(max = arr \
                inject: 0 \
                into: -> { a, c | \
                    (a > c) if_true: a \
                             if_false: b \
                } \
        )", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_0, OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("c"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("c"), OP_BINARY, marg_string_new(">"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_KEYWORD, marg_string_new("if_true:if_false:"), marg_string_new("2"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("inject:into:"), marg_string_new("2"), OP_STORE, marg_string_new("max")));
        parse("(x = arr shuffled)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_UNARY, marg_string_new("shuffled"), OP_STORE, marg_string_new("x")));
    });
})

#endif
