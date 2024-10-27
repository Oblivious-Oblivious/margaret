#ifndef __INSTRUCTION_SPEC_H_
#define __INSTRUCTION_SPEC_H_

#include "../libs/cSpec/export/cSpec.h"
#include "instruction.h"

VM _vm = {0};
VM *vm = &_vm;

static void reset_vm(void) {
  vm_init(vm);
  vm->ip++;
}

module(instruction_format_spec, {
  before_each(&reset_vm);

  it("#OP", {
    OP((Instruction)0xffff);
    assert_that_size_t(vm->bytecode[0] equals to 0xffff000000000000);
    assert_that_size_t(O equals to 0xffff);
  });

  it("#OAk", {
    OAk((Instruction)0xffff, 0xabcd);
    OAk((Instruction)0xffff, 0xabcd);
    vm->ip++;
    assert_that_size_t(vm->bytecode[1] equals to 0xffff000000010000);
    assert_that_size_t(O equals to 0xffff);
    assert_that_size_t(KAk equals to 0xabcd);
  });

  it("#OABk", {
    OABk((Instruction)0xffff, "x", 0xabcd);
    OABk((Instruction)0xffff, "y", 0xabcd);
    vm->ip++;
    assert_that_size_t(vm->bytecode[1] equals to 0xffff000100000001);
    assert_that_size_t(O equals to 0xffff);
    assert_that_size_t(A equals to 0x0001);
    assert_that_size_t(KBk equals to 0xabcd);
  });

  it("#OA", {
    OA((Instruction)0xffff, "x");
    OA((Instruction)0xffff, "y");
    vm->ip++;
    assert_that_size_t(vm->bytecode[1] equals to 0xffff000100000000);
    assert_that_size_t(O equals to 0xffff);
    assert_that_size_t(A equals to 0x0001);
  });

  it("#OAB", {
    OAB((Instruction)0xffff, "a", "a");
    OAB((Instruction)0xffff, "c", "d");
    vm->ip++;
    assert_that_size_t(vm->bytecode[1] equals to 0xffff000100020000);
    assert_that_size_t(O equals to 0xffff);
    assert_that_size_t(A equals to 0x0001);
    assert_that_size_t(B equals to 0x0002);
  });

  it("#OABC", {
    OABC((Instruction)0xffff, "a", "b", "c");
    OABC((Instruction)0xffff, "d", "e", "f");
    vm->ip++;
    assert_that_size_t(vm->bytecode[1] equals to 0xffff000300040005);
    assert_that_size_t(O equals to 0xffff);
    assert_that_size_t(A equals to 0x0003);
    assert_that_size_t(B equals to 0x0004);
    assert_that_size_t(C equals to 0x0005);
  });
})

#endif
