#include "Evaluator.h"

// static void op_put_tensor_helper(VM *vm, MargValue temporary) {
//   ptrdiff_t number_of_elements = AS_INTEGER(temporary)->value;
//   MargValue tensor_value       = MARG_TENSOR();
//   MargTensor *tensor_object    = AS_TENSOR(tensor_value);

//   ptrdiff_t i;
//   for(i = number_of_elements - 1; i >= 0; i--) {
//     tensor_object->value[i] = fs_pop(vm->sp);
//   }

//   fs_push(vm->sp, tensor_value);
// }

// static void op_put_table_helper(VM *vm, MargValue temporary) {
//   ptrdiff_t number_of_elements = AS_INTEGER(temporary)->value / 2;
//   MargValue table_value        = MARG_TABLE();
//   MargTable *table_object      = AS_TABLE(table_value);

//   ptrdiff_t i;
//   for(i = 0; i < number_of_elements; i++) {
//     MargValue value = fs_pop(vm->sp);
//     MargValue key   = fs_pop(vm->sp);
//     marg_table_add(table_object, AS_STRING(key)->value, value);
//   }

//   fs_push(vm->sp, table_value);
// }

// static MargValue dispatch_method_from_delegation_chain(
//   MargObject *object, MargValue message_name
// ) {
//   MargValue method_value =
//     table_get(&object->messages, AS_STRING(message_name)->value);
//   if(IS_UNDEFINED(method_value)) {
//     if(string_equals(object->name, "$Margaret")) {
//       return method_value;
//     } else {
//       return dispatch_method_from_delegation_chain(
//         AS_OBJECT(object->parent), message_name
//       );
//     }
//   } else {
//     return table_get(&object->messages, AS_STRING(message_name)->value);
//   }
// }

// static MargValue retrieve_all_messages_in_delegation_chain(
//   VM *vm, MargValue messages_tensor, MargObject *object
// ) {
//   EmeraldsTable *messages = &object->messages;

//   size_t i;
//   for(i = 0; i < messages->size; i++) {
//     /* table_entry *entry = &messages->entries[i]; */
//     if(!IS_NOT_INTERNED(MARG_STRING(messages->keys[i])) &&
//        strncmp(messages->keys[i], "", 1)) {
//       marg_tensor_add(
//         AS_TENSOR(messages_tensor), MARG_STRING(messages->keys[i])
//       );
//     }
//   }

//   if(string_equals(object->name, "$Margaret")) {
//     return messages_tensor;
//   } else {
//     return retrieve_all_messages_in_delegation_chain(
//       vm, messages_tensor, AS_OBJECT(object->parent)
//     );
//   }
// }

// static void op_send_helper(VM *vm, MargValue message_name) {
//   /* NOTE - Read temporary values */
//   ptrdiff_t i;
//   MargObject *object;
//   MargValue method_value;
//   MargMethod *method            = NULL;
//   ptrdiff_t number_of_arguments = AS_INTEGER(fs_pop(vm->sp))->value;

//   /* NOTE - Pop all arguments first */
//   MargValue *actual_arguments = NULL;
//   vector_initialize_n(actual_arguments, number_of_arguments);

//   for(i = number_of_arguments - 1; i >= 0; i--) {
//     actual_arguments[i] = fs_pop(vm->sp);
//   }

//   /* NOTE - Pop object after arguments */
//   object       = AS_OBJECT(fs_pop(vm->sp));
//   method_value = dispatch_method_from_delegation_chain(object, message_name);
//   if(IS_UNDEFINED(method_value)) {
//     fs_push(vm->sp, QNAN_BOX(object));
//     fs_push(vm->sp, message_name);
//     fs_push(vm->sp, MARG_INTEGER(1));
//     op_send_helper(vm, MARG_STRING("dnu:"));
//   } else {
//     method               = AS_METHOD(method_value);
//     method->bound_object = object;
//     method->bound_method = vm->current;

//     /* NOTE - Close over local variables */
//     table_add_all(&vm->current->local_variables, &method->local_variables);

//     /* NOTE - Inject method arguments */
//     for(i = 0; i < number_of_arguments; i++) {
//       table_add(
//         &method->local_variables, method->arguments[i], actual_arguments[i]
//       );
//     }

