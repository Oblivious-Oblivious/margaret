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

  it("tests to_string", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_SYMBOL(":sym");
    assert_that_charptr(marg_symbol_to_string(AS_SYMBOL(x)) equals to ":sym");
  });
})

#endif
