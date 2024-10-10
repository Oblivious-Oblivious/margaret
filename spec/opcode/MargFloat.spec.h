#ifndef __MARG_FLOAT_SPEC_H_
#define __MARG_FLOAT_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/MargValue.h"

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

  it("tests to_string", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_FLOAT(42.42);
    assert_that_charptr(marg_float_to_string(AS_FLOAT(x)) equals to "42.42");
  });
})

#endif
