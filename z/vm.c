#include "vm.h"

void vm_init(VM *vm) {
  vm->ip        = 0;
  vm->bytecode  = NULL;
  vm->constants = NULL;

  table_init(&vm->local_variables);
  table_init(&vm->instance_variables);
  table_init(&vm->global_variables);
}
