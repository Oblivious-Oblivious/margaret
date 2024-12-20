#include "vm.h"

#include "../opcode/instruction.h"
#include "../primitives/BitstringPrimitives.h"
#include "../primitives/MargaretPrimitives.h"
#include "../primitives/NumericPrimitives.h"
#include "../primitives/StringPrimitives.h"
#include "../primitives/TablePrimitives.h"
#include "../primitives/TensorPrimitives.h"
#include "../primitives/TuplePrimitives.h"

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

#define define_prim(name, msg) \
  table_add(&vm->primitives, (name), MARG_PRIMITIVE((name), (msg)))

p_inline void setup_primitives(VM *vm) {
  define_prim("MARGARET_INSPECT:", __PRIM_INSPECT);
  define_prim("MARGARET_RAISE:", __PRIM_RAISE);
  define_prim("MARGARET_BIND:TO:", __PRIM_BIND);
  define_prim("MARGARET_MESSAGES:", __PRIM_MARGARET_MESSAGES);

  define_prim("NUMERIC_ADD:WITH:", __PRIM_NUMERIC_ADD);
  define_prim("NUMERIC_SUB:WITH:", __PRIM_NUMERIC_SUB);
  define_prim("NUMERIC_MUL:WITH:", __PRIM_NUMERIC_MUL);
  define_prim("NUMERIC_DIV:WITH:", __PRIM_NUMERIC_DIV);

  define_prim("STRING_ADD:STR:", __PRIM_STRING_ADD);
  define_prim("STRING_SIZE:", __PRIM_STRING_SIZE);
  define_prim("STRING_SHORTEN:TO:", __PRIM_STRING_SHORTEN);
  define_prim("STRING_SKIP_FIRST:CHARS:", __PRIM_STRING_SKIP_FIRST);
  define_prim("STRING_IGNORE_LAST:CHARS:", __PRIM_STRING_IGNORE_LAST);
  define_prim("STRING_DELETE:", __PRIM_STRING_DELETE);
  define_prim("STRING_REMOVE:CHAR:", __PRIM_STRING_REMOVE);
  define_prim("STRING_EQUALS:OTHER:", __PRIM_STRING_EQUALS);

  define_prim("TENSOR_ADD:ELEMENT:", __PRIM_TENSOR_ADD);
  define_prim("TENSOR_ADD:TENSOR:", __PRIM_TENSOR_ADD_TENSOR);
  define_prim("TENSOR_REMOVE:ELEMENT:", __PRIM_TENSOR_REMOVE);
  define_prim("TENSOR_REMOVE_LAST:", __PRIM_TENSOR_REMOVE_LAST);
  define_prim("TENSOR_LAST:", __PRIM_TENSOR_LAST);
  define_prim("TENSOR_SIZE:", __PRIM_TENSOR_SIZE);

  define_prim("TUPLE_ADD:ELEMENT:", __PRIM_TUPLE_ADD);
  define_prim("TUPLE_SIZE:", __PRIM_TUPLE_SIZE);

  define_prim("TABLE_ADD:KEY:VALUE:", __PRIM_TABLE_ADD);
  define_prim("TABLE_GET:KEY:", __PRIM_TABLE_GET);
  define_prim("TABLE_REMOVE:KEY:", __PRIM_TABLE_REMOVE);
  define_prim("TABLE_SIZE:", __PRIM_TABLE_SIZE);

  define_prim("BITSTRING_ADD:VALUE:BITS:", __PRIM_BITSTRING_ADD);
  define_prim("BITSTRING_SIZE:", __PRIM_BITSTRING_SIZE);
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
  table_init(&vm->primitives);

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

  vm->do_not_display = false;

  return vm;
}
