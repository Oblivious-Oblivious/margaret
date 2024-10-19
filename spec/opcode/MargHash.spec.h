#ifndef __MARG_HASH_SPEC_H_
#define __MARG_HASH_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/MargValue.h"

module(MargHashSpec, {
  it("tests QNAN boxed hashes", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_HASH();
    assert_that(x isnot MARG_UNDEFINED);
    assert_that(marg_hash_size(AS_HASH(x)) is 0);
  });

  it("ensures that the same hash creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_HASH();
    MargValue y = MARG_HASH();
    assert_that(x isnot y);
    assert_that(marg_hash_size(AS_HASH(x)) is 0);
    assert_that(marg_hash_size(AS_HASH(y)) is 0);
  });

  context("on the rest of predefined functions", {
    it("#marg_hash_add", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_HASH();
      marg_hash_add(AS_HASH(x), string_new("a"), MARG_INTEGER(42));
      marg_hash_add(AS_HASH(x), string_new("b"), MARG_FLOAT(42.123));
      marg_hash_add(AS_HASH(x), string_new("c"), MARG_STRING("hello"));
      assert_that_size_t(marg_hash_size(AS_HASH(x)) equals to 3);
    });

    it("#marg_hash_add_all", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_HASH();
      MargValue y = MARG_HASH();
      marg_hash_add(AS_HASH(x), string_new("a"), MARG_INTEGER(42));
      marg_hash_add(AS_HASH(x), string_new("b"), MARG_FLOAT(42.123));
      marg_hash_add(AS_HASH(x), string_new("c"), MARG_STRING("hello"));
      marg_hash_add_all(AS_HASH(x), AS_HASH(y));
      assert_that_size_t(marg_hash_size(AS_HASH(y)) equals to 3);
      assert_that_size_t(marg_hash_size(AS_HASH(x)) equals to 3);
    });

    it("#marg_hash_get", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_HASH();
      marg_hash_add(AS_HASH(x), string_new("a"), MARG_INTEGER(42));
      marg_hash_add(AS_HASH(x), string_new("b"), MARG_FLOAT(42.123));
      marg_hash_add(AS_HASH(x), string_new("c"), MARG_STRING("hello"));
      assert_that_ptrdiff_t(
        AS_INTEGER(marg_hash_get(AS_HASH(x), string_new("a")))
          ->value equals to 42
      );
      assert_that_double(AS_FLOAT(marg_hash_get(AS_HASH(x), string_new("b")))
                           ->value equals to 42.123);
      assert_that_charptr(AS_STRING(marg_hash_get(AS_HASH(x), string_new("c")))
                            ->value equals to "hello");
    });

    it("#marg_hash_remove", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_HASH();
      marg_hash_add(AS_HASH(x), string_new("a"), MARG_INTEGER(42));
      marg_hash_add(AS_HASH(x), string_new("b"), MARG_FLOAT(42.123));
      marg_hash_add(AS_HASH(x), string_new("c"), MARG_STRING("hello"));
      marg_hash_remove(AS_HASH(x), string_new("a"));
      assert_that_size_t(marg_hash_size(AS_HASH(x)) equals to 2);
    });

    it("#marg_hash_size", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_HASH();
      marg_hash_add(AS_HASH(x), string_new("a"), MARG_INTEGER(42));
      marg_hash_add(AS_HASH(x), string_new("b"), MARG_FLOAT(42.123));
      marg_hash_add(AS_HASH(x), string_new("c"), MARG_STRING("hello"));
      assert_that_size_t(marg_hash_size(AS_HASH(x)) equals to 3);
    });
  });

  it("ensures that self and super are set correctly", {
    VM *vm          = vm_new("file.marg");
    MargValue x     = MARG_HASH();
    MargValue self  = table_get(&AS_OBJECT(x)->instance_variables, "@self");
    MargValue super = table_get(&AS_OBJECT(x)->instance_variables, "@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "$Hash");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$Enumerable");
  });
})

#endif
