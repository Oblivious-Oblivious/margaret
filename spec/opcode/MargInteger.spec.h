#ifndef __MARG_INTEGER_SPEC_H_
#define __MARG_INTEGER_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/MargValue.h"

module(MargIntegerSpec, {
  it("tests QNAN boxed integers", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_INTEGER(42);
    assert_that_ptrdiff_t(AS_INTEGER(x)->value equals to 42);
  });

  it("ensures that the same integer creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_INTEGER(42);
    MargValue y = MARG_INTEGER(42);
    nassert_that_ptrdiff_t(x equals to y);
  });

  it("ensures that self and super are set correctly", {
    VM *vm          = vm_new("file.marg");
    MargValue x     = MARG_INTEGER(42);
    MargValue self  = table_get(&AS_OBJECT(x)->instance_variables, "@self");
    MargValue super = table_get(&AS_OBJECT(x)->instance_variables, "@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "$Integer");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$Numeric");
  });
})

#endif
