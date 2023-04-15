#ifndef __EVALUATOR_SPEC_H_
#define __EVALUATOR_SPEC_H_

#include "../../src/ast/FormalMessagesBytecode.h"
#include "../../src/evaluator/Evaluator.h"
#include "../../src/lexer/Lexer.h"
#include "../../src/parser/Parser.h"

#include "../_helpers.h"

module(EvaluatorSpec, {
//     it("emits for a simple message", {
//         evalcodes("2 + 3", "5");
//     });

//     it("emits for assignment", {
//         evalcodes("x = 4", "4");
//         evalcodes("x = y = z = 6", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("6"), OP_STORE, marg_string_new("z"), OP_STORE, marg_string_new("y"), OP_STORE, marg_string_new("x")));
//         evalcodes("x = (y = 6) + 1", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("6"), OP_STORE, marg_string_new("y"), OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("x")));
//         evalcodes("@x = x + 2", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_2, OP_BINARY, marg_string_new("+"), OP_STORE_INSTANCE, marg_string_new("x")));
//         evalcodes("a = b = (c = 42) + 12", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_STORE, marg_string_new("c"), OP_PUSH_INTEGER, marg_string_new("12"), OP_BINARY, marg_string_new("+"), OP_STORE, marg_string_new("b"), OP_STORE, marg_string_new("a")));
//         evalcodes("a = a negate", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("a"), OP_UNARY, marg_string_new("negate"), OP_STORE, marg_string_new("a")));
//         evalcodes("@a = @a negate", marg_vector_new(OP_PUSH_INSTANCE, marg_string_new("a"), OP_UNARY, marg_string_new("negate"), OP_STORE_INSTANCE, marg_string_new("a")));
//     });

//     it("emits for unary messages", {
//         evalcodes("42 factorial", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial")));
//         evalcodes("17 incr puts", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("17"), OP_UNARY, marg_string_new("incr"), OP_UNARY, marg_string_new("puts")));
//         evalcodes("23 one two three", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("23"), OP_UNARY, marg_string_new("one"), OP_UNARY, marg_string_new("two"), OP_UNARY, marg_string_new("three")));
//         evalcodes("@inst one two three", marg_vector_new(OP_PUSH_INSTANCE, marg_string_new("inst"), OP_UNARY, marg_string_new("one"), OP_UNARY, marg_string_new("two"), OP_UNARY, marg_string_new("three")));
//         evalcodes("42 puts", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("puts")));
//         evalcodes("obj puts", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_UNARY, marg_string_new("puts")));
//         evalcodes("x = obj puts", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_UNARY, marg_string_new("puts"), OP_STORE, marg_string_new("x")));
//         evalcodes("(obj puts, 42 incr)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_UNARY, marg_string_new("puts"), OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("incr")));
//         evalcodes("((obj puts), (42 incr))", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("obj"), OP_UNARY, marg_string_new("puts"), OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("incr")));
//         evalcodes("42 incr incr decr decr", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("incr"), OP_UNARY, marg_string_new("incr"), OP_UNARY, marg_string_new("decr"), OP_UNARY, marg_string_new("decr")));
//         evalcodes("x = 42 incr incr decr decr", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("incr"), OP_UNARY, marg_string_new("incr"), OP_UNARY, marg_string_new("decr"), OP_UNARY, marg_string_new("decr"), OP_STORE, marg_string_new("x")));
//         evalcodes("x incr!", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("incr!")));
//         evalcodes("x is_empty?", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("is_empty?")));
//         evalcodes("(42 one, 43 two, 44 three, 45, 46 four)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("one"), OP_PUSH_INTEGER, marg_string_new("43"), OP_UNARY, marg_string_new("two"), OP_PUSH_INTEGER, marg_string_new("44"), OP_UNARY, marg_string_new("three"), OP_PUSH_INTEGER, marg_string_new("45"), OP_PUSH_INTEGER, marg_string_new("46"), OP_UNARY, marg_string_new("four")));
//         evalcodes("p1 + p2 calc puts", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("p1"), OP_PUSH_VARIABLE, marg_string_new("p2"), OP_UNARY, marg_string_new("calc"), OP_UNARY, marg_string_new("puts"), OP_BINARY, marg_string_new("+")));
//         evalcodes("(p1 + p2 calc) puts", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("p1"), OP_PUSH_VARIABLE, marg_string_new("p2"), OP_UNARY, marg_string_new("calc"), OP_BINARY, marg_string_new("+"), OP_UNARY, marg_string_new("puts")));
//     });

//     it("emits for binary messages", {
//         evalcodes("2 + 3", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+")));
//         evalcodes("2 + 3 * 4 + 5", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("4"), OP_BINARY, marg_string_new("*"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("+")));
//         evalcodes("2 * 5", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("*")));
//         evalcodes("a + b", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_BINARY, marg_string_new("+")));
//         evalcodes("42 factorial + 17", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial"), OP_PUSH_INTEGER, marg_string_new("17"), OP_BINARY, marg_string_new("+")));
//         evalcodes("41 factorial + 42 factorial + 43 factorial", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_UNARY, marg_string_new("factorial"), OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("43"), OP_UNARY, marg_string_new("factorial"), OP_BINARY, marg_string_new("+")));
//         evalcodes("(41 + 1, 42 + 0, 43 - 1)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_0, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("43"), OP_PUSH_1, OP_BINARY, marg_string_new("-")));
//         evalcodes("((41 + 1), (42 + 0), (43 - 1))", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_0, OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("43"), OP_PUSH_1, OP_BINARY, marg_string_new("-")));
//         evalcodes("x = a + b * 2 - 5", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_BINARY, marg_string_new("+"), OP_PUSH_2, OP_BINARY, marg_string_new("*"), OP_PUSH_INTEGER, marg_string_new("5"), OP_BINARY, marg_string_new("-"), OP_STORE, marg_string_new("x")));
//         evalcodes("x << item", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("item"), OP_BINARY, marg_string_new("<<")));
//         evalcodes("[1, 2, 3] ++ [4, 5]", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_PUSH_TENSOR, marg_string_new("3"), OP_PUSH_INTEGER, marg_string_new("4"), OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_TENSOR, marg_string_new("2"), OP_BINARY, marg_string_new("++")));
//         evalcodes("(4 + 3) * (5 + 6)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("4"), OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_INTEGER, marg_string_new("6"), OP_BINARY, marg_string_new("+"), OP_BINARY, marg_string_new("*")));
//     });

//     it("emits for keyword messages", {
//         evalcodes("list put: 42 at: 5", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("put:at:"), marg_string_new("2")));
//         evalcodes("list put: (42 incr) at: 5", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("incr"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("put:at:"), marg_string_new("2")));
//         evalcodes("( \
//             list = List new, \
//             list put: 42 at: 5, \
//             x = list get: 2, \
//             x puts \
//         )", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("List"), OP_UNARY, marg_string_new("new"), OP_STORE, marg_string_new("list"), OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("put:at:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_2, OP_KEYWORD, marg_string_new("get:"), marg_string_new("1"), OP_STORE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("x"), OP_UNARY, marg_string_new("puts")));
//         evalcodes("2 + 3 incr add: 11", marg_vector_new(OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_UNARY, marg_string_new("incr"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("11"), OP_KEYWORD, marg_string_new("add:"), marg_string_new("1")));
//         evalcodes("[1, 2, 3] reverse!: true", marg_vector_new(OP_PUSH_1, OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_PUSH_TENSOR, marg_string_new("3"), OP_PUSH_TRUE, OP_KEYWORD, marg_string_new("reverse!:"), marg_string_new("1")));
//         evalcodes("true then: 1 else: 2", marg_vector_new(OP_PUSH_TRUE, OP_PUSH_1, OP_PUSH_2, OP_KEYWORD, marg_string_new("then:else:"), marg_string_new("2")));
//         evalcodes("x ok?: true otherwise!: false", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_TRUE, OP_PUSH_FALSE, OP_KEYWORD, marg_string_new("ok?:otherwise!:"), marg_string_new("2")));
//         evalcodes("(5 + 13) greater_than?: (11 + 2)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("5"), OP_PUSH_INTEGER, marg_string_new("13"), OP_BINARY, marg_string_new("+"), OP_PUSH_INTEGER, marg_string_new("11"), OP_PUSH_2, OP_BINARY, marg_string_new("+"), OP_KEYWORD, marg_string_new("greater_than?:"), marg_string_new("1")));
//         evalcodes("42 factorial and: (2 + 3)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_UNARY, marg_string_new("factorial"), OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_KEYWORD, marg_string_new("and:"), marg_string_new("1")));
//         evalcodes("(list at: 3) + (list at: 5)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("at:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("list"), OP_PUSH_INTEGER, marg_string_new("5"), OP_KEYWORD, marg_string_new("at:"), marg_string_new("1"), OP_BINARY, marg_string_new("+")));
//         evalcodes("arr add: 1 add: 2 add: 3", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_1, OP_KEYWORD, marg_string_new("add:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_2, OP_KEYWORD, marg_string_new("add:"), marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("add:"), marg_string_new("1")));
//         evalcodes("arr add: 'a' add: 'b' at: 3", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_CHAR, marg_string_new("'a'"), OP_PUSH_CHAR, marg_string_new("'b'"), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("add:add:at:"), marg_string_new("3")));
//         evalcodes("arr add: 'a' at: 1 add: 'b' at: 2", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("arr"), OP_PUSH_CHAR, marg_string_new("'a'"), OP_PUSH_1, OP_PUSH_CHAR, marg_string_new("'b'"), OP_PUSH_2, OP_KEYWORD, marg_string_new("add:at:add:at:"), marg_string_new("4")));
//     });

    it("emits for groups", {
        evalcodes("()", "nil");
        evalcodes("(1, 2, 3)", "3");
        evalcodes("(1, 2, (10, 20, 30), 3)", "3");
        evalcodes("(1, \"2\", c, 42.42)", "42.42");
    });

//     it("emits for variables", {
//         evalcodes("ident", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("ident")));
//         evalcodes("variable", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("variable")));
//         evalcodes("@instvar", marg_vector_new(OP_PUSH_INSTANCE, marg_string_new("instvar")));
//         evalcodes("@x", marg_vector_new(OP_PUSH_INSTANCE, marg_string_new("x")));
//         evalcodes("nil", marg_vector_new(OP_PUSH_NIL));
//         evalcodes("true", marg_vector_new(OP_PUSH_TRUE));
//         evalcodes("false", marg_vector_new(OP_PUSH_FALSE));
//         evalcodes("self", marg_vector_new(OP_PUSH_SELF));
//         evalcodes("super", marg_vector_new(OP_PUSH_SUPER));
//     });

//     it("emits for procs", {
//         evalcodes("->{x = (x = 1, y = 2)}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_1, OP_STORE, marg_string_new("x"), OP_PUSH_2, OP_STORE, marg_string_new("y"), OP_STORE, marg_string_new("x"), OP_END_PUSH_PROC));
//         evalcodes("x = ->{ \
//             v1, v2, ( \
//                 v1 += 1, \
//                 v1 += 2, \
//                 v1 * v2 \
//             ) \
//         }", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("v1"), OP_PUSH_VARIABLE, marg_string_new("v2"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("v1"), OP_PUSH_1, OP_BINARY, marg_string_new("+="), OP_PUSH_VARIABLE, marg_string_new("v1"), OP_PUSH_2, OP_BINARY, marg_string_new("+="), OP_PUSH_VARIABLE, marg_string_new("v1"), OP_PUSH_VARIABLE, marg_string_new("v2"), OP_BINARY, marg_string_new("*"), OP_END_PUSH_PROC, OP_STORE, marg_string_new("x")));
//         evalcodes("->{42}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_INTEGER, marg_string_new("42"), OP_END_PUSH_PROC));
//         evalcodes("->{a | a puts}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_UNARY, marg_string_new("puts"), OP_END_PUSH_PROC));
//         evalcodes("->{2 + 3}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_2, OP_PUSH_INTEGER, marg_string_new("3"), OP_BINARY, marg_string_new("+"), OP_END_PUSH_PROC));
//         evalcodes("->{(x = 1, y = 2, x + y)}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_1, OP_STORE, marg_string_new("x"), OP_PUSH_2, OP_STORE, marg_string_new("y"), OP_PUSH_VARIABLE, marg_string_new("x"), OP_PUSH_VARIABLE, marg_string_new("y"), OP_BINARY, marg_string_new("+"), OP_END_PUSH_PROC));
//         evalcodes("->{a, b | a + b}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_BINARY, marg_string_new("+"), OP_END_PUSH_PROC));
//         evalcodes("->{a, a}", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("a"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_END_PUSH_PROC));
//         evalcodes("->{x = 2} exec", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_2, OP_STORE, marg_string_new("x"), OP_END_PUSH_PROC, OP_UNARY, marg_string_new("exec")));
//         evalcodes("->{param | param puts} value: 42", marg_vector_new(OP_START_PUSH_PROC, OP_PUSH_VARIABLE, marg_string_new("param"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_VARIABLE, marg_string_new("param"), OP_UNARY, marg_string_new("puts"), OP_END_PUSH_PROC, OP_PUSH_INTEGER, marg_string_new("42"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1")));
//     });

//     it("emits for unary method definitions", {
//         evalcodes("#incr => self + 1",   marg_vector_new(OP_START_PUSH_UNARY_METHOD, marg_string_new("\"incr\""), OP_PUSH_SELF, OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_END_PUSH_UNARY_METHOD));
//         evalcodes("#  incr => self + 1", marg_vector_new(OP_START_PUSH_UNARY_METHOD, marg_string_new("\"incr\""), OP_PUSH_SELF, OP_PUSH_1, OP_BINARY, marg_string_new("+"), OP_END_PUSH_UNARY_METHOD));
//         evalcodes("#is_empty? => true", marg_vector_new(OP_START_PUSH_UNARY_METHOD, marg_string_new("\"is_empty?\""), OP_PUSH_TRUE, OP_END_PUSH_UNARY_METHOD));
//         // evalcodes("# 0 fact => 1");

//         // 0 fact => 1,
//         // _ fact => self * (self-1) fact
//     });

//     it("emits for binary method definitions", {
//         evalcodes("#** a_number => self raised_to: a_number", marg_vector_new(OP_START_PUSH_BINARY_METHOD, marg_string_new("\"**\""), OP_PUSH_VARIABLE, marg_string_new("a_number"), OP_PUSH_SELF, OP_PUSH_VARIABLE, marg_string_new("a_number"), OP_KEYWORD, marg_string_new("raised_to:"), marg_string_new("1"), OP_END_PUSH_BINARY_METHOD));
//         // evalcodes("# 0 ** a_number => 0", "");
//         // evalcodes("# 0 ** 0 => nil", "");
//     });

//     it("emits for keyword method definitions", {
//         evalcodes("#add: element at: position => 42", marg_vector_new(OP_START_PUSH_KEYWORD_METHOD, marg_string_new("\"add:at:\""), OP_PUSH_VARIABLE, marg_string_new("element"), OP_PUSH_VARIABLE, marg_string_new("position"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_INTEGER, marg_string_new("42"), OP_END_PUSH_KEYWORD_METHOD));
//         evalcodes("#ok?: value1 otherwise!: value2 => 17", marg_vector_new(OP_START_PUSH_KEYWORD_METHOD, marg_string_new("\"ok?:otherwise!:\""), OP_PUSH_VARIABLE, marg_string_new("value1"), OP_PUSH_VARIABLE, marg_string_new("value2"), OP_PUSH_TENSOR, marg_string_new("2"), OP_PUSH_INTEGER, marg_string_new("17"), OP_END_PUSH_KEYWORD_METHOD));
//         // evalcodes("# [] add: element at: position => 17");
//         // evalcodes("# [] add: 'a' at: 0 => ['a']");
//         // evalcodes("#add: 'a' at: 0 => ['a'] ++ self");

//         evalcodes("#times: a_block => ( \
//             remaining = self, \
//             ->{ (remaining = remaining - 1) >= 0 } while_true: ->{ a_block value } \
//         )", marg_vector_new(OP_START_PUSH_KEYWORD_METHOD, marg_string_new("\"times:\""), OP_PUSH_VARIABLE, marg_string_new("a_block"), OP_PUSH_TENSOR, marg_string_new("1"), OP_PUSH_SELF, OP_STORE, marg_string_new("remaining"), OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_VARIABLE, marg_string_new("remaining"), OP_PUSH_1, OP_BINARY, marg_string_new("-"), OP_STORE, marg_string_new("remaining"), OP_PUSH_0, OP_BINARY, marg_string_new(">="), OP_END_PUSH_PROC, OP_START_PUSH_PROC, OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_VARIABLE, marg_string_new("a_block"), OP_UNARY, marg_string_new("value"), OP_END_PUSH_PROC, OP_KEYWORD, marg_string_new("while_true:"), marg_string_new("1"), OP_END_PUSH_KEYWORD_METHOD));
//     });

//     it("emits for C function definitions", {
//         evalcodes("###void f()", marg_vector_new(OP_START_PUSH_C_FUNCTION, OP_PUSH_VARIABLE, marg_string_new("void"), OP_PUSH_VARIABLE, marg_string_new("f"), OP_PUSH_TENSOR, marg_string_new("0"), OP_END_PUSH_C_FUNCTION));
//         evalcodes("###void f2(int a, int b)", marg_vector_new(OP_START_PUSH_C_FUNCTION, OP_PUSH_VARIABLE, marg_string_new("void"), OP_PUSH_VARIABLE, marg_string_new("f2"), OP_PUSH_VARIABLE, marg_string_new("CFunParam"), OP_PUSH_VARIABLE, marg_string_new("int"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("CFunParam"), OP_PUSH_VARIABLE, marg_string_new("int"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), OP_PUSH_TENSOR, marg_string_new("2"), OP_END_PUSH_C_FUNCTION));
//     });

    it("emits for integers", {
        evalcodes("0", "0");
        evalcodes("-0", "0");
        evalcodes("+0", "0");
        evalcodes("1", "1");
        evalcodes("+1", "1");
        evalcodes("-1", "-1");
        evalcodes("2", "2");
        evalcodes("+2", "2");
        evalcodes("42", "42");
        evalcodes("-42", "-42");
        evalcodes("+42", "42");
        evalcodes("4_200", "4200");
        evalcodes("-4_200", "-4200");
        evalcodes("4____20__0", "4200");
        evalcodes("-4____20__0", "-4200");
        evalcodes("+4____20__0", "4200");
    });

    it("emits for floats", {
        evalcodes("42.0", "42.0");
        evalcodes("-42.0", "-42.0");
        evalcodes("986513.00056129", "986513.00056129");
        evalcodes("-986513.00056129", "-986513.00056129");
        evalcodes("0.1_2_3", "0.123");
        evalcodes("0.1__23", "0.123");
    });

    it("emits for binaries", {
        evalcodes("0b0110", "6");
        evalcodes("0B10", "2");
        evalcodes("-0b0110", "-6");
        evalcodes("-0B10", "-2");
        // evalcodes("( \
        //     x = 0b0101 + 0b1011, \
        //     x to_int puts, \
        // )", "16");
    });

    it("emits for hexadecimals", {
        evalcodes("0xbeef", "48879");
        evalcodes("-0xbeEf", "-48879");
        evalcodes("0X0427", "1063");
        evalcodes("-0X0427", "-1063");
        // evalcodes("x = 0xbeef to_bin to_int puts", "48879");
        // evalcodes("0xbeef - 0xabb2", "4925");
        evalcodes("0xbe____e___f", "48879");
    });

    it("emits for octals", {
        evalcodes("0o741", "481");
        evalcodes("-0o741", "-481");
        evalcodes("0O0210", "136");
        evalcodes("-0O0210", "-136");
        // evalcodes("0o751 to_hex to_bin to_int puts", "489");
        // evalcodes("0O541 + 0o777", "864");
    });

    it("emits for characters", {
        evalcodes("'a'", "'a'");
        evalcodes("'\n'", "'\n'");
        // evalcodes("'œ'", "'œ'");
        // evalcodes("-'œ'", "-'œ'");
        // evalcodes("('a' to_uppercase)", "'A'");
        // evalcodes("('B' to_ascii)", "42");
        // evalcodes("('a' <= 'b')", "true");
    });

    it("emits for strings", {
        evalcodes("\"string\"", "\"string\"");
        evalcodes("\"foo\tbar\"", "\"foo\tbar\"");
        evalcodes("\"a string lit\"", "\"a string lit\"");
        evalcodes("\"str\"", "\"str\"");
    });

//     it("emits for tensors", {
//         evalcodes("[]", marg_vector_new(OP_PUSH_TENSOR, marg_string_new("0")));
//         evalcodes("[41, 42]", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_TENSOR, marg_string_new("2")));
//         evalcodes("[42, \"str\", var]", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_STRING, marg_string_new("\"str\""), OP_PUSH_VARIABLE, marg_string_new("var"), OP_PUSH_TENSOR, marg_string_new("3")));
//         evalcodes("[41,42,43,44,45]", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_INTEGER, marg_string_new("43"), OP_PUSH_INTEGER, marg_string_new("44"), OP_PUSH_INTEGER, marg_string_new("45"), OP_PUSH_TENSOR, marg_string_new("5")));
//     });

//     it("emits for hashes", {
//         evalcodes("{}", marg_vector_new(OP_PUSH_HASH, marg_string_new("0")));
//         evalcodes("{a: {}, b: {}}", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"a\""), OP_PUSH_HASH, marg_string_new("0"), OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"b\""), OP_PUSH_HASH, marg_string_new("0"), OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_HASH, marg_string_new("2")));
//         evalcodes("{a: 1, b: 2, c: 3}", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"a\""), OP_PUSH_1, OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"b\""), OP_PUSH_2, OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"c\""), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_HASH, marg_string_new("3")));
//         evalcodes("{\"a\": 1, \"b\": 2, \"c\": 3}", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"a\""), OP_PUSH_1, OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"b\""), OP_PUSH_2, OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("Association"), OP_PUSH_STRING, marg_string_new("\"c\""), OP_PUSH_INTEGER, marg_string_new("3"), OP_KEYWORD, marg_string_new("key:value:"), marg_string_new("2"), OP_PUSH_HASH, marg_string_new("3")));
//     });
})

#endif
