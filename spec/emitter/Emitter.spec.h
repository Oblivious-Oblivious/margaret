#ifndef __EMITTER_SPEC_H_
#define __EMITTER_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/emitter/Emitter.h"
#include "../../src/opcode/fmcodes.h"
#include "../../src/opcode/MargProc.h"
#include "../../src/opcode/opcodes.h"

static VM *vm;
static void initialize_vm(void) { vm = vm_new(); }

module(EmitterSpec, {
  before_each(&initialize_vm);

  // TODO Test for a `postcard` type mini program that includes every single
  // feature

  it("parses a simple program", {
    char **formal_bytecode = vector_new(FM_INTEGER, string_new("42"), FM_POP);
    vm                     = emitter_emit(vm, formal_bytecode);
    assert_that_int(vm->current->bytecode->size equals to 4);
    assert_that_int(vm->current->bytecode->items[0] equals to OP_PUT_OBJECT);
    assert_that_int(vm->current->bytecode->items[1] equals to 0);
    assert_that_int(vm->current->bytecode->items[2] equals to OP_POP);
    assert_that_int(vm->current->bytecode->items[3] equals to OP_HALT);
  });
})

#endif
