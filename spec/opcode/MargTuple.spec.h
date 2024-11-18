#ifndef __MARG_TUPLE_SPEC_H_
#define __MARG_TUPLE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/MargValue.h"

module(MargTupleSpec, {
  it("tests QNAN boxed tuples", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_TUPLE();
    assert_that(x isnot MARG_UNDEFINED);
    assert_that(AS_TUPLE(x)->value is NULL);
  });

  it("ensures that the same tuple creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_TUPLE();
    MargValue y = MARG_TUPLE();
    assert_that(x isnot y);
    assert_that(AS_TUPLE(x)->value is NULL);
    assert_that(AS_TUPLE(y)->value is NULL);
  });

  it("ensures that self and super are set correctly", {
    VM *vm          = vm_new("file.marg");
    MargValue x     = MARG_TUPLE();
    MargValue self  = table_get(&AS_OBJECT(x)->instance_variables, "@self");
    MargValue super = table_get(&AS_OBJECT(x)->instance_variables, "@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "$Tuple");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$Tensor");
  });
})

#endif