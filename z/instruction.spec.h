#ifndef __INSTRUCTION_SPEC_H_
#define __INSTRUCTION_SPEC_H_

#include "../libs/cSpec/export/cSpec.h"
#include "instruction.h"

VM _vm          = {0};
VM *vm          = &_vm;
Instruction *bc = NULL;

static void reset_vm(void) {
  vm_init(vm);
  bc = NULL;
}

#define R(i) (vm->registers[i])
#define K(i) (vm->constants[i])

#define O(i)  (uint16_t)(((i) & 0xffff000000000000) >> 48)
#define A(i)  (uint16_t)(((i) & 0x0000ffff00000000) >> 32)
#define B(i)  (uint16_t)(((i) & 0x00000000ffff0000) >> 16)
#define C(i)  (uint16_t)(((i) & 0x000000000000ffff) >> 0)
#define Ak(i) (uint32_t)(((i) & 0x0000ffffffff0000) >> 16)
#define Bk(i) (uint32_t)(((i) & 0x00000000ffffffff) >> 0)

#define RA(i)  R(A(i))
#define RB(i)  R(B(i))
#define RC(i)  R(C(i))
#define KAk(i) K(Ak(i))
#define KBk(i) K(Bk(i))

module(instruction_format_spec, {
  before_each(&reset_vm);

  it("#OP", {
    OP((Instruction)0xffff);
    assert_that_size_t(bc[0] equals to 0xffff000000000000);
    assert_that_size_t(O(bc[0]) equals to 0xffff);
  });

  it("#OAk", {
    OAk((Instruction)0xffff, 0xabcd);
    OAk((Instruction)0xffff, 0xabcd);
    assert_that_size_t(bc[1] equals to 0xffff000000010000);
    assert_that_size_t(O(bc[1]) equals to 0xffff);
    assert_that_size_t(KAk(bc[1]) equals to 0xabcd);
  });

  it("#OABk", {
    OABk((Instruction)0xffff, "x", 0xabcd);
    OABk((Instruction)0xffff, "y", 0xabcd);
    assert_that_size_t(bc[1] equals to 0xffff000100000001);
    assert_that_size_t(O(bc[1]) equals to 0xffff);
    assert_that_size_t(A(bc[1]) equals to 0x0001);
    assert_that_size_t(KBk(bc[1]) equals to 0xabcd);
  });

  it("#OA", {
    OA((Instruction)0xffff, "x");
    OA((Instruction)0xffff, "y");
    assert_that_size_t(bc[1] equals to 0xffff000100000000);
    assert_that_size_t(O(bc[1]) equals to 0xffff);
    assert_that_size_t(A(bc[1]) equals to 0x0001);
  });

  it("#OAB", {
    OAB((Instruction)0xffff, "a", "a");
    OAB((Instruction)0xffff, "c", "d");
    assert_that_size_t(bc[1] equals to 0xffff000100020000);
    assert_that_size_t(O(bc[1]) equals to 0xffff);
    assert_that_size_t(A(bc[1]) equals to 0x0001);
    assert_that_size_t(B(bc[1]) equals to 0x0002);
  });

  it("#OABC", {
    OABC((Instruction)0xffff, "a", "b", "c");
    OABC((Instruction)0xffff, "d", "e", "f");
    assert_that_size_t(bc[1] equals to 0xffff000300040005);
    assert_that_size_t(O(bc[1]) equals to 0xffff);
    assert_that_size_t(A(bc[1]) equals to 0x0003);
    assert_that_size_t(B(bc[1]) equals to 0x0004);
    assert_that_size_t(C(bc[1]) equals to 0x0005);
  });
})

#endif
