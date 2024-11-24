#ifndef __MARG_TABLE_SPEC_H_
#define __MARG_TABLE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"

module(MargTableSpec, {
  it("tests QNAN boxed tables", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_TABLE();
    assert_that(x isnot MARG_UNDEFINED);
    assert_that(marg_table_size(AS_TABLE(x)) is 0);
  });

  it("ensures that the same table creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_TABLE();
    MargValue y = MARG_TABLE();
    assert_that(x isnot y);
    assert_that(marg_table_size(AS_TABLE(x)) is 0);
    assert_that(marg_table_size(AS_TABLE(y)) is 0);
  });

  context("on the rest of predefined functions", {
    it("#marg_table_add", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TABLE();
      marg_table_add(AS_TABLE(x), string_new("a"), MARG_INTEGER(42));
      marg_table_add(AS_TABLE(x), string_new("b"), MARG_FLOAT(42.123));
      marg_table_add(AS_TABLE(x), string_new("c"), MARG_STRING("hello"));
      assert_that_size_t(marg_table_size(AS_TABLE(x)) equals to 3);
    });

    it("#marg_table_add_all", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TABLE();
      MargValue y = MARG_TABLE();
      marg_table_add(AS_TABLE(x), string_new("a"), MARG_INTEGER(42));
      marg_table_add(AS_TABLE(x), string_new("b"), MARG_FLOAT(42.123));
      marg_table_add(AS_TABLE(x), string_new("c"), MARG_STRING("hello"));
      marg_table_add_all(AS_TABLE(x), AS_TABLE(y));
      assert_that_size_t(marg_table_size(AS_TABLE(y)) equals to 3);
      assert_that_size_t(marg_table_size(AS_TABLE(x)) equals to 3);
    });

    it("#marg_table_get", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TABLE();
      marg_table_add(AS_TABLE(x), string_new("a"), MARG_INTEGER(42));
      marg_table_add(AS_TABLE(x), string_new("b"), MARG_FLOAT(42.123));
      marg_table_add(AS_TABLE(x), string_new("c"), MARG_STRING("hello"));
      assert_that_ptrdiff_t(
        AS_INTEGER(marg_table_get(AS_TABLE(x), string_new("a")))
          ->value equals to 42
      );
      assert_that_double(AS_FLOAT(marg_table_get(AS_TABLE(x), string_new("b")))
                           ->value equals to 42.123);
      assert_that_charptr(AS_STRING(marg_table_get(AS_TABLE(x), string_new("c"))
      )
                            ->value equals to "hello");
    });

    it("#marg_table_remove", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TABLE();
      marg_table_add(AS_TABLE(x), string_new("a"), MARG_INTEGER(42));
      marg_table_add(AS_TABLE(x), string_new("b"), MARG_FLOAT(42.123));
      marg_table_add(AS_TABLE(x), string_new("c"), MARG_STRING("hello"));
      marg_table_remove(AS_TABLE(x), string_new("a"));
      assert_that_size_t(marg_table_size(AS_TABLE(x)) equals to 2);
    });

    it("#marg_table_size", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_TABLE();
      marg_table_add(AS_TABLE(x), string_new("a"), MARG_INTEGER(42));
      marg_table_add(AS_TABLE(x), string_new("b"), MARG_FLOAT(42.123));
      marg_table_add(AS_TABLE(x), string_new("c"), MARG_STRING("hello"));
      assert_that_size_t(marg_table_size(AS_TABLE(x)) equals to 3);
    });
  });

  it("ensures that self and super are set correctly", {
    VM *vm                    = vm_new("file.marg");
    MargValue x               = MARG_TABLE();
    vm->current->bound_object = AS_OBJECT(x);
    MargValue self            = I("@self");
    MargValue super           = I("@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$Table");
    assert_that_charptr(AS_OBJECT(super)->proto->name equals to "$Enumerable");
  });
})

#endif
