#ifndef __MARG_BITSTRING_SPEC_H_
#define __MARG_BITSTRING_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"

module(MargBitstringSpec, {
  it("tests QNAN boxed bitstrings", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_BITSTRING();
    assert_that(x isnot MARG_UNDEFINED);
  });

  it("ensures that the same bitstring creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_BITSTRING();
    MargValue y = MARG_BITSTRING();
    assert_that(x isnot y);
  });

  it("ensures that self and super are set correctly", {
    VM *vm                    = vm_new("file.marg");
    MargValue x               = MARG_BITSTRING();
    vm->current->bound_object = AS_OBJECT(x);
    MargValue self            = I("@self");
    MargValue super           = I("@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$Bitstring");
    assert_that_charptr(AS_OBJECT(super)->proto->name equals to "$Enumerable");
  });
})

#endif
