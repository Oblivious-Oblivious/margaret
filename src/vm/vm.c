#include "vm.h"

#include "../opcode/MargValue.h"

/**
 * @brief Sets up the delegation chain of proto objects
    and defines rudimentary messages like self and super
 * @param vm -> Current vm
 */
static void setup_proto_object_chain(VM *vm) {
  /* TODO - Define as $(obj)Proto $Float = $FloatProto clone, or have literals
   * define themselves as $(obj)Literal like $FloatInstance = $Float clone  */
  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$Margaret");

  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$nil");
  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$false");
  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$true");

  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$Numeric");
  MARG_OBJECT(table_get(&vm->global_variables, "$Numeric"), "$Integer");
  MARG_OBJECT(table_get(&vm->global_variables, "$Numeric"), "$Float");

  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$Label");
  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$String");

  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$Enumerable");
  MARG_OBJECT(table_get(&vm->global_variables, "$Enumerable"), "$Tensor");
  MARG_OBJECT(table_get(&vm->global_variables, "$Tensor"), "$Tuple");
  MARG_OBJECT(table_get(&vm->global_variables, "$Enumerable"), "$Hash");
  MARG_OBJECT(table_get(&vm->global_variables, "$Enumerable"), "$Bitstring");

  MARG_OBJECT(table_get(&vm->global_variables, "$Margaret"), "$Method");
}

/**
 * @brief Defines the main entry point of execution
 * @param vm -> Current vm
 */
static void define_main_method(VM *vm) {
  MargObject *margaret =
    AS_OBJECT(table_get(&vm->global_variables, "$Margaret"));
  MargMethod *method = AS_METHOD(MARG_METHOD(margaret, ""));
  table_add(&margaret->messages, "", QNAN_BOX(method));
}

static void point_ip_to_main_method(VM *vm) {
  MargObject *margaret =
    AS_OBJECT(table_get(&vm->global_variables, "$Margaret"));
  MargMethod *method = AS_METHOD(table_get(&margaret->messages, ""));
  vm->current        = method->proc;
}

VM *vm_new(const char *filename) {
  VM *vm = (VM *)malloc(sizeof(VM));

  vm->filename = filename;
  vm->source   = NULL;
  vm->lineno   = 1;
  vm->charno   = 0;
  vm->error    = NULL;

  vm->tid = 0;
  tokens_init(&vm->tokens);
  vm->formal_bytecode = NULL;

  /* TODO - Remove */
  vm->sp = vm->stack;

  table_init(&vm->global_variables);
  table_init(&vm->interned_strings);
  vm->current = NULL;

  setup_proto_object_chain(vm);
  /* define_main_method(vm);
  point_ip_to_main_method(vm); */

  return vm;
}
