#ifndef __C_FUNCTIONS_SPEC_H_
#define __C_FUNCTIONS_SPEC_H_

#include "../_helpers.h"

module(c_functions_spec, {
    it("parses C function definitions", {
        parse("###void f()", marg_vector_new(OP_START_PUSH_C_FUNCTION, OP_PUSH_VARIABLE, marg_string_new("void"), OP_PUSH_VARIABLE, marg_string_new("f"), OP_PUSH_TENSOR, marg_string_new("0"), OP_END_PUSH_C_FUNCTION));
        parse("###void f2(int a, int b)", marg_vector_new(OP_START_PUSH_C_FUNCTION, OP_PUSH_VARIABLE, marg_string_new("void"), OP_PUSH_VARIABLE, marg_string_new("f2"), OP_PUSH_VARIABLE, marg_string_new("CFunParam"), OP_PUSH_VARIABLE, marg_string_new("int"), OP_PUSH_VARIABLE, marg_string_new("a"), OP_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), OP_PUSH_VARIABLE, marg_string_new("CFunParam"), OP_PUSH_VARIABLE, marg_string_new("int"), OP_PUSH_VARIABLE, marg_string_new("b"), OP_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), OP_PUSH_TENSOR, marg_string_new("2"), OP_END_PUSH_C_FUNCTION));
        // TODO Creates matchers and extensions at compile time
    });
})

#endif