//     vm->current = method;
//   }
// }

// #define integer_unary_operation_helper(operation)                         \
//   do {                                                                    \
//     MargValue number = fs_pop(vm->sp);                                    \
//     fs_pop(vm->sp);                                                       \
//     if(IS_INTEGER(number)) {                                              \
//       fs_push(vm->sp, MARG_INTEGER(AS_INTEGER(number)->value operation)); \
//     } else {                                                              \
//       fs_push(vm->sp, MARG_NIL);                                          \
//     }                                                                     \
//   } while(0)

// #define numeric_binary_operation_helper(operation)                            \
//   do {                                                                        \
//     MargValue op2 = fs_pop(vm->sp);                                           \
//     MargValue op1 = fs_pop(vm->sp);                                           \
//     fs_pop(vm->sp);                                                           \
//     if(IS_INTEGER(op1) && IS_INTEGER(op2)) {                                  \
//       fs_push(                                                                \
//         vm->sp,                                                               \
//         MARG_INTEGER(AS_INTEGER(op1)->value operation AS_INTEGER(op2)->value) \
//       );                                                                      \
//     } else if(IS_INTEGER(op1) && IS_FLOAT(op2)) {                             \
//       fs_push(                                                                \
//         vm->sp,                                                               \
//         MARG_FLOAT(AS_INTEGER(op1)->value operation AS_FLOAT(op2)->value)     \
//       );                                                                      \
//     } else if(IS_FLOAT(op1) && IS_INTEGER(op2)) {                             \
//       fs_push(                                                                \
//         vm->sp,                                                               \
//         MARG_FLOAT(AS_FLOAT(op1)->value operation AS_INTEGER(op2)->value)     \
//       );                                                                      \
//     } else if(IS_FLOAT(op1) && IS_FLOAT(op2)) {                               \
//       fs_push(                                                                \
//         vm->sp,                                                               \
//         MARG_FLOAT(AS_FLOAT(op1)->value operation AS_FLOAT(op2)->value)       \
//       );                                                                      \
//     } else {                                                                  \
//       fs_push(vm->sp, MARG_NIL);                                              \
//     }                                                                         \
//   } while(0)

// #define numeric_binary_comparison_helper(operation)                 \
//   do {                                                              \
//     MargValue op2 = fs_pop(vm->sp);                                 \
//     MargValue op1 = fs_pop(vm->sp);                                 \
//     fs_pop(vm->sp);                                                 \
//     if(IS_INTEGER(op1) && IS_INTEGER(op2)) {                        \
//       if(AS_INTEGER(op1)->value operation AS_INTEGER(op2)->value) { \
//         fs_push(vm->sp, MARG_TRUE);                                 \
//       } else {                                                      \
//         fs_push(vm->sp, MARG_FALSE);                                \
//       }                                                             \
//     } else if(IS_INTEGER(op1) && IS_FLOAT(op2)) {                   \
//       if(AS_INTEGER(op1)->value operation AS_FLOAT(op2)->value) {   \
//         fs_push(vm->sp, MARG_TRUE);                                 \
//       } else {                                                      \
//         fs_push(vm->sp, MARG_FALSE);                                \
//       }                                                             \
//     } else if(IS_FLOAT(op1) && IS_INTEGER(op2)) {                   \
//       if(AS_FLOAT(op1)->value operation AS_INTEGER(op2)->value) {   \
//         fs_push(vm->sp, MARG_TRUE);                                 \
//       } else {                                                      \
//         fs_push(vm->sp, MARG_FALSE);                                \
//       }                                                             \
//     } else if(IS_FLOAT(op1) && IS_FLOAT(op2)) {                     \
//       if(AS_FLOAT(op1)->value operation AS_FLOAT(op2)->value) {     \
//         fs_push(vm->sp, MARG_TRUE);                                 \
//       } else {                                                      \
//         fs_push(vm->sp, MARG_FALSE);                                \
//       }                                                             \
//     } else {                                                        \
//       fs_push(vm->sp, MARG_NIL);                                    \
//     }                                                               \
//   } while(0)

// static void op_prim_to_string_helper(VM *vm, MargValue object) {
//   fs_push(vm->sp, MARG_STRING(marg_value_format(object)));
// }

