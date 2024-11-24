#include "instruction.h"

MargPrimitive *marg_primitive_new(
  VM *vm, const char *primitive_name, MargPrimitiveFunction function
) {
  MargObject *obj = (MargObject *)marg_object_new(
    vm, sizeof(MargPrimitive), G("Primitive"), string_new("")
  );
  MargPrimitive *self = (MargPrimitive *)obj;

  obj->instance_registers[1] = MARG_NIL;
  table_remove(&obj->instance_variables, "@super");
  self->function       = function;
  self->primitive_name = primitive_name;

  return self;
}
