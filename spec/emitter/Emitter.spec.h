#ifndef __EMITTER_SPEC_H_
#define __EMITTER_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/emitter/Emitter.h"
#include "../../src/opcode/fmcodes.h"
#include "../../src/opcode/MargProc.h"
#include "../../src/opcode/opcodes.h"

static VM *vm;
static void initialize_vm(void) { vm = vm_new("test.marg"); }

module(EmitterSpec, {
  before_each(&initialize_vm);

  // TODO - Test a `postcard` mini program including every single feature.

  it("parses a simple program", {
    vm->formal_bytecode = vector_new(FM_INTEGER, string_new("42"));
    vm                  = emitter_emit(vm);
    assert_that_int(vector_size(vm->current->bytecode) equals to 3);
    assert_that_int(vm->current->bytecode[0] equals to OP_PUT_OBJECT);
    assert_that_int(vm->current->bytecode[1] equals to 0);
    assert_that_int(vm->current->bytecode[2] equals to OP_HALT);
  });
})

#endif
