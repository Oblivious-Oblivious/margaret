#ifndef __VM_H_
#define __VM_H_

#include "../libs/EmeraldsTable/export/EmeraldsTable.h"
#include "nan_tagging.h"

#define MAX_REGISTERS (2 << 7)
#define MAX_CONSTANTS (2 << 7)

typedef uint32_t Instruction;

typedef struct {
  Value registers[MAX_REGISTERS];
  Value constants[MAX_CONSTANTS];
  uint8_t num_constants;
  size_t ip;
  Instruction *bytecode;
  uint8_t current_reg_index;
  EmeraldsTable local_variables;
} VM;

void vm_init(VM *vm);
uint8_t vm_make_constant(VM *vm, Value value);

#endif
