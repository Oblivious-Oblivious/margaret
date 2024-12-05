#ifndef __MARG_FLOAT_SPEC_H_
#define __MARG_FLOAT_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"

module(MargFloatSpec, {
  it("tests QNAN boxes floats", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_FLOAT(42.42);
    assert_that_double(AS_FLOAT(x)->value equals to 42.42);
  });

  it("ensures that the same float creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_FLOAT(42.42);
    MargValue y = MARG_FLOAT(42.42);
    nassert_that_double(x equals to y);
  });

  it("ensures that self and super are set correctly", {
    VM *vm                    = vm_new("file.marg");
    MargValue x               = MARG_FLOAT(42.42);
    vm->current->bound_object = AS_OBJECT(x);
    MargValue self            = I("@self");
    MargValue super           = I("@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$Float");
    assert_that_charptr(AS_OBJECT(super)->proto->name equals to "$Numeric");
  });
})

#endif
