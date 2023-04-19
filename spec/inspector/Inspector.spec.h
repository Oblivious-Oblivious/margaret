#ifndef __INSPECTOR_SPEC_H_
#define __INSPECTOR_SPEC_H_

#include "../../src/inspector/Inspector.h"
#include "../cSpec.h"

#include "../../src/opcode/Opcodes.h"

module(InspectorSpec, {
    // TODO Test for a `postcard` type mini program that includes every single feature

    // for(size_t i = 0; i < marg_vector_size(res); i++)
    //     printf("%s\n", marg_string_get(marg_vector_get(res, i)));

    it("prints a list of emmitted opcodes", {
        VM *vm = vm_new();
        Chunk *bytecode = vm->bytecode;

        uint8_t constant = chunk_add_constant(bytecode, MARG_NUMBER(0.7));
        chunk_add_with_line(bytecode, OP_CONSTANT, 123);
        chunk_add_with_line(bytecode, constant, 123);
        constant = chunk_add_constant(bytecode, MARG_NUMBER(0.8));
        chunk_add_with_line(bytecode, OP_CONSTANT, 123);
        chunk_add_with_line(bytecode, constant, 123);
        constant = chunk_add_constant(bytecode, MARG_NUMBER(0.9));
        chunk_add_with_line(bytecode, OP_CONSTANT, 123);
        chunk_add_with_line(bytecode, constant, 123);
        chunk_add_with_line(bytecode, OP_RETURN, 123);

        marg_vector *res = inspect_vm_bytecode(vm);
        assert_that_charptr(marg_string_get(marg_vector_get(res, 0)) equals to "0000       123      04 00               CONSTANT         0 (0.7)");
        assert_that_charptr(marg_string_get(marg_vector_get(res, 1)) equals to "0002         |      04 01               CONSTANT         1 (0.8)");
        assert_that_charptr(marg_string_get(marg_vector_get(res, 2)) equals to "0004         |      04 02               CONSTANT         2 (0.9)");
        assert_that_charptr(marg_string_get(marg_vector_get(res, 3)) equals to "0006         |      00                  RETURN");
    });

    it("tests multiple long constants", {
        VM *vm = vm_new();
        Chunk *bytecode = vm->bytecode;

        for(int i = 0; i <= 4000; i++) {
            uint32_t long_constant = chunk_add_long_constant(bytecode, MARG_NUMBER(42.42));
            chunk_add_with_line(bytecode, OP_LONG_CONSTANT, 123);
            uint8_t *constant_in_bytes = long_constant_to_bytes(long_constant);
            chunk_add_with_line(bytecode, constant_in_bytes[0], 123);
            chunk_add_with_line(bytecode, constant_in_bytes[1], 123);
            chunk_add_with_line(bytecode, constant_in_bytes[2], 123);
            chunk_add_with_line(bytecode, constant_in_bytes[3], 123);
        }

        marg_vector *res = inspect_vm_bytecode(vm);
        assert_that_charptr(marg_string_get(marg_vector_get(res, 4000)) equals to "4e20         |      05 00 00 0f a0      LONG_CONSTANT    4000 (42.42)");
    });
})

#endif
