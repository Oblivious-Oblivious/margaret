#ifndef __INSTRUCTION_SPEC_H_
#define __INSTRUCTION_SPEC_H_

#include "../libs/cSpec/export/cSpec.h"
#include "instruction.h"
#include "object.h"
#include "opcode.h"
#include "vm.h"

VM _vm = {0};
VM *vm = &_vm;

static void reset_vm(void) { vm_init(vm); }

module(instruction_format_spec, {
  before_each(&reset_vm);

  it("correctly encodes and decodes mov instructions", {
    OAB(OP_MOV, LOCAL("x"), CONST(MARG_NUMBER(123)));
    OAB(OP_MOV, INSTANCE("@y"), CONST(MARG_NUMBER(456)));
    OAB(OP_MOV, GLOBAL("$z"), CONST(MARG_NUMBER(789)));
    OABC(OP_ADD, GLOBAL("$z"), INSTANCE("@y"), LOCAL("x"));

    vm->ip = 0;
    SRA(RB);

    assert_that_size_t(O equals to OP_MOV);
    assert_that_size_t(GET_INDEX(A) equals to 0);
    assert_that(IS_CONSTANT(B));
    assert_that_size_t(GET_INDEX(B) equals to 0);
    assert_that_size_t(AS_MARG_NUMBER(RA)->value equals to 123);
    assert_that_size_t(AS_MARG_NUMBER(RB)->value equals to 123);

    vm->ip = 1;
    SRA(RB);

    assert_that_size_t(O equals to OP_MOV);
    assert_that_size_t(GET_INDEX(A) equals to 1);
    assert_that(IS_CONSTANT(B));
    assert_that_size_t(GET_INDEX(B) equals to 1);
    assert_that_size_t(AS_MARG_NUMBER(RA)->value equals to 456);
    assert_that_size_t(AS_MARG_NUMBER(RB)->value equals to 456);

    vm->ip = 2;
    SRA(RB);

    assert_that_size_t(O equals to OP_MOV);
    assert_that_size_t(GET_INDEX(A) equals to 2);
    assert_that(IS_CONSTANT(B));
    assert_that_size_t(GET_INDEX(B) equals to 2);
    assert_that_size_t(AS_MARG_NUMBER(RA)->value equals to 789);
    assert_that_size_t(AS_MARG_NUMBER(RB)->value equals to 789);

    vm->ip = 3;
    SRA(MARG_NUMBER(AS_MARG_NUMBER(RB)->value + AS_MARG_NUMBER(RC)->value));

    assert_that_size_t(O equals to OP_ADD);
    assert_that_size_t(GET_INDEX(A) equals to 2);
    assert_that_size_t(GET_INDEX(B) equals to 1);
    assert_that_size_t(GET_INDEX(C) equals to 0);
    assert_that_size_t(AS_MARG_NUMBER(RA)->value equals to 579);
    assert_that_size_t(AS_MARG_NUMBER(RB)->value equals to 456);
    assert_that_size_t(AS_MARG_NUMBER(RC)->value equals to 123);
  });
})

#endif
