#include "vm.h"

#include "nan_tagging.h"

static void setup_proto_object_chain(VM *vm) {
  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$Margaret");

  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$nil");
  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$false");
  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$true");

  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$Number");
  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$String");
  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$Method");
}

static void setup_vm_main(VM *vm) {
  Value marg = table_get(&vm->global_variables, "$Margaret");
  Value main = MARG_METHOD(AS_MARG_OBJECT(marg), NULL, "");
  table_add(&AS_MARG_OBJECT(marg)->messages, "", main);
  vm->current = AS_MARG_METHOD(main);
}

void vm_init(VM *vm) {
  table_init(&vm->global_variables);

  setup_proto_object_chain(vm);
  setup_vm_main(vm);
}
