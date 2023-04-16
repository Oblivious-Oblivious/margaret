#ifndef __INTERVALS_SPEC_H_
#define __INTERVALS_SPEC_H_

#include "../_helpers.h"

module(intervals_spec, {
    it("parses intervals", {
        parse("(x = Interval from: 5 to: 10)", marg_vector_new(FM_VARIABLE, marg_string_new("Interval"), FM_INTEGER, marg_string_new("5"), FM_INTEGER, marg_string_new("10"), FM_KEYWORD, marg_string_new("from:to:"), marg_string_new("2"), FM_STORE, marg_string_new("x")));
        parse("(x = Interval from: 5 to: 10 by: 2)", marg_vector_new(FM_VARIABLE, marg_string_new("Interval"), FM_INTEGER, marg_string_new("5"), FM_INTEGER, marg_string_new("10"), FM_2, FM_KEYWORD, marg_string_new("from:to:by:"), marg_string_new("3"), FM_STORE, marg_string_new("x")));
        parse("(x = 5 to: 10)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_INTEGER, marg_string_new("10"), FM_KEYWORD, marg_string_new("to:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = 5 to: 10 by: 2)", marg_vector_new(FM_INTEGER, marg_string_new("5"), FM_INTEGER, marg_string_new("10"), FM_2, FM_KEYWORD, marg_string_new("to:by:"), marg_string_new("2"), FM_STORE, marg_string_new("x")));
    });
})

#endif
