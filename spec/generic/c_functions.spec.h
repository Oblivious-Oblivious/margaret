#ifndef __C_FUNCTIONS_SPEC_H_
#define __C_FUNCTIONS_SPEC_H_

#include "../_helpers.h"

module(c_functions_spec, {
    it("parses C function definitions", {
        parse("###void f()", marg_vector_new(FM_START_C_FUNCTION, FM_VARIABLE, marg_string_new("void"), FM_VARIABLE, marg_string_new("f"), FM_TENSOR, marg_string_new("0"), FM_END_C_FUNCTION));
        parse("###void f2(int a, int b)", marg_vector_new(FM_START_C_FUNCTION, FM_VARIABLE, marg_string_new("void"), FM_VARIABLE, marg_string_new("f2"), FM_VARIABLE, marg_string_new("CFunParam"), FM_VARIABLE, marg_string_new("int"), FM_VARIABLE, marg_string_new("a"), FM_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("CFunParam"), FM_VARIABLE, marg_string_new("int"), FM_VARIABLE, marg_string_new("b"), FM_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), FM_TENSOR, marg_string_new("2"), FM_END_C_FUNCTION));
        parse("###int f3(void)", marg_vector_new(FM_START_C_FUNCTION, FM_VARIABLE, marg_string_new("int"), FM_VARIABLE, marg_string_new("f3"), FM_TENSOR, marg_string_new("0"), FM_END_C_FUNCTION));
        parse("###void *f4(int *a, int b, char *c)", marg_vector_new(FM_START_C_FUNCTION, FM_VARIABLE, marg_string_new("void*"), FM_VARIABLE, marg_string_new("f4"), FM_VARIABLE, marg_string_new("CFunParam"), FM_VARIABLE, marg_string_new("int*"), FM_VARIABLE, marg_string_new("a"), FM_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("CFunParam"), FM_VARIABLE, marg_string_new("int"), FM_VARIABLE, marg_string_new("b"), FM_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("CFunParam"), FM_VARIABLE, marg_string_new("char*"), FM_VARIABLE, marg_string_new("c"), FM_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), FM_TENSOR, marg_string_new("3"), FM_END_C_FUNCTION));
        parse("###void **f5(int ***a, int b, char *c)", marg_vector_new(FM_START_C_FUNCTION, FM_VARIABLE, marg_string_new("void**"), FM_VARIABLE, marg_string_new("f5"), FM_VARIABLE, marg_string_new("CFunParam"), FM_VARIABLE, marg_string_new("int***"), FM_VARIABLE, marg_string_new("a"), FM_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("CFunParam"), FM_VARIABLE, marg_string_new("int"), FM_VARIABLE, marg_string_new("b"), FM_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), FM_VARIABLE, marg_string_new("CFunParam"), FM_VARIABLE, marg_string_new("char*"), FM_VARIABLE, marg_string_new("c"), FM_KEYWORD, marg_string_new("c_type:c_name:"), marg_string_new("2"), FM_TENSOR, marg_string_new("3"), FM_END_C_FUNCTION));
        // TODO Creates matchers and extensions at compile time
    });
})

#endif
