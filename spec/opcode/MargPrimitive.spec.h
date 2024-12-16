#ifndef __MARG_PRIMITIVE_SPEC_H_
#define __MARG_PRIMITIVE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"

static MargValue ret42(VM *vm, MargValue args) {
  (void)vm;
  (void)args;
  return MARG_INTEGER(42);
}

module(MargPrimitiveSpec, {
  it("tests QNAN boxed primitives", {
    VM *vm = vm_new("file.marg");
    assert_that(AS_PRIMITIVE(MARG_PRIMITIVE("+", NULL)) isnot NULL);
    assert_that(AS_PRIMITIVE(MARG_PRIMITIVE("+", NULL))->function is NULL);
    assert_that_charptr(
      AS_PRIMITIVE(MARG_PRIMITIVE("+", NULL))->primitive_name equals to "+"
    );

    MargValue prim = MARG_PRIMITIVE("ret42", (MargPrimitiveFunction)ret42);
    assert_that(AS_PRIMITIVE(prim) isnot NULL);
    assert_that_charptr(AS_PRIMITIVE(prim)->primitive_name equals to "ret42");

    MargValue res = AS_PRIMITIVE(prim)->function(vm, MARG_UNDEFINED);
    assert_that_size_t(AS_INTEGER(res)->value equals to 42);
  });

  it("ensures that the same primitive creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_PRIMITIVE("+", NULL);
    MargValue y = MARG_PRIMITIVE("+", NULL);
    assert_that(x isnot y);
    assert_that_charptr(
      AS_PRIMITIVE(x)->primitive_name equals to AS_PRIMITIVE(y)->primitive_name
    );
  });

  it("ensures that self is set and super does not exist", {
    VM *vm                    = vm_new("file.marg");
    MargValue x               = MARG_PRIMITIVE("+", NULL);
    vm->current->bound_object = AS_OBJECT(x);
    MargValue self            = I("@self");
    MargValue super           = I("@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "");
    assert_that_charptr(AS_OBJECT(super)->name equals to "Primitive");
  });
})

#endif
