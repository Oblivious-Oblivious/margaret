#ifndef __ASSIGNMENTS_SPEC_H_
#define __ASSIGNMENTS_SPEC_H_

#include "../_helpers.h"

module(assignments_spec, {
    it("parses assignments", {
        parse("(x = 4)", vector_new(FM_INTEGER, string_new("4"), FM_STORE_LOCAL, string_new("x"), FM_POP));
        parse("(x = y = z = 6)", vector_new(FM_INTEGER, string_new("6"), FM_STORE_LOCAL, string_new("z"), FM_STORE_LOCAL, string_new("y"), FM_STORE_LOCAL, string_new("x"), FM_POP));
        parse("(x = (y = 6) + 1)", vector_new(FM_INTEGER, string_new("6"), FM_STORE_LOCAL, string_new("y"), FM_INTEGER, string_new("1"), FM_BINARY, string_new("+"), FM_STORE_LOCAL, string_new("x"), FM_POP));
        parse("(x = Object new)", vector_new(FM_LOCAL, string_new("Object"), FM_UNARY, string_new("new"), FM_STORE_LOCAL, string_new("x"), FM_POP));
        parse("var = 12", vector_new(FM_INTEGER, string_new("12"), FM_STORE_LOCAL, string_new("var"), FM_POP));
        parse("arr = []", vector_new(FM_TENSOR, string_new("0"), FM_STORE_LOCAL, string_new("arr"), FM_POP));
        parse("@x = x + 2", vector_new(FM_LOCAL, string_new("x"), FM_INTEGER, string_new("2"), FM_BINARY, string_new("+"), FM_STORE_INSTANCE, string_new("@x"), FM_POP));
        parse("a = b", vector_new(FM_LOCAL, string_new("b"), FM_STORE_LOCAL, string_new("a"), FM_POP));
        parse("a = b = c", vector_new(FM_LOCAL, string_new("c"), FM_STORE_LOCAL, string_new("b"), FM_STORE_LOCAL, string_new("a"), FM_POP));
        parse("@a = @b = @c", vector_new(FM_INSTANCE, string_new("@c"), FM_STORE_INSTANCE, string_new("@b"), FM_STORE_INSTANCE, string_new("@a"), FM_POP));
        parse("$a = $b = $c", vector_new(FM_GLOBAL, string_new("$c"), FM_STORE_GLOBAL, string_new("$b"), FM_STORE_GLOBAL, string_new("$a"), FM_POP));
        parse("a = b = c = d = 42", vector_new(FM_INTEGER, string_new("42"), FM_STORE_LOCAL, string_new("d"), FM_STORE_LOCAL, string_new("c"), FM_STORE_LOCAL, string_new("b"), FM_STORE_LOCAL, string_new("a"), FM_POP));
        parse("(a = 2, b = 3, c = a = b)", vector_new(FM_INTEGER, string_new("2"), FM_STORE_LOCAL, string_new("a"), FM_POP, FM_INTEGER, string_new("3"), FM_STORE_LOCAL, string_new("b"), FM_POP, FM_LOCAL, string_new("b"), FM_STORE_LOCAL, string_new("a"), FM_STORE_LOCAL, string_new("c"), FM_POP));
        parse("((a = 2), (b = 3), (c = a = b))", vector_new(FM_INTEGER, string_new("2"), FM_STORE_LOCAL, string_new("a"), FM_POP, FM_INTEGER, string_new("3"), FM_STORE_LOCAL, string_new("b"), FM_POP, FM_LOCAL, string_new("b"), FM_STORE_LOCAL, string_new("a"), FM_STORE_LOCAL, string_new("c"), FM_POP));
        parse("a = b = (c = 42) + 12", vector_new(FM_INTEGER, string_new("42"), FM_STORE_LOCAL, string_new("c"), FM_INTEGER, string_new("12"), FM_BINARY, string_new("+"), FM_STORE_LOCAL, string_new("b"), FM_STORE_LOCAL, string_new("a"), FM_POP));
        parse("a = 12 + 3 * 4", vector_new(FM_INTEGER, string_new("12"), FM_INTEGER, string_new("3"), FM_BINARY, string_new("+"), FM_INTEGER, string_new("4"), FM_BINARY, string_new("*"), FM_STORE_LOCAL, string_new("a"), FM_POP));
    });

    it("parses assignments as a plain message on non assignable values", {
        parse("[a, b, c] = [1, 2, 3]", vector_new(FM_LOCAL, string_new("a"), FM_LOCAL, string_new("b"), FM_LOCAL, string_new("c"), FM_TENSOR, string_new("3"), FM_INTEGER, string_new("1"), FM_INTEGER, string_new("2"), FM_INTEGER, string_new("3"), FM_TENSOR, string_new("3"), FM_BINARY, string_new("="), FM_POP));
        parse("a = 3 + 4", vector_new(FM_INTEGER, string_new("3"), FM_INTEGER, string_new("4"), FM_BINARY, string_new("+"), FM_STORE_LOCAL, string_new("a"), FM_POP));
        parse("2 = 3 + 4", vector_new(FM_INTEGER, string_new("2"), FM_INTEGER, string_new("3"), FM_BINARY, string_new("="), FM_INTEGER, string_new("4"), FM_BINARY, string_new("+"), FM_POP));
    });
})

#endif
