#ifndef __BITWISE_SPEC_H_
#define __BITWISE_SPEC_H_

#include "../_helpers.h"

module(bitwise_spec, {
    it("parses bitwise operations", {
        parse("(x = 0xff bitand: 0x0f)", marg_vector_new(OP_INTEGER, marg_string_new("255"), OP_INTEGER, marg_string_new("15"), OP_KEYWORD, marg_string_new("bitand:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 0xf0 bitor: 0x0f)", marg_vector_new(OP_INTEGER, marg_string_new("240"), OP_INTEGER, marg_string_new("15"), OP_KEYWORD, marg_string_new("bitor:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 0xff bitxor: 0x0f)", marg_vector_new(OP_INTEGER, marg_string_new("255"), OP_INTEGER, marg_string_new("15"), OP_KEYWORD, marg_string_new("bitxor:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 0xff bitinvert)", marg_vector_new(OP_INTEGER, marg_string_new("255"), OP_UNARY, marg_string_new("bitinvert"), OP_STORE, marg_string_new("x")));
        parse("(x = 0x0f bitshift: 4)", marg_vector_new(OP_INTEGER, marg_string_new("15"), OP_INTEGER, marg_string_new("4"), OP_KEYWORD, marg_string_new("bitshift:"), marg_string_new("1"), OP_STORE, marg_string_new("x"))); // Left shift
        parse("(x = 0xf0 bitshift: -4)", marg_vector_new(OP_INTEGER, marg_string_new("240"), OP_INTEGER, marg_string_new("-4"), OP_KEYWORD, marg_string_new("bitshift:"), marg_string_new("1"), OP_STORE, marg_string_new("x"))); // Right shift
        parse("(x = 0x80 highbit)", marg_vector_new(OP_INTEGER, marg_string_new("128"), OP_UNARY, marg_string_new("highbit"), OP_STORE, marg_string_new("x")));
        parse("(x = 0xff all_mask: 0x0f)", marg_vector_new(OP_INTEGER, marg_string_new("255"), OP_INTEGER, marg_string_new("15"), OP_KEYWORD, marg_string_new("all_mask:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 0xff any_mask: 0x0f)", marg_vector_new(OP_INTEGER, marg_string_new("255"), OP_INTEGER, marg_string_new("15"), OP_KEYWORD, marg_string_new("any_mask:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = 0xff no_mask: 0x0f)", marg_vector_new(OP_INTEGER, marg_string_new("255"), OP_INTEGER, marg_string_new("15"), OP_KEYWORD, marg_string_new("no_mask:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
    });
})

#endif
