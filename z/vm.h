#ifndef __VM_H_
#define __VM_H_

#include "../libs/EmeraldsTable/export/EmeraldsTable.h"
#include "value.h"

#define MAX_REGISTERS (1 << 16)
typedef size_t Instruction;

typedef struct VM {
  MargValue global_registers[MAX_REGISTERS];
  uint16_t global_index;
  EmeraldsTable global_variables;
  struct MargMethod *current;
} VM;

void vm_init(VM *vm);

#endif
