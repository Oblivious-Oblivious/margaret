#ifndef __TUPLES_SPEC_H_
#define __TUPLES_SPEC_H_

#include "../_helpers.h"

module(tuples_spec, {
    it("parses tuple literals", {
        parse("[<]", marg_vector_new(OP_TUPLE, marg_string_new("0")));
        parse("([<])", marg_vector_new(OP_TUPLE, marg_string_new("0")));
        parse("[<[<], [<]]", marg_vector_new(OP_TUPLE, marg_string_new("0"), OP_TUPLE, marg_string_new("0"), OP_TUPLE, marg_string_new("2")));
        parse("[<41, 42]", marg_vector_new(OP_INTEGER, marg_string_new("41"), OP_INTEGER, marg_string_new("42"), OP_TUPLE, marg_string_new("2")));
        parse("([<41, 42])", marg_vector_new(OP_INTEGER, marg_string_new("41"), OP_INTEGER, marg_string_new("42"), OP_TUPLE, marg_string_new("2")));
        parse("[<42, \"str\", var]", marg_vector_new(OP_INTEGER, marg_string_new("42"), OP_STRING, marg_string_new("str"), OP_VARIABLE, marg_string_new("var"), OP_TUPLE, marg_string_new("3")));
        parse("[<42, \"Hello\", 'x', v1, v2]", marg_vector_new(OP_INTEGER, marg_string_new("42"), OP_STRING, marg_string_new("Hello"), OP_CHAR, marg_string_new("x"), OP_VARIABLE, marg_string_new("v1"), OP_VARIABLE, marg_string_new("v2"), OP_TUPLE, marg_string_new("5")));
        parse("[<42, \"Hello\", 'x', v1, v2, (), [], {}, [<], x = 1]", marg_vector_new(OP_INTEGER, marg_string_new("42"), OP_STRING, marg_string_new("Hello"), OP_CHAR, marg_string_new("x"), OP_VARIABLE, marg_string_new("v1"), OP_VARIABLE, marg_string_new("v2"), OP_TENSOR, marg_string_new("0"), OP_HASH, marg_string_new("0"), OP_TUPLE, marg_string_new("0"), OP_1, OP_STORE, marg_string_new("x"), OP_TUPLE, marg_string_new("10")));
    });
})

#endif
