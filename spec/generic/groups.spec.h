#ifndef __GROUPS_SPEC_H_
#define __GROUPS_SPEC_H_

#include "../_helpers.h"

module(groups_spec, {
    it("parses an empty group as a first unit", {
        parse("()", vector_new_empty());
    });

    it("parses multiple groups as translation units", {
        parse("(())", vector_new_empty());
        parse("((()))", vector_new_empty());
        parse("((), (), (), ())", vector_new_empty());
        parse("((()), ())", vector_new_empty());
    });

    it("parses infinite groups of groups", {
        parse("(42)", vector_new(FM_INTEGER, string_new("42")));
        parse("(42, 43, 44)", vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("43"), FM_INTEGER, string_new("44")));
        parse("(42, (), 43, ())", vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("43")));
        parse("(42, (43), 44, ())", vector_new(FM_INTEGER, string_new("42"), FM_INTEGER, string_new("43"), FM_INTEGER, string_new("44")));
        parse("((((()))))", vector_new_empty());
        parse("(1, 2, (10, 20, 30), 3)", vector_new(FM_INTEGER, string_new("1"), FM_INTEGER, string_new("2"), FM_INTEGER, string_new("10"), FM_INTEGER, string_new("20"), FM_INTEGER, string_new("30"), FM_INTEGER, string_new("3")));
    });

    it("parses list messages", {
        parse("(arr = [1, 2, 3, 4])", vector_new(FM_INTEGER, string_new("1"), FM_INTEGER, string_new("2"), FM_INTEGER, string_new("3"), FM_INTEGER, string_new("4"), FM_TENSOR, string_new("4"), FM_STORE, string_new("arr")));
        parse("arr << 1 << 2 << 3", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("1"), FM_BINARY, string_new("<<"), FM_INTEGER, string_new("2"), FM_BINARY, string_new("<<"), FM_INTEGER, string_new("3"), FM_BINARY, string_new("<<")));
        parse("arr add: 1 add: 2 add: 3", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("1"), FM_KEYWORD, string_new("add:"), string_new("1"), FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("2"), FM_KEYWORD, string_new("add:"), string_new("1"), FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("3"), FM_KEYWORD, string_new("add:"), string_new("1")));
        parse("(arr at: 1 put: 5, arr at: 2 put: 6)", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("1"), FM_INTEGER, string_new("5"), FM_KEYWORD, string_new("at:put:"), string_new("2"), FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("2"), FM_INTEGER, string_new("6"), FM_KEYWORD, string_new("at:put:"), string_new("2")));
        parse("(b = arr is_empty?)", vector_new(FM_VARIABLE, string_new("arr"), FM_UNARY, string_new("is_empty?"), FM_STORE, string_new("b")));
        parse("(x = arr size)", vector_new(FM_VARIABLE, string_new("arr"), FM_UNARY, string_new("size"), FM_STORE, string_new("x")));
        parse("(x = arr at: 4)", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("4"), FM_KEYWORD, string_new("at:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = arr includes?: 3)", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("3"), FM_KEYWORD, string_new("includes?:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = arr includes: 3)", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("3"), FM_KEYWORD, string_new("includes:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = arr copy_from: 2 to: 4)", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("2"), FM_INTEGER, string_new("4"), FM_KEYWORD, string_new("copy_from:to:"), string_new("2"), FM_STORE, string_new("x")));
        parse("(x = arr index_of: 3 if_absent: -1)", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("3"), FM_INTEGER, string_new("-1"), FM_KEYWORD, string_new("index_of:if_absent:"), string_new("2"), FM_STORE, string_new("x")));
        parse("(x = arr occurrences_of: 3)", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("3"), FM_KEYWORD, string_new("occurrences_of:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(arr each: { a | a puts })", vector_new(FM_VARIABLE, string_new("arr"), FM_START_PROC, FM_VARIABLE, string_new("a"), FM_TENSOR, string_new("1"), FM_VARIABLE, string_new("a"), FM_UNARY, string_new("puts"), FM_END_PROC, FM_KEYWORD, string_new("each:"), string_new("1")));
        parse("(b = arr conform: { a | (a >= 1) && (a <= 4) })", vector_new(FM_VARIABLE, string_new("arr"), FM_START_PROC, FM_VARIABLE, string_new("a"), FM_TENSOR, string_new("1"), FM_VARIABLE, string_new("a"), FM_INTEGER, string_new("1"), FM_BINARY, string_new(">="), FM_VARIABLE, string_new("a"), FM_INTEGER, string_new("4"), FM_BINARY, string_new("<="), FM_BINARY, string_new("&&"), FM_END_PROC, FM_KEYWORD, string_new("conform:"), string_new("1"), FM_STORE, string_new("b")));
        parse("(x = arr select: { a | a > 2 })", vector_new(FM_VARIABLE, string_new("arr"), FM_START_PROC, FM_VARIABLE, string_new("a"), FM_TENSOR, string_new("1"), FM_VARIABLE, string_new("a"), FM_INTEGER, string_new("2"), FM_BINARY, string_new(">"), FM_END_PROC, FM_KEYWORD, string_new("select:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = arr reject: { a | a < 2 })", vector_new(FM_VARIABLE, string_new("arr"), FM_START_PROC, FM_VARIABLE, string_new("a"), FM_TENSOR, string_new("1"), FM_VARIABLE, string_new("a"), FM_INTEGER, string_new("2"), FM_BINARY, string_new("<"), FM_END_PROC, FM_KEYWORD, string_new("reject:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = arr collect: { a | a + a })", vector_new(FM_VARIABLE, string_new("arr"), FM_START_PROC, FM_VARIABLE, string_new("a"), FM_TENSOR, string_new("1"), FM_VARIABLE, string_new("a"), FM_VARIABLE, string_new("a"), FM_BINARY, string_new("+"), FM_END_PROC, FM_KEYWORD, string_new("collect:"), string_new("1"), FM_STORE, string_new("x")));
        parse("(x = arr detect: { a | a > 3 } if_none: ())", vector_new(FM_VARIABLE, string_new("arr"), FM_START_PROC, FM_VARIABLE, string_new("a"), FM_TENSOR, string_new("1"), FM_VARIABLE, string_new("a"), FM_INTEGER, string_new("3"), FM_BINARY, string_new(">"), FM_END_PROC, FM_KEYWORD, string_new("detect:if_none:"), string_new("2"), FM_STORE, string_new("x")));
        parse("( \
            arr = [1, 2, 3, 4], \
            sum = 0, \
            arr each: { a | sum += a }, \
            sum \
        )", vector_new(FM_INTEGER, string_new("1"), FM_INTEGER, string_new("2"), FM_INTEGER, string_new("3"), FM_INTEGER, string_new("4"), FM_TENSOR, string_new("4"), FM_STORE, string_new("arr"), FM_INTEGER, string_new("0"), FM_STORE, string_new("sum"), FM_VARIABLE, string_new("arr"), FM_START_PROC, FM_VARIABLE, string_new("a"), FM_TENSOR, string_new("1"), FM_VARIABLE, string_new("sum"), FM_VARIABLE, string_new("a"), FM_BINARY, string_new("+="), FM_END_PROC, FM_KEYWORD, string_new("each:"), string_new("1"), FM_VARIABLE, string_new("sum")));
        parse("(sum = arr inject: 0 into: { a, c | a + c })", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("0"), FM_START_PROC, FM_VARIABLE, string_new("a"), FM_VARIABLE, string_new("c"), FM_TENSOR, string_new("2"), FM_VARIABLE, string_new("a"), FM_VARIABLE, string_new("c"), FM_BINARY, string_new("+"), FM_END_PROC, FM_KEYWORD, string_new("inject:into:"), string_new("2"), FM_STORE, string_new("sum")));
        parse("(sum = arr fold: 0 into: { a, c | a + c })", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("0"), FM_START_PROC, FM_VARIABLE, string_new("a"), FM_VARIABLE, string_new("c"), FM_TENSOR, string_new("2"), FM_VARIABLE, string_new("a"), FM_VARIABLE, string_new("c"), FM_BINARY, string_new("+"), FM_END_PROC, FM_KEYWORD, string_new("fold:into:"), string_new("2"), FM_STORE, string_new("sum")));
        parse("(max = arr \
                inject: 0 \
                into: { a, c | \
                    (a > c) if_true: a \
                             if_false: b \
                } \
        )", vector_new(FM_VARIABLE, string_new("arr"), FM_INTEGER, string_new("0"), FM_START_PROC, FM_VARIABLE, string_new("a"), FM_VARIABLE, string_new("c"), FM_TENSOR, string_new("2"), FM_VARIABLE, string_new("a"), FM_VARIABLE, string_new("c"), FM_BINARY, string_new(">"), FM_VARIABLE, string_new("a"), FM_VARIABLE, string_new("b"), FM_KEYWORD, string_new("if_true:if_false:"), string_new("2"), FM_END_PROC, FM_KEYWORD, string_new("inject:into:"), string_new("2"), FM_STORE, string_new("max")));
        parse("(x = arr shuffled)", vector_new(FM_VARIABLE, string_new("arr"), FM_UNARY, string_new("shuffled"), FM_STORE, string_new("x")));
    });
})

#endif
