#ifndef __INSPECTOR_SPEC_H_
#define __INSPECTOR_SPEC_H_

#include "../../src/inspector/Inspector.h"
#include "../cSpec.h"

#include "../../src/opcode/Opcodes.h"

module(InspectorSpec, {
    // TODO Test for a `postcard` type mini program that includes every single feature
    it("prints a list of emmitted opcodes", {
        Chunk *bytecode = chunk_new_empty();
        int constant = chunk_add_constant(bytecode, 1.2);
        chunk_add(bytecode, OP_CONSTANT);
        chunk_add(bytecode, constant);
        chunk_add(bytecode, OP_RETURN);

        marg_vector *res = inspect_chunk(bytecode);
        assert_that_charptr(marg_string_get(marg_vector_get(res, 0)) equals to "0000       123      04 00       CONSTANT         0 (1.2)");
        assert_that_charptr(marg_string_get(marg_vector_get(res, 1)) equals to "0002         |      00          RETURN");

        // for(size_t i = 0; i < marg_vector_size(res); i++)
        //     printf("%s\n", marg_string_get(marg_vector_get(res, i)));
    });
})

#endif
