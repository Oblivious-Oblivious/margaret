#ifndef __CONVERSIONS_SPEC_H_
#define __CONVERSIONS_SPEC_H_

#include "../_helpers.h"

module(conversions_spec, {
    it("parses object conversion", {
        parse("(x = 3.99 to_int)", marg_vector_new(FM_FLOAT, marg_string_new("3.99"), FM_UNARY, marg_string_new("to_int"), FM_STORE, marg_string_new("x")));
        parse("(x = 3.99 to_fraction)", marg_vector_new(FM_FLOAT, marg_string_new("3.99"), FM_UNARY, marg_string_new("to_fraction"), FM_STORE, marg_string_new("x")));
        parse("(x = 3 to_float)", marg_vector_new(FM_INTEGER, marg_string_new("3"), FM_UNARY, marg_string_new("to_float"), FM_STORE, marg_string_new("x")));
        parse("(x = 65 to_char)", marg_vector_new(FM_INTEGER, marg_string_new("65"), FM_UNARY, marg_string_new("to_char"), FM_STORE, marg_string_new("x")));
        parse("(x = \"A\" to_ascii)", marg_vector_new(FM_STRING, marg_string_new("A"), FM_UNARY, marg_string_new("to_ascii"), FM_STORE, marg_string_new("x")));
        parse("(x = 'b' to_ascii)", marg_vector_new(FM_CHAR, marg_string_new("b"), FM_UNARY, marg_string_new("to_ascii"), FM_STORE, marg_string_new("x")));
    });
})

#endif
