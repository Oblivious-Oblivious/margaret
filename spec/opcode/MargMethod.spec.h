#ifndef __MARG_METHOD_SPEC_H_
#define __MARG_METHOD_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"

module(MargMethodSpec, {
  it("tests QNAN boxed methods", {
    VM *vm        = vm_new("file.marg");
    MargValue x   = MARG_METHOD(AS_OBJECT(G("$Margaret")), vm->current, "msg");
    MargMethod *m = AS_METHOD(x);
    assert_that(x isnot MARG_UNDEFINED);
    assert_that_charptr(m->bound_object->name equals to "$Margaret");
    assert_that_charptr(m->bound_method->message_name equals to "");
    assert_that_charptr(m->message_name equals to "msg");
    assert_that_size_t(vector_size(m->constants) equals to 0);
    assert_that_size_t(table_size(&m->local_variables) equals to 0);
    assert_that_size_t(vector_size(m->bytecode) equals to 0);
    assert_that_size_t(m->ip equals to - 1);
  });

  it("ensures that the same method creates different QNAN boxed values", {
    VM *vm      = vm_new("file.marg");
    MargValue x = MARG_METHOD(AS_OBJECT(G("$Margaret")), vm->current, "msg");
    MargValue y = MARG_METHOD(AS_OBJECT(G("$Margaret")), vm->current, "msg");
    assert_that(x isnot y);
    assert_that_charptr(AS_METHOD(x)->message_name equals to "msg");
  });

  it("ensures that self and super are set correctly", {
    VM *vm        = vm_new("file.marg");
    MargValue x   = MARG_METHOD(AS_OBJECT(G("$Margaret")), vm->current, "msg");
    MargMethod *m = AS_METHOD(x);
    assert_that_charptr(m->bound_object->name equals to "$Margaret");
    assert_that_charptr(m->bound_method->message_name equals to "");
    assert_that_charptr(m->message_name equals to "msg");
    assert_that_size_t(vector_size(m->constants) equals to 0);
    assert_that_size_t(table_size(&m->local_variables) equals to 0);
    assert_that_size_t(vector_size(m->bytecode) equals to 0);
    assert_that_size_t(m->ip equals to - 1);
  });
})

#endif
