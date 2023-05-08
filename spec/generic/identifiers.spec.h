#ifndef __IDENTIFIERS_SPEC_H_
#define __IDENTIFIERS_SPEC_H_

#include "../_helpers.h"

module(identifiers_spec, {
    it("parses identifiers", {
        parse("(ident, 42, another)", vector_new(FM_LOCAL, string_new("ident"), FM_INTEGER, string_new("42"), FM_LOCAL, string_new("another")));
        parse("(stuff,ident2)", vector_new(FM_LOCAL, string_new("stuff"), FM_LOCAL, string_new("ident2")));
    });

    it("parses normal and instance variables", {
        parse("variable", vector_new(FM_LOCAL, string_new("variable")));
        parse("@instvar", vector_new(FM_INSTANCE, string_new("instvar")));
        parse("@x", vector_new(FM_INSTANCE, string_new("x")));
    });

    it("parses pseudo variables (used as normal identifiers)", {
        parse("$nil", vector_new(FM_NIL));
        parse("$true", vector_new(FM_TRUE));
        parse("$false", vector_new(FM_FALSE));
        parse("@self", vector_new(FM_SELF));
        parse("@super", vector_new(FM_SUPER));
    });
})

#endif
