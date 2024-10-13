#include "MargValue.h"

MargLabel *marg_label_new(VM *vm, char *value, size_t index) {
  MargObject *obj = marg_object_new(
    vm,
    sizeof(MargLabel),
    table_get(&vm->global_variables, "$Label"),
    string_new("$Label")
  );
  MargLabel *self = (MargLabel *)obj;

  self->value = value;
  self->index = index;

  return self;
}

char *marg_label_to_string(MargLabel *object) {
  char *res = string_new("");
  string_addf(&res, "<%s:%zu>", object->value, object->index);
  return res;
}
