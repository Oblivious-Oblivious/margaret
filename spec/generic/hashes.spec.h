#ifndef __HASHES_SPEC_H_
#define __HASHES_SPEC_H_

#include "../_helpers.h"

module(hashes_spec, {
    it("parses hash literals", {
        parse("({})", vector_new(FM_HASH, string_new("0")));
        parse("({a: {}, b: {}})", vector_new(FM_LOCAL, string_new("Association"), FM_STRING, string_new("a"), FM_HASH, string_new("0"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("b"), FM_HASH, string_new("0"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_HASH, string_new("2")));
        parse("({a: 1, b: 2, c: 3})", vector_new(FM_LOCAL, string_new("Association"), FM_STRING, string_new("a"), FM_INTEGER, string_new("1"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("b"), FM_INTEGER, string_new("2"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("c"), FM_INTEGER, string_new("3"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_HASH, string_new("3")));
        parse("{\"a\": 1, \"b\": 2, \"c\": 3}", vector_new(FM_LOCAL, string_new("Association"), FM_STRING, string_new("a"), FM_INTEGER, string_new("1"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("b"), FM_INTEGER, string_new("2"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("c"), FM_INTEGER, string_new("3"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_HASH, string_new("3")));
        parse("({\"k1\": \"v1\", \"k2\": \"v2\", \"k3\": \"v3\"})", vector_new(FM_LOCAL, string_new("Association"), FM_STRING, string_new("k1"), FM_STRING, string_new("v1"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("k2"), FM_STRING, string_new("v2"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("k3"), FM_STRING, string_new("v3"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_HASH, string_new("3")));
        parse("{x: {a: 1, b: 2}, y: {c: 3, d: 4}}", vector_new(FM_LOCAL, string_new("Association"), FM_STRING, string_new("x"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("a"), FM_INTEGER, string_new("1"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("b"), FM_INTEGER, string_new("2"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_HASH, string_new("2"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("y"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("c"), FM_INTEGER, string_new("3"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("d"), FM_INTEGER, string_new("4"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_HASH, string_new("2"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_HASH, string_new("2")));
        parse("{a: 42 factorial, b: 2 + 3, c: 41 plus: 1, d: (42 incr decr, 41 incr)}", vector_new(FM_LOCAL, string_new("Association"), FM_STRING, string_new("a"), FM_INTEGER, string_new("42"), FM_UNARY, string_new("factorial"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("b"), FM_INTEGER, string_new("2"), FM_INTEGER, string_new("3"), FM_BINARY, string_new("+"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("c"), FM_INTEGER, string_new("41"), FM_INTEGER, string_new("1"), FM_KEYWORD, string_new("plus:"), string_new("1"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_LOCAL, string_new("Association"), FM_STRING, string_new("d"), FM_INTEGER, string_new("42"), FM_UNARY, string_new("incr"), FM_UNARY, string_new("decr"), FM_INTEGER, string_new("41"), FM_UNARY, string_new("incr"), FM_KEYWORD, string_new("key:value:"), string_new("2"), FM_HASH, string_new("4")));
    });

    it("parses hashes", {
        parse("(x at: 'a' put: 3)", vector_new(FM_LOCAL, string_new("x"), FM_STRING, string_new("a"), FM_INTEGER, string_new("3"), FM_KEYWORD, string_new("at:put:"), string_new("2")));
        parse("(x is_empty?)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("is_empty?")));
        parse("(x size)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("size")));
        parse("(x at: \"a\" if_absent: \"\")", vector_new(FM_LOCAL, string_new("x"), FM_STRING, string_new("a"), FM_STRING, string_new(""), FM_KEYWORD, string_new("at:if_absent:"), string_new("2")));
        parse("(x key_at_value: 3 if_absent: \"\")", vector_new(FM_LOCAL, string_new("x"), FM_INTEGER, string_new("3"), FM_STRING, string_new(""), FM_KEYWORD, string_new("key_at_value:if_absent:"), string_new("2")));
        parse("(x remove_key: \"e\" if_absent: \"\")", vector_new(FM_LOCAL, string_new("x"), FM_STRING, string_new("e"), FM_STRING, string_new(""), FM_KEYWORD, string_new("remove_key:if_absent:"), string_new("2")));
        parse("(b = x includes_key: \"a\")", vector_new(FM_LOCAL, string_new("x"), FM_STRING, string_new("a"), FM_KEYWORD, string_new("includes_key:"), string_new("1"), FM_STORE_LOCAL, string_new("b")));
        parse("(x keys puts)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("keys"), FM_UNARY, string_new("puts")));
        parse("(x values puts)", vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("values"), FM_UNARY, string_new("puts")));
        parse("(x each_key: {a | a puts})", vector_new(FM_LOCAL, string_new("x"), FM_START_PROC, FM_PROC_PARAMETER, string_new("a"), FM_LOCAL, string_new("a"), FM_UNARY, string_new("puts"), FM_END_PROC, FM_KEYWORD, string_new("each_key:"), string_new("1")));
        parse("(x each_value: {a | a puts})", vector_new(FM_LOCAL, string_new("x"), FM_START_PROC, FM_PROC_PARAMETER, string_new("a"), FM_LOCAL, string_new("a"), FM_UNARY, string_new("puts"), FM_END_PROC, FM_KEYWORD, string_new("each_value:"), string_new("1")));
        parse("(x each: {a | a puts})", vector_new(FM_LOCAL, string_new("x"), FM_START_PROC, FM_PROC_PARAMETER, string_new("a"), FM_LOCAL, string_new("a"), FM_UNARY, string_new("puts"), FM_END_PROC, FM_KEYWORD, string_new("each:"), string_new("1")));
    });
})

#endif
