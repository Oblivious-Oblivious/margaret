#ifndef __MARG_LABEL_SPEC_H_
#define __MARG_LABEL_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"

module(MargLabelSpec, {
  it("tests QNAN boxed labels", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_LABEL("hello world");
    assert_that(x isnot MARG_UNDEFINED);
    assert_that_charptr(AS_LABEL(x)->name equals to "hello world");
    assert_that_size_t(AS_LABEL(x)->value equals to 0);
  });

  it("ensures that the same label creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_LABEL("hello world");
    MargValue y = MARG_LABEL("hello world");
    assert_that(x isnot y);
    assert_that_charptr(AS_LABEL(x)->name equals to AS_LABEL(x)->name);
  });

  it("ensures that self and super are set correctly", {
    VM *vm                    = vm_new("file.marg");
    MargValue x               = MARG_LABEL(":l");
    vm->current->bound_object = AS_OBJECT(x);
    MargValue self            = I("@self");
    MargValue super           = I("@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$Label");
    assert_that_charptr(AS_OBJECT(super)->proto->name equals to "$String");
  });
})

#endif
