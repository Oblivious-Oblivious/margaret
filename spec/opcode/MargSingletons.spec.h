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
})

#endif
