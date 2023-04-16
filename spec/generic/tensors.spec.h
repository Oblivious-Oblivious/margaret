#ifndef __TENSORS_SPEC_H_
#define __TENSORS_SPEC_H_

#include "../_helpers.h"

module(tensors_spec, {
    it("parses tensor literals", {
        parse("[]", marg_vector_new(FM_TENSOR, marg_string_new("0")));
        parse("([])", marg_vector_new(FM_TENSOR, marg_string_new("0")));
        parse("[[], []]", marg_vector_new(FM_TENSOR, marg_string_new("0"), FM_TENSOR, marg_string_new("0"), FM_TENSOR, marg_string_new("2")));
        parse("[41, 42]", marg_vector_new(FM_INTEGER, marg_string_new("41"), FM_INTEGER, marg_string_new("42"), FM_TENSOR, marg_string_new("2")));
        parse("([41, 42])", marg_vector_new(FM_INTEGER, marg_string_new("41"), FM_INTEGER, marg_string_new("42"), FM_TENSOR, marg_string_new("2")));
        parse("[42, \"str\", var]", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_STRING, marg_string_new("str"), FM_VARIABLE, marg_string_new("var"), FM_TENSOR, marg_string_new("3")));
        parse("[42, \"Hello\", 'x', v1, v2]", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_STRING, marg_string_new("Hello"), FM_CHAR, marg_string_new("x"), FM_VARIABLE, marg_string_new("v1"), FM_VARIABLE, marg_string_new("v2"), FM_TENSOR, marg_string_new("5")));
        parse("[42, \"Hello\", 'x', v1, v2, (), [], {}, x = 1]", marg_vector_new(FM_INTEGER, marg_string_new("42"), FM_STRING, marg_string_new("Hello"), FM_CHAR, marg_string_new("x"), FM_VARIABLE, marg_string_new("v1"), FM_VARIABLE, marg_string_new("v2"), FM_TENSOR, marg_string_new("0"), FM_HASH, marg_string_new("0"), FM_1, FM_STORE, marg_string_new("x"), FM_TENSOR, marg_string_new("9")));
    });
})

#endif
