#ifndef __MARG_OBJECT_SPEC_H_
#define __MARG_OBJECT_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/MargValue.h"

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
    MargValue marg_obj       = table_get(&vm->global_variables, "$Margaret");
    MargValue nil_obj        = table_get(&vm->global_variables, "$nil");
    MargValue false_obj      = table_get(&vm->global_variables, "$false");
    MargValue true_obj       = table_get(&vm->global_variables, "$true");
    MargValue numeric_obj    = table_get(&vm->global_variables, "$Numeric");
    MargValue integer_obj    = table_get(&vm->global_variables, "$Integer");
    MargValue float_obj      = table_get(&vm->global_variables, "$Float");
    MargValue label_obj      = table_get(&vm->global_variables, "$Label");
    MargValue string_obj     = table_get(&vm->global_variables, "$String");
    MargValue enumerable_obj = table_get(&vm->global_variables, "$Enumerable");
    MargValue tensor_obj     = table_get(&vm->global_variables, "$Tensor");
    MargValue tuple_obj      = table_get(&vm->global_variables, "$Tuple");
    MargValue hash_obj       = table_get(&vm->global_variables, "$Hash");
    MargValue bitstring_obj  = table_get(&vm->global_variables, "$Bitstring");
    MargValue method_obj     = table_get(&vm->global_variables, "$Method");

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
    assert_that(hash_obj isnot MARG_UNDEFINED);
    assert_that(bitstring_obj isnot MARG_UNDEFINED);
    assert_that(method_obj isnot MARG_UNDEFINED);

    assert_that_size_t(table_size(&AS_OBJECT(marg_obj)->instance_variables)
                         equals to 2);
    assert_that_size_t(table_get(
      &AS_OBJECT(marg_obj)->instance_variables, "@self"
    ) equals to marg_obj);
    assert_that_size_t(table_get(
      &AS_OBJECT(marg_obj)->instance_variables, "@super"
    ) equals to MARG_UNDEFINED);

    assert_that_size_t(table_get(
      &AS_OBJECT(tensor_obj)->instance_variables, "@self"
    ) equals to tensor_obj);
    assert_that_size_t(table_get(
      &AS_OBJECT(tensor_obj)->instance_variables, "@super"
    ) equals to enumerable_obj);

    assert_that_size_t(table_get(
      &AS_OBJECT(float_obj)->instance_variables, "@self"
    ) equals to float_obj);
    assert_that_size_t(table_get(
      &AS_OBJECT(float_obj)->instance_variables, "@super"
    ) equals to numeric_obj);

    assert_that_size_t(table_get(
      &AS_OBJECT(nil_obj)->instance_variables, "@self"
    ) equals to nil_obj);
    assert_that_size_t(table_get(
      &AS_OBJECT(nil_obj)->instance_variables, "@super"
    ) equals to marg_obj);
  });

  it("tests the to_string method with the default hash", {
    VM *vm             = vm_new("test.marg");
    MargValue marg_obj = table_get(&vm->global_variables, "$Integer");
    char *to_s_value   = marg_object_to_string_with_hash(marg_obj);
    assert_that_charptr(string_split(to_s_value, '@')[0] equals to "$Integer");
  });

  it("tests that 2 VMs produce different object hashes for the same objects", {
    VM *vm1             = vm_new("test.marg");
    MargValue marg_obj1 = table_get(&vm1->global_variables, "$Integer");
    char *to_s_value1   = marg_object_to_string_with_hash(marg_obj1);
    assert_that_charptr(string_split(to_s_value1, '@')[0] equals to "$Integer");

    VM *vm2             = vm_new("test.marg");
    MargValue marg_obj2 = table_get(&vm2->global_variables, "$Integer");
    char *to_s_value2   = marg_object_to_string_with_hash(marg_obj2);
    assert_that_charptr(string_split(to_s_value2, '@')[0] equals to "$Integer");

    nassert_that_charptr(string_split(
      to_s_value1, '@'
    )[1] equals to string_split(to_s_value2, '@')[1]);
  });
})

#endif
