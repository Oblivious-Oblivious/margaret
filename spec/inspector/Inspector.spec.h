#ifndef __INSPECTOR_SPEC_H_
#define __INSPECTOR_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/inspector/Inspector.h"
#include "../../src/opcode/MargValue.h"
#include "../../src/opcode/opcodes.h"

module(InspectorSpec, {
  // TODO Test for a `postcard` type mini program that includes every single
  // feature
  it("tests multiple long temporaries", {
    VM *vm          = vm_new();
    chunk *bytecode = vm->current->bytecode;

    for(int i = 0; i <= 4000; i++) {
      uint32_t word_temporary_index;
      chunk_temporaries_add(bytecode, MARG_FLOAT(42.42), &word_temporary_index);
      chunk_add(bytecode, OP_PUT_OBJECT_WORD, 123);
      uint8_t *temporary_in_bytes = word_to_bytes(word_temporary_index);
      chunk_add(bytecode, temporary_in_bytes[0], 123);
      chunk_add(bytecode, temporary_in_bytes[1], 123);
    }

    EmeraldsVector *res = inspect_vm_bytecode(vm);
    assert_that_charptr(string_get((EmeraldsString *)vector_get(res, 4000))
                          equals to "2ee0         |      0c 0f a0            "
                                    "PUT_OBJECT_WORD          42.42 @[4000]");
  });
})

#endif
