#include "Primitives.h"

void define_primitive(
  VM *vm, const char *name, const char *object_name, MargPrimitiveFunction msg
) {
  MargObject *obj = NULL;
  if(object_name && object_name[0] == '$') {
    obj = AS_OBJECT(G(object_name));
  } else if(object_name && object_name[0] == '@') {
    obj = AS_OBJECT(I(object_name));
  } else {
    obj = AS_OBJECT(L(object_name));
  }

  table_add(&obj->primitives, name, MARG_PRIMITIVE(name, msg));
}
