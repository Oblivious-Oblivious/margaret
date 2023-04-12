#ifndef __TUPLES_SPEC_H_
#define __TUPLES_SPEC_H_

#include "../_helpers.h"

module(tuples_spec, {
    it("parses tensor literals", {
        parse("[<]", marg_vector_new(OP_PUSH_TUPLE, marg_string_new("0")));
        parse("([<])", marg_vector_new(OP_PUSH_TUPLE, marg_string_new("0")));
        parse("[<[<], [<]]", marg_vector_new(OP_PUSH_TUPLE, marg_string_new("0"), OP_PUSH_TUPLE, marg_string_new("0"), OP_PUSH_TUPLE, marg_string_new("2")));
        parse("[<41, 42]", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_TUPLE, marg_string_new("2")));
        parse("([<41, 42])", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("41"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_TUPLE, marg_string_new("2")));
        parse("[<42, \"str\", var]", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_STRING, marg_string_new("\"str\""), OP_PUSH_VARIABLE, marg_string_new("var"), OP_PUSH_TUPLE, marg_string_new("3")));
        parse("[<42, \"Hello\", 'x', v1, v2]", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_STRING, marg_string_new("\"Hello\""), OP_PUSH_CHAR, marg_string_new("'x'"), OP_PUSH_VARIABLE, marg_string_new("v1"), OP_PUSH_VARIABLE, marg_string_new("v2"), OP_PUSH_TUPLE, marg_string_new("5")));
        parse("[<42, \"Hello\", 'x', v1, v2, (), [], {}, [<], x = 1]", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_STRING, marg_string_new("\"Hello\""), OP_PUSH_CHAR, marg_string_new("'x'"), OP_PUSH_VARIABLE, marg_string_new("v1"), OP_PUSH_VARIABLE, marg_string_new("v2"), OP_PUSH_TENSOR, marg_string_new("0"), OP_PUSH_HASH, marg_string_new("0"), OP_PUSH_TUPLE, marg_string_new("0"), OP_PUSH_1, OP_STORE, marg_string_new("x"), OP_PUSH_TUPLE, marg_string_new("10")));
    });
})

#endif
