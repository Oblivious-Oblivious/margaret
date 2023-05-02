#ifndef __CONSTANTS_SPEC_H_
#define __CONSTANTS_SPEC_H_

#include "../_helpers.h"

module(constants_spec, {
    it("parses constants", {
        parse("(b = $true)", vector_new(FM_TRUE, FM_STORE_LOCAL, string_new("b")));
        parse("(b = $false)", vector_new(FM_FALSE, FM_STORE_LOCAL, string_new("b")));
        parse("(x = $nil)", vector_new(FM_NIL, FM_STORE_LOCAL, string_new("x")));
        parse("true = 123", vector_new(FM_INTEGER, string_new("123"), FM_STORE_LOCAL, string_new("true")));
        parse("false = 123", vector_new(FM_INTEGER, string_new("123"), FM_STORE_LOCAL, string_new("false")));
        parse("nil = 123", vector_new(FM_INTEGER, string_new("123"), FM_STORE_LOCAL, string_new("nil")));

        parse("(x = 1)", vector_new(FM_INTEGER, string_new("1"), FM_STORE_LOCAL, string_new("x")));
        parse("(x = -1)", vector_new(FM_INTEGER, string_new("-1"), FM_STORE_LOCAL, string_new("x")));
        parse("(x = 3.14159)", vector_new(FM_FLOAT, string_new("3.14159"), FM_STORE_LOCAL, string_new("x")));
        parse("(x = 0.42)", vector_new(FM_FLOAT, string_new("0.42"), FM_STORE_LOCAL, string_new("x")));
        parse("(x = 0xbeef)", vector_new(FM_INTEGER, string_new("48879"), FM_STORE_LOCAL, string_new("x")));
        parse("(x = 0b0101)", vector_new(FM_INTEGER, string_new("5"), FM_STORE_LOCAL, string_new("x")));
        parse("(x = 0o741)", vector_new(FM_INTEGER, string_new("481"), FM_STORE_LOCAL, string_new("x")));

        parse("(x = \"Hello\")", vector_new(FM_STRING, string_new("Hello"), FM_STORE_LOCAL, string_new("x")));
    });
})

#endif
