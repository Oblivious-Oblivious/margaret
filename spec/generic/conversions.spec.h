#ifndef __CONVERSIONS_SPEC_H_
#define __CONVERSIONS_SPEC_H_

#include "../_helpers.h"

module(conversions_spec, {
    it("parses object conversion", {
        parse("(x = 3.99 to_int)", vector_new(FM_FLOAT, string_new("3.99"), FM_UNARY, string_new("to_int"), FM_STORE, string_new("x")));
        parse("(x = 3.99 to_fraction)", vector_new(FM_FLOAT, string_new("3.99"), FM_UNARY, string_new("to_fraction"), FM_STORE, string_new("x")));
        parse("(x = 3 to_float)", vector_new(FM_INTEGER, string_new("3"), FM_UNARY, string_new("to_float"), FM_STORE, string_new("x")));
        parse("(x = 65 to_char)", vector_new(FM_INTEGER, string_new("65"), FM_UNARY, string_new("to_char"), FM_STORE, string_new("x")));
        parse("(x = \"A\" to_ascii)", vector_new(FM_STRING, string_new("A"), FM_UNARY, string_new("to_ascii"), FM_STORE, string_new("x")));
        parse("(x = 'b' to_ascii)", vector_new(FM_CHAR, string_new("b"), FM_UNARY, string_new("to_ascii"), FM_STORE, string_new("x")));
    });
})

#endif
