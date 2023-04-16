#ifndef __BITSTRINGS_SPEC_H_
#define __BITSTRINGS_SPEC_H_

#include "../_helpers.h"

module(bitstrings_spec, {
    it("parses bitstrings literals", {
        parse("{<}", marg_vector_new(FM_BITSTRING, marg_string_new("0")));
        parse("({<})", marg_vector_new(FM_BITSTRING, marg_string_new("0")));
        parse("{<{<}, {<}}", marg_vector_new(FM_VARIABLE, marg_string_new("Bit"), FM_BITSTRING, marg_string_new("0"), FM_KEYWORD, marg_string_new("value:"), marg_string_new("1"), FM_VARIABLE, marg_string_new("Bit"), FM_BITSTRING, marg_string_new("0"), FM_KEYWORD, marg_string_new("value:"), marg_string_new("1"), FM_BITSTRING, marg_string_new("2")));
        parse("{<41, 42}", marg_vector_new(FM_VARIABLE, marg_string_new("Bit"), FM_INTEGER, marg_string_new("41"), FM_KEYWORD, marg_string_new("value:"), marg_string_new("1"), FM_VARIABLE, marg_string_new("Bit"), FM_INTEGER, marg_string_new("42"), FM_KEYWORD, marg_string_new("value:"), marg_string_new("1"), FM_BITSTRING, marg_string_new("2")));
        parse("({<41, 42})", marg_vector_new(FM_VARIABLE, marg_string_new("Bit"), FM_INTEGER, marg_string_new("41"), FM_KEYWORD, marg_string_new("value:"), marg_string_new("1"), FM_VARIABLE, marg_string_new("Bit"), FM_INTEGER, marg_string_new("42"), FM_KEYWORD, marg_string_new("value:"), marg_string_new("1"), FM_BITSTRING, marg_string_new("2")));
        parse("{<42, \"str\", var}", marg_vector_new(FM_VARIABLE, marg_string_new("Bit"), FM_INTEGER, marg_string_new("42"), FM_KEYWORD, marg_string_new("value:"), marg_string_new("1"), FM_VARIABLE, marg_string_new("Bit"), FM_STRING, marg_string_new("str"), FM_KEYWORD, marg_string_new("value:"), marg_string_new("1"), FM_VARIABLE, marg_string_new("Bit"), FM_VARIABLE, marg_string_new("var"), FM_KEYWORD, marg_string_new("value:"), marg_string_new("1"), FM_BITSTRING, marg_string_new("3")));
        parse("{<0:1, 0:1, 1:1, 1:1}", marg_vector_new(FM_VARIABLE, marg_string_new("Bit"), FM_0, FM_1, FM_KEYWORD, marg_string_new("value:size:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("Bit"), FM_0, FM_1, FM_KEYWORD, marg_string_new("value:size:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("Bit"), FM_1, FM_1, FM_KEYWORD, marg_string_new("value:size:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("Bit"), FM_1, FM_1, FM_KEYWORD, marg_string_new("value:size:"), marg_string_new("2"), FM_BITSTRING, marg_string_new("4")));
        parse("{<3:4}", marg_vector_new(FM_VARIABLE, marg_string_new("Bit"), FM_INTEGER, marg_string_new("3"), FM_INTEGER, marg_string_new("4"), FM_KEYWORD, marg_string_new("value:size:"), marg_string_new("2"), FM_BITSTRING, marg_string_new("1")));
    });
})

#endif
