#include "vm.h"

void vm_init(VM *vm) {
  vm->constants = NULL;
  vm->ip        = 0;
  vm->bytecode  = NULL;
  table_init(&vm->local_variables);
}
