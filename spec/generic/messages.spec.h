#ifndef __MESSAGES_SPEC_H_
#define __MESSAGES_SPEC_H_

#include "../_helpers.h"

module(messages_spec, {
    it("parses unary messages", {
        parse("42 factorial", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial")));
        parse("17 incr puts", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("17"), OP_UNARY, marg_string_new("incr"), OP_UNARY, marg_string_new("puts")));
        parse("23 one two three", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("23"), OP_UNARY, marg_string_new("one"), OP_UNARY, marg_string_new("two"), OP_UNARY, marg_string_new("three")));
        parse("@inst one two three", marg_vector_new(OP_PUSH_INSTANCE, marg_string_new("inst"), OP_UNARY, marg_string_new("one"), OP_UNARY, marg_string_new("two"), OP_UNARY, marg_string_new("three")));
        parse("42 puts", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("puts")));
        parse("obj puts", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_UNARY, marg_string_new("puts")));
        parse("x = (obj puts)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_UNARY, marg_string_new("puts"), OP_STORE, marg_string_new("x")));
        parse("(obj puts, 42 incr)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_UNARY, marg_string_new("puts"), OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("incr")));
        parse("((obj puts), (42 incr))", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_UNARY, marg_string_new("puts"), OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("incr")));
        parse("42 incr incr decr decr", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("incr"), OP_UNARY, marg_string_new("incr"), OP_UNARY, marg_string_new("decr"), OP_UNARY, marg_string_new("decr")));
        parse("x = 42 incr incr decr decr", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("incr"), OP_UNARY, marg_string_new("incr"), OP_UNARY, marg_string_new("decr"), OP_UNARY, marg_string_new("decr"), OP_STORE, marg_string_new("x")));
        parse("x incr!", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("incr!")));
        parse("x is_empty?", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("is_empty?")));
        parse("(42 one, 43 two, 44 three, 45, 46 four)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("one"), OP_PUSH_INTEGER, marg_string_new("43"), OP_UNARY, marg_string_new("two"), OP_PUSH_INTEGER, marg_string_new("44"), OP_UNARY, marg_string_new("three"), OP_PUSH_INTEGER, marg_string_new("45"), OP_PUSH_INTEGER, marg_string_new("46"), OP_UNARY, marg_string_new("four")));
        parse("p1 + p2 calc puts", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("p1"), OP_PUSH_VARIABLE, marg_string_new("p2"), OP_UNARY, marg_string_new("calc"), OP_UNARY, marg_string_new("puts"), OP_BINARY, marg_string_new("+")));
        parse("(p1 + p2 calc) puts", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("p1"), OP_PUSH_VARIABLE, marg_string_new("p2"), OP_UNARY, marg_string_new("calc"), OP_BINARY, marg_string_new("+"), OP_UNARY, marg_string_new("puts")));
    });
    
    it("parses binary messages", {
        parse("2 + 3", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+")));
        parse("2 + 3 + 4 + 5", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("4"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("+")));
        parse("2 * 5", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("*")));
        parse("a + b", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_BINARY, marg_string_new("+")));
        parse("42 factorial + 17", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial"), OP_PUSH_INTEGER, marg_string_new("17"), OP_BINARY, marg_string_new("+")));
        parse("41 factorial + 42 factorial + 43 factorial", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_UNARY, marg_string_new("factorial"), OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("43"), OP_UNARY, marg_string_new("factorial"), OP_BINARY, marg_string_new("+")));
        parse("(41 + 1, 42 + 0, 43 - 1)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_0, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("43"), OP_PUSH_1, OP_BINARY, marg_string_new("-")));
        parse("((41 + 1), (42 + 0), (43 - 1))", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_0, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("43"), OP_PUSH_1, OP_BINARY, marg_string_new("-")));
        parse("x = a + b * 2 - 5", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_BINARY, marg_string_new("+"), OP_PUSH_2, OP_BINARY, marg_string_new("*"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("-"), OP_STORE, marg_string_new("x")));
        parse("x << item", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("item"), OP_BINARY, marg_string_new("<<")));
        parse("x <<>>+-++-- 15", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_INTEGER, marg_string_new("15"), OP_BINARY, marg_string_new("<<>>+-++--")));
        parse("[1, 2, 3] ++ [4, 5]", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_PUSH_TENSOR, marg_string_new("3"), OP_PUSH_INTEGER, marg_string_new("4"), OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_TENSOR, marg_string_new("2"), OP_BINARY, marg_string_new("++")));
        parse("(4 + 3) * (5 + 6)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("4"), OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_INTEGER, marg_string_new("6"), OP_BINARY, marg_string_new("+"), OP_BINARY, marg_string_new("*")));
    });

    it("parses keyword messages", {
        parse("list put: 42 at: 5", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("put:at:"), marg_string_new("2")));
        parse("list put: (42 incr) at: 5", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("incr"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("put:at:"), marg_string_new("2")));
        parse("( \
            list = List new, \
            list put: 42 at: 5, \
            x = list get: 2, \
            x puts \
        )", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("List"), OP_UNARY, marg_string_new("new"), OP_STORE, marg_string_new("list"), OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("put:at:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_2, OP_KEYWORD, marg_string_new("get:"), marg_string_new("1"), OP_STORE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("puts")));
        parse("2 + 3 incr add: 11", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_UNARY, marg_string_new("incr"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("11"), OP_KEYWORD, marg_string_new("add:"), marg_string_new("1")));
        parse("(1, 2, 3) reverse!: true", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_PUSH_TRUE, OP_KEYWORD, marg_string_new("reverse!:"), marg_string_new("1")));
        parse("true then: 1 else: 2", marg_vector_new(OP_PUSH_TRUE, OP_PUSH_1, OP_PUSH_2, OP_KEYWORD, marg_string_new("then:else:"), marg_string_new("2")));
        parse("x ok?: true otherwise!: false", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_TRUE, OP_PUSH_FALSE, OP_KEYWORD, marg_string_new("ok?:otherwise!:"), marg_string_new("2")));
        parse("(5 + 13) greater_than?: (11 + 2)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_INTEGER, marg_string_new("13"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("11"), OP_PUSH_2, OP_BINARY, marg_string_new("+"), OP_KEYWORD, marg_string_new("greater_than?:"), marg_string_new("1")));
        parse("42 factorial and: (2 + 3)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial"), OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_KEYWORD, marg_string_new("and:"), marg_string_new("1")));
        parse("(list at: 3) + (list at: 5)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("at:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("at:"), marg_string_new("1"), OP_BINARY, marg_string_new("+")));
    });

    it("chains keyword messages of exactly the same selector", {
        parse("arr add: 1 add: 2 add: 3", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_1, OP_KEYWORD, marg_string_new("add:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_2, OP_KEYWORD, marg_string_new("add:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("add:"), marg_string_new("1")));
        parse("arr add: 'a' add: 'b' at: 3", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_CHAR, marg_string_new("'a'"), OP_PUSH_CHAR, marg_string_new("'b'"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("add:add:at:"), marg_string_new("3")));
        parse("arr add: 'a' at: 1 add: 'b' at: 2", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_CHAR, marg_string_new("'a'"), OP_PUSH_1, OP_PUSH_CHAR, marg_string_new("'b'"), OP_PUSH_2, OP_KEYWORD, marg_string_new("add:at:add:at:"), marg_string_new("4")));
    });

    it("parses composit messages", {
        parse("3 factorial + 4 factorial between: 10 and: 100", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("3"), OP_UNARY, marg_string_new("factorial"), OP_PUSH_INTEGER, marg_string_new("4"), OP_UNARY, marg_string_new("factorial"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("10"), OP_PUSH_INTEGER, marg_string_new("100"), OP_KEYWORD, marg_string_new("between:and:"), marg_string_new("2")));
        parse("( \
            origin <= point \
                if_true: ->{ out goto } \
                if_false: ->{ false return }, \
            out = Label new \
        )", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("origin"), OP_PUSH_VARIABLE, marg_string_new("point"), OP_BINARY, marg_string_new("<="), OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_VARIABLE, marg_string_new("out"), OP_UNARY, marg_string_new("goto"), OP_END_PUSH_PROC, OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_FALSE, OP_UNARY, marg_string_new("return"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("if_true:if_false:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Label"), OP_UNARY, marg_string_new("new"), OP_STORE, marg_string_new("out")));
    });
})

#endif
