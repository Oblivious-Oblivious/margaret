#ifndef __BITSTRINGS_SPEC_H_
#define __BITSTRINGS_SPEC_H_

#include "../_helpers.h"

module(bitstrings_spec, {
    it("parses bitstrings literals", {
        parse("{<}", vector_new(FM_BITSTRING, string_new("0")));
        parse("({<})", vector_new(FM_BITSTRING, string_new("0")));
        parse("{<{<}, {<}}", vector_new(FM_LOCAL, string_new("Bit"), FM_BITSTRING, string_new("0"), FM_KEYWORD, string_new("value:"), string_new("1"), FM_LOCAL, string_new("Bit"), FM_BITSTRING, string_new("0"), FM_KEYWORD, string_new("value:"), string_new("1"), FM_BITSTRING, string_new("2")));
        parse("{<41, 42}", vector_new(FM_LOCAL, string_new("Bit"), FM_INTEGER, string_new("41"), FM_KEYWORD, string_new("value:"), string_new("1"), FM_LOCAL, string_new("Bit"), FM_INTEGER, string_new("42"), FM_KEYWORD, string_new("value:"), string_new("1"), FM_BITSTRING, string_new("2")));
        parse("({<41, 42})", vector_new(FM_LOCAL, string_new("Bit"), FM_INTEGER, string_new("41"), FM_KEYWORD, string_new("value:"), string_new("1"), FM_LOCAL, string_new("Bit"), FM_INTEGER, string_new("42"), FM_KEYWORD, string_new("value:"), string_new("1"), FM_BITSTRING, string_new("2")));
        parse("{<42, \"str\", var}", vector_new(FM_LOCAL, string_new("Bit"), FM_INTEGER, string_new("42"), FM_KEYWORD, string_new("value:"), string_new("1"), FM_LOCAL, string_new("Bit"), FM_STRING, string_new("str"), FM_KEYWORD, string_new("value:"), string_new("1"), FM_LOCAL, string_new("Bit"), FM_LOCAL, string_new("var"), FM_KEYWORD, string_new("value:"), string_new("1"), FM_BITSTRING, string_new("3")));
        parse("{<0:1, 0:1, 1:1, 1:1}", vector_new(FM_LOCAL, string_new("Bit"), FM_INTEGER, string_new("0"), FM_INTEGER, string_new("1"), FM_KEYWORD, string_new("value:size:"), string_new("2"), FM_LOCAL, string_new("Bit"), FM_INTEGER, string_new("0"), FM_INTEGER, string_new("1"), FM_KEYWORD, string_new("value:size:"), string_new("2"), FM_LOCAL, string_new("Bit"), FM_INTEGER, string_new("1"), FM_INTEGER, string_new("1"), FM_KEYWORD, string_new("value:size:"), string_new("2"), FM_LOCAL, string_new("Bit"), FM_INTEGER, string_new("1"), FM_INTEGER, string_new("1"), FM_KEYWORD, string_new("value:size:"), string_new("2"), FM_BITSTRING, string_new("4")));
        parse("{<3:4}", vector_new(FM_LOCAL, string_new("Bit"), FM_INTEGER, string_new("3"), FM_INTEGER, string_new("4"), FM_KEYWORD, string_new("value:size:"), string_new("2"), FM_BITSTRING, string_new("1")));
    });
})

#endif
