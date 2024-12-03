#ifndef __MARG_STRING_SPEC_H_
#define __MARG_STRING_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"

module(MargStringSpec, {
  it("tests QNAN boxed strings", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_STRING("hello world");
    assert_that(x isnot MARG_UNDEFINED);
    assert_that_charptr(AS_STRING(x)->value equals to "hello world");
  });

  it("ensures that the same string creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_STRING("hello world");
    MargValue y = MARG_STRING("hello world");
    assert_that(x isnot y);
    assert_that_charptr(AS_STRING(x)->value equals to AS_STRING(x)->value);
  });

  it("ensures that self and super are set correctly", {
    VM *vm                    = vm_new("file.marg");
    MargValue x               = MARG_STRING("hello world");
    vm->current->bound_object = AS_OBJECT(x);
    MargValue self            = I("@self");
    MargValue super           = I("@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$String");
    assert_that_charptr(AS_OBJECT(super)->proto->name equals to "$Margaret");
  });
})

#endif
