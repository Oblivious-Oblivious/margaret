#ifndef __MARG_TENSOR_SPEC_H_
#define __MARG_TENSOR_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/MargValue.h"

module(MargTensorSpec, {
  it("tests QNAN boxed tensors", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_TENSOR();
    assert_that_size_t(marg_tensor_capacity(AS_TENSOR(x)) equals to 0);
    assert_that_size_t(marg_tensor_size(AS_TENSOR(x)) equals to 0);
  });

  it("ensures that the same tensor creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_TENSOR();
    MargValue y = MARG_TENSOR();
    assert_that(x isnot y);
    assert_that_size_t(marg_tensor_capacity(AS_TENSOR(x))
                         equals to marg_tensor_capacity(AS_TENSOR(y)));
  });

  context("on the rest of predefined functions", {
    it("#marg_tensor_initialize", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_initialize(AS_TENSOR(x));
      assert_that_size_t(marg_tensor_capacity(AS_TENSOR(x)) equals to 4);
    });

    it("#marg_tensor_initialize_n", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_initialize_n(AS_TENSOR(x), 13);
      assert_that_size_t(marg_tensor_capacity(AS_TENSOR(x)) equals to 13);
    });

    it("#marg_tensor_add", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(42));
      assert_that_size_t(marg_tensor_size(AS_TENSOR(x)) equals to 1);
      assert_that_ptrdiff_t(
        AS_INTEGER(AS_TENSOR(x)->value[0])->value equals to 42
      );
    });

    it("#marg_tensor_add_tensor", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      MargValue y = MARG_TENSOR();
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(42));
      marg_tensor_add(AS_TENSOR(y), MARG_INTEGER(43));
      marg_tensor_add_tensor(AS_TENSOR(x), AS_TENSOR(y));
      assert_that_size_t(marg_tensor_size(AS_TENSOR(x)) equals to 2);
      assert_that_size_t(marg_tensor_size(AS_TENSOR(y)) equals to 1);
      assert_that_ptrdiff_t(
        AS_INTEGER(AS_TENSOR(x)->value[0])->value equals to 42
      );
      assert_that_ptrdiff_t(
        AS_INTEGER(AS_TENSOR(x)->value[1])->value equals to 43
      );
      assert_that_ptrdiff_t(
        AS_INTEGER(AS_TENSOR(y)->value[0])->value equals to 43
      );
    });

    it("#marg_tensor_remove_n", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(42));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(43));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(44));
      marg_tensor_remove_n(AS_TENSOR(x), 0, 2);
      assert_that_size_t(marg_tensor_size(AS_TENSOR(x)) equals to 1);
      assert_that_ptrdiff_t(
        AS_INTEGER(AS_TENSOR(x)->value[0])->value equals to 44
      );
    });

    it("#marg_tensor_remove", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(42));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(43));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(44));
      marg_tensor_remove(AS_TENSOR(x), 0);
      assert_that_size_t(marg_tensor_size(AS_TENSOR(x)) equals to 2);
      assert_that_ptrdiff_t(
        AS_INTEGER(AS_TENSOR(x)->value[0])->value equals to 43
      );
      assert_that_ptrdiff_t(
        AS_INTEGER(AS_TENSOR(x)->value[1])->value equals to 44
      );
    });

    it("#marg_tensor_remove_last", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(42));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(43));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(44));
      marg_tensor_remove_last(AS_TENSOR(x));
      assert_that_size_t(marg_tensor_size(AS_TENSOR(x)) equals to 2);
      assert_that_ptrdiff_t(
        AS_INTEGER(AS_TENSOR(x)->value[0])->value equals to 42
      );
      assert_that_ptrdiff_t(
        AS_INTEGER(AS_TENSOR(x)->value[1])->value equals to 43
      );
    });

    it("#marg_tensor_last", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(42));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(43));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(44));
      assert_that_ptrdiff_t(
        AS_INTEGER(marg_tensor_last(AS_TENSOR(x)))->value equals to 44
      );
    });

    it("#marg_tensor_size", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(42));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(43));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(44));
      assert_that_size_t(marg_tensor_size(AS_TENSOR(x)) equals to 3);
    });

    it("#marg_tensor_size_signed", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(42));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(43));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(44));
      assert_that_ptrdiff_t(marg_tensor_size_signed(AS_TENSOR(x)) equals to 3);
    });

    it("#marg_tensor_capacity", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_initialize(AS_TENSOR(x));
      assert_that_size_t(marg_tensor_capacity(AS_TENSOR(x)) equals to 4);
    });

    it("#marg_tensor_capacity_signed", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_initialize_n(AS_TENSOR(x), 32);
      assert_that_ptrdiff_t(marg_tensor_capacity_signed(AS_TENSOR(x))
                              equals to 32);
    });

    it("#marg_tensor_push", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_initialize(AS_TENSOR(x));
      marg_tensor_push(AS_TENSOR(x), MARG_INTEGER(42));
      assert_that_size_t(marg_tensor_size(AS_TENSOR(x)) equals to 1);
      assert_that_ptrdiff_t(
        AS_INTEGER(AS_TENSOR(x)->value[0])->value equals to 42
      );
    });

    it("#marg_tensor_pop", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(42));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(43));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(44));
      assert_that_ptrdiff_t(
        AS_INTEGER(marg_tensor_pop(AS_TENSOR(x)))->value equals to 44
      );
      assert_that_ptrdiff_t(
        AS_INTEGER(marg_tensor_pop(AS_TENSOR(x)))->value equals to 43
      );
      assert_that_ptrdiff_t(
        AS_INTEGER(marg_tensor_pop(AS_TENSOR(x)))->value equals to 42
      );
      assert_that_size_t(marg_tensor_size(AS_TENSOR(x)) equals to 0);
    });

    it("#marg_tensor_peek", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TENSOR();
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(42));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(43));
      marg_tensor_add(AS_TENSOR(x), MARG_INTEGER(44));
      assert_that_ptrdiff_t(
        AS_INTEGER(marg_tensor_peek(AS_TENSOR(x)))->value equals to 44
      );
      assert_that_ptrdiff_t(
        AS_INTEGER(marg_tensor_peek(AS_TENSOR(x)))->value equals to 44
      );
      (void)marg_tensor_pop(AS_TENSOR(x));
      assert_that_ptrdiff_t(
        AS_INTEGER(marg_tensor_peek(AS_TENSOR(x)))->value equals to 43
      );
      assert_that_ptrdiff_t(
        AS_INTEGER(marg_tensor_peek(AS_TENSOR(x)))->value equals to 43
      );
    });
  });

  it("ensures that self and super are set correctly", {
    VM *vm          = vm_new("file.marg");
    MargValue x     = MARG_TENSOR();
    MargValue self  = table_get(&AS_OBJECT(x)->instance_variables, "@self");
    MargValue super = table_get(&AS_OBJECT(x)->instance_variables, "@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "$Tensor");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$Enumerable");
  });
})

#endif
