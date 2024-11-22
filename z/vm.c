#include "vm.h"

#include "primitives.h"

static void setup_margaret(VM *vm) {
  MargValue marg         = SG(MARG_UNDEFINED, "$Margaret");
  AS_OBJECT(marg)->proto = AS_OBJECT(marg);
}

static void setup_proto_object_chain(VM *vm) {
  MargValue marg = G("$Margaret");

  SG(marg, "$nil");
  SG(marg, "$false");
  SG(marg, "$true");

  SG(marg, "$Number");
  SG(marg, "$Label");
  SG(marg, "$String");
  SG(marg, "$Method");
  SG(marg, "Primitive");
}

static void setup_main(VM *vm) {
  MargValue main;
  MargValue marg                = G("$Margaret");
  main                          = MARG_METHOD(AS_OBJECT(marg), NULL, "");
  AS_METHOD(main)->bound_method = AS_METHOD(main);
  table_add(&AS_OBJECT(marg)->messages, "", main);
  vm->current = AS_METHOD(main);
}

static void setup_primitives(VM *vm) {
  define_primitive(
    vm, "inspect:", "$Margaret", (MargPrimitiveFunction)primitive_INSPECT
  );
  define_primitive(vm, "+", "$Number", (MargPrimitiveFunction)primitive_ADD);
  define_primitive(vm, "-", "$Number", (MargPrimitiveFunction)primitive_SUB);
  define_primitive(vm, "*", "$Number", (MargPrimitiveFunction)primitive_MUL);
  define_primitive(vm, "/", "$Number", (MargPrimitiveFunction)primitive_DIV);
}

void vm_init(VM *vm) {
  vm->global_index = 0;
  table_init(&vm->global_variables);

  setup_margaret(vm);
  setup_proto_object_chain(vm);
  setup_main(vm);
  setup_primitives(vm);
}
