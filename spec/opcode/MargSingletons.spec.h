#ifndef __MARG_SINGLETONS_SPEC_H_
#define __MARG_SINGLETONS_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/MargValue.h"

module(MargSingletonsSpec, {
  it("tests QNAN boxed singletons", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_NIL;
    MargValue y = MARG_FALSE;
    MargValue z = MARG_TRUE;
    assert_that(x isnot MARG_UNDEFINED);
    assert_that(y isnot MARG_UNDEFINED);
    assert_that(z isnot MARG_UNDEFINED);
  });

  it("ensures that values are singletons", {
    VM *vm       = vm_new("file.marg");
    MargValue x1 = MARG_NIL;
    MargValue x2 = MARG_NIL;
    assert_that(x1 is x2);

    MargValue y1 = MARG_FALSE;
    MargValue y2 = MARG_FALSE;
    assert_that(y1 is y2);

    MargValue z1 = MARG_TRUE;
    MargValue z2 = MARG_TRUE;
    assert_that(z1 is z2);
  });

  it("ensures that self and super are set correctly", {
    VM *vm = vm_new("file.marg");
    assert_that_charptr(
      AS_OBJECT(table_get(&AS_OBJECT(MARG_NIL)->instance_variables, "@self"))
        ->name equals to "$nil"
    );
    assert_that_charptr(
      AS_OBJECT(table_get(&AS_OBJECT(MARG_NIL)->instance_variables, "@super"))
        ->name equals to "$Margaret"
    );
    assert_that_charptr(
      AS_OBJECT(table_get(&AS_OBJECT(MARG_FALSE)->instance_variables, "@self"))
        ->name equals to "$false"
    );
    assert_that_charptr(
      AS_OBJECT(table_get(&AS_OBJECT(MARG_FALSE)->instance_variables, "@super"))
        ->name equals to "$Margaret"
    );
    assert_that_charptr(
      AS_OBJECT(table_get(&AS_OBJECT(MARG_TRUE)->instance_variables, "@self"))
        ->name equals to "$true"
    );
    assert_that_charptr(
      AS_OBJECT(table_get(&AS_OBJECT(MARG_TRUE)->instance_variables, "@super"))
        ->name equals to "$Margaret"
    );
  });
})

#endif
