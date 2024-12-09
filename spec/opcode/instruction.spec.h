#ifndef __INSTRUCTION_SPEC_H_
#define __INSTRUCTION_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/instruction.h"
#include "../../src/opcode/opcodes.h"

static VM *vm;
static void reset_vm(void) { vm = vm_new("file.marg"); }

module(instruction_spec, {
  before_each(&reset_vm);

  it("masks and unmasks values correctly", {
    Instruction l1 = LOCAL("l1");
    assert_that_size_t(l1 equals to 0);
    Instruction l2 = LOCAL("l2");
    assert_that_size_t(l2 equals to 1);

    Instruction i1 = INSTANCE("@i1");
    assert_that_size_t(i1 equals to 2);
    Instruction i2 = INSTANCE("@i2");
    assert_that_size_t(i2 equals to 3);

    Instruction g1 = GLOBAL("$g1");
    assert_that_size_t(g1 equals to 18);
    Instruction g2 = GLOBAL("$g2");
    assert_that_size_t(g2 equals to 19);

    Instruction i3 = INSTANCE("@i3");
    Instruction g3 = GLOBAL("$g3");
    Instruction i4 = INSTANCE("@i4");
    assert_that_size_t(i3 equals to 4);
    assert_that_size_t(g3 equals to 20);
    assert_that_size_t(i4 equals to 5);

    Instruction l3 = LOCAL("l3");
    assert_that_size_t(l3 equals to 2);
    Instruction g4 = GLOBAL("$g4");
    assert_that_size_t(g4 equals to 21);
  });

  it("does not override values in each register table", {
    OA(OP_STOZK, CONST(MARG_INTEGER(123)));
    OA(OP_LODZL, LOCAL("l1"));
    OA(OP_STOZK, CONST(MARG_INTEGER(456)));
    OA(OP_LODZI, INSTANCE("@i1"));
    OA(OP_STOZK, CONST(MARG_INTEGER(789)));
    OA(OP_LODZG, GLOBAL("$g1"));

    assert_that_size_t(LOCAL("l1") equals to 0);
    assert_that_size_t(INSTANCE("@i1") equals to 2);
    assert_that_size_t(GLOBAL("$g1") equals to 18);

    vm->current->ip = 0;
    CONST(KA);
    assert_that_size_t(AS_INTEGER(KZ)->value equals to 123);
    vm->current->ip++;
    SLA(KZ);
    assert_that_size_t(AS_INTEGER(LA)->value equals to 123);
    assert_that_size_t(AS_INTEGER(KZ)->value equals to 123);

    vm->current->ip++;
    CONST(KA);
    assert_that_size_t(AS_INTEGER(KZ)->value equals to 456);
    vm->current->ip++;
    SIA(KZ);
    assert_that_size_t(AS_INTEGER(IA)->value equals to 456);
    assert_that_size_t(AS_INTEGER(KZ)->value equals to 456);

    vm->current->ip++;
    CONST(KA);
    assert_that_size_t(AS_INTEGER(KZ)->value equals to 789);
    vm->current->ip++;
    SGA(KZ);
    assert_that_size_t(AS_INTEGER(GA)->value equals to 789);
    assert_that_size_t(AS_INTEGER(KZ)->value equals to 789);
  });
})

#endif
