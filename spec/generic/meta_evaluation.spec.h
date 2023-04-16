#ifndef __META_EVALUATION_SPEC_H_
#define __META_EVALUATION_SPEC_H_

#include "../_helpers.h"

module(meta_evaluation_spec, {
    it("compiles and calls messages dynamically", {
        // NOTE Figure out dynamic send
    });

    it("parses metaclass messages", {
        parse("(x = String name)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("name"), FM_STORE, marg_string_new("x")));
        parse("(x = String category)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("category"), FM_STORE, marg_string_new("x")));
        parse("(x = String description)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("description"), FM_STORE, marg_string_new("x")));
        parse("(x = String kind_of_subclass)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("kind_of_subclass"), FM_STORE, marg_string_new("x")));
        parse("(x = String definition)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("definition"), FM_STORE, marg_string_new("x")));
        parse("(x = String field_names)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("field_names"), FM_STORE, marg_string_new("x")));
        parse("(x = String all_field_names)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("all_field_names"), FM_STORE, marg_string_new("x")));
        parse("(x = String selectors)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("selectors"), FM_STORE, marg_string_new("x")));
        parse("(x = String source_code_at: \"message\")", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_STRING, marg_string_new("message"), FM_KEYWORD, marg_string_new("source_code_at:"), marg_string_new("1"), FM_STORE, marg_string_new("x")));
        parse("(x = String all_instances)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("all_instances"), FM_STORE, marg_string_new("x")));
        parse("(x = String superclass)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("superclass"), FM_STORE, marg_string_new("x")));
        parse("(x = String all_superclasses)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("all_superclasses"), FM_STORE, marg_string_new("x")));
        parse("(x = String subclasses)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("subclasses"), FM_STORE, marg_string_new("x")));
        parse("(x = String all_subclasses)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("all_subclasses"), FM_STORE, marg_string_new("x")));
        parse("(x = String number_of_instances)", marg_vector_new(FM_VARIABLE, marg_string_new("String"), FM_UNARY, marg_string_new("number_of_instances"), FM_STORE, marg_string_new("x")));
    });
})

#endif
