#ifndef __MESSAGES_SPEC_H_
#define __MESSAGES_SPEC_H_

#include "../_helpers.h"

module(messages_spec, {
    it("parses unary messages", {
        parse("42 factorial", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_UNARY, marg_string_new("factorial")));
        parse("17 incr puts", marg_vector_new(FM_INTEGER, marg_string_new("17"), FM_UNARY, marg_string_new("incr"), FM_UNARY, marg_string_new("puts")));
        parse("23 one two three", marg_vector_new(FM_INTEGER, marg_string_new("23"), FM_UNARY, marg_string_new("one"), FM_UNARY, marg_string_new("two"), FM_UNARY, marg_string_new("three")));
        parse("@inst one two three", marg_vector_new(FM_INSTANCE, marg_string_new("inst"), FM_UNARY, marg_string_new("one"), FM_UNARY, marg_string_new("two"), FM_UNARY, marg_string_new("three")));
        parse("42 puts", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_UNARY, marg_string_new("puts")));
        parse("obj puts", marg_vector_new(FM_VARIABLE, marg_string_new("obj"), FM_UNARY, marg_string_new("puts")));
        parse("x = (obj puts)", marg_vector_new(FM_VARIABLE, marg_string_new("obj"), FM_UNARY, marg_string_new("puts"), FM_STORE, marg_string_new("x")));
        parse("(obj puts, 42 incr)", marg_vector_new(FM_VARIABLE, marg_string_new("obj"), FM_UNARY, marg_string_new("puts"), FM_INTEGER, marg_string_new("42"), FM_UNARY, marg_string_new("incr")));
        parse("((obj puts), (42 incr))", marg_vector_new(FM_VARIABLE, marg_string_new("obj"), FM_UNARY, marg_string_new("puts"), FM_INTEGER, marg_string_new("42"), FM_UNARY, marg_string_new("incr")));
        parse("42 incr incr decr decr", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_UNARY, marg_string_new("incr"), FM_UNARY, marg_string_new("incr"), FM_UNARY, marg_string_new("decr"), FM_UNARY, marg_string_new("decr")));
        parse("x = 42 incr incr decr decr", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_UNARY, marg_string_new("incr"), FM_UNARY, marg_string_new("incr"), FM_UNARY, marg_string_new("decr"), FM_UNARY, marg_string_new("decr"), FM_STORE, marg_string_new("x")));
        parse("x incr!", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("incr!")));
        parse("x is_empty?", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("is_empty?")));
        parse("(42 one, 43 two, 44 three, 45, 46 four)", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_UNARY, marg_string_new("one"), FM_INTEGER, marg_string_new("43"), FM_UNARY, marg_string_new("two"), FM_INTEGER, marg_string_new("44"), FM_UNARY, marg_string_new("three"), FM_INTEGER, marg_string_new("45"), FM_INTEGER, marg_string_new("46"), FM_UNARY, marg_string_new("four")));
        parse("p1 + p2 calc puts", marg_vector_new(FM_VARIABLE, marg_string_new("p1"), FM_VARIABLE, marg_string_new("p2"), FM_UNARY, marg_string_new("calc"), FM_UNARY, marg_string_new("puts"), FM_BINARY, marg_string_new("+")));
        parse("(p1 + p2 calc) puts", marg_vector_new(FM_VARIABLE, marg_string_new("p1"), FM_VARIABLE, marg_string_new("p2"), FM_UNARY, marg_string_new("calc"), FM_BINARY, marg_string_new("+"), FM_UNARY, marg_string_new("puts")));
    });
    
    it("parses binary messages", {
        parse("2 + 3", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("+")));
        parse("2 + 3 + 4 + 5", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("4"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("5"), FM_BINARY, marg_string_new("+")));
        parse("2 * 5", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("5"), FM_BINARY, marg_string_new("*")));
        parse("a + b", marg_vector_new(FM_VARIABLE, marg_string_new("a"), FM_VARIABLE, marg_string_new("b"), FM_BINARY, marg_string_new("+")));
        parse("42 factorial + 17", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_UNARY, marg_string_new("factorial"), FM_INTEGER, marg_string_new("17"), FM_BINARY, marg_string_new("+")));
        parse("41 factorial + 42 factorial + 43 factorial", marg_vector_new(FM_INTEGER, marg_string_new("41"), FM_UNARY, marg_string_new("factorial"), FM_INTEGER, marg_string_new("42"), FM_UNARY, marg_string_new("factorial"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("43"), FM_UNARY, marg_string_new("factorial"), FM_BINARY, marg_string_new("+")));
        parse("(41 + 1, 42 + 0, 43 - 1)", marg_vector_new(FM_INTEGER, marg_string_new("41"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("42"), FM_INTEGER, marg_string_new("0"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("43"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new("-")));
        parse("((41 + 1), (42 + 0), (43 - 1))", marg_vector_new(FM_INTEGER, marg_string_new("41"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("42"), FM_INTEGER, marg_string_new("0"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("43"), FM_INTEGER, marg_string_new("1"), FM_BINARY, marg_string_new("-")));
        parse("x = a + b * 2 - 5", marg_vector_new(FM_VARIABLE, marg_string_new("a"), FM_VARIABLE, marg_string_new("b"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("2"), FM_BINARY, marg_string_new("*"), FM_INTEGER, marg_string_new("5"), FM_BINARY, marg_string_new("-"), FM_STORE, marg_string_new("x")));
        parse("x << item", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_VARIABLE, marg_string_new("item"), FM_BINARY, marg_string_new("<<")));
        parse("x <<>>+-++-- 15", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_INTEGER, marg_string_new("15"), FM_BINARY, marg_string_new("<<>>+-++--")));
        parse("[1, 2, 3] ++ [4, 5]", marg_vector_new(FM_INTEGER, marg_string_new("1"), FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_TENSOR, marg_string_new("3"), FM_INTEGER, marg_string_new("4"), FM_INTEGER, marg_string_new("5"), FM_TENSOR, marg_string_new("2"), FM_BINARY, marg_string_new("++")));
        parse("(4 + 3) * (5 + 6)", marg_vector_new(FM_INTEGER, marg_string_new("4"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("5"), FM_INTEGER, marg_string_new("6"), FM_BINARY, marg_string_new("+"), FM_BINARY, marg_string_new("*")));
    });

    it("parses keyword messages", {
        parse("list put: 42 at: 5", marg_vector_new(FM_VARIABLE, marg_string_new("list"), FM_INTEGER, marg_string_new("42"), FM_INTEGER, marg_string_new("5"), FM_KEYWORD, marg_string_new("put:at:"), marg_string_new("2")));
        parse("list put: (42 incr) at: 5", marg_vector_new(FM_VARIABLE, marg_string_new("list"), FM_INTEGER, marg_string_new("42"), FM_UNARY, marg_string_new("incr"), FM_INTEGER, marg_string_new("5"), FM_KEYWORD, marg_string_new("put:at:"), marg_string_new("2")));
        parse("( \
            list = List new, \
            list put: 42 at: 5, \
            x = list get: 2, \
            x puts \
        )", marg_vector_new(FM_VARIABLE, marg_string_new("List"), FM_UNARY, marg_string_new("new"), FM_STORE, marg_string_new("list"), FM_VARIABLE, marg_string_new("list"), FM_INTEGER, marg_string_new("42"), FM_INTEGER, marg_string_new("5"), FM_KEYWORD, marg_string_new("put:at:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("list"), FM_INTEGER, marg_string_new("2"), FM_KEYWORD, marg_string_new("get:"), marg_string_new("1"), FM_STORE, marg_string_new("x"), FM_VARIABLE, marg_string_new("x"), FM_UNARY, marg_string_new("puts")));
        parse("2 + 3 incr add: 11", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_UNARY, marg_string_new("incr"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("11"), FM_KEYWORD, marg_string_new("add:"), marg_string_new("1")));
        parse("(1, 2, 3) reverse!: true", marg_vector_new(FM_INTEGER, marg_string_new("1"), FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_TRUE, FM_KEYWORD, marg_string_new("reverse!:"), marg_string_new("1")));
        parse("true then: 1 else: 2", marg_vector_new(FM_TRUE, FM_INTEGER, marg_string_new("1"), FM_INTEGER, marg_string_new("2"), FM_KEYWORD, marg_string_new("then:else:"), marg_string_new("2")));
        parse("x ok?: true otherwise!: false", marg_vector_new(FM_VARIABLE, marg_string_new("x"), FM_TRUE, FM_FALSE, FM_KEYWORD, marg_string_new("ok?:otherwise!:"), marg_string_new("2")));
        parse("(5 + 13) greater_than?: (11 + 2)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_INTEGER, marg_string_new("13"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("11"), FM_INTEGER, marg_string_new("2"), FM_BINARY, marg_string_new("+"), FM_KEYWORD, marg_string_new("greater_than?:"), marg_string_new("1")));
        parse("42 factorial and: (2 + 3)", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_UNARY, marg_string_new("factorial"), FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_BINARY, marg_string_new("+"), FM_KEYWORD, marg_string_new("and:"), marg_string_new("1")));
        parse("(list at: 3) + (list at: 5)", marg_vector_new(FM_VARIABLE, marg_string_new("list"), FM_INTEGER, marg_string_new("3"), FM_KEYWORD, marg_string_new("at:"), marg_string_new("1"), FM_VARIABLE, marg_string_new("list"), FM_INTEGER, marg_string_new("5"), FM_KEYWORD, marg_string_new("at:"), marg_string_new("1"), FM_BINARY, marg_string_new("+")));
    });

    it("chains keyword messages of exactly the same selector", {
        parse("arr add: 1 add: 2 add: 3", marg_vector_new(FM_VARIABLE, marg_string_new("arr"), FM_INTEGER, marg_string_new("1"), FM_KEYWORD, marg_string_new("add:"), marg_string_new("1"), FM_VARIABLE, marg_string_new("arr"), FM_INTEGER, marg_string_new("2"), FM_KEYWORD, marg_string_new("add:"), marg_string_new("1"), FM_VARIABLE, marg_string_new("arr"), FM_INTEGER, marg_string_new("3"), FM_KEYWORD, marg_string_new("add:"), marg_string_new("1")));
        parse("arr add: 'a' add: 'b' at: 3", marg_vector_new(FM_VARIABLE, marg_string_new("arr"), FM_CHAR, marg_string_new("a"), FM_CHAR, marg_string_new("b"), FM_INTEGER, marg_string_new("3"), FM_KEYWORD, marg_string_new("add:add:at:"), marg_string_new("3")));
        parse("arr add: 'a' at: 1 add: 'b' at: 2", marg_vector_new(FM_VARIABLE, marg_string_new("arr"), FM_CHAR, marg_string_new("a"), FM_INTEGER, marg_string_new("1"), FM_CHAR, marg_string_new("b"), FM_INTEGER, marg_string_new("2"), FM_KEYWORD, marg_string_new("add:at:add:at:"), marg_string_new("4")));
    });

    it("parses composit messages", {
        parse("3 factorial + 4 factorial between: 10 and: 100", marg_vector_new(FM_INTEGER, marg_string_new("3"), FM_UNARY, marg_string_new("factorial"), FM_INTEGER, marg_string_new("4"), FM_UNARY, marg_string_new("factorial"), FM_BINARY, marg_string_new("+"), FM_INTEGER, marg_string_new("10"), FM_INTEGER, marg_string_new("100"), FM_KEYWORD, marg_string_new("between:and:"), marg_string_new("2")));
        parse("( \
            origin <= point \
                if_true: { out goto } \
                if_false: { false return }, \
            out = Label new \
        )", marg_vector_new(FM_VARIABLE, marg_string_new("origin"), FM_VARIABLE, marg_string_new("point"), FM_BINARY, marg_string_new("<="), FM_START_PROC, FM_TENSOR, marg_string_new("0"), FM_VARIABLE, marg_string_new("out"), FM_UNARY, marg_string_new("goto"), FM_END_PROC, FM_START_PROC, FM_TENSOR, marg_string_new("0"), FM_FALSE, FM_UNARY, marg_string_new("return"), FM_END_PROC, FM_KEYWORD, marg_string_new("if_true:if_false:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("Label"), FM_UNARY, marg_string_new("new"), FM_STORE, marg_string_new("out")));
    });
})

#endif
