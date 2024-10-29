#ifndef __VM_H_
#define __VM_H_

#include "../libs/EmeraldsTable/export/EmeraldsTable.h"
#include "nan_tagging.h"

#define MAX_LOCALS    (1 << 16)
#define MAX_INSTANCES (1 << 16)
#define MAX_GLOBALS   (1 << 16)

typedef size_t Instruction;

typedef struct VM {
  size_t ip;
  Instruction *bytecode;
  Value *constants;

  Value locals[MAX_LOCALS];
  Value instances[MAX_INSTANCES];
  Value globals[MAX_GLOBALS];

  EmeraldsTable local_variables;
  EmeraldsTable instance_variables;
  EmeraldsTable global_variables;
} VM;

void vm_init(VM *vm);

#endif
