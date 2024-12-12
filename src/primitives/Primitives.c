#include "Primitives.h"

void define_primitive(VM *vm, const char *name, MargPrimitiveFunction msg) {
  table_add(&vm->primitives, name, MARG_PRIMITIVE(name, msg));
}
