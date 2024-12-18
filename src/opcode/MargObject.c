#include "MargObject.h"

#include "instruction.h"

MargObject *
marg_object_init(VM *vm, size_t size, MargValue proto, const char *name) {
  MargObject *self = (MargObject *)malloc(size);

  self->is_marked = false;
  self->next      = NULL;

  self->bound_vm = vm;

  self->name      = name;
  self->name_hash = komihash_hash(name, string_size(name));
  self->proto     = AS_OBJECT(proto);

  self->instance_index = 0;
  table_init(&self->instance_variables);
  table_init(&self->messages);

  if(!IS_UNDEFINED(proto)) {
    table_add_all_non_labels(
      &self->proto->instance_variables, &self->instance_variables
    );
  }

  table_add(&self->instance_variables, "@self", self->instance_index);
  self->instance_registers[self->instance_index++] = QNAN_BOX(self);
  table_add(&self->instance_variables, "@super", self->instance_index);
  self->instance_registers[self->instance_index++] = QNAN_BOX(self->proto);

  return self;
}

MargInteger *marg_integer_init(VM *vm, ptrdiff_t value) {
  MargObject *obj = (MargObject *)marg_object_init(
    vm, sizeof(MargInteger), G("$Integer"), string_new("")
  );
  MargInteger *self = (MargInteger *)obj;

  self->value = value;

  return self;
}

MargFloat *marg_float_init(VM *vm, double value) {
  MargObject *obj =
    marg_object_init(vm, sizeof(MargFloat), G("$Float"), string_new(""));
  MargFloat *self = (MargFloat *)obj;

  self->value = value;

  return self;
}

MargSymbol *marg_symbol_init(VM *vm, char *value) {
  MargObject *obj = (MargObject *)marg_object_init(
    vm, sizeof(MargSymbol), G("$Symbol"), string_new("")
  );
  MargSymbol *self = (MargSymbol *)obj;

  self->value = string_new(value);

  return self;
}

MargLabel *marg_label_init(VM *vm, const char *name) {
  MargObject *obj = (MargObject *)marg_object_init(
    vm, sizeof(MargLabel), G("$Label"), string_new("")
  );
  MargLabel *self = (MargLabel *)obj;

  self->name  = string_new(name);
  self->value = vector_size(vm->current->bytecode);

  return self;
}

MargString *marg_string_init(VM *vm, const char *value) {
  MargObject *obj = (MargObject *)marg_object_init(
    vm, sizeof(MargString), G("$String"), string_new("")
  );
  MargString *self = (MargString *)obj;

  self->value = string_new(value);

  return self;
}

MargTensor *marg_tensor_init(VM *vm) {
  MargObject *obj = (MargObject *)marg_object_init(
    vm, sizeof(MargTensor), G("$Tensor"), string_new("")
  );
  MargTensor *self = (MargTensor *)obj;

  self->value = NULL;

  return self;
}

MargTuple *marg_tuple_init(VM *vm) {
  MargObject *obj = (MargObject *)marg_object_init(
    vm, sizeof(MargTuple), G("$Tuple"), string_new("")
  );
  MargTuple *self = (MargTuple *)obj;

  self->value = NULL;

  return self;
}

MargTable *marg_table_init(VM *vm) {
  MargObject *obj = (MargObject *)marg_object_init(
    vm, sizeof(MargTable), G("$Table"), string_new("")
  );
  MargTable *self = (MargTable *)obj;

  table_init(&self->value);

  return self;
}

MargBitstring *marg_bitstring_init(VM *vm) {
  MargObject *obj = (MargObject *)marg_object_init(
    vm, sizeof(MargBitstring), G("$Bitstring"), string_new("")
  );
  MargBitstring *self = (MargBitstring *)obj;

  self->bits  = marg_tensor_init(vm);
  self->sizes = marg_tensor_init(vm);

  return self;
}

MargMethod *marg_method_init(
  VM *vm,
  MargObject *bound_object,
  MargMethod *bound_method,
  const char *message_name
) {
  MargObject *obj = (MargObject *)marg_object_init(
    vm, sizeof(MargMethod), G("$Method"), string_new("")
  );
  MargMethod *self = (MargMethod *)obj;

  self->bound_object = bound_object;
  self->bound_method = bound_method;

  self->message_name   = message_name;
  self->argument_names = NULL;

  self->constants = NULL;
  table_init(&self->local_variables);
  self->local_index = 0;

  self->bytecode = NULL;
  self->ip       = -1;

  return self;
}

MargPrimitive *marg_primitive_init(
  VM *vm, const char *primitive_name, MargPrimitiveFunction function
) {
  MargObject *obj = (MargObject *)marg_object_init(
    vm, sizeof(MargPrimitive), G("Primitive"), string_new("")
  );
  MargPrimitive *self = (MargPrimitive *)obj;

  self->function       = function;
  self->primitive_name = primitive_name;

  return self;
}

MargVariable *marg_variable_init(
  VM *vm, const char *name, MargValue value, MargVariableType type
) {
  MargObject *obj = (MargObject *)marg_object_init(
    vm, sizeof(MargVariable), G("Variable"), string_new("")
  );
  MargVariable *self = (MargVariable *)obj;

  self->name  = name;
  self->value = value;
  self->type  = type;

  return self;
}
