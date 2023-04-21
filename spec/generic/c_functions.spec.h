#ifndef __C_FUNCTIONS_SPEC_H_
#define __C_FUNCTIONS_SPEC_H_

#include "../_helpers.h"

module(c_functions_spec, {
    it("parses C function definitions", {
        parse("###void f()", vector_new(FM_START_C_FUNCTION, FM_VARIABLE, string_new("void"), FM_VARIABLE, string_new("f"), FM_TENSOR, string_new("0"), FM_END_C_FUNCTION));
        parse("###void f2(int a, int b)", vector_new(FM_START_C_FUNCTION, FM_VARIABLE, string_new("void"), FM_VARIABLE, string_new("f2"), FM_VARIABLE, string_new("CFunParam"), FM_VARIABLE, string_new("int"), FM_VARIABLE, string_new("a"), FM_KEYWORD, string_new("c_type:c_name:"), string_new("2"), FM_VARIABLE, string_new("CFunParam"), FM_VARIABLE, string_new("int"), FM_VARIABLE, string_new("b"), FM_KEYWORD, string_new("c_type:c_name:"), string_new("2"), FM_TENSOR, string_new("2"), FM_END_C_FUNCTION));
        parse("###int f3(void)", vector_new(FM_START_C_FUNCTION, FM_VARIABLE, string_new("int"), FM_VARIABLE, string_new("f3"), FM_TENSOR, string_new("0"), FM_END_C_FUNCTION));
        parse("###void *f4(int *a, int b, char *c)", vector_new(FM_START_C_FUNCTION, FM_VARIABLE, string_new("void*"), FM_VARIABLE, string_new("f4"), FM_VARIABLE, string_new("CFunParam"), FM_VARIABLE, string_new("int*"), FM_VARIABLE, string_new("a"), FM_KEYWORD, string_new("c_type:c_name:"), string_new("2"), FM_VARIABLE, string_new("CFunParam"), FM_VARIABLE, string_new("int"), FM_VARIABLE, string_new("b"), FM_KEYWORD, string_new("c_type:c_name:"), string_new("2"), FM_VARIABLE, string_new("CFunParam"), FM_VARIABLE, string_new("char*"), FM_VARIABLE, string_new("c"), FM_KEYWORD, string_new("c_type:c_name:"), string_new("2"), FM_TENSOR, string_new("3"), FM_END_C_FUNCTION));
        parse("###void **f5(int ***a, int b, char *c)", vector_new(FM_START_C_FUNCTION, FM_VARIABLE, string_new("void**"), FM_VARIABLE, string_new("f5"), FM_VARIABLE, string_new("CFunParam"), FM_VARIABLE, string_new("int***"), FM_VARIABLE, string_new("a"), FM_KEYWORD, string_new("c_type:c_name:"), string_new("2"), FM_VARIABLE, string_new("CFunParam"), FM_VARIABLE, string_new("int"), FM_VARIABLE, string_new("b"), FM_KEYWORD, string_new("c_type:c_name:"), string_new("2"), FM_VARIABLE, string_new("CFunParam"), FM_VARIABLE, string_new("char*"), FM_VARIABLE, string_new("c"), FM_KEYWORD, string_new("c_type:c_name:"), string_new("2"), FM_TENSOR, string_new("3"), FM_END_C_FUNCTION));
        // TODO Creates matchers and extensions at compile time
    });
})

#endif
