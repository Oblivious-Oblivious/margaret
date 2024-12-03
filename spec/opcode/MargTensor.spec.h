#ifndef __MARG_TENSOR_SPEC_H_
#define __MARG_TENSOR_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"

module(MargTensorSpec, {
  it("ensures that self and super are set correctly", {
    VM *vm                    = vm_new("file.marg");
    MargValue x               = MARG_TENSOR();
    vm->current->bound_object = AS_OBJECT(x);
    MargValue self            = I("@self");
    MargValue super           = I("@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$Tensor");
    assert_that_charptr(AS_OBJECT(super)->proto->name equals to "$Enumerable");
  });
})

#endif
