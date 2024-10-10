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

  it("tests to_string", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_INTEGER(42);
    assert_that_charptr(marg_integer_to_string(AS_INTEGER(x)) equals to "42");
  });
})

#endif
