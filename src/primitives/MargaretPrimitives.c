#include "MargaretPrimitives.h"

#include "Primitives.h"

#include <float.h> /* LDBL_DIG */
#include <stdio.h> /* fprintf, stdout */

MargValue __PRIM_RAISE(VM *vm, MargValue self, MargValue args_value) {
  (void)vm;
  (void)args_value;
  fprintf(stdout, "raise: `%s`\n", AS_STRING(self)->value);
  return self;
}

/* MargValue primitive_DNU(VM *vm, MargValue self, MargValue args_value) {
  MargValue message_name = fs_pop(vm->sp);
  MargValue object       = fs_pop(vm->sp);
  fs_pop(vm->sp);
  if(!IS_UNDEFINED(object) && IS_STRING(message_name)) {
    char *dnu_message = string_new("");
    string_addf(
      &dnu_message,
      "Object `%s` or any other object in the delegation chain does not "
      "understand: `%s`",
      AS_OBJECT(object)->name,
      AS_STRING(message_name)->value
    );
    fs_push(vm->sp, MARG_STRING(dnu_message));
  } else {
    fs_push(vm->sp, MARG_NIL);
  }
} */

/* MargValue primitive_CLONE(VM *vm, MargValue self, MargValue args_value) {
  MargValue new_object_name = fs_pop(vm->sp);
  MargValue parent_object   = fs_pop(vm->sp);
  fs_pop(vm->sp);
  if(!IS_UNDEFINED(parent_object) && IS_STRING(new_object_name)) {
    fs_push(
      vm->sp, MARG_OBJECT(parent_object, AS_STRING(new_object_name)->value)
    );
  } else {
    fs_push(vm->sp, MARG_NIL);
  }
} */

MargValue __PRIM_INSPECT(VM *vm, MargValue self, MargValue args_value) {
  (void)args_value;

  printf("%s\n", marg_value_format(vm, self));
  return self;
}
