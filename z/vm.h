#ifndef __VM_H_
#define __VM_H_

#include "../libs/EmeraldsTable/export/EmeraldsTable.h"
#include "nan_tagging.h"

#define MAX_REGISTERS (1 << 16)

typedef size_t Instruction;

typedef struct VM {
  size_t ip;
  Instruction *bytecode;

  Value *constants;
  Value registers[MAX_REGISTERS];

  EmeraldsTable local_variables;
  EmeraldsTable instance_variables;
  EmeraldsTable global_variables;
} VM;

void vm_init(VM *vm);

#endif
