#ifndef __STRINGS_SPEC_H_
#define __STRINGS_SPEC_H_

#include "../_helpers.h"

module(strings_spec, {
    it("parses string literals", {
        parse("(\"hello\" puts)", marg_vector_new(OP_STRING, marg_string_new("hello"), OP_UNARY, marg_string_new("puts")));
        parse("\"multi\n\
            line\n\
            string\"", marg_vector_new(OP_STRING, marg_string_new("multi\n            line\n            string")));
    });

    it("parses escape strings", {
        parse("\"foo\tbar\"", marg_vector_new(OP_STRING, marg_string_new("foo\tbar")));
        parse("\"a string lit\"", marg_vector_new(OP_STRING, marg_string_new("a string lit")));
        parse("\"str\"", marg_vector_new(OP_STRING, marg_string_new("str")));

        parse("\"\a\"", marg_vector_new(OP_STRING, marg_string_new("\a")));
        parse("\"\b\"", marg_vector_new(OP_STRING, marg_string_new("\b")));
        parse("\"\t\"", marg_vector_new(OP_STRING, marg_string_new("\t")));
        parse("\"\n\"", marg_vector_new(OP_STRING, marg_string_new("\n")));
        parse("\"\v\"", marg_vector_new(OP_STRING, marg_string_new("\v")));
        parse("\"\f\"", marg_vector_new(OP_STRING, marg_string_new("\f")));
        parse("\"\r\"", marg_vector_new(OP_STRING, marg_string_new("\r")));
        parse("\"\\\"", marg_vector_new(OP_STRING, marg_string_new("\\")));
    });

    it("parses string messages", {
        parse("(b = s is_empty?)", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_UNARY, marg_string_new("is_empty?"), OP_STORE, marg_string_new("b")));
        parse("(x = s size)", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_UNARY, marg_string_new("size"), OP_STORE, marg_string_new("x")));
        parse("(x = s at: 2)", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_2, OP_KEYWORD, marg_string_new("at:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = s copy_from: 2 to: 4)", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_2, OP_INTEGER, marg_string_new("4"), OP_KEYWORD, marg_string_new("copy_from:to:"), marg_string_new("2"), OP_STORE, marg_string_new("x")));
        parse("(x = s index_of: 'a' if_absent: 0)", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_CHAR, marg_string_new("a"), OP_0, OP_KEYWORD, marg_string_new("index_of:if_absent:"), marg_string_new("2"), OP_STORE, marg_string_new("x")));
        parse("(s at: 1 put: 'a', s at: 2 put: 'b', s at: 3 put: 'c')", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_1, OP_CHAR, marg_string_new("a"), OP_KEYWORD, marg_string_new("at:put:"), marg_string_new("2"), OP_VARIABLE, marg_string_new("s"), OP_2, OP_CHAR, marg_string_new("b"), OP_KEYWORD, marg_string_new("at:put:"), marg_string_new("2"), OP_VARIABLE, marg_string_new("s"), OP_INTEGER, marg_string_new("3"), OP_CHAR, marg_string_new("c"), OP_KEYWORD, marg_string_new("at:put:"), marg_string_new("2")));
        parse("s << 'a' << 'b' << 'c' << 'd'", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_CHAR, marg_string_new("a"), OP_BINARY, marg_string_new("<<"), OP_CHAR, marg_string_new("b"), OP_BINARY, marg_string_new("<<"), OP_CHAR, marg_string_new("c"), OP_BINARY, marg_string_new("<<"), OP_CHAR, marg_string_new("d"), OP_BINARY, marg_string_new("<<")));
        parse("s add: 'a' add: 'b' add: 'c' add: 'd'", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_CHAR, marg_string_new("a"), OP_KEYWORD, marg_string_new("add:"), marg_string_new("1"), OP_VARIABLE, marg_string_new("s"), OP_CHAR, marg_string_new("b"), OP_KEYWORD, marg_string_new("add:"), marg_string_new("1"), OP_VARIABLE, marg_string_new("s"), OP_CHAR, marg_string_new("c"), OP_KEYWORD, marg_string_new("add:"), marg_string_new("1"), OP_VARIABLE, marg_string_new("s"), OP_CHAR, marg_string_new("d"), OP_KEYWORD, marg_string_new("add:"), marg_string_new("1")));
        parse("(s each_char: {a | a puts})", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_START_PROC, OP_VARIABLE, marg_string_new("a"), OP_TENSOR, marg_string_new("1"), OP_VARIABLE, marg_string_new("a"), OP_UNARY, marg_string_new("puts"), OP_END_PROC, OP_KEYWORD, marg_string_new("each_char:"), marg_string_new("1")));
        parse("(b = s conform: {a | (a >= 'a') && (a <= 'z')})", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_START_PROC, OP_VARIABLE, marg_string_new("a"), OP_TENSOR, marg_string_new("1"), OP_VARIABLE, marg_string_new("a"), OP_CHAR, marg_string_new("a"), OP_BINARY, marg_string_new(">="), OP_VARIABLE, marg_string_new("a"), OP_CHAR, marg_string_new("z"), OP_BINARY, marg_string_new("<="), OP_BINARY, marg_string_new("&&"), OP_END_PROC, OP_KEYWORD, marg_string_new("conform:"), marg_string_new("1"), OP_STORE, marg_string_new("b")));
        parse("(x = s select: { a | a > 'a'})", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_START_PROC, OP_VARIABLE, marg_string_new("a"), OP_TENSOR, marg_string_new("1"), OP_VARIABLE, marg_string_new("a"), OP_CHAR, marg_string_new("a"), OP_BINARY, marg_string_new(">"), OP_END_PROC, OP_KEYWORD, marg_string_new("select:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = s to_list)", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_UNARY, marg_string_new("to_list"), OP_STORE, marg_string_new("x")));
        parse("(x = s to_symbol)", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_UNARY, marg_string_new("to_symbol"), OP_STORE, marg_string_new("x")));
        parse("(x = \"abcd\" to_byte_array)", marg_vector_new(OP_STRING, marg_string_new("abcd"), OP_UNARY, marg_string_new("to_byte_array"), OP_STORE, marg_string_new("x")));
        parse("(x = s shuffled)", marg_vector_new(OP_VARIABLE, marg_string_new("s"), OP_UNARY, marg_string_new("shuffled"), OP_STORE, marg_string_new("x")));
    });
})

#endif