// /**
//  * @brief Runs the iterator that evaluates
//     the result of the generated opcodes
//  * @param vm -> result enum
//  */
// static void evaluator_run(VM *vm) {
//   bool on_explicit_send = false;
//   vm->current->ip       = vm->current->bytecode;

//   /* TODO - Branch table, computed goto, otherwise use binary search */
//   while(true) {
//   enter_explicit_send:;
//     switch(READ_BYTE()) {
//     case OP_HALT:
//       return;
//     case OP_POP: {
//       fs_pop(vm->sp);
//       break;
//     }

//     case OP_PUT_NIL: {
//       fs_push(vm->sp, MARG_NIL);
//       break;
//     }
//     case OP_PUT_TRUE: {
//       fs_push(vm->sp, MARG_TRUE);
//       break;
//     }
//     case OP_PUT_FALSE: {
//       fs_push(vm->sp, MARG_FALSE);
//       break;
//     }

//     case OP_PUT_SELF: {
//       fs_push(vm->sp, QNAN_BOX(vm->current->bound_method->bound_object));
//       break;
//     }
//     case OP_PUT_SUPER: {
//       fs_push(vm->sp, vm->current->bound_method->bound_object->parent);
//       break;
//     }

//     case OP_PUT_MINUS_1: {
//       fs_push(vm->sp, MARG_INTEGER(-1));
//       break;
//     }
//     case OP_PUT_0: {
//       fs_push(vm->sp, MARG_INTEGER(0));
//       break;
//     }
//     case OP_PUT_1: {
//       fs_push(vm->sp, MARG_INTEGER(1));
//       break;
//     }
//     case OP_PUT_2: {
//       fs_push(vm->sp, MARG_INTEGER(2));
//       break;
//     }

//     case OP_PUT_OBJECT: {
//       MargValue object = READ_TEMPORARY();
//       /* if(IS_PROC(object)) {
//         table_add_all(
//           &vm->current->local_variables, &AS_PROC(object)->local_variables
//         );
//       } */
//       fs_push(vm->sp, object);
//       break;
//     }
//     case OP_PUT_OBJECT_WORD: {
//       MargValue object = READ_TEMPORARY_WORD();
//       /* if(IS_PROC(object)) {
//         table_add_all(
//           &vm->current->local_variables, &AS_PROC(object)->local_variables
//         );
//       } */
//       fs_push(vm->sp, object);
//       break;
//     }
//     case OP_PUT_OBJECT_DWORD: {
//       MargValue object = READ_TEMPORARY_DWORD();
//       /* if(IS_PROC(object)) {
//         table_add_all(
//           &vm->current->local_variables, &AS_PROC(object)->local_variables
//         );
//       } */
//       fs_push(vm->sp, object);
//       break;
//     }

//     case OP_PUT_TENSOR: {
//       op_put_tensor_helper(vm, READ_TEMPORARY());
//       break;
//     }
//     case OP_PUT_TENSOR_WORD: {
//       op_put_tensor_helper(vm, READ_TEMPORARY_WORD());
//       break;
//     }
//     case OP_PUT_TENSOR_DWORD: {
//       op_put_tensor_helper(vm, READ_TEMPORARY_DWORD());
//       break;
//     }
//       /* case OP_PUT_TUPLE: {break;}
//       case OP_PUT_TUPLE_WORD: {break;}
//       case OP_PUT_TUPLE_DWORD: {break;} */

//     case OP_PUT_TABLE: {
//       op_put_table_helper(vm, READ_TEMPORARY());
//       break;
//     }
//     case OP_PUT_TABLE_WORD: {
//       op_put_table_helper(vm, READ_TEMPORARY_WORD());
//       break;
//     }
//     case OP_PUT_TABLE_DWORD: {
//       op_put_table_helper(vm, READ_TEMPORARY_DWORD());
//       break;
//     }
//       /* case OP_PUT_BITSTRING: {break;}
//       case OP_PUT_BITSTRING_WORD: {break;}
//       case OP_PUT_BITSTRING_DWORD: {break;}

//       case OP_JUMP: {break;}
//       case OP_JUMP_LOCAL: {break;}
//       case OP_PUT_LABEL: {break;}
//       case OP_PUT_LABEL_WORD: {break;}
//       case OP_PUT_LABEL_DWORD: {break;} */

