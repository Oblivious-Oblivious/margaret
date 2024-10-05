#ifndef __VM_H_
#define __VM_H_

#include "../libs/EmeraldsTable/export/EmeraldsTable.h"
#include "nan_tagging.h"

#define MAX_REGISTERS (1 << 16)

typedef size_t Instruction;

typedef struct {
  Value registers[MAX_REGISTERS];
  Value *constants;
  size_t ip;
  Instruction *bytecode;
  EmeraldsTable local_variables;
} VM;

void vm_init(VM *vm);
Instruction vm_make_constant(VM *vm, Value value);

#endif
