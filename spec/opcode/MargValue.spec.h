#ifndef __MARG_VALUE_SPEC_H_
#define __MARG_VALUE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"

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

    it("uses marg_value_format by calling the equivalent to_string functions", {
      VM *vm = vm_new("file.marg");
      assert_that_charptr(marg_value_format(MARG_NIL) equals to "$nil");
      assert_that_charptr(marg_value_format(MARG_FALSE) equals to "$false");
      assert_that_charptr(marg_value_format(MARG_TRUE) equals to "$true");
      assert_that_charptr(marg_value_format(MARG_INTEGER(42)) equals to "42");
      assert_that_charptr(marg_value_format(MARG_FLOAT(42.4)) equals to "42.4");
      assert_that_charptr(marg_value_format(MARG_LABEL("::l")) equals to
                          "<::l:0>");
      assert_that_charptr(marg_value_format(MARG_STRING("hello world"))
                            equals to "\"hello world\"");
      assert_that_charptr(marg_value_format(MARG_SYMBOL(":sym")) equals to
                          ":sym");
      assert_that_charptr(marg_value_format(MARG_TENSOR()) equals to "[]");
      MargValue t = MARG_TENSOR();
      marg_tensor_add(AS_TENSOR(t), MARG_INTEGER(42));
      marg_tensor_add(AS_TENSOR(t), MARG_FLOAT(42.123));
      marg_tensor_add(AS_TENSOR(t), MARG_STRING("hello"));
      assert_that_charptr(marg_value_format(t) equals to
                          "[42, 42.123, \"hello\"]");
      assert_that_charptr(marg_value_format(MARG_TUPLE()) equals to "%[]");
      MargValue tup = MARG_TUPLE();
      marg_tensor_add(AS_TENSOR(tup), MARG_INTEGER(42));
      marg_tensor_add(AS_TENSOR(tup), MARG_FLOAT(42.123));
      marg_tensor_add(AS_TENSOR(tup), MARG_STRING("hello"));
      assert_that_charptr(marg_value_format(tup) equals to
                          "%[42, 42.123, \"hello\"]");
      assert_that_charptr(marg_value_format(MARG_TABLE()) equals to "%{}");
      MargValue h = MARG_TABLE();
      marg_table_add(AS_TABLE(h), string_new("a"), MARG_INTEGER(42));
      marg_table_add(AS_TABLE(h), string_new("b"), MARG_FLOAT(42.123));
      marg_table_add(AS_TABLE(h), string_new("c"), MARG_STRING("hello"));
      assert_that_charptr(marg_value_format(h) equals to
                          "%{c: \"hello\", b: 42.123, a: 42}");
      assert_that_charptr(marg_value_format(MARG_BITSTRING()) equals to "%()");
      MargValue b = MARG_BITSTRING();
      marg_bitstring_add(AS_BITSTRING(b), MARG_INTEGER(42), MARG_INTEGER(2));
      marg_bitstring_add(AS_BITSTRING(b), MARG_INTEGER(43), MARG_INTEGER(4));
      assert_that_charptr(marg_value_format(b) equals to "%(42::2, 43::4)");
      assert_that_charptr(marg_value_format(
        MARG_METHOD(AS_OBJECT(G("$Margaret")), vm->current, "msg")
      ) equals to "< $Margaret#msg >");
      assert_that_charptr(marg_value_format(MARG_OBJECT(G("$Margaret"), "Name"))
                            equals to "Name");
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
