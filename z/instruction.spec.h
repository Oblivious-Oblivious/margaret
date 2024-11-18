#ifndef __INSTRUCTION_SPEC_H_
#define __INSTRUCTION_SPEC_H_

#include "../libs/cSpec/export/cSpec.h"
#include "helpers.spec.h"
#include "instruction.h"
#include "nan_tagging.h"
#include "opcode.h"

module(instruction_spec, {
  before_each(&reset_vm);

  it("masks and unmasks values correctly", {
    Instruction l1 = LOCAL("l1");
    assert_that_size_t(GET_INDEX(l1) equals to 0);
    Instruction l2 = LOCAL("l2");
    assert_that_size_t(GET_INDEX(l2) equals to 1);

    Instruction i1 = INSTANCE("@i1");
    assert_that_size_t(GET_INDEX(i1) equals to 2);
    Instruction i2 = INSTANCE("@i2");
    assert_that_size_t(GET_INDEX(i2) equals to 3);

    Instruction g1 = GLOBAL("$g1");
    assert_that_size_t(GET_INDEX(g1) equals to 8);
    Instruction g2 = GLOBAL("$g2");
    assert_that_size_t(GET_INDEX(g2) equals to 9);

    Instruction i3 = INSTANCE("@i3");
    Instruction g3 = GLOBAL("$g3");
    Instruction i4 = INSTANCE("@i4");
    assert_that_size_t(GET_INDEX(i3) equals to 4);
    assert_that_size_t(GET_INDEX(g3) equals to 10);
    assert_that_size_t(GET_INDEX(i4) equals to 5);

    Instruction l3 = LOCAL("l3");
    assert_that_size_t(GET_INDEX(l3) equals to 2);
    Instruction g4 = GLOBAL("$g4");
    assert_that_size_t(GET_INDEX(g4) equals to 11);
  });

  it("does not override values in each register table", {
    OAB(OP_MOV, LOCAL("l1"), CONST(MARG_NUMBER(123)));
    OAB(OP_MOV, INSTANCE("@i1"), CONST(MARG_NUMBER(456)));
    OAB(OP_MOV, GLOBAL("$g1"), CONST(MARG_NUMBER(789)));

    assert_that_size_t(GET_INDEX(LOCAL("l1")) equals to 0);
    assert_that_size_t(GET_INDEX(INSTANCE("@i1")) equals to 2);
    assert_that_size_t(GET_INDEX(GLOBAL("$g1")) equals to 8);

    assert_that(IS_LOCAL(LOCAL("l1")));
    assert_that(IS_INSTANCE(INSTANCE("@i1")));
    assert_that(IS_GLOBAL(GLOBAL("$g1")));

    vm->current->ip = 0;
    SRA(RB);
    assert_that_size_t(AS_NUMBER(RA)->value equals to 123);

    vm->current->ip = 1;
    SRA(RB);
    assert_that_size_t(AS_NUMBER(RA)->value equals to 456);

    vm->current->ip = 2;
    SRA(RB);
    assert_that_size_t(AS_NUMBER(RA)->value equals to 789);
  });

  it("correctly encodes and decodes mov instructions", {
    OAB(OP_MOV, LOCAL("l1"), CONST(MARG_NUMBER(123)));
    OAB(OP_MOV, INSTANCE("@i1"), CONST(MARG_NUMBER(456)));
    OAB(OP_MOV, GLOBAL("$g1"), CONST(MARG_NUMBER(789)));
    OAB(OP_MOV, LOCAL("l2"), CONST(MARG_NUMBER(321)));
    OAB(OP_MOV, LOCAL("l3"), CONST(MARG_NUMBER(321321)));
    OAB(OP_MOV, INSTANCE("@i2"), CONST(MARG_NUMBER(654)));
    OAB(OP_MOV, GLOBAL("$g2"), CONST(MARG_NUMBER(987)));
    OAB(OP_MOV, INSTANCE("@i3"), CONST(MARG_NUMBER(654654)));

    vm->current->ip = 0;
    SRA(RB);

    assert_that_size_t(O equals to OP_MOV);
    assert_that(IS_LOCAL(A));
    assert_that_size_t(GET_INDEX(A) equals to 0);
    assert_that(IS_CONSTANT(B));
    assert_that_size_t(GET_INDEX(B) equals to 0);
    assert_that_size_t(AS_NUMBER(RA)->value equals to 123);
    assert_that_size_t(AS_NUMBER(RB)->value equals to 123);

    vm->current->ip = 1;
    SRA(RB);

    assert_that_size_t(O equals to OP_MOV);
    assert_that(IS_INSTANCE(A));
    assert_that_size_t(GET_INDEX(A) equals to 2);
    assert_that(IS_CONSTANT(B));
    assert_that_size_t(GET_INDEX(B) equals to 1);
    assert_that_size_t(AS_NUMBER(RA)->value equals to 456);
    assert_that_size_t(AS_NUMBER(RB)->value equals to 456);

    vm->current->ip = 2;
    SRA(RB);

    assert_that_size_t(O equals to OP_MOV);
    assert_that(IS_GLOBAL(A));
    assert_that_size_t(GET_INDEX(A) equals to 8);
    assert_that(IS_CONSTANT(B));
    assert_that_size_t(GET_INDEX(B) equals to 2);
    assert_that_size_t(AS_NUMBER(RA)->value equals to 789);
    assert_that_size_t(AS_NUMBER(RB)->value equals to 789);

    vm->current->ip = 3;
    SRA(RB);

    assert_that_size_t(O equals to OP_MOV);
    assert_that(IS_LOCAL(A));
    assert_that_size_t(GET_INDEX(A) equals to 1);
    assert_that(IS_CONSTANT(B));
    assert_that_size_t(GET_INDEX(B) equals to 3);
    assert_that_size_t(AS_NUMBER(RA)->value equals to 321);
    assert_that_size_t(AS_NUMBER(RB)->value equals to 321);

    vm->current->ip = 4;
    SRA(RB);

    assert_that_size_t(O equals to OP_MOV);
    assert_that(IS_LOCAL(A));
    assert_that_size_t(GET_INDEX(A) equals to 2);
    assert_that(IS_CONSTANT(B));
    assert_that_size_t(GET_INDEX(B) equals to 4);
    assert_that_size_t(AS_NUMBER(RA)->value equals to 321321);
    assert_that_size_t(AS_NUMBER(RB)->value equals to 321321);

    vm->current->ip = 5;
    SRA(RB);

    assert_that_size_t(O equals to OP_MOV);
    assert_that(IS_INSTANCE(A));
    assert_that_size_t(GET_INDEX(A) equals to 3);
    assert_that(IS_CONSTANT(B));
    assert_that_size_t(GET_INDEX(B) equals to 5);
    assert_that_size_t(AS_NUMBER(RA)->value equals to 654);
    assert_that_size_t(AS_NUMBER(RB)->value equals to 654);

    vm->current->ip = 6;
    SRA(RB);

    assert_that_size_t(O equals to OP_MOV);
    assert_that(IS_GLOBAL(A));
    assert_that_size_t(GET_INDEX(A) equals to 9);
    assert_that(IS_CONSTANT(B));
    assert_that_size_t(GET_INDEX(B) equals to 6);
    assert_that_size_t(AS_NUMBER(RA)->value equals to 987);
    assert_that_size_t(AS_NUMBER(RB)->value equals to 987);

    vm->current->ip = 7;
    SRA(RB);

    assert_that_size_t(O equals to OP_MOV);
    assert_that(IS_INSTANCE(A));
    assert_that_size_t(GET_INDEX(A) equals to 4);
    assert_that(IS_CONSTANT(B));
    assert_that_size_t(GET_INDEX(B) equals to 7);
    assert_that_size_t(AS_NUMBER(RA)->value equals to 654654);
    assert_that_size_t(AS_NUMBER(RB)->value equals to 654654);
  });
})

#endif
