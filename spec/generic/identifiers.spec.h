#ifndef __IDENTIFIERS_SPEC_H_
#define __IDENTIFIERS_SPEC_H_

#include "../_helpers.h"

module(identifiers_spec, {
    it("parses identifiers", {
        parse("(ident, 42, another)", marg_vector_new(FM_VARIABLE, marg_string_new("ident"), FM_INTEGER, marg_string_new("42"), FM_VARIABLE, marg_string_new("another")));
        parse("(stuff,ident2)", marg_vector_new(FM_VARIABLE, marg_string_new("stuff"), FM_VARIABLE, marg_string_new("ident2")));
    });

    it("parses normal and instance variables", {
        parse("variable", marg_vector_new(FM_VARIABLE, marg_string_new("variable")));
        parse("@instvar", marg_vector_new(FM_INSTANCE, marg_string_new("instvar")));
        parse("@x", marg_vector_new(FM_INSTANCE, marg_string_new("x")));
    });

    it("parses pseudo variables (used as normal identifiers)", {
        parse("nil", marg_vector_new(FM_NIL));
        parse("true", marg_vector_new(FM_TRUE));
        parse("false", marg_vector_new(FM_FALSE));
        parse("self", marg_vector_new(FM_SELF));
        parse("super", marg_vector_new(FM_SUPER));
    });
})

#endif
