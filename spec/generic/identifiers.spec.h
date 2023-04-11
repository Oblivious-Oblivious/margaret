#ifndef __IDENTIFIERS_SPEC_H_
#define __IDENTIFIERS_SPEC_H_

#include "../_helpers.h"

module(identifiers_spec, {
    it("parses identifiers", {
        parse("(ident, 42, another)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("ident"), OP_PUSH_INTEGER, marg_string_new("42"), OP_PUSH_VARIABLE, marg_string_new("another")));
        parse("(stuff,ident2)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("stuff"), OP_PUSH_VARIABLE, marg_string_new("ident2")));
    });

    it("parses normal and instance variables", {
        parse("variable", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("variable")));
        parse("@instvar", marg_vector_new(OP_PUSH_INSTANCE, marg_string_new("instvar")));
        parse("@x", marg_vector_new(OP_PUSH_INSTANCE, marg_string_new("x")));
    });

    it("parses pseudo variables (used as normal identifiers)", {
        parse("nil", marg_vector_new(OP_PUSH_NIL));
        parse("true", marg_vector_new(OP_PUSH_TRUE));
        parse("false", marg_vector_new(OP_PUSH_FALSE));
        parse("self", marg_vector_new(OP_PUSH_SELF));
        parse("super", marg_vector_new(OP_PUSH_SUPER));
    });
})

#endif