#include "MargaretPrimitives.h"

#include "TensorPrimitives.h"

#include <stdio.h> /* fprintf, stdout */

MargValue __PRIM_RAISE(VM *vm, MargValue error) {
  (void)vm;
  fprintf(stdout, "\033[1;31mraise:\033[0m `%s`\n", AS_STRING(error)->value);
  return MARG_UNDEFINED;
}

/* MargValue primitive_DNU(VM *vm, MargValue args_value) {
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

/* MargValue primitive_CLONE(VM *vm, MargValue args_value) {
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

MargValue __PRIM_INSPECT(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  printf("%s\n", marg_value_format(vm, args[0]));
  vm->do_not_display = true;
  return args[0];
}

MargValue __PRIM_BIND(VM *vm, MargValue args_value) {
  MargValue *args = AS_TENSOR(args_value)->value;
  (void)vm;
  AS_METHOD(args[0])->bound_object = AS_OBJECT(args[1]);
  table_add(
    &AS_OBJECT(args[1])->messages, AS_METHOD(args[0])->message_name, args[0]
  );
  return args[0];
}

MargValue __PRIM_MARGARET_MESSAGES(VM *vm, MargValue args_value) {
  size_t i;
  MargValue *args              = AS_TENSOR(args_value)->value;
  EmeraldsTable marg_msg_table = AS_OBJECT(args[0])->messages;
  size_t capacity              = vector_capacity(marg_msg_table.keys);
  MargValue messages           = MARG_TENSOR();
  (void)vm;

  if(table_size(&marg_msg_table) > 0) {
    for(i = 0; i < capacity; i++) {
      if(marg_msg_table.states[i] == TABLE_STATE_FILLED &&
         marg_msg_table.keys[i][0] != '\0') {
        char *message_name = (char *)marg_msg_table.keys[i];
        MargValue args     = MARG_TENSOR();

        size_t index = -1;
        size_t i;
        for(i = 0; i < string_size(message_name); i++) {
          if(message_name[i] == '_') {
            index = i;
          }
        }
        if(index + 1 != 0) {
          message_name = string_substring(message_name, 0, index);
        }
        vector_add(AS_TENSOR(args)->value, messages);
        vector_add(AS_TENSOR(args)->value, MARG_STRING(message_name));
        __PRIM_TENSOR_ADD(NULL, args);
      }
    }
  }

  return messages;
}
