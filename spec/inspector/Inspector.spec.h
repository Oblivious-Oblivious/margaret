#ifndef __INSPECTOR_SPEC_H_
#define __INSPECTOR_SPEC_H_

#include "../../src/inspector/Inspector.h"
#include "../cSpec.h"

#include "../../src/opcode/Opcodes.h"
#include "../../src/vm/byte_conversions.h"

module(InspectorSpec, {
    // TODO Test for a `postcard` type mini program that includes every single feature
    it("tests multiple long temporaries", {
        VM *vm = vm_new();
        chunk *bytecode = vm->bytecode;

        for(int i = 0; i <= 4000; i++) {
            uint32_t long_temporary_index;
            chunk_temporaries_add(bytecode, MARG_FLOAT(42.42), &long_temporary_index);
            chunk_add(bytecode, OP_PUT_OBJECT_LONG, 123);
            uint8_t *temporary_in_bytes = dword_to_bytes(long_temporary_index);
            chunk_add(bytecode, temporary_in_bytes[0], 123);
            chunk_add(bytecode, temporary_in_bytes[1], 123);
            chunk_add(bytecode, temporary_in_bytes[2], 123);
            chunk_add(bytecode, temporary_in_bytes[3], 123);
        }

        vector *res = inspect_vm_bytecode(vm);
        assert_that_charptr(string_get(vector_get(res, 4000)) equals to "4e20         |      09 00 00 0f a0      PUT_OBJECT_LONG          42.42 @[4000]");
    });
})

#endif