//     case OP_SET_GLOBAL: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY()];
//       table_add(
//         &vm->global_variables, AS_STRING(temp)->value, fs_peek(vm->sp, 0)
//       );
//       break;
//     }
//     case OP_SET_GLOBAL_WORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_WORD()];
//       table_add(
//         &vm->global_variables, AS_STRING(temp)->value, fs_peek(vm->sp, 0)
//       );
//       break;
//     }
//     case OP_SET_GLOBAL_DWORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_DWORD()];
//       table_add(
//         &vm->global_variables, AS_STRING(temp)->value, fs_peek(vm->sp, 0)
//       );
//       break;
//     }
//     case OP_SET_INSTANCE: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY()];
//       table_add(
//         &vm->current->bound_method->bound_object->instance_variables,
//         AS_STRING(temp)->value,
//         fs_peek(vm->sp, 0)
//       );
//       break;
//     }
//     case OP_SET_INSTANCE_WORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_WORD()];
//       table_add(
//         &vm->current->bound_method->bound_object->instance_variables,
//         AS_STRING(temp)->value,
//         fs_peek(vm->sp, 0)
//       );
//       break;
//     }
//     case OP_SET_INSTANCE_DWORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_DWORD()];
//       table_add(
//         &vm->current->bound_method->bound_object->instance_variables,
//         AS_STRING(temp)->value,
//         fs_peek(vm->sp, 0)
//       );
//       break;
//     }
//     case OP_SET_LOCAL: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY()];
//       table_add(
//         &vm->current->local_variables,
//         AS_STRING(temp)->value,
//         fs_peek(vm->sp, 0)
//       );
//       break;
//     }
//     case OP_SET_LOCAL_WORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_WORD()];
//       table_add(
//         &vm->current->local_variables,
//         AS_STRING(temp)->value,
//         fs_peek(vm->sp, 0)
//       );
//       break;
//     }
//     case OP_SET_LOCAL_DWORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_DWORD()];
//       table_add(
//         &vm->current->local_variables,
//         AS_STRING(temp)->value,
//         fs_peek(vm->sp, 0)
//       );
//       break;
//     }

//     case OP_GET_GLOBAL: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY()];
//       fs_push(vm->sp, table_get(&vm->global_variables,
//       AS_STRING(temp)->value)); break;
//     }
//     case OP_GET_GLOBAL_WORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_WORD()];
//       fs_push(vm->sp, table_get(&vm->global_variables,
//       AS_STRING(temp)->value)); break;
//     }
//     case OP_GET_GLOBAL_DWORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_DWORD()];
//       fs_push(vm->sp, table_get(&vm->global_variables,
//       AS_STRING(temp)->value)); break;
//     }
//     case OP_GET_INSTANCE: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY()];
//       fs_push(
//         vm->sp,
//         table_get(
//           &vm->current->bound_method->bound_object->instance_variables,
//           AS_STRING(temp)->value
//         )
//       );
//       break;
//     }
//     case OP_GET_INSTANCE_WORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_WORD()];
//       fs_push(
//         vm->sp,
//         table_get(
//           &vm->current->bound_method->bound_object->instance_variables,
//           AS_STRING(temp)->value
//         )
//       );
//       break;
//     }
//     case OP_GET_INSTANCE_DWORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_DWORD()];
//       fs_push(
//         vm->sp,
//         table_get(
//           &vm->current->bound_method->bound_object->instance_variables,
//           AS_STRING(temp)->value
//         )
//       );
//       break;
//     }
//     case OP_GET_LOCAL: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY()];
//       fs_push(
//         vm->sp, table_get(&vm->current->local_variables,
//         AS_STRING(temp)->value)
//       );
//       break;
//     }
//     case OP_GET_LOCAL_WORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_WORD()];
//       fs_push(
//         vm->sp, table_get(&vm->current->local_variables,
//         AS_STRING(temp)->value)
//       );
//       break;
//     }
//     case OP_GET_LOCAL_DWORD: {
//       MargValue temp = vm->current->constants[READ_TEMPORARY_DWORD()];
//       fs_push(
//         vm->sp, table_get(&vm->current->local_variables,
//         AS_STRING(temp)->value)
//       );
//       break;
//     }

