#include "vm.h"

#include "../opcode/MargValue.h"

/**
 * @brief Creates a proto object with a predefined parent slot.
    Sets up @self and @super instances and initially has no methods.
    Proto chain is always global.
 * @param vm -> Current vm
 * @param parent_name -> Name of parent object to bind to
 * @param name -> Name of the new proto
 * @return MargValue -> New object value
 */
MargValue create_new_proto_object(VM *vm, char *parent_name, char *name) {
  MargValue proto_object  = MARG_OBJECT(name);
  MargValue parent_object = table_get(&vm->global_variables, parent_name);

  table_add(&vm->global_variables, name, proto_object);
  table_add(
    &AS_OBJECT(proto_object)->instance_variables, "@self", proto_object
  );
  table_add(
    &AS_OBJECT(proto_object)->instance_variables, "@super", parent_object
  );
  AS_OBJECT(proto_object)->parent = AS_OBJECT(parent_object);

  return proto_object;
}

/**
 * @brief Sets up the delegation chain of proto objects
    and defines rudimentary messages like self and super
 * @param vm -> Current vm
 */
static void setup_proto_object_chain(VM *vm) {
  create_new_proto_object(vm, "$Margaret", "$Margaret");

  create_new_proto_object(vm, "$Margaret", "$nil");
  create_new_proto_object(vm, "$Margaret", "$false");
  create_new_proto_object(vm, "$Margaret", "$true");

  create_new_proto_object(vm, "$Margaret", "$Numeric");
  create_new_proto_object(vm, "$Numeric", "$Integer");
  create_new_proto_object(vm, "$Numeric", "$Float");

  create_new_proto_object(vm, "$Margaret", "$String");

  create_new_proto_object(vm, "$Margaret", "$Enumerable");
  create_new_proto_object(vm, "$Enumerable", "$Tensor");
  /* create_new_proto_object(vm, "$Tensor", "$Tuple"); */
  create_new_proto_object(vm, "$Enumerable", "$Hash");
  /* create_new_proto_object(vm, "$Enumerable", "$Bitstring"); */

  create_new_proto_object(vm, "$Margaret", "$Method");
  create_new_proto_object(vm, "$Margaret", "$Proc");
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

  vm->filename  = filename;
  vm->source    = NULL;
  vm->lineno    = 1;
  vm->charno    = 0;
  vm->index     = 0;
  vm->has_error = false;

  vm->eof_token       = token_new(string_new("eof"), TOKEN_EOF, 1, 1);
  vm->tokens          = NULL;
  vm->formal_bytecode = NULL;

  vm->sp = vm->stack;

  table_init(&vm->global_variables);
  table_init(&vm->interned_strings);
  vm->current = NULL;

  setup_proto_object_chain(vm);
  define_main_method(vm);
  point_ip_to_main_method(vm);

  return vm;
}
