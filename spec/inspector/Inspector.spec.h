#ifndef __INSPECTOR_SPEC_H_
#define __INSPECTOR_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsVector/export/EmeraldsVector.h"
#include "../../src/inspector/Inspector.h"
#include "../../src/opcode/MargValue.h"
#include "../../src/opcode/opcodes.h"

module(InspectorSpec, {
  // TODO - Test for a `postcard` type mini program that includes every single
  // feature
  it("tests multiple long temporaries", {
    VM *vm = vm_new();

    for(int i = 0; i <= 4000; i++) {
      vector_add(vm->current->temporaries, MARG_FLOAT(42.42));
      uint32_t word_temporary_index = vector_size(vm->current->temporaries) - 1;

      vector_add(vm->current->bytecode, OP_PUT_OBJECT_WORD);
      uint8_t temporary_in_bytes[2];
      word_to_bytes(word_temporary_index, temporary_in_bytes);
      vector_add(vm->current->bytecode, temporary_in_bytes[0]);
      vector_add(vm->current->bytecode, temporary_in_bytes[1]);
    }

    char **res = inspect_vm_bytecode(vm);
    assert_that_int(vector_size(res) equals to 4001);
    assert_that_charptr(res[4000] equals to
                        "2ee0         |      0c 0f a0            "
                        "PUT_OBJECT_WORD          42.42 @[4000]");
  });
})

#endif