//     case OP_SEND: {
//       op_send_helper(vm, READ_TEMPORARY());
//       break;
//     }
//     case OP_SEND_WORD: {
//       op_send_helper(vm, READ_TEMPORARY_WORD());
//       break;
//     }
//     case OP_SEND_DWORD: {
//       op_send_helper(vm, READ_TEMPORARY_DWORD());
//       break;
//     }
//     case OP_EXIT_ACTIVATION_RECORD: {
//       /* NOTE - Reset proc's IP */
//       vm->current->ip = vm->current->bytecode;
//       /* NOTE - Reset parameter table */
//       vector_free(vm->current->arguments);
//       /* NOTE - Reset back to enclosing bound method */
//       vm->current = vm->current->bound_method;
//       if(on_explicit_send) {
//         goto exit_explicit_send;
//       }
//       break;
//     }

//     case OP_PUTS: {
//       MargValue object = fs_pop(vm->sp);
//       fs_pop(vm->sp);
//       if(IS_STRING(object)) {
//         printf("%s\n", AS_STRING(object)->value);
//       } else {
//         op_prim_to_string_helper(vm, object);
//         fs_push(vm->sp, object);
//         fs_push(vm->sp, MARG_INTEGER(0));
//         op_send_helper(vm, MARG_STRING("to_string"));

//         /* NOTE - `puts` either prints the characters of a string or
//          * tries to send `to_string` to the object in question.
//          * When sending a new message in the middle of execution
//          * of an opcode, we need to store a panic state where
//          * sending the `to_string` message modifies the stack
//          * and then returns back to finish execution of `puts`.
//          * We first enable an `explicit_send` flag before
//          * directly jumping to the beginning of the jump table
//          * executing `to_string`, and then we jump back to
//          * continue with printf'ing the top of the stack.
//          * We make sure that OP_EXIT_ACTIVATION_RECORD checks
//          * for an explicit_send state to either jump here or
//          * continue normally.
//          */
//         on_explicit_send = true;
//         goto enter_explicit_send;
//       exit_explicit_send:;
//         on_explicit_send = false;
//         printf("%s\n", AS_STRING(fs_pop(vm->sp))->value);
//       }
//       fs_push(vm->sp, object);
//       break;
//     }

//     case OP_INCLUDE: {
//       uint8_t *previous_bytecode = vm->current->bytecode;
//       uint8_t *previous_position = vm->current->ip;

//       MargValue filename = fs_pop(vm->sp);
//       fs_pop(vm->sp);
//       vm->filename = AS_STRING(filename)->value;

//       EVAL(OPTIMIZE(EMIT(FORMALIZE(READ(LOAD(vm))))));

//       vm->current->bytecode = previous_bytecode;
//       vm->current->ip       = previous_position;
//       vm->sp++;
//       break;
//     }

//       /* case OP_PROC_CALL: {
//         MargValue proc = fs_pop(vm->sp);
//         fs_pop(vm->sp);
//         if(IS_PROC_CLONE(proc)) {
//           AS_PROC(proc)->bound_proc = vm->current;
//           vm->current               = AS_PROC(proc);
//         } else {
//           fs_push(vm->sp, MARG_NIL);
//         }
//         break;
//       } */

//       /* case OP_PROC_CALL_PARAMS: {
//         MargTable *arguments = AS_TABLE(fs_pop(vm->sp));
//         MargValue proc       = fs_pop(vm->sp);
//         fs_pop(vm->sp);

//         if(IS_PROC_CLONE(proc)) {
//           size_t i;
//           AS_PROC(proc)->bound_proc = vm->current;

//           for(i = 0; i < arguments->alloced; i++) {
//             MargTableEntry *entry = &arguments->entries[i];
//             if(!IS_NOT_INTERNED(entry->key)) {
//               table_add(
//                 &AS_PROC(proc)->local_variables,
//                 AS_STRING(entry->key)->value,
//                 entry->value
//               );
//             }
//           }

//           vm->current = AS_PROC(proc);
//         } else {
//           fs_push(vm->sp, MARG_NIL);
//         }
//         break;
//       } */

