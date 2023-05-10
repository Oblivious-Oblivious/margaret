#ifndef __BITWISE_SPEC_H_
#define __BITWISE_SPEC_H_

#include "../_helpers.h"

module(bitwise_spec, {
    it("parses bitwise operations", {
        parse("(x = 0xff bitand: 0x0f)", vector_new(FM_INTEGER, string_new("255"), FM_INTEGER, string_new("15"), FM_KEYWORD, string_new("bitand:"), string_new("1"), FM_STORE_LOCAL, string_new("x"), FM_POP));
        parse("(x = 0xf0 bitor: 0x0f)", vector_new(FM_INTEGER, string_new("240"), FM_INTEGER, string_new("15"), FM_KEYWORD, string_new("bitor:"), string_new("1"), FM_STORE_LOCAL, string_new("x"), FM_POP));
        parse("(x = 0xff bitxor: 0x0f)", vector_new(FM_INTEGER, string_new("255"), FM_INTEGER, string_new("15"), FM_KEYWORD, string_new("bitxor:"), string_new("1"), FM_STORE_LOCAL, string_new("x"), FM_POP));
        parse("(x = 0xff bitinvert)", vector_new(FM_INTEGER, string_new("255"), FM_UNARY, string_new("bitinvert"), FM_STORE_LOCAL, string_new("x"), FM_POP));
        parse("(x = 0x0f bitshift: 4)", vector_new(FM_INTEGER, string_new("15"), FM_INTEGER, string_new("4"), FM_KEYWORD, string_new("bitshift:"), string_new("1"), FM_STORE_LOCAL, string_new("x"), FM_POP)); // Left shift
        parse("(x = 0xf0 bitshift: -4)", vector_new(FM_INTEGER, string_new("240"), FM_INTEGER, string_new("-4"), FM_KEYWORD, string_new("bitshift:"), string_new("1"), FM_STORE_LOCAL, string_new("x"), FM_POP)); // Right shift
        parse("(x = 0x80 highbit)", vector_new(FM_INTEGER, string_new("128"), FM_UNARY, string_new("highbit"), FM_STORE_LOCAL, string_new("x"), FM_POP));
        parse("(x = 0xff all_mask: 0x0f)", vector_new(FM_INTEGER, string_new("255"), FM_INTEGER, string_new("15"), FM_KEYWORD, string_new("all_mask:"), string_new("1"), FM_STORE_LOCAL, string_new("x"), FM_POP));
        parse("(x = 0xff any_mask: 0x0f)", vector_new(FM_INTEGER, string_new("255"), FM_INTEGER, string_new("15"), FM_KEYWORD, string_new("any_mask:"), string_new("1"), FM_STORE_LOCAL, string_new("x"), FM_POP));
        parse("(x = 0xff no_mask: 0x0f)", vector_new(FM_INTEGER, string_new("255"), FM_INTEGER, string_new("15"), FM_KEYWORD, string_new("no_mask:"), string_new("1"), FM_STORE_LOCAL, string_new("x"), FM_POP));
    });
})

#endif
