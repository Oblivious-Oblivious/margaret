#ifndef __MARG_OBJECT_SPEC_H_
#define __MARG_OBJECT_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"

module(MargObjectSpec, {
  it("tests QNAN boxed objects", {
    VM *vm = vm_new("file.marg");
    MargValue x =
      MARG_OBJECT(table_get(&vm->global_variables, "testobj"), "testobj");
    assert_that_charptr(AS_OBJECT(x)->name equals to "testobj");
  });

  it("ensures messages are empty on initialization", {
    VM *vm = vm_new("file.marg");
    MargValue marg_obj =
      MARG_OBJECT(table_get(&vm->global_variables, "testobj"), "testobj");
    assert_that_size_t(table_size(&AS_OBJECT(marg_obj)->messages) equals to 0);
  });

  it("tests the parent inheritance chain for objects", {
    VM *vm = vm_new("file.marg");

    /* Assumes that VM defines the prototype chain */
    MargValue marg_obj       = G("$Margaret");
    MargValue nil_obj        = G("$nil");
    MargValue false_obj      = G("$false");
    MargValue true_obj       = G("$true");
    MargValue numeric_obj    = G("$Numeric");
    MargValue integer_obj    = G("$Integer");
    MargValue float_obj      = G("$Float");
    MargValue label_obj      = G("$Label");
    MargValue string_obj     = G("$String");
    MargValue enumerable_obj = G("$Enumerable");
    MargValue tensor_obj     = G("$Tensor");
    MargValue tuple_obj      = G("$Tuple");
    MargValue table_obj      = G("$Table");
    MargValue bitstring_obj  = G("$Bitstring");
    MargValue method_obj     = G("$Method");

    assert_that(marg_obj isnot MARG_UNDEFINED);
    assert_that(nil_obj isnot MARG_UNDEFINED);
    assert_that(false_obj isnot MARG_UNDEFINED);
    assert_that(true_obj isnot MARG_UNDEFINED);
    assert_that(numeric_obj isnot MARG_UNDEFINED);
    assert_that(integer_obj isnot MARG_UNDEFINED);
    assert_that(float_obj isnot MARG_UNDEFINED);
    assert_that(label_obj isnot MARG_UNDEFINED);
    assert_that(string_obj isnot MARG_UNDEFINED);
    assert_that(enumerable_obj isnot MARG_UNDEFINED);
    assert_that(tensor_obj isnot MARG_UNDEFINED);
    assert_that(tuple_obj isnot MARG_UNDEFINED);
    assert_that(table_obj isnot MARG_UNDEFINED);
    assert_that(bitstring_obj isnot MARG_UNDEFINED);
    assert_that(method_obj isnot MARG_UNDEFINED);

    assert_that_size_t(table_size(&AS_OBJECT(marg_obj)->instance_variables)
                         equals to 2);
    assert_that_size_t(AS_OBJECT(marg_obj)->instance_registers[table_get(
      &AS_OBJECT(marg_obj)->instance_variables, "@self"
    )] equals to marg_obj);
    assert_that_size_t(AS_OBJECT(marg_obj)->instance_registers[table_get(
      &AS_OBJECT(marg_obj)->instance_variables, "@super"
    )] equals to marg_obj);

    assert_that_size_t(AS_OBJECT(tensor_obj)
                         ->instance_registers[table_get(
                           &AS_OBJECT(tensor_obj)->instance_variables, "@self"
                         )] equals to tensor_obj);
    assert_that_size_t(AS_OBJECT(tensor_obj)
                         ->instance_registers[table_get(
                           &AS_OBJECT(tensor_obj)->instance_variables, "@super"
                         )] equals to enumerable_obj);

    assert_that_size_t(AS_OBJECT(float_obj)->instance_registers[table_get(
      &AS_OBJECT(float_obj)->instance_variables, "@self"
    )] equals to float_obj);
    assert_that_size_t(AS_OBJECT(float_obj)->instance_registers[table_get(
      &AS_OBJECT(float_obj)->instance_variables, "@super"
    )] equals to numeric_obj);

    assert_that_size_t(AS_OBJECT(nil_obj)->instance_registers[table_get(
      &AS_OBJECT(nil_obj)->instance_variables, "@self"
    )] equals to nil_obj);
    assert_that_size_t(AS_OBJECT(nil_obj)->instance_registers[table_get(
      &AS_OBJECT(nil_obj)->instance_variables, "@super"
    )] equals to marg_obj);
  });
})

#endif