//     case OP_PRIM_MESSAGES: {
//       MargValue object = fs_pop(vm->sp);
//       fs_pop(vm->sp);
//       if(!IS_UNDEFINED(object)) {
//         fs_push(
//           vm->sp,
//           retrieve_all_messages_in_delegation_chain(
//             vm, MARG_TENSOR(), AS_OBJECT(object)
//           )
//         );
//       } else {
//         fs_push(vm->sp, MARG_NIL);
//       }
//       break;
//     }

//     case OP_PRIM_OBJECT_ID: {
//       MargValue object = fs_pop(vm->sp);
//       fs_pop(vm->sp);
//       if(!IS_UNDEFINED(object)) {
//         char qnan_encoded_value[32];
//         snprintf(qnan_encoded_value, 32, "0x%016zx" PRIx64, object);
//         fs_push(vm->sp, MARG_STRING(qnan_encoded_value));
//       } else {
//         fs_push(vm->sp, MARG_NIL);
//       }
//       break;
//     }

//     case OP_PRIM_TO_STRING: {
//       MargValue object = fs_pop(vm->sp);
//       fs_pop(vm->sp);
//       op_prim_to_string_helper(vm, object);
//       break;
//     }

//     case OP_PRIM_EQUALS: {
//       MargValue obj1 = fs_pop(vm->sp);
//       MargValue obj2 = fs_pop(vm->sp);
//       fs_pop(vm->sp);
//       obj1 == obj2 ? fs_push(vm->sp, MARG_TRUE) : fs_push(vm->sp,
//       MARG_FALSE); break;
//     }

//     case OP_PRIM_EQUALS_NUMERIC: {
//       numeric_binary_comparison_helper(==);
//       break;
//     }

//     case OP_PRIM_DNU: {
//       MargValue message_name = fs_pop(vm->sp);
//       MargValue object       = fs_pop(vm->sp);
//       fs_pop(vm->sp);
//       if(!IS_UNDEFINED(object) && IS_STRING(message_name)) {
//         char *dnu_message = string_new("");
//         string_addf(
//           &dnu_message,
//           "Object `%s` or any other object in the delegation chain does not "
//           "understand: `%s`",
//           AS_OBJECT(object)->name,
//           AS_STRING(message_name)->value
//         );
//         fs_push(vm->sp, MARG_STRING(dnu_message));
//       } else {
//         /* TODO - Instead of pushing a nil, we should throw an error. */
//         fs_push(vm->sp, MARG_NIL);
//       }
//       break;
//     }

//     case OP_PRIM_CLONE_OBJECT: {
//       MargValue new_object_name = fs_pop(vm->sp);
//       MargValue parent_object   = fs_pop(vm->sp);
//       fs_pop(vm->sp);
//       if(!IS_UNDEFINED(parent_object) && IS_STRING(new_object_name)) {
//         fs_push(
//           vm->sp, MARG_OBJECT(parent_object,
//           AS_STRING(new_object_name)->value)
//         );
//       } else {
//         fs_push(vm->sp, MARG_NIL);
//       }
//       break;
//     }

//     case OP_PRIM_BIND_METHOD: {
//       MargValue object = fs_pop(vm->sp);
//       MargValue method = fs_pop(vm->sp);
//       fs_pop(vm->sp);
//       if(!IS_UNDEFINED(object) && IS_METHOD(method)) {
//         table_add(
//           &AS_OBJECT(object)->messages, AS_METHOD(method)->message_name,
//           method
//         );
//         AS_METHOD(method)->bound_object = AS_OBJECT(object);
//         fs_push(vm->sp, method);
//       } else {
//         fs_push(vm->sp, MARG_NIL);
//       }
//       break;
//     }

//     case OP_PRIM_ADD: {
//       numeric_binary_operation_helper(+);
//       break;
//     }

//     case OP_PRIM_SUB: {
//       numeric_binary_operation_helper(-);
//       break;
//     }

//     case OP_PRIM_MUL: {
//       numeric_binary_operation_helper(*);
//       break;
//     }

//     case OP_PRIM_DIV: {
//       numeric_binary_operation_helper(/);
//       break;
//     }

