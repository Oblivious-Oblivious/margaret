#ifndef __INSPECTOR_SPEC_H_
#define __INSPECTOR_SPEC_H_

#include "../../src/inspector/Inspector.h"
#include "../cSpec.h"

#include "../../src/opcode/Opcodes.h"

module(InspectorSpec, {
    // TODO Test for a `postcard` type mini program that includes every single feature
    it("prints a list of emmitted opcodes", {
        Chunk *bytecode = chunk_new();
        chunk_add(bytecode, OP_NIL);
        chunk_add(bytecode, OP_NIL);
        chunk_add(bytecode, OP_TRUE);
        chunk_add(bytecode, OP_FALSE);
        chunk_add(bytecode, OP_NIL);
        chunk_add(bytecode, OP_RETURN);

        marg_vector *res = inspect_chunk(bytecode);
        assert_that_charptr(marg_string_get(marg_vector_get(res, 0)) equals to "0000    01          NIL");
        assert_that_charptr(marg_string_get(marg_vector_get(res, 1)) equals to "0001    01          NIL");
        assert_that_charptr(marg_string_get(marg_vector_get(res, 2)) equals to "0002    02          TRUE");
        assert_that_charptr(marg_string_get(marg_vector_get(res, 3)) equals to "0003    03          FALSE");
        assert_that_charptr(marg_string_get(marg_vector_get(res, 4)) equals to "0004    01          NIL");
        assert_that_charptr(marg_string_get(marg_vector_get(res, 5)) equals to "0005    00          RETURN");
    });
})

#endif
