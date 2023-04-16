#ifndef __COMPLEX_SPEC_H_
#define __COMPLEX_SPEC_H_

#include "../_helpers.h"

module(complex_spec, {
    it("parses complex literals", {
        parse("1i", marg_vector_new(FM_1, FM_UNARY, marg_string_new("i")));
        parse("1i * 1i", marg_vector_new(FM_1, FM_UNARY, marg_string_new("i"), FM_1, FM_UNARY, marg_string_new("i"), FM_BINARY, marg_string_new("*")));
        parse("12.3r i", marg_vector_new(FM_FLOAT, marg_string_new("12.3"), FM_UNARY, marg_string_new("r"), FM_UNARY, marg_string_new("i")));
    });

    it("parses complex literal messages", {
        // TODO
    });
})

#endif
