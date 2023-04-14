#ifndef __COMPLEX_SPEC_H_
#define __COMPLEX_SPEC_H_

#include "../_helpers.h"

module(complex_spec, {
    it("parses complex literals", {
        parse("1i", marg_vector_new(OP_PUSH_1, OP_UNARY, marg_string_new("i")));
        parse("1i * 1i", marg_vector_new(OP_PUSH_1, OP_UNARY, marg_string_new("i"), OP_PUSH_1, OP_UNARY, marg_string_new("i"), OP_BINARY, marg_string_new("*")));
        parse("12.3r i", marg_vector_new(OP_PUSH_FLOAT, marg_string_new("12.3"), OP_UNARY, marg_string_new("r"), OP_UNARY, marg_string_new("i")));
    });

    it("parses complex literal messages", {
        // TODO
    });
})

#endif
