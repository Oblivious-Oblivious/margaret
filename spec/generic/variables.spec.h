#ifndef __VARIABLES_SPEC_H_
#define __VARIABLES_SPEC_H_

#include "../_helpers.h"

module(variables_spec, {
    it("parses local variables", {
        parse("x", vector_new(FM_LOCAL, string_new("x")));
        parse("y", vector_new(FM_LOCAL, string_new("y")));
        parse("(x, y)", vector_new(FM_LOCAL, string_new("x"), FM_LOCAL, string_new("y")));
    });

    it("parses instance variables", {
        parse("@x", vector_new(FM_INSTANCE, string_new("x")));
        parse("@y", vector_new(FM_INSTANCE, string_new("y")));
        parse("(@x, @y, z)", vector_new(FM_INSTANCE, string_new("x"), FM_INSTANCE, string_new("y"), FM_LOCAL, string_new("z")));
    });

    it("parses global variables", {
        parse("$x", vector_new(FM_GLOBAL, string_new("x")));
        parse("$y", vector_new(FM_GLOBAL, string_new("y")));
        parse("($x, @y, z)", vector_new(FM_GLOBAL, string_new("x"), FM_INSTANCE, string_new("y"), FM_LOCAL, string_new("z")));
    });
})

#endif
