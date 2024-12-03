#ifndef __MARG_VALUE_SPEC_H_
#define __MARG_VALUE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"
#include "../../src/primitives/BitstringPrimitives.h"

module(MargValueSpec, {
  describe("tests NaN boxing", {
    it("boxes the same value producing the same result", {
      int *arr     = (int *)malloc(sizeof(int) * 10);
      MargValue v1 = QNAN_BOX(arr);
      MargValue v2 = QNAN_BOX(arr);
      MargValue v3 = QNAN_BOX(arr);

      assert_that_size_t(v1 equals to v2);
      assert_that_size_t(v2 equals to v3);
    });

    it("boxes and unboxes producing the same result", {
      int *arr     = (int *)malloc(sizeof(int) * 10);
      MargValue v1 = QNAN_BOX(arr);
      MargValue v2 = QNAN_BOX(arr);
      MargValue v3 = QNAN_BOX(arr);

      assert_that_size_t(QNAN_BOX(QNAN_UNBOX(v1)) equals to v1);
      assert_that_size_t(QNAN_BOX(QNAN_UNBOX(v2)) equals to v2);
      assert_that_size_t(QNAN_BOX(QNAN_UNBOX(v3)) equals to v3);
    });

    it("ensures that UNDEFINED is a static value", {
      assert_that_size_t(MARG_UNDEFINED equals to 18445618173802708992ull);
      assert_that_size_t(MARG_UNDEFINED equals to 18445618173802708992ull);
      assert_that_size_t(MARG_UNDEFINED equals to 18445618173802708992ull);
    });

    it("ensures cloned objects do not receive label values from parent", {
      VM *vm         = vm_new("file.marg");
      MargValue marg = G("$Margaret");
      assert_that(marg isnot MARG_UNDEFINED);
      assert_that_charptr(AS_OBJECT(marg)->name equals to "$Margaret");
      assert_that_size_t(
        AS_OBJECT(marg)->name_hash equals to 4789181502764186150
      );
      table_add(
        &AS_OBJECT(marg)->instance_variables, "@::l1", MARG_LABEL("@::l1")
      );
      table_add(
        &AS_OBJECT(marg)->instance_variables, "@::l2", MARG_LABEL("@::l2")
      );

      assert_that_size_t(table_size(&AS_OBJECT(marg)->instance_variables)
                           equals to 4);

      MargValue clone = SG(marg, "ACLONE");
      assert_that(clone isnot MARG_UNDEFINED);
      assert_that_charptr(AS_OBJECT(clone)->name equals to "ACLONE");
      assert_that_charptr(AS_OBJECT(clone)->proto->name equals to "$Margaret");
      assert_that_size_t(
        AS_OBJECT(clone)->name_hash equals to 3455395588760667778
      );
      assert_that_size_t(
        AS_OBJECT(clone)->proto->name_hash equals to 4789181502764186150
      );
      assert_that_size_t(table_size(&AS_OBJECT(clone)->instance_variables)
                           equals to 2);
    });

    it("ensures @self and @super are setup correctly", {
      VM *vm          = vm_new("file.marg");
      MargValue clone = SG(G("$Margaret"), "ACLONE");

      assert_that_charptr(AS_OBJECT(AS_OBJECT(clone)->instance_registers[0])
                            ->name equals to "ACLONE");
      assert_that_charptr(AS_OBJECT(AS_OBJECT(clone)->instance_registers[1])
                            ->name equals to "$Margaret");
      assert_that_size_t(AS_OBJECT(AS_OBJECT(clone)->instance_registers[0])
                           ->name_hash equals to 3455395588760667778);
      assert_that_size_t(AS_OBJECT(AS_OBJECT(clone)->instance_registers[1])
                           ->name_hash equals to 4789181502764186150);
    });
  });
})

#endif
