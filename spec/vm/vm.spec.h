#ifndef __VM_SPEC_H_
#define __VM_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"
#include "../../src/vm/vm.h"

module(VmSpec, {
  VM *vm = vm_new("file.marg");

  describe("built-in objects", {
    it("has 17 built-in objects", {
      assert_that_size_t(table_size(&vm->global_variables) equals to 17);
    });

    context("on singletons", {
      it("verifies that $nil, $false and $true are singleton implementations", {
        MargValue singleton_nil   = G("$nil");
        MargValue singleton_false = G("$false");
        MargValue singleton_true  = G("$true");
        size_t new_nil            = MARG_NIL;
        size_t new_false          = MARG_FALSE;
        size_t new_true           = MARG_TRUE;
        assert_that_size_t(singleton_nil equals to new_nil);
        assert_that_size_t(singleton_false equals to new_false);
        assert_that_size_t(singleton_true equals to new_true);
        assert_that(!IS_UNDEFINED(new_nil));
        assert_that(!IS_UNDEFINED(new_false));
        assert_that(!IS_UNDEFINED(new_true));
      });
    });

    context("on non-singletons", {
      it("ensures we define global $Numeric, $String and $Method objects", {
        assert_that(!IS_UNDEFINED(G("$Numeric")));
        assert_that(!IS_UNDEFINED(G("$String")));
        assert_that(!IS_UNDEFINED(G("$Label")));
        assert_that(!IS_UNDEFINED(G("$Method")));
        assert_that(!IS_UNDEFINED(G("Primitive")));
      });
    });
  });

  describe("main method", {
    it("ensures ip points to the main method", {
      assert_that(vm->current->bound_method is vm->current);
      MargObject *marg = vm->current->bound_object;
      assert_that_charptr(marg->name equals to "$Margaret");
      assert_that_size_t(marg->name_hash equals to 4789181502764186150);
    });
  });
})

#endif
