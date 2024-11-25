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
    vm, "inspect:", "$Margaret", (MargPrimitiveFunction)primitive_INSPECT
  );
  define_primitive(vm, "+", "$Numeric", (MargPrimitiveFunction)primitive_ADD);
  define_primitive(vm, "-", "$Numeric", (MargPrimitiveFunction)primitive_SUB);
  define_primitive(vm, "*", "$Numeric", (MargPrimitiveFunction)primitive_MUL);
  define_primitive(vm, "/", "$Numeric", (MargPrimitiveFunction)primitive_DIV);
}

VM *vm_new(const char *filename) {
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

  return vm;
}
