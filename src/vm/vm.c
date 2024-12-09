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
  SG(margaret, "Variable");
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
    vm, "__PRIM_RAISE:", "$Margaret", (MargPrimitiveFunction)__PRIM_RAISE
  );
  define_primitive(
    vm, "__PRIM_INSPECT:", "$Margaret", (MargPrimitiveFunction)__PRIM_INSPECT
  );

  define_primitive(
    vm,
    "__PRIM_NUMERIC_ADD:",
    "$Numeric",
    (MargPrimitiveFunction)__PRIM_NUMERIC_ADD
  );
  define_primitive(
    vm,
    "__PRIM_NUMERIC_SUB:",
    "$Numeric",
    (MargPrimitiveFunction)__PRIM_NUMERIC_SUB
  );
  define_primitive(
    vm,
    "__PRIM_NUMERIC_MUL:",
    "$Numeric",
    (MargPrimitiveFunction)__PRIM_NUMERIC_MUL
  );
  define_primitive(
    vm,
    "__PRIM_NUMERIC_DIV:",
    "$Numeric",
    (MargPrimitiveFunction)__PRIM_NUMERIC_DIV
  );

  define_primitive(
    vm,
    "__PRIM_STRING_ADDN:",
    "$String",
    (MargPrimitiveFunction)__PRIM_STRING_ADDN
  );
  define_primitive(
    vm,
    "__PRIM_STRING_ADD:",
    "$String",
    (MargPrimitiveFunction)__PRIM_STRING_ADD
  );
  define_primitive(
    vm,
    "__PRIM_STRING_ADDI:",
    "$String",
    (MargPrimitiveFunction)__PRIM_STRING_ADDI
  );
  define_primitive(
    vm,
    "__PRIM_STRING_SIZE:",
    "$String",
    (MargPrimitiveFunction)__PRIM_STRING_SIZE
  );
  define_primitive(
    vm,
    "__PRIM_STRING_SHORTEN:",
    "$String",
    (MargPrimitiveFunction)__PRIM_STRING_SHORTEN
  );
  define_primitive(
    vm,
    "__PRIM_STRING_SKIP_FIRST:",
    "$String",
    (MargPrimitiveFunction)__PRIM_STRING_SKIP_FIRST
  );
  define_primitive(
    vm,
    "__PRIM_STRING_IGNORE_LAST:",
    "$String",
    (MargPrimitiveFunction)__PRIM_STRING_IGNORE_LAST
  );
  define_primitive(
    vm,
    "__PRIM_STRING_DELETE:",
    "$String",
    (MargPrimitiveFunction)__PRIM_STRING_DELETE
  );
  define_primitive(
    vm,
    "__PRIM_STRING_REMOVE:",
    "$String",
    (MargPrimitiveFunction)__PRIM_STRING_REMOVE
  );
  define_primitive(
    vm,
    "__PRIM_STRING_EQUALS:",
    "$String",
    (MargPrimitiveFunction)__PRIM_STRING_EQUALS
  );

  define_primitive(
    vm, "__PRIM_NEW:", "$Tensor", (MargPrimitiveFunction)__PRIM_TENSOR_NEW
  );
  define_primitive(
    vm,
    "__PRIM_TENSOR_ADD:",
    "$Tensor",
    (MargPrimitiveFunction)__PRIM_TENSOR_ADD
  );
  define_primitive(
    vm,
    "__PRIM_TENSOR_ADD_TENSOR:",
    "$Tensor",
    (MargPrimitiveFunction)__PRIM_TENSOR_ADD_TENSOR
  );
  define_primitive(
    vm,
    "__PRIM_TENSOR_REMOVE:",
    "$Tensor",
    (MargPrimitiveFunction)__PRIM_TENSOR_REMOVE
  );
  define_primitive(
    vm,
    "__PRIM_TENSOR_REMOVE_LAST:",
    "$Tensor",
    (MargPrimitiveFunction)__PRIM_TENSOR_REMOVE_LAST
  );
  define_primitive(
    vm,
    "__PRIM_TENSOR_LAST:",
    "$Tensor",
    (MargPrimitiveFunction)__PRIM_TENSOR_LAST
  );
  define_primitive(
    vm,
    "__PRIM_TENSOR_SIZE:",
    "$Tensor",
    (MargPrimitiveFunction)__PRIM_TENSOR_SIZE
  );

  define_primitive(
    vm, "__PRIM_NEW:", "$Tuple", (MargPrimitiveFunction)__PRIM_TUPLE_NEW
  );
  define_primitive(
    vm, "__PRIM_TUPLE_ADD:", "$Tuple", (MargPrimitiveFunction)__PRIM_TUPLE_ADD
  );
  define_primitive(
    vm, "__PRIM_TUPLE_SIZE:", "$Tuple", (MargPrimitiveFunction)__PRIM_TUPLE_SIZE
  );

  define_primitive(
    vm, "__PRIM_NEW:", "$Table", (MargPrimitiveFunction)__PRIM_TABLE_NEW
  );
  define_primitive(
    vm, "__PRIM_TABLE_ADD:", "$Table", (MargPrimitiveFunction)__PRIM_TABLE_ADD
  );
  define_primitive(
    vm, "__PRIM_TABLE_GET:", "$Table", (MargPrimitiveFunction)__PRIM_TABLE_GET
  );
  define_primitive(
    vm,
    "__PRIM_TABLE_REMOVE:",
    "$Table",
    (MargPrimitiveFunction)__PRIM_TABLE_REMOVE
  );
  define_primitive(
    vm, "__PRIM_TABLE_SIZE:", "$Table", (MargPrimitiveFunction)__PRIM_TABLE_SIZE
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
  define_primitive(
    vm,
    "__PRIM_BITSTRING_SIZE:",
    "$Bitstring",
    (MargPrimitiveFunction)__PRIM_BITSTRING_SIZE
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
