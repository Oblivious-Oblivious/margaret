#include "vm.h"

void vm_init(VM *vm) {
  vm->constants = NULL;
  vm->ip        = 0;
  vm->bytecode  = NULL;
  table_init(&vm->local_variables);
}

uint8_t vm_make_constant(VM *vm, Value value) {
  vector_add(vm->constants, value);
  return vector_size(vm->constants) - 1;
}
