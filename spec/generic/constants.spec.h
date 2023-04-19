#ifndef __CONSTANTS_SPEC_H_
#define __CONSTANTS_SPEC_H_

#include "../_helpers.h"

module(constants_spec, {
    it("parses constants", {
        parse("(b = true)", marg_vector_new(FM_TRUE, FM_STORE, marg_string_new("b")));
        parse("(b = false)", marg_vector_new(FM_FALSE, FM_STORE, marg_string_new("b")));
        parse("(x = nil)", marg_vector_new(FM_NIL, FM_STORE, marg_string_new("x")));

        parse("(x = 1)", marg_vector_new(FM_INTEGER, marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = -1)", marg_vector_new(FM_INTEGER, marg_string_new("-1"), FM_STORE, marg_string_new("x")));
        parse("(x = 3.14159)", marg_vector_new(FM_FLOAT, marg_string_new("3.14159"), FM_STORE, marg_string_new("x")));
        parse("(x = 0.42)", marg_vector_new(FM_FLOAT, marg_string_new("0.42"), FM_STORE, marg_string_new("x")));
        parse("(x = 0xbeef)", marg_vector_new(FM_INTEGER, marg_string_new("48879"), FM_STORE, marg_string_new("x")));
        parse("(x = 0b0101)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_STORE, marg_string_new("x")));
        parse("(x = 0o741)", marg_vector_new(FM_INTEGER, marg_string_new("481"), FM_STORE, marg_string_new("x")));

        parse("(x = \"Hello\")", marg_vector_new(FM_STRING, marg_string_new("Hello"), FM_STORE, marg_string_new("x")));
    });
})

#endif