//     case OP_PRIM_ABS: {
//       MargValue number = fs_pop(vm->sp);
//       fs_pop(vm->sp);
//       if(IS_INTEGER(number)) {
//         fs_push(
//           vm->sp,
//           MARG_INTEGER(
//             (AS_INTEGER(number)->value < 0) ? -AS_INTEGER(number)->value
//                                             : AS_INTEGER(number)->value
//           )
//         );
//       } else if(IS_FLOAT(number)) {
//         fs_push(
//           vm->sp,
//           MARG_FLOAT(
//             (AS_FLOAT(number)->value < 0) ? -AS_FLOAT(number)->value
//                                           : AS_FLOAT(number)->value
//           )
//         );
//       } else {
//         fs_push(vm->sp, MARG_NIL);
//       }
//       break;
//     }

//     case OP_PRIM_LT: {
//       numeric_binary_comparison_helper(<);
//       break;
//     }

//     case OP_PRIM_GT: {
//       numeric_binary_comparison_helper(>);
//       break;
//     }

//     case OP_PRIM_LTE: {
//       numeric_binary_comparison_helper(<=);
//       break;
//     }

//     case OP_PRIM_GTE: {
//       numeric_binary_comparison_helper(>=);
//       break;
//     }

//     case OP_PRIM_INCR: {
//       integer_unary_operation_helper(+1);
//       break;
//     }

//     case OP_PRIM_DECR: {
//       integer_unary_operation_helper(-1);
//       break;
//     }

//     case OP_PRIM_DOUBLE: {
//       integer_unary_operation_helper(*2);
//       break;
//     }
//     }
//   }
// }

#include "../opcode/instruction.h"
#include "../opcode/opcodes.h"
#include "../primitives/Primitives.h"

#define FETCH() (vm->current->ip++, O)

#define goto_helper(label)                                 \
  if(IS_LABEL(label)) {                                    \
    vm->current     = AS_OBJECT(label)->bound_vm->current; \
    vm->current->ip = AS_LABEL(label)->value;              \
  } else {                                                 \
    SKZ(raise("Error: cannot goto to a non-label."));      \
  }

#define proc_helper(proc_value)                    \
  ptrdiff_t argc = AS_INTEGER(KB)->value;          \
  if(IS_UNDEFINED(proc_value)) {                   \
    raise("Error: cannot call a non-proc value."); \
  } else {                                         \
    ptrdiff_t i;                                   \
    MargValue *args = NULL;                        \
    for(i = 1; i <= argc; i++) {                   \
      vector_add(args, K(-i));                     \
    }                                              \
    vm->current = AS_METHOD(proc_value);           \
    for(i = 0; i < argc; i++) {                    \
      SET_L(i, args[i]);                           \
    }                                              \
    vector_free(args);                             \
  }

static MargValue dispatch_method_from_delegation_chain(VM *vm, MargValue self) {
  char *name            = AS_STRING(KA)->value;
  MargValue curr_object = self;
  MargValue msg_value   = table_get(&AS_OBJECT(curr_object)->messages, name);
  while(IS_UNDEFINED(msg_value) && !IS_MARGARET(self)) {
    curr_object = QNAN_BOX(AS_OBJECT(curr_object)->proto);
    msg_value   = table_get(&AS_OBJECT(curr_object)->messages, name);
  }
  return msg_value;
}

static MargValue
dispatch_primitive_from_delegation_chain(VM *vm, MargValue self) {
  char *name            = AS_STRING(KA)->value;
  MargValue curr_object = self;
  MargValue prim_msg    = table_get(&AS_OBJECT(curr_object)->primitives, name);
  while(IS_UNDEFINED(prim_msg) && !IS_MARGARET(self)) {
    curr_object = QNAN_BOX(AS_OBJECT(curr_object)->proto);
    prim_msg    = table_get(&AS_OBJECT(curr_object)->primitives, name);
  }
  return prim_msg;
}

/**
 * @brief Runs the iterator that evaluates
    the result of the generated opcodes
 * @param vm -> result enum
 */
