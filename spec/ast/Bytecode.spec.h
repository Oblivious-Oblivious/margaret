#ifndef __BYTECODE_SPEC_H_
#define __BYTECODE_SPEC_H_

#include "../../src/ast/Bytecode.h"
#include "../../src/lexer/Lexer.h"
#include "../../src/parser/Parser.h"

#include "../_helpers.h"

module(BytecodeSpec, {
    it("emits for a simple message", {
        parse("2 + 3", marg_vector_new(
            OP_PUSH_2,
            OP_PUSH_INTEGER, marg_string_new("3"),
            OP_BINARY, marg_string_new("+")
        ));
    });

    it("emits for assignment", {
        parse("x = 4", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("4"), OP_STORE, marg_string_new("x")));
        parse("x = y = z = 6", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("6"), OP_STORE, marg_string_new("z"), OP_STORE, marg_string_new("y"), OP_STORE, marg_string_new("x")));
        parse("x = (y = 6) + 1", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("6"), OP_STORE, marg_string_new("y"), OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("x")));
        parse("@x = x + 2", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_2, OP_BINARY, marg_string_new("+"), OP_STORE_INSTANCE, marg_string_new("x")));
        parse("a = b = (c = 42) + 12", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_STORE, marg_string_new("c"), OP_PUSH_INTEGER, marg_string_new("12"), OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("b"), OP_STORE, marg_string_new("a")));
        parse("a = a negate", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("a"), OP_UNARY, marg_string_new("negate"), OP_STORE, marg_string_new("a")));
        parse("@a = @a negate", marg_vector_new(OP_PUSH_INSTANCE, marg_string_new("a"), OP_UNARY, marg_string_new("negate"), OP_STORE_INSTANCE, marg_string_new("a")));
    });

    it("emits for unary messages", {
        parse("42 factorial", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial")));
        parse("17 incr puts", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("17"), OP_UNARY, marg_string_new("incr"), OP_UNARY, marg_string_new("puts")));
        parse("23 one two three", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("23"), OP_UNARY, marg_string_new("one"), OP_UNARY, marg_string_new("two"), OP_UNARY, marg_string_new("three")));
        parse("@inst one two three", marg_vector_new(OP_PUSH_INSTANCE, marg_string_new("inst"), OP_UNARY, marg_string_new("one"), OP_UNARY, marg_string_new("two"), OP_UNARY, marg_string_new("three")));
        parse("42 puts", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("puts")));
        parse("obj puts", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_UNARY, marg_string_new("puts")));
        parse("x = obj puts", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_UNARY, marg_string_new("puts"), OP_STORE, marg_string_new("x")));
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

    it("emits for binary messages", {
        parse("2 + 3", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+")));
        parse("2 + 3 * 4 + 5", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("4"), OP_BINARY, marg_string_new("*"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("+")));
        parse("2 * 5", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("*")));
        parse("a + b", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_BINARY, marg_string_new("+")));
        parse("42 factorial + 17", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial"), OP_PUSH_INTEGER, marg_string_new("17"), OP_BINARY, marg_string_new("+")));
        parse("41 factorial + 42 factorial + 43 factorial", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_UNARY, marg_string_new("factorial"), OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("43"), OP_UNARY, marg_string_new("factorial"), OP_BINARY, marg_string_new("+")));
        parse("(41 + 1, 42 + 0, 43 - 1)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_0, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("43"), OP_PUSH_1, OP_BINARY, marg_string_new("-")));
        parse("((41 + 1), (42 + 0), (43 - 1))", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_0, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("43"), OP_PUSH_1, OP_BINARY, marg_string_new("-")));
        parse("x = a + b * 2 - 5", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_BINARY, marg_string_new("+"), OP_PUSH_2, OP_BINARY, marg_string_new("*"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("-"), OP_STORE, marg_string_new("x")));
        parse("x << item", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("item"), OP_BINARY, marg_string_new("<<")));
        parse("[1, 2, 3] ++ [4, 5]", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_PUSH_TENSOR, marg_string_new("3"), OP_PUSH_INTEGER, marg_string_new("4"), OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_TENSOR, marg_string_new("2"), OP_BINARY, marg_string_new("++")));
        parse("(4 + 3) * (5 + 6)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("4"), OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_INTEGER, marg_string_new("6"), OP_BINARY, marg_string_new("+"), OP_BINARY, marg_string_new("*")));
    });

    it("emits for keyword messages", {
        parse("list put: 42 at: 5", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("put:at:"), marg_string_new("2")));
        parse("list put: (42 incr) at: 5", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("incr"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("put:at:"), marg_string_new("2")));
        parse("( \
            list = List new, \
            list put: 42 at: 5, \
            x = list get: 2, \
            x puts \
        )", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("List"), OP_UNARY, marg_string_new("new"), OP_STORE, marg_string_new("list"), OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("put:at:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_2, OP_KEYWORD, marg_string_new("get:"), marg_string_new("1"), OP_STORE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("puts")));
        parse("2 + 3 incr add: 11", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_UNARY, marg_string_new("incr"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("11"), OP_KEYWORD, marg_string_new("add:"), marg_string_new("1")));
        parse("[1, 2, 3] reverse!: true", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_PUSH_TENSOR, marg_string_new("3"), OP_PUSH_TRUE, OP_KEYWORD, marg_string_new("reverse!:"), marg_string_new("1")));
        parse("true then: 1 else: 2", marg_vector_new(OP_PUSH_TRUE, OP_PUSH_1, OP_PUSH_2, OP_KEYWORD, marg_string_new("then:else:"), marg_string_new("2")));
        parse("x ok?: true otherwise!: false", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_TRUE, OP_PUSH_FALSE, OP_KEYWORD, marg_string_new("ok?:otherwise!:"), marg_string_new("2")));
        parse("(5 + 13) greater_than?: (11 + 2)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_INTEGER, marg_string_new("13"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("11"), OP_PUSH_2, OP_BINARY, marg_string_new("+"), OP_KEYWORD, marg_string_new("greater_than?:"), marg_string_new("1")));
        parse("42 factorial and: (2 + 3)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial"), OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_KEYWORD, marg_string_new("and:"), marg_string_new("1")));
        parse("(list at: 3) + (list at: 5)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("at:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("at:"), marg_string_new("1"), OP_BINARY, marg_string_new("+")));
        parse("arr add: 1 add: 2 add: 3", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_1, OP_KEYWORD, marg_string_new("add:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_2, OP_KEYWORD, marg_string_new("add:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("add:"), marg_string_new("1")));
        parse("arr add: 'a' add: 'b' at: 3", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_CHAR, marg_string_new("'a'"), OP_PUSH_CHAR, marg_string_new("'b'"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("add:add:at:"), marg_string_new("3")));
        parse("arr add: 'a' at: 1 add: 'b' at: 2", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_CHAR, marg_string_new("'a'"), OP_PUSH_1, OP_PUSH_CHAR, marg_string_new("'b'"), OP_PUSH_2, OP_KEYWORD, marg_string_new("add:at:add:at:"), marg_string_new("4")));
    });

    it("emits for groups", {
        parse("()", marg_vector_new_empty());
        parse("(1, 2, 3)", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3")));
        parse("(1, 2, (10, 20, 30), 3)", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("10"), OP_PUSH_INTEGER, marg_string_new("20"), OP_PUSH_INTEGER, marg_string_new("30"), OP_PUSH_INTEGER, marg_string_new("3")));
        parse("(1, \"2\", c, 42.42)", marg_vector_new(OP_PUSH_1, OP_PUSH_STRING, marg_string_new("\"2\""), OP_PUSH_VARIABLE, marg_string_new("c"), OP_PUSH_FLOAT, marg_string_new("42.42")));
    });

    it("emits for variables", {
        parse("ident", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("ident")));
        parse("variable", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("variable")));
        parse("@instvar", marg_vector_new(OP_PUSH_INSTANCE, marg_string_new("instvar")));
        parse("@x", marg_vector_new(OP_PUSH_INSTANCE, marg_string_new("x")));
        parse("nil", marg_vector_new(OP_PUSH_NIL));
        parse("true", marg_vector_new(OP_PUSH_TRUE));
        parse("false", marg_vector_new(OP_PUSH_FALSE));
        parse("self", marg_vector_new(OP_PUSH_SELF));
        parse("super", marg_vector_new(OP_PUSH_SUPER));
    });

    it("emits for procs", {
        parse("->{x = (x = 1, y = 2)}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_1, OP_STORE, marg_string_new("x"), OP_PUSH_2, OP_STORE, marg_string_new("y"), OP_STORE, marg_string_new("x"), OP_END_PUSH_PROC));
        parse("x = ->{ \
            v1, v2, ( \
                v1 += 1, \
                v1 += 2, \
                v1 * v2 \
            ) \
        }", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("v1"), OP_PUSH_VARIABLE, marg_string_new("v2"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("v1"), OP_PUSH_1, OP_BINARY, marg_string_new("+="), OP_PUSH_VARIABLE, marg_string_new("v1"), OP_PUSH_2, OP_BINARY, marg_string_new("+="), OP_PUSH_VARIABLE, marg_string_new("v1"), OP_PUSH_VARIABLE, marg_string_new("v2"), OP_BINARY, marg_string_new("*"), OP_END_PUSH_PROC, OP_STORE, marg_string_new("x")));
        parse("->{42}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_INTEGER, marg_string_new("42"), OP_END_PUSH_PROC));
        parse("->{a | a puts}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_UNARY, marg_string_new("puts"), OP_END_PUSH_PROC));
        parse("->{2 + 3}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_END_PUSH_PROC));
        parse("->{(x = 1, y = 2, x + y)}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_1, OP_STORE, marg_string_new("x"), OP_PUSH_2, OP_STORE, marg_string_new("y"), OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_BINARY, marg_string_new("+"), OP_END_PUSH_PROC));
        parse("->{a, b | a + b}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_BINARY, marg_string_new("+"), OP_END_PUSH_PROC));
        parse("->{a, a}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_END_PUSH_PROC));
        parse("->{x = 2} exec", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_2, OP_STORE, marg_string_new("x"), OP_END_PUSH_PROC, OP_UNARY, marg_string_new("exec")));
        parse("->{param | param puts} value: 42", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("param"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("param"), OP_UNARY, marg_string_new("puts"), OP_END_PUSH_PROC, OP_PUSH_INTEGER, marg_string_new("42"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1")));
    });

    it("emits for unary method definitions", {
        parse("#incr => self + 1",   marg_vector_new(OP_START_PUSH_UNARY_METHOD, marg_string_new("\"incr\""), OP_PUSH_SELF, OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_END_PUSH_UNARY_METHOD));
        parse("#  incr => self + 1", marg_vector_new(OP_START_PUSH_UNARY_METHOD, marg_string_new("\"incr\""), OP_PUSH_SELF, OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_END_PUSH_UNARY_METHOD));
        parse("#is_empty? => true", marg_vector_new(OP_START_PUSH_UNARY_METHOD, marg_string_new("\"is_empty?\""), OP_PUSH_TRUE, OP_END_PUSH_UNARY_METHOD));
        // parse("# 0 fact => 1");

        // 0 fact => 1,
        // _ fact => self * (self-1) fact
    });

    it("emits for binary method definitions", {
        parse("#** a_number => self raised_to: a_number", marg_vector_new(OP_START_PUSH_BINARY_METHOD, marg_string_new("\"**\""), OP_PUSH_VARIABLE, marg_string_new("a_number"), OP_PUSH_SELF, OP_PUSH_VARIABLE, marg_string_new("a_number"), OP_KEYWORD, marg_string_new("raised_to:"), marg_string_new("1"), OP_END_PUSH_BINARY_METHOD));
        // parse("# 0 ** a_number => 0", "");
        // parse("# 0 ** 0 => nil", "");
    });

    it("emits for keyword method definitions", {
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

    it("emits for C function definitions", {
        parse("###void f()", marg_vector_new(OP_START_PUSH_C_FUNCTION, OP_PUSH_VARIABLE, marg_string_new("void"), OP_PUSH_VARIABLE, marg_string_new("f"), OP_PUSH_TENSOR, marg_string_new("0"), OP_END_PUSH_C_FUNCTION));
        parse("###void f2(int a, int b)", marg_vector_new(OP_START_PUSH_C_FUNCTION, OP_PUSH_VARIABLE, marg_string_new("void"), OP_PUSH_VARIABLE, marg_string_new("f2"), OP_PUSH_VARIABLE, marg_string_new("CFunParam"), OP_PUSH_VARIABLE, marg_string_new("int"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("CFunParam"), OP_PUSH_VARIABLE, marg_string_new("int"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), OP_PUSH_TENSOR, marg_string_new("2"), OP_END_PUSH_C_FUNCTION));
    });

    it("emits for integers", {
        parse("0", marg_vector_new(OP_PUSH_0));
        parse("-0", marg_vector_new(OP_PUSH_0));
        parse("+0", marg_vector_new(OP_PUSH_0));
        parse("1", marg_vector_new(OP_PUSH_1));
        parse("+1", marg_vector_new(OP_PUSH_1));
        parse("-1", marg_vector_new(OP_PUSH_MINUS_1));
        parse("2", marg_vector_new(OP_PUSH_2));
        parse("+2", marg_vector_new(OP_PUSH_2));
        parse("42", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42")));
        parse("-42", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-42")));
        parse("+42", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42")));
        parse("4_200", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("4200")));
        parse("-4_200", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-4200")));
        parse("4____20__0", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("4200")));
        parse("-4____20__0", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-4200")));
        parse("+4____20__0", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("4200")));
    });

    it("emits for floats", {
        parse("42.0", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("42.0")));
        parse("-42.0", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("-42.0")));
        parse("986513.00056129", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("986513.00056129")));
        parse("-986513.00056129", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("-986513.00056129")));
        parse("0.1_2_3", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("0.123")));
        parse("0.1__23", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("0.123")));
    });

    it("emits for binaries", {
        parse("0b0110", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("6")));
        parse("0B10", marg_vector_new(OP_PUSH_2));
        parse("-0b0110", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-6")));
        parse("-0B10", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-2")));
        parse("( \
            x = 0b0101 + 0b1011,\
            x to_int puts,\
        )", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_INTEGER, marg_string_new("11"), OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("to_int"), OP_UNARY, marg_string_new("puts")));
    });

    it("emits for hexadecimals", {
        parse("0xbeef", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("48879")));
        parse("-0xbeEf", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-48879")));
        parse("0X0427", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("1063")));
        parse("-0X0427", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-1063")));
        parse("x = 0xbeef to_bin to_int puts", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("48879"), OP_UNARY, marg_string_new("to_bin"), OP_UNARY, marg_string_new("to_int"), OP_UNARY, marg_string_new("puts"), OP_STORE, marg_string_new("x")));
        parse("0xbeef - 0xabb2", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("48879"), OP_PUSH_INTEGER, marg_string_new("43954"), OP_BINARY, marg_string_new("-")));
        parse("0xbe____e___f", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("48879")));
    });

    it("emits for octals", {
        parse("0o741", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("481")));
        parse("-0o741", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-481")));
        parse("0O0210", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("136")));
        parse("-0O0210", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-136")));
        parse("x = 0o751 to_hex to_bin to_int puts", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("489"), OP_UNARY, marg_string_new("to_hex"), OP_UNARY, marg_string_new("to_bin"), OP_UNARY, marg_string_new("to_int"), OP_UNARY, marg_string_new("puts"), OP_STORE, marg_string_new("x")));
        parse("0O541 + 0o777", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("353"), OP_PUSH_INTEGER, marg_string_new("511"), OP_BINARY, marg_string_new("+")));
    });

    it("emits for characters", {
        parse("'a'", marg_vector_new(OP_PUSH_CHAR, marg_string_new("'a'")));
        parse("'\n'", marg_vector_new(OP_PUSH_CHAR, marg_string_new("'\n'")));
        parse("'œ'", marg_vector_new(OP_PUSH_CHAR, marg_string_new("'œ'")));
        parse("-'œ'", marg_vector_new(OP_PUSH_CHAR, marg_string_new("-'œ'")));
        parse("('a' to_uppercase)", marg_vector_new(OP_PUSH_CHAR, marg_string_new("'a'"), OP_UNARY, marg_string_new("to_uppercase")));
        parse("('B' to_ascii)", marg_vector_new(OP_PUSH_CHAR, marg_string_new("'B'"), OP_UNARY, marg_string_new("to_ascii")));
        parse("('a' <= 'b')", marg_vector_new(OP_PUSH_CHAR, marg_string_new("'a'"), OP_PUSH_CHAR, marg_string_new("'b'"), OP_BINARY, marg_string_new("<=")));
    });

    it("emits for strings", {
        parse("\"string\"", marg_vector_new(OP_PUSH_STRING, marg_string_new("\"string\"")));
        parse("\"foo\tbar\"", marg_vector_new(OP_PUSH_STRING, marg_string_new("\"foo\tbar\"")));
        parse("\"a string lit\"", marg_vector_new(OP_PUSH_STRING, marg_string_new("\"a string lit\"")));
        parse("\"str\"", marg_vector_new(OP_PUSH_STRING, marg_string_new("\"str\"")));
    });

    it("emits for tensors", {
        parse("[]", marg_vector_new(OP_PUSH_TENSOR, marg_string_new("0")));
        parse("[41, 42]", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_TENSOR, marg_string_new("2")));
        parse("[42, \"str\", var]", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_STRING, marg_string_new("\"str\""), OP_PUSH_VARIABLE, marg_string_new("var"), OP_PUSH_TENSOR, marg_string_new("3")));
        parse("[41,42,43,44,45]", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("43"), OP_PUSH_INTEGER, marg_string_new("44"), OP_PUSH_INTEGER, marg_string_new("45"), OP_PUSH_TENSOR, marg_string_new("5")));
    });

    it("emits for hashes", {
        parse("{}", marg_vector_new(OP_PUSH_HASH, marg_string_new("0")));
        parse("{a: {}, b: {}}", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"a\""), OP_PUSH_HASH, marg_string_new("0"), OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"b\""), OP_PUSH_HASH, marg_string_new("0"), OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_HASH, marg_string_new("2")));
        parse("{a: 1, b: 2, c: 3}", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"a\""), OP_PUSH_1, OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"b\""), OP_PUSH_2, OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"c\""), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_HASH, marg_string_new("3")));
        parse("{\"a\": 1, \"b\": 2, \"c\": 3}", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"a\""), OP_PUSH_1, OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"b\""), OP_PUSH_2, OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"c\""), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_HASH, marg_string_new("3")));
    });
})

#endif
