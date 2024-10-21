#ifndef __MARG_SYMBOL_SPEC_H_
#define __MARG_SYMBOL_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/MargValue.h"

module(MargSymbolSpec, {
  it("tests symbol", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_SYMBOL(":sym");
    assert_that(x isnot MARG_UNDEFINED);
    assert_that_charptr(AS_SYMBOL(x)->value equals to ":sym");
  });

  it("ensures that the same symbol creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_SYMBOL(":sym");
    MargValue y = MARG_SYMBOL(":sym");
    assert_that(x isnot y);
    assert_that_charptr(AS_SYMBOL(x)->value equals to AS_SYMBOL(x)->value);
  });

  it("ensures that self and super are set correctly", {
    VM *vm          = vm_new("file.marg");
    MargValue x     = MARG_SYMBOL(":sym");
    MargValue self  = table_get(&AS_OBJECT(x)->instance_variables, "@self");
    MargValue super = table_get(&AS_OBJECT(x)->instance_variables, "@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "$Symbol");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$String");
  });
})

#endif
