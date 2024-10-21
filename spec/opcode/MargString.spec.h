#ifndef __MARG_STRING_SPEC_H_
#define __MARG_STRING_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/MargValue.h"

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

  context("on the rest of predefined functions", {
    it("#marg_string_size", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_STRING("hello world");
      assert_that_size_t(marg_string_size(AS_STRING(x)) equals to 11);
    });

    it("#marg_string_size_signed", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_STRING("hello world");
      assert_that_ptrdiff_t(marg_string_size_signed(AS_STRING(x)) equals to 11);
    });

    it("#marg_string_shorten", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_STRING("hello world");
      marg_string_shorten(AS_STRING(x), 3);
      assert_that_size_t(marg_string_size(AS_STRING(x)) equals to 3);
      assert_that_charptr(AS_STRING(x)->value equals to "hel");
    });

    it("#marg_string_skip_first", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_STRING("hello world");
      marg_string_skip_first(AS_STRING(x), 8);
      assert_that_size_t(marg_string_size(AS_STRING(x)) equals to 3);
      assert_that_charptr(AS_STRING(x)->value equals to "rld");
    });

    it("#marg_string_ignore_last", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_STRING("hello world");
      marg_string_ignore_last(AS_STRING(x), 8);
      assert_that_size_t(marg_string_size(AS_STRING(x)) equals to 3);
      assert_that_charptr(AS_STRING(x)->value equals to "hel");
    });

    it("#marg_string_delete", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_STRING("hello world");
      marg_string_delete(AS_STRING(x));
      assert_that_size_t(marg_string_size(AS_STRING(x)) equals to 0);
    });

    it("#marg_string_remove", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_STRING("hello world");
      marg_string_remove(AS_STRING(x), 5);
      assert_that_size_t(marg_string_size(AS_STRING(x)) equals to 10);
      assert_that_charptr(AS_STRING(x)->value equals to "helloworld");
    });

    it("#marg_string_equals", {
      VM *vm      = vm_new("file.marg");
      MargValue x = MARG_STRING("hello world");
      MargValue y = MARG_STRING("hello world");
      assert_that(marg_string_equals(AS_STRING(x), AS_STRING(y)));
    });
  });

  it("ensures that self and super are set correctly", {
    VM *vm          = vm_new("file.marg");
    MargValue x     = MARG_STRING("hello world");
    MargValue self  = table_get(&AS_OBJECT(x)->instance_variables, "@self");
    MargValue super = table_get(&AS_OBJECT(x)->instance_variables, "@super");
    assert_that_charptr(AS_OBJECT(self)->name equals to "$String");
    assert_that_charptr(AS_OBJECT(super)->name equals to "$Margaret");
  });
})

#endif
