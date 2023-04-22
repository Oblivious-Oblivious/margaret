#ifndef __INTERVALS_SPEC_H_
#define __INTERVALS_SPEC_H_

#include "../_helpers.h"

module(intervals_spec, {
    it("parses intervals", {
        parse("(x = Interval from: 5 to: 10)", vector_new(FM_LOCAL, string_new("Interval"), FM_INTEGER, string_new("5"), FM_INTEGER, string_new("10"), FM_KEYWORD, string_new("from:to:"), string_new("2"), FM_STORE_LOCAL, string_new("x")));
        parse("(x = Interval from: 5 to: 10 by: 2)", vector_new(FM_LOCAL, string_new("Interval"), FM_INTEGER, string_new("5"), FM_INTEGER, string_new("10"), FM_INTEGER, string_new("2"), FM_KEYWORD, string_new("from:to:by:"), string_new("3"), FM_STORE_LOCAL, string_new("x")));
        parse("(x = 5 to: 10)", vector_new(FM_INTEGER, string_new("5"), FM_INTEGER, string_new("10"), FM_KEYWORD, string_new("to:"), string_new("1"), FM_STORE_LOCAL, string_new("x")));
        parse("(x = 5 to: 10 by: 2)", vector_new(FM_INTEGER, string_new("5"), FM_INTEGER, string_new("10"), FM_INTEGER, string_new("2"), FM_KEYWORD, string_new("to:by:"), string_new("2"), FM_STORE_LOCAL, string_new("x")));
    });
})

#endif
