#ifndef __BITSTRINGS_SPEC_H_
#define __BITSTRINGS_SPEC_H_

#include "../_helpers.h"

module(bitstrings_spec, {
    it("parses bitstrings literals", {
        parse("{<}", marg_vector_new(OP_BITSTRING, marg_string_new("0")));
        parse("({<})", marg_vector_new(OP_BITSTRING, marg_string_new("0")));
        parse("{<{<}, {<}}", marg_vector_new(OP_VARIABLE, marg_string_new("Bit"), OP_BITSTRING, marg_string_new("0"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1"), OP_VARIABLE, marg_string_new("Bit"), OP_BITSTRING, marg_string_new("0"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1"), OP_BITSTRING, marg_string_new("2")));
        parse("{<41, 42}", marg_vector_new(OP_VARIABLE, marg_string_new("Bit"), OP_INTEGER, marg_string_new("41"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1"), OP_VARIABLE, marg_string_new("Bit"), OP_INTEGER, marg_string_new("42"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1"), OP_BITSTRING, marg_string_new("2")));
        parse("({<41, 42})", marg_vector_new(OP_VARIABLE, marg_string_new("Bit"), OP_INTEGER, marg_string_new("41"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1"), OP_VARIABLE, marg_string_new("Bit"), OP_INTEGER, marg_string_new("42"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1"), OP_BITSTRING, marg_string_new("2")));
        parse("{<42, \"str\", var}", marg_vector_new(OP_VARIABLE, marg_string_new("Bit"), OP_INTEGER, marg_string_new("42"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1"), OP_VARIABLE, marg_string_new("Bit"), OP_STRING, marg_string_new("str"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1"), OP_VARIABLE, marg_string_new("Bit"), OP_VARIABLE, marg_string_new("var"), OP_KEYWORD, marg_string_new("value:"), marg_string_new("1"), OP_BITSTRING, marg_string_new("3")));
        parse("{<0:1, 0:1, 1:1, 1:1}", marg_vector_new(OP_VARIABLE, marg_string_new("Bit"), OP_0, OP_1, OP_KEYWORD, marg_string_new("value:size:"), marg_string_new("2"), OP_VARIABLE, marg_string_new("Bit"), OP_0, OP_1, OP_KEYWORD, marg_string_new("value:size:"), marg_string_new("2"), OP_VARIABLE, marg_string_new("Bit"), OP_1, OP_1, OP_KEYWORD, marg_string_new("value:size:"), marg_string_new("2"), OP_VARIABLE, marg_string_new("Bit"), OP_1, OP_1, OP_KEYWORD, marg_string_new("value:size:"), marg_string_new("2"), OP_BITSTRING, marg_string_new("4")));
        parse("{<3:4}", marg_vector_new(OP_VARIABLE, marg_string_new("Bit"), OP_INTEGER, marg_string_new("3"), OP_INTEGER, marg_string_new("4"), OP_KEYWORD, marg_string_new("value:size:"), marg_string_new("2"), OP_BITSTRING, marg_string_new("1")));
    });
})

#endif
