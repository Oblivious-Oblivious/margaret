#include "vm.h"

void vm_init(VM *vm) {
  vm->num_constants     = 0;
  vm->ip                = 0;
  vm->bytecode          = NULL;
  vm->current_reg_index = 0;
  table_init(&vm->local_variables);
}

uint8_t vm_make_constant(VM *vm, Value value) {
  vm->constants[vm->num_constants++] = value;
  return vm->num_constants - 1;
}
