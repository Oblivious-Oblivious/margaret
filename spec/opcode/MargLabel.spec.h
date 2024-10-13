#ifndef __MARG_LABEL_SPEC_H_
#define __MARG_LABEL_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/MargValue.h"

module(MargLabelSpec, {
  it("tests QNAN boxed labels", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_LABEL("hello world", 42);
    assert_that(x isnot MARG_UNDEFINED);
    assert_that_charptr(AS_LABEL(x)->value equals to "hello world");
    assert_that_size_t(AS_LABEL(x)->index equals to 42);
  });

  it("ensures that the same label creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_LABEL("hello world", 42);
    MargValue y = MARG_LABEL("hello world", 42);
    assert_that(x isnot y);
    assert_that_charptr(AS_LABEL(x)->value equals to AS_LABEL(x)->value);
  });

  it("tests to_string", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_LABEL("::l", 42);
    assert_that_charptr(marg_label_to_string(AS_LABEL(x)) equals to "<::l:42>");
  });
})

#endif
