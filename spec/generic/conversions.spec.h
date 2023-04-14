#ifndef __CONVERSIONS_SPEC_H_
#define __CONVERSIONS_SPEC_H_

#include "../_helpers.h"

module(conversions_spec, {
    it("parses object conversion", {
        parse("(x = 3.99 to_int)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("3.99"), OP_UNARY, marg_string_new("to_int"), OP_STORE, marg_string_new("x")));
        parse("(x = 3.99 to_fraction)", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("3.99"), OP_UNARY, marg_string_new("to_fraction"), OP_STORE, marg_string_new("x")));
        parse("(x = 3 to_float)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("3"), OP_UNARY, marg_string_new("to_float"), OP_STORE, marg_string_new("x")));
        parse("(x = 65 to_char)", marg_vector_new(OP_PUSH_INTEGER, marg_string_new("65"), OP_UNARY, marg_string_new("to_char"), OP_STORE, marg_string_new("x")));
        parse("(x = \"A\" to_ascii)", marg_vector_new(OP_PUSH_STRING, marg_string_new("A"), OP_UNARY, marg_string_new("to_ascii"), OP_STORE, marg_string_new("x")));
        parse("(x = 'b' to_ascii)", marg_vector_new(OP_PUSH_CHAR, marg_string_new("b"), OP_UNARY, marg_string_new("to_ascii"), OP_STORE, marg_string_new("x")));
    });
})

#endif
