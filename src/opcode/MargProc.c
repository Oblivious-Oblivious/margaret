#include "MargValue.h"

/* TODO - Remove */
MargProc *marg_proc_new(VM *vm, MargMethod *bound_method) {
  (void)vm;
  (void)bound_method;
  return NULL;
}

char *marg_proc_to_string(MargProc *object) {
  char *res = string_new("");
  string_addf(&res, "< %s:proc >", object->bound_method->bound_object->name);
  return res;
}
