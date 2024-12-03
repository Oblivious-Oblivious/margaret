#ifndef __MARG_BITSTRING_SPEC_H_
#define __MARG_BITSTRING_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"
#include "../../src/primitives/Primitives.h"

module(MargBitstringSpec, {
  it("tests QNAN boxed bitstrings", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_BITSTRING();
    assert_that(x isnot MARG_UNDEFINED);
    assert_that_size_t(
      AS_INTEGER(
        __PRIM_TENSOR_SIZE(vm, QNAN_BOX(AS_BITSTRING(x)->bits), MARG_UNDEFINED)
      )
        ->value equals to 0
    );
    assert_that_size_t(
      AS_INTEGER(
        __PRIM_TENSOR_SIZE(vm, QNAN_BOX(AS_BITSTRING(x)->sizes), MARG_UNDEFINED)
      )
        ->value equals to 0
    );
  });

  it("ensures that the same bitstring creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_BITSTRING();
    MargValue y = MARG_BITSTRING();
    assert_that(x isnot y);
  });

  it("ensures that self and super are set correctly", {
    VM *vm                    = vm_new("file.marg");
    MargValue x               = MARG_BITSTRING();
    vm->current->bound_object = AS_OBJECT(x);
    MargValue self            = I("@self");
    MargValue super           = I("@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$Bitstring");
    assert_that_charptr(AS_OBJECT(super)->proto->name equals to "$Enumerable");
  });

  it("adds new elements to the bitstring", {
    VM *vm         = vm_new("file.marg");
    MargValue x    = MARG_BITSTRING();
    MargValue args = MARG_TENSOR();
    vector_add(AS_TENSOR(args)->value, MARG_INTEGER(1));
    vector_add(AS_TENSOR(args)->value, MARG_INTEGER(2));
    __PRIM_BITSTRING_ADD(NULL, x, args);
    vector_free(AS_TENSOR(args)->value);
    vector_add(AS_TENSOR(args)->value, MARG_INTEGER(3));
    vector_add(AS_TENSOR(args)->value, MARG_INTEGER(4));
    __PRIM_BITSTRING_ADD(NULL, x, args);
    vector_free(AS_TENSOR(args)->value);
    assert_that_size_t(
      AS_INTEGER(
        __PRIM_TENSOR_SIZE(vm, QNAN_BOX(AS_BITSTRING(x)->bits), MARG_UNDEFINED)
      )
        ->value equals to 2
    );
    assert_that_size_t(
      AS_INTEGER(
        __PRIM_TENSOR_SIZE(vm, QNAN_BOX(AS_BITSTRING(x)->sizes), MARG_UNDEFINED)
      )
        ->value equals to 2
    );
    assert_that_int(
      AS_INTEGER(AS_BITSTRING(x)->bits->value[0])->value equals to 1
    );
    assert_that_int(
      AS_INTEGER(AS_BITSTRING(x)->sizes->value[0])->value equals to 2
    );
    assert_that_int(
      AS_INTEGER(AS_BITSTRING(x)->bits->value[1])->value equals to 3
    );
    assert_that_int(
      AS_INTEGER(AS_BITSTRING(x)->sizes->value[1])->value equals to 4
    );
  });

  it("gets the number of elements in the bitstring", {
    VM *vm         = vm_new("file.marg");
    MargValue x    = MARG_BITSTRING();
    MargValue args = MARG_TENSOR();
    vector_add(AS_TENSOR(args)->value, MARG_INTEGER(2));
    vector_add(AS_TENSOR(args)->value, MARG_INTEGER(2));
    __PRIM_BITSTRING_ADD(NULL, x, args);
    vector_free(AS_TENSOR(args)->value);
    vector_add(AS_TENSOR(args)->value, MARG_INTEGER(3));
    vector_add(AS_TENSOR(args)->value, MARG_INTEGER(4));
    __PRIM_BITSTRING_ADD(NULL, x, args);
    vector_free(AS_TENSOR(args)->value);
    vector_add(AS_TENSOR(args)->value, MARG_INTEGER(5));
    vector_add(AS_TENSOR(args)->value, MARG_INTEGER(8));
    __PRIM_BITSTRING_ADD(NULL, x, args);
    assert_that_size_t(AS_INTEGER(__PRIM_BITSTRING_SIZE(vm, x, MARG_UNDEFINED))
                         ->value equals to 3);
  });
})

#endif
