#ifndef __META_EVALUATION_SPEC_H_
#define __META_EVALUATION_SPEC_H_

#include "../_helpers.h"

module(meta_evaluation_spec, {
    it("compiles and calls messages dynamically", {
        // NOTE Figure out dynamic send
    });

    it("parses metaclass messages", {
        parse("(x = String name)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("name"), OP_STORE, marg_string_new("x")));
        parse("(x = String category)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("category"), OP_STORE, marg_string_new("x")));
        parse("(x = String description)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("description"), OP_STORE, marg_string_new("x")));
        parse("(x = String kind_of_subclass)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("kind_of_subclass"), OP_STORE, marg_string_new("x")));
        parse("(x = String definition)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("definition"), OP_STORE, marg_string_new("x")));
        parse("(x = String field_names)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("field_names"), OP_STORE, marg_string_new("x")));
        parse("(x = String all_field_names)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("all_field_names"), OP_STORE, marg_string_new("x")));
        parse("(x = String selectors)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("selectors"), OP_STORE, marg_string_new("x")));
        parse("(x = String source_code_at: \"message\")", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_PUSH_STRING, marg_string_new("message"), OP_KEYWORD, marg_string_new("source_code_at:"), marg_string_new("1"), OP_STORE, marg_string_new("x")));
        parse("(x = String all_instances)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("all_instances"), OP_STORE, marg_string_new("x")));
        parse("(x = String superclass)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("superclass"), OP_STORE, marg_string_new("x")));
        parse("(x = String all_superclasses)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("all_superclasses"), OP_STORE, marg_string_new("x")));
        parse("(x = String subclasses)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("subclasses"), OP_STORE, marg_string_new("x")));
        parse("(x = String all_subclasses)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("all_subclasses"), OP_STORE, marg_string_new("x")));
        parse("(x = String number_of_instances)", marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("String"), OP_UNARY, marg_string_new("number_of_instances"), OP_STORE, marg_string_new("x")));
    });
})

#endif
