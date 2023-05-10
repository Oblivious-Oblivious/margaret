#ifndef __TENSORS_SPEC_H_
#define __TENSORS_SPEC_H_

#include "../_helpers.h"

module(tensors_spec, {
    it("parses tensor literals", {
        parse("[]", vector_new(FM_TENSOR, string_new("0"), FM_POP));
        parse("([])", vector_new(FM_TENSOR, string_new("0"), FM_POP));
        parse("[[], []]", vector_new(FM_TENSOR, string_new("0"), FM_TENSOR, string_new("0"), FM_TENSOR, string_new("2"), FM_POP));
        parse("[41, 42]", vector_new(FM_INTEGER, string_new("41"), FM_INTEGER, string_new("42"), FM_TENSOR, string_new("2"), FM_POP));
        parse("([41, 42])", vector_new(FM_INTEGER, string_new("41"), FM_INTEGER, string_new("42"), FM_TENSOR, string_new("2"), FM_POP));
        parse("[42, \"str\", var]", vector_new(FM_INTEGER, string_new("42"), FM_STRING, string_new("str"), FM_LOCAL, string_new("var"), FM_TENSOR, string_new("3"), FM_POP));
        parse("[42, \"Hello\", v1, v2]", vector_new(FM_INTEGER, string_new("42"), FM_STRING, string_new("Hello"), FM_LOCAL, string_new("v1"), FM_LOCAL, string_new("v2"), FM_TENSOR, string_new("4"), FM_POP));
        parse("[42, \"Hello\", v1, v2, (), [], {}, x = 1]", vector_new( \
            FM_INTEGER, string_new("42"), \
            FM_STRING, string_new("Hello"), \
            FM_LOCAL, string_new("v1"), \
            FM_LOCAL, string_new("v2"), \
            FM_NIL, \
            FM_TENSOR, string_new("0"), \
            FM_HASH, string_new("0"), \
            FM_INTEGER, string_new("1"), FM_STORE_LOCAL, string_new("x"), \
            FM_TENSOR, string_new("8"), \
            FM_POP \
        ));
    });
})

#endif
