#ifndef __VM_H_
#define __VM_H_

#include "../libs/EmeraldsTable/export/EmeraldsTable.h"
#include "value.h"

#define MAX_REGISTERS (1 << 16)
typedef size_t Instruction;

typedef struct VM {
  Value global_registers[MAX_REGISTERS];
  EmeraldsTable global_variables;
  struct Method *current;
} VM;

void vm_init(VM *vm);

#endif
