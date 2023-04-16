#ifndef __CONSTANTS_SPEC_H_
#define __CONSTANTS_SPEC_H_

#include "../_helpers.h"

module(constants_spec, {
    it("parses constants", {
        parse("(b = true)", marg_vector_new(OP_TRUE, OP_STORE, marg_string_new("b")));
        parse("(b = false)", marg_vector_new(OP_FALSE, OP_STORE, marg_string_new("b")));
        parse("(x = nil)", marg_vector_new(OP_NIL, OP_STORE, marg_string_new("x")));

        parse("(x = 1)", marg_vector_new(OP_1, OP_STORE, marg_string_new("x")));
        parse("(x = -1)", marg_vector_new(OP_MINUS_1, OP_STORE, marg_string_new("x")));
        parse("(x = 3.14159)", marg_vector_new(OP_FLOAT, marg_string_new("3.14159"), OP_STORE, marg_string_new("x")));
        parse("(x = 0.42)", marg_vector_new(OP_FLOAT, marg_string_new("0.42"), OP_STORE, marg_string_new("x")));
        parse("(x = 0xbeef)", marg_vector_new(OP_INTEGER, marg_string_new("48879"), OP_STORE, marg_string_new("x")));
        parse("(x = 0b0101)", marg_vector_new(OP_INTEGER, marg_string_new("5"), OP_STORE, marg_string_new("x")));
        parse("(x = 0o741)", marg_vector_new(OP_INTEGER, marg_string_new("481"), OP_STORE, marg_string_new("x")));

        parse("(x = \"Hello\")", marg_vector_new(OP_STRING, marg_string_new("Hello"), OP_STORE, marg_string_new("x")));
    });
})

#endif
