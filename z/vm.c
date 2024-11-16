#include "vm.h"

#include "primitives.h"

static void setup_proto_object_chain(VM *vm) {
  MargValue marg;

  SG(MARG_UNDEFINED, "$Margaret");
  marg = G("$Margaret");

  SG(marg, "$nil");
  SG(marg, "$false");
  SG(marg, "$true");

  SG(marg, "$Number");
  SG(marg, "$String");
  SG(marg, "$Method");
}

static void setup_vm_main(VM *vm) {
  MargValue marg = G("$Margaret");
  MargValue main = MARG_METHOD(AS_OBJECT(marg), NULL, "");
  table_add(&AS_OBJECT(marg)->messages, "", main);
  vm->current = AS_METHOD(main);
}

static void setup_primitives(VM *vm) {
  define_primitive(vm, "+", "$Number", (MargPrimitiveFunction)primitive_ADD);
  define_primitive(vm, "-", "$Number", (MargPrimitiveFunction)primitive_SUB);
  define_primitive(vm, "*", "$Number", (MargPrimitiveFunction)primitive_MUL);
  define_primitive(vm, "/", "$Number", (MargPrimitiveFunction)primitive_DIV);
}

void vm_init(VM *vm) {
  table_init(&vm->global_variables);

  setup_proto_object_chain(vm);
  setup_vm_main(vm);
  setup_primitives(vm);
}
