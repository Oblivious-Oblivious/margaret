#include "vm.h"

#include "../opcode/instruction.h"
#include "../primitives/Primitives.h"

/**
 * @brief Setup ad-hoc $Margaret object
 * @param vm -> Current vm
 */
p_inline void setup_margaret(VM *vm) {
  MargValue marg                         = SG(MARG_UNDEFINED, "$Margaret");
  AS_OBJECT(marg)->proto                 = AS_OBJECT(marg);
  AS_OBJECT(marg)->instance_registers[1] = marg;
}

/**
 * @brief Sets up the delegation chain of proto objects
    and defines rudimentary messages like self and super
 * @param vm -> Current vm
 */
p_inline void setup_proto_object_chain(VM *vm) {
  MargValue margaret;
  MargValue numeric;
  MargValue string;
  MargValue enumerable;
  MargValue tensor;

  margaret = G("$Margaret");

  SG(margaret, "$nil");
  SG(margaret, "$false");
  SG(margaret, "$true");

  numeric = SG(margaret, "$Numeric");
  SG(numeric, "$Integer");
  SG(numeric, "$Float");

  string = SG(margaret, "$String");
  SG(string, "$Label");
  SG(string, "$Symbol");

  enumerable = SG(margaret, "$Enumerable");
  tensor     = SG(enumerable, "$Tensor");
  SG(tensor, "$Tuple");
  SG(enumerable, "$Table");
  SG(enumerable, "$Bitstring");

  SG(margaret, "$Method");
  SG(margaret, "Primitive");
}

/**
 * @brief Defines main entry point that is inaccessible lexically
 * @param vm -> Current vm
 */
p_inline void setup_main(VM *vm) {
  MargValue main_method;
  MargValue margaret = G("$Margaret");
  main_method        = MARG_METHOD(AS_OBJECT(margaret), NULL, "");
  AS_METHOD(main_method)->bound_method = AS_METHOD(main_method);
  table_add(&AS_OBJECT(margaret)->messages, "", main_method);
  vm->current = AS_METHOD(main_method);
}

p_inline void setup_primitives(VM *vm) {
  define_primitive(
    vm, "__PRIM_INSPECT:", "$Margaret", (MargPrimitiveFunction)__PRIM_INSPECT
  );

  define_primitive(
    vm, "__PRIM_ADD:", "$Numeric", (MargPrimitiveFunction)__PRIM_ADD
  );
  define_primitive(
    vm, "__PRIM_SUB:", "$Numeric", (MargPrimitiveFunction)__PRIM_SUB
  );
  define_primitive(
    vm, "__PRIM_MUL:", "$Numeric", (MargPrimitiveFunction)__PRIM_MUL
  );
  define_primitive(
    vm, "__PRIM_DIV:", "$Numeric", (MargPrimitiveFunction)__PRIM_DIV
  );

  define_primitive(
    vm, "__PRIM_NEW:", "$Tensor", (MargPrimitiveFunction)__PRIM_TENSOR_NEW
  );
  /* define_primitive(
    vm,
    "__PRIM_TENSOR_ADD:",
    "$Tensor",
    (MargPrimitiveFunction)__PRIM_TENSOR_ADD
  ); */

  define_primitive(
    vm, "__PRIM_NEW:", "$Tuple", (MargPrimitiveFunction)__PRIM_TUPLE_NEW
  );
  /* define_primitive(
    vm,
    "__PRIM_TUPLE_ADD:",
    "$Tuple",
    (MargPrimitiveFunction)__PRIM_TUPLE_ADD
  ); */

  define_primitive(
    vm, "__PRIM_NEW:", "$Table", (MargPrimitiveFunction)__PRIM_TABLE_NEW
  );
  define_primitive(
    vm, "__PRIM_TABLE_ADD:", "$Table", (MargPrimitiveFunction)__PRIM_TABLE_ADD
  );

  define_primitive(
    vm, "__PRIM_NEW:", "$Bitstring", (MargPrimitiveFunction)__PRIM_BITSTRING_NEW
  );
  define_primitive(
    vm,
    "__PRIM_BITSTRING_ADD:",
    "$Bitstring",
    (MargPrimitiveFunction)__PRIM_BITSTRING_ADD
  );
}

VM *vm_new(const char *filename) {
  size_t i;
  /* TODO - Maybe convert to initializer */
  VM *vm = (VM *)malloc(sizeof(VM));

  vm->filename    = string_new(filename);
  vm->source      = NULL;
  vm->lineno      = 1;
  vm->charno      = 0;
  vm->error       = NULL;
  vm->error_token = NULL;

  vm->tid = 0;
  tokens_init(&vm->tokens);
  vm->formal_bytecode = NULL;

  vm->global_index = 0;
  table_init(&vm->global_variables);

  setup_margaret(vm);
  setup_proto_object_chain(vm);
  setup_main(vm);
  setup_primitives(vm);

  for(i = vm->global_index; i < MAX_REGISTERS; i++) {
    vm->global_registers[i] = MARG_NIL;
  }
  for(i = vm->current->bound_object->instance_index; i < MAX_REGISTERS; i++) {
    vm->current->bound_object->instance_registers[i] = MARG_NIL;
  }
  for(i = vm->current->local_index; i < MAX_REGISTERS; i++) {
    vm->current->local_registers[i] = MARG_NIL;
  }

  return vm;
}