static void evaluator_run(VM *vm) {
#if defined(__GNUC__) || defined(__clang__)
  dispatch_table();
  #define switch_opcode   goto *_computed_gotos[FETCH()];
  #define case_opcode(op) _computed_goto_##op:
  #define default_opcode  _computed_goto_##ERROR:
#else
  #define switch_opcode   switch(FETCH())
  #define case_opcode(op) case(op):
  #define default_opcode  default:
#endif

#define next_opcode goto _opcode_loop

_opcode_loop:;
  switch_opcode {
    case_opcode(OP_STOZK) {
      CONST(KA);
      next_opcode;
    }
    case_opcode(OP_STOZL) {
      CONST(LA);
      next_opcode;
    }
    case_opcode(OP_STOZI) {
      CONST(IA);
      next_opcode;
    }
    case_opcode(OP_STOZG) {
      CONST(GA);
      next_opcode;
    }
    case_opcode(OP_LODZL) {
      SLA(KZ);
      next_opcode;
    }
    case_opcode(OP_LODZI) {
      SIA(KZ);
      next_opcode;
    }
    case_opcode(OP_LODZG) {
      SGA(KZ);
      next_opcode;
    }
    case_opcode(OP_GOTOL) {
      MargValue label =
        GET_L(table_get(&vm->current->local_variables, AS_STRING(KA)->value));
      goto_helper(label);
      next_opcode;
    }
    case_opcode(OP_GOTOI) {
      MargValue label = GET_I(table_get(
        &vm->current->bound_object->instance_variables, AS_STRING(KA)->value
      ));
      goto_helper(label);
      next_opcode;
    }
    case_opcode(OP_GOTOG) {
      MargValue label =
        GET_G(table_get(&vm->global_variables, AS_STRING(KA)->value));
      goto_helper(label);
      next_opcode;
    }
    case_opcode(OP_PRIM) {
      ptrdiff_t argc = AS_INTEGER(KB)->value;
      MargValue self = K(-1 - argc);

      MargValue prim_msg = dispatch_primitive_from_delegation_chain(vm, self);
      if(IS_UNDEFINED(prim_msg)) {
        SKZ(raise("Error: cannot call because primitive does not exist."));
      } else {
        ptrdiff_t i;
        MargValue *args = NULL;
        for(i = 1; i <= argc; i++) {
          /* TODO - Turn this into a MARG_TENSOR to be included in the GC */
          vector_add(args, K(-i));
        }
        SKZ(AS_PRIMITIVE(prim_msg)->function(vm, self, args));
      }
      next_opcode;
    }
    case_opcode(OP_SEND) {
      ptrdiff_t argc = AS_INTEGER(KB)->value;
      MargValue self = K(-1 - argc);

      MargValue msg_value = dispatch_method_from_delegation_chain(vm, self);
      if(IS_UNDEFINED(msg_value)) {
        raise("Error: cannot send because message does not exist.");
      } else {
        ptrdiff_t i;
        MargValue *args = NULL;
        for(i = 1; i <= argc; i++) {
          /* TODO - Probably also should be a MARG_TENSOR */
          vector_add(args, K(-i));
        }
        vm->current = AS_METHOD(msg_value);
        for(i = 0; i < argc; i++) {
          SET_L(i, args[i]);
        }
        vector_free(args);
      }
      next_opcode;
    }
    case_opcode(OP_PROCK) {
      proc_helper(KA);
      next_opcode;
    }
    case_opcode(OP_PROCL) {
      proc_helper(LA);
      next_opcode;
    }
    case_opcode(OP_PROCI) {
      proc_helper(IA);
      next_opcode;
    }
    case_opcode(OP_PROCG) {
      proc_helper(GA);
      next_opcode;
    }
    case_opcode(OP_RAISE) {
      SKZ(primitive_RAISE(NULL, KA, NULL));
      next_opcode;
    }
    case_opcode(OP_EXACTREC) {
      MargValue ret_value = KZ;
      vm->current         = vm->current->bound_method;
      SKZ(ret_value);
      next_opcode;
    }
    case_opcode(OP_NOP) { next_opcode; }
    case_opcode(OP_HALT) { return; }
    default_opcode { exit(1); }
  }
}

MargValue evaluator_evaluate(VM *vm) {
  if(vm->error) {
    return MARG_UNDEFINED;
  }

  evaluator_run(vm);
  if(vector_size(vm->current->bytecode) == 1 &&
     vm->current->bytecode[0] == OP_HALT) {
    return MARG_NIL;
  } else {
    return KZ;
  }
}
