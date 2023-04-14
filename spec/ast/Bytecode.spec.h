#ifndef __BYTECODE_SPEC_H_
#define __BYTECODE_SPEC_H_

#include "../../src/ast/Bytecode.h"
#include "../../src/lexer/Lexer.h"
#include "../../src/parser/Parser.h"

#include "../_helpers.h"

module(BytecodeSpec, {
    it("emits for a simple message", {
        parse("2 + 3", marg_vector_new(
            OP_PUSH_2,
            OP_PUSH_INTEGER, marg_string_new("3"),
            OP_BINARY, marg_string_new("+")
        ));
    });
})

#endif
