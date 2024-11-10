#ifndef __VM_SPEC_H_
#define __VM_SPEC_H_

#include "../libs/cSpec/export/cSpec.h"
#include "helpers.spec.h"
#include "nan_tagging.h"

module(vm_spec, {
  before_each(&reset_vm);

  describe("built-in objects", {
    it("has 7 built-in objects", {
      assert_that_size_t(table_size(&vm->global_variables) equals to 7);
    });

    context("on singletons", {
      it("verifies that $nil, $false and $true are singleton implementations", {
        size_t singleton_nil   = table_get(&vm->global_variables, "$nil");
        size_t singleton_false = table_get(&vm->global_variables, "$false");
        size_t singleton_true  = table_get(&vm->global_variables, "$true");
        size_t new_nil         = MARG_NIL();
        size_t new_false       = MARG_FALSE();
        size_t new_true        = MARG_TRUE();
        assert_that_size_t(singleton_nil equals to new_nil);
        assert_that_size_t(singleton_false equals to new_false);
        assert_that_size_t(singleton_true equals to new_true);
        assert_that(!IS_UNDEFINED(new_nil));
        assert_that(!IS_UNDEFINED(new_false));
        assert_that(!IS_UNDEFINED(new_true));
      });
    });

    context("on non-singletons", {
      it("ensures we define global $Number, $String and $Method objects", {
        assert_that(!IS_UNDEFINED(table_get(&vm->global_variables, "$Number")));
        assert_that(!IS_UNDEFINED(table_get(&vm->global_variables, "$String")));
        assert_that(!IS_UNDEFINED(table_get(&vm->global_variables, "$Method")));
      });
    });
  });

  describe("main method", {
    it("ensures ip points to the main method", {
      assert_that(vm->current->bound_method is NULL);
      MargObject *marg = vm->current->bound_object;
      assert_that_charptr(marg->name equals to "$Margaret");
    });
  });
})

#endif
