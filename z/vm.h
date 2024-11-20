#ifndef __VM_H_
#define __VM_H_

#include "../libs/EmeraldsTable/export/EmeraldsTable.h"
#include "value.h"

typedef struct VM {
  MargValue global_registers[MAX_REGISTERS];
  uint32_t global_index;
  EmeraldsTable global_variables;
  struct MargMethod *current;
} VM;

void vm_init(VM *vm);

#endif
