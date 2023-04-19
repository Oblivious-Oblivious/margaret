#ifndef __RATIONAL_SPEC_H_
#define __RATIONAL_SPEC_H_

#include "../_helpers.h"

module(rational_spec, {
    it("parses rational literals", {
        parse("1r", marg_vector_new(FM_INTEGER, marg_string_new("1"), FM_UNARY, marg_string_new("r")));
        parse("2/3r", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("3"), FM_UNARY, marg_string_new("r"), FM_BINARY, marg_string_new("/")));
        parse("-1r", marg_vector_new(FM_INTEGER, marg_string_new("-1"), FM_UNARY, marg_string_new("r")));
        parse("-2/3r", marg_vector_new(FM_INTEGER, marg_string_new("-2"), FM_INTEGER, marg_string_new("3"), FM_UNARY, marg_string_new("r"), FM_BINARY, marg_string_new("/")));
        // TODO Separate `-` message on its own token (avoids `-/` or `/-`)
        parse("2/(-3r)", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("-3"), FM_UNARY, marg_string_new("r"), FM_BINARY, marg_string_new("/")));
        parse("-2/(-3r)", marg_vector_new(FM_INTEGER, marg_string_new("-2"), FM_INTEGER, marg_string_new("-3"), FM_UNARY, marg_string_new("r"), FM_BINARY, marg_string_new("/")));
        parse("+1 / (+3r)", marg_vector_new(FM_INTEGER, marg_string_new("1"), FM_INTEGER, marg_string_new("3"), FM_UNARY, marg_string_new("r"), FM_BINARY, marg_string_new("/")));
        parse("1.2r", marg_vector_new(FM_FLOAT, marg_string_new("1.2"), FM_UNARY, marg_string_new("r")));
        parse("1_1/2_2r", marg_vector_new(FM_INTEGER, marg_string_new("11"), FM_INTEGER, marg_string_new("22"), FM_UNARY, marg_string_new("r"), FM_BINARY, marg_string_new("/")));
        parse("2/4r", marg_vector_new(FM_INTEGER, marg_string_new("2"), FM_INTEGER, marg_string_new("4"), FM_UNARY, marg_string_new("r"), FM_BINARY, marg_string_new("/")));
    });

    it("parses rational literal messages", {
        // TODO
    });
})

#endif
