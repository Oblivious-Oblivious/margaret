#include "Evaluator.h"

#include <stdio.h> /* printf, snprintf */
#include <inttypes.h> /* PRIx64 */

#include "../opcode/opcodes.h"
#include "../opcode/MargValue.h"

#include "../opcode/MargInteger.h"
#include "../opcode/MargFloat.h"
#include "../opcode/MargString.h"

#include "../opcode/MargTensor.h"
#include "../opcode/MargHash.h"

#include "../opcode/MargObject.h"
#include "../opcode/MargMethod.h"
#include "../opcode/MargProc.h"

#include "../vm/on_demand_compilation_pipeline.h"

static void op_put_tensor_helper(VM *vm, MargValue temporary) {
    int64_t number_of_elements = AS_INTEGER(temporary)->value;
    MargValue tensor_value = MARG_TENSOR(number_of_elements);
    MargTensor *tensor_object = AS_TENSOR(tensor_value);

    for(int64_t i = number_of_elements-1; i >= 0; i--)
        marg_tensor_add_at(tensor_object, STACK_POP(vm), i);

    STACK_PUSH(vm, tensor_value);
}

static void op_put_hash_helper(VM *vm, MargValue temporary) {
    int64_t number_of_elements = AS_INTEGER(temporary)->value / 2;
    MargValue hash_value = MARG_HASH;
    MargHash *hash_object = AS_HASH(hash_value);

    for(int64_t i = 0; i < number_of_elements; i++) {
        MargValue value = STACK_POP(vm);
        MargValue key = STACK_POP(vm);
        marg_hash_add(hash_object, key, value);
    }

    STACK_PUSH(vm, hash_value);
}

static MargValue dispatch_method_from_delegation_chain(MargObject *object, MargValue message_name) {
    MargValue method_value = table_get(&object->messages, message_name);
    if(IS_UNDEFINED(method_value)) {
        if(!strncmp(object->name, "$Margaret", 10)) {
            return method_value;
        }
        else {
            return dispatch_method_from_delegation_chain(object->parent, message_name);
        }
    }
    else {
        return table_get(&object->messages, message_name);
    }
}

static MargValue retrieve_all_messages_in_delegation_chain(VM *vm, MargValue messages_tensor, MargObject *object) {
    table *messages = &object->messages;
    for(size_t i = 0; i < messages->capacity; i++) {
        table_entry *entry = &messages->entries[i];
        if(!IS_NOT_INTERNED(entry->key) && strncmp(AS_STRING(entry->key)->chars, "", 1))
            marg_tensor_add(AS_TENSOR(messages_tensor), entry->key);
    }

    if(!strncmp(object->name, "$Margaret", 10))
        return messages_tensor;
    else
        return retrieve_all_messages_in_delegation_chain(vm, messages_tensor, object->parent);
}

static void op_send_helper(VM *vm, MargValue message_name) {
    /* Read temporary values */
    int64_t number_of_parameters = AS_INTEGER(STACK_POP(vm))->value;

    /* Pop all parameters first */
    MargValue *actual_parameters = collected_malloc(sizeof(MargValue) * number_of_parameters);
    for(int64_t i = number_of_parameters-1; i >= 0; i--)
        actual_parameters[i] = STACK_POP(vm);

    /* Pop object after parameters */
    MargObject *object = AS_OBJECT(STACK_POP(vm));
    MargValue method_value = dispatch_method_from_delegation_chain(object, message_name);
    MargMethod *method = NULL;
    if(IS_UNDEFINED(method_value)) {
        STACK_PUSH(vm, QNAN_BOX(object));
        STACK_PUSH(vm, message_name);
        STACK_PUSH(vm, MARG_INTEGER(1));
        op_send_helper(vm, MARG_STRING("dnu:"));
    }
    else {
        method = AS_METHOD(method_value);
        method->bound_object = object;
        method->proc->bound_proc = vm->current;

        /* Close over local variables */
        table_add_all(&vm->current->local_variables, &method->proc->local_variables);

        /* Inject method parameters */
        for(int64_t i = 0; i < number_of_parameters; i++) {
            MargValue parameter_name = marg_tensor_get(AS_TENSOR(method->parameter_names), i);
            table_set(&method->proc->local_variables, parameter_name, actual_parameters[i]);
        }

        vm->current = method->proc;
    }
}

#define integer_unary_operation_helper(operation) do { \
    MargValue number = STACK_POP(vm); \
    STACK_POP(vm); \
    if(IS_INTEGER(number)) \
        STACK_PUSH(vm, MARG_INTEGER(AS_INTEGER(number)->value operation)); \
    else \
        STACK_PUSH(vm, MARG_NIL); \
} while(0)

#define numeric_binary_operation_helper(operation) do { \
    MargValue op2 = STACK_POP(vm); \
    MargValue op1 = STACK_POP(vm); \
    STACK_POP(vm); \
    if(IS_INTEGER(op1) && IS_INTEGER(op2)) \
        STACK_PUSH(vm, MARG_INTEGER(AS_INTEGER(op1)->value operation AS_INTEGER(op2)->value)); \
    else if(IS_INTEGER(op1) && IS_FLOAT(op2)) \
        STACK_PUSH(vm, MARG_FLOAT(AS_INTEGER(op1)->value operation AS_FLOAT(op2)->value)); \
    else if(IS_FLOAT(op1) && IS_INTEGER(op2)) \
        STACK_PUSH(vm, MARG_FLOAT(AS_FLOAT(op1)->value operation AS_INTEGER(op2)->value)); \
    else if(IS_FLOAT(op1) && IS_FLOAT(op2)) \
        STACK_PUSH(vm, MARG_FLOAT(AS_FLOAT(op1)->value operation AS_FLOAT(op2)->value)); \
    else \
        STACK_PUSH(vm, MARG_NIL); \
} while(0)

#define numeric_binary_comparison_helper(operation) do { \
    MargValue op2 = STACK_POP(vm); \
    MargValue op1 = STACK_POP(vm); \
    STACK_POP(vm); \
    if(IS_INTEGER(op1) && IS_INTEGER(op2)) { \
        if(AS_INTEGER(op1)->value operation AS_INTEGER(op2)->value) \
            STACK_PUSH(vm, MARG_TRUE); \
        else \
            STACK_PUSH(vm, MARG_FALSE); \
    } \
    else if(IS_INTEGER(op1) && IS_FLOAT(op2)) { \
        if(AS_INTEGER(op1)->value operation AS_FLOAT(op2)->value) \
            STACK_PUSH(vm, MARG_TRUE); \
        else \
            STACK_PUSH(vm, MARG_FALSE); \
    } \
    else if(IS_FLOAT(op1) && IS_INTEGER(op2)) { \
        if(AS_FLOAT(op1)->value operation AS_INTEGER(op2)->value) \
            STACK_PUSH(vm, MARG_TRUE); \
        else \
            STACK_PUSH(vm, MARG_FALSE); \
    } \
    else if(IS_FLOAT(op1) && IS_FLOAT(op2)) { \
        if(AS_FLOAT(op1)->value operation AS_FLOAT(op2)->value) \
            STACK_PUSH(vm, MARG_TRUE); \
        else \
            STACK_PUSH(vm, MARG_FALSE); \
    } \
    else \
        STACK_PUSH(vm, MARG_NIL); \
} while(0)

static bool op_prim_to_string_helper(VM *vm, MargValue object) {
    if(IS_UNDEFINED(object))
        STACK_PUSH(vm, MARG_STRING("<unbound>"));
    else if(IS_NIL_CLONE(object))
        STACK_PUSH(vm, MARG_STRING(AS_OBJECT(object)->name));
    else if(IS_FALSE_CLONE(object))
        STACK_PUSH(vm, MARG_STRING(AS_OBJECT(object)->name));
    else if(IS_TRUE_CLONE(object))
        STACK_PUSH(vm, MARG_STRING(AS_OBJECT(object)->name));
    else if(IS_INTEGER_CLONE(object))
        STACK_PUSH(vm, MARG_STRING(marg_integer_to_string(object)));
    else if(IS_FLOAT_CLONE(object))
        STACK_PUSH(vm, MARG_STRING(marg_float_to_string(object)));
    else if(IS_STRING_CLONE(object))
        STACK_PUSH(vm, object);
    else if(IS_METHOD_CLONE(object))
        STACK_PUSH(vm, MARG_STRING(marg_method_to_string(object)));
    else if(IS_PROC_CLONE(object))
        STACK_PUSH(vm, MARG_STRING(marg_proc_to_string(object)));

    // TODO Implement inside of $Tensor and $Hash
    else if(IS_TENSOR_CLONE(object))
        STACK_PUSH(vm, MARG_STRING(marg_tensor_to_string(object)));
    else if(IS_HASH_CLONE(object))
        STACK_PUSH(vm, MARG_STRING(marg_hash_to_string(object)));

    else {
        STACK_PUSH(vm, MARG_STRING(marg_object_to_string_with_hash(object)));
        return true;
    }
    
    return false;
}

/**
 * @brief Runs the iterator that evaluates
    the result of the generated opcodes
 * @param vm -> result enum
 */
static void evaluator_run(VM *vm) {
    bool on_explicit_send = false;
    vm->current->ip = vm->current->bytecode->items;

    // TODO Branch table, computed goto
    while(1) {
        enter_explicit_send:;
        switch(READ_BYTE()) {
            case OP_HALT:
                return;
            case OP_POP: {
                STACK_POP(vm);
                break;
            }

            case OP_PUT_NIL: {
                STACK_PUSH(vm, MARG_NIL);
                break;
            }
            case OP_PUT_TRUE: {
                STACK_PUSH(vm, MARG_TRUE);
                break;
            }
            case OP_PUT_FALSE: {
                STACK_PUSH(vm, MARG_FALSE);
                break;
            }

            case OP_PUT_SELF: {
                STACK_PUSH(vm, QNAN_BOX(vm->current->bound_method->bound_object));
                break;
            }
            case OP_PUT_SUPER: {
                STACK_PUSH(vm, QNAN_BOX(vm->current->bound_method->bound_object->parent));
                break;
            }

            case OP_PUT_MINUS_1: {
                STACK_PUSH(vm, MARG_INTEGER(-1));
                break;
            }
            case OP_PUT_0: {
                STACK_PUSH(vm, MARG_INTEGER(0));
                break;
            }
            case OP_PUT_1: {
                STACK_PUSH(vm, MARG_INTEGER(1));
                break;
            }
            case OP_PUT_2: {
                STACK_PUSH(vm, MARG_INTEGER(2));
                break;
            }

            case OP_PUT_OBJECT: {
                MargValue object = READ_TEMPORARY();
                if(IS_PROC(object))
                    table_add_all(&vm->current->local_variables, &AS_PROC(object)->local_variables);
                STACK_PUSH(vm, object);
                break;
            }
            case OP_PUT_OBJECT_WORD: {
                MargValue object = READ_TEMPORARY_WORD();
                if(IS_PROC(object))
                    table_add_all(&vm->current->local_variables, &AS_PROC(object)->local_variables);
                STACK_PUSH(vm, object);
                break;
            }
            case OP_PUT_OBJECT_DWORD: {
                MargValue object = READ_TEMPORARY_DWORD();
                if(IS_PROC(object))
                    table_add_all(&vm->current->local_variables, &AS_PROC(object)->local_variables);
                STACK_PUSH(vm, object);
                break;
            }

            case OP_PUT_TENSOR: {
                op_put_tensor_helper(vm, READ_TEMPORARY());
                break;
            }
            case OP_PUT_TENSOR_WORD: {
                op_put_tensor_helper(vm, READ_TEMPORARY_WORD());
                break;
            }
            case OP_PUT_TENSOR_DWORD: {
                op_put_tensor_helper(vm, READ_TEMPORARY_DWORD());
                break;
            }
            // case OP_PUT_TUPLE: {break;}
            // case OP_PUT_TUPLE_WORD: {break;}
            // case OP_PUT_TUPLE_DWORD: {break;}

            case OP_PUT_HASH: {
                op_put_hash_helper(vm, READ_TEMPORARY());
                break;
            }
            case OP_PUT_HASH_WORD: {
                op_put_hash_helper(vm, READ_TEMPORARY_WORD());
                break;
            }
            case OP_PUT_HASH_DWORD: {
                op_put_hash_helper(vm, READ_TEMPORARY_DWORD());
                break;
            }
            // case OP_PUT_BITSTRING: {break;}
            // case OP_PUT_BITSTRING_WORD: {break;}
            // case OP_PUT_BITSTRING_DWORD: {break;}

            // case OP_JUMP: {break;}
            // case OP_JUMP_LOCAL: {break;}
            // case OP_PUT_LABEL: {break;}
            // case OP_PUT_LABEL_WORD: {break;}
            // case OP_PUT_LABEL_DWORD: {break;}

            case OP_SET_GLOBAL: {
                table_set(&vm->global_variables, READ_TEMPORARY(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_GLOBAL_WORD: {
                table_set(&vm->global_variables, READ_TEMPORARY_WORD(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_GLOBAL_DWORD: {
                table_set(&vm->global_variables, READ_TEMPORARY_DWORD(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_INSTANCE: {
                table_set(&vm->current->bound_method->bound_object->instance_variables, READ_TEMPORARY(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_INSTANCE_WORD: {
                table_set(&vm->current->bound_method->bound_object->instance_variables, READ_TEMPORARY_WORD(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_INSTANCE_DWORD: {
                table_set(&vm->current->bound_method->bound_object->instance_variables, READ_TEMPORARY_DWORD(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_LOCAL: {
                table_set(&vm->current->local_variables, READ_TEMPORARY(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_LOCAL_WORD: {
                table_set(&vm->current->local_variables, READ_TEMPORARY_WORD(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_LOCAL_DWORD: {
                table_set(&vm->current->local_variables, READ_TEMPORARY_DWORD(), STACK_PEEK(vm, 0));
                break;
            }

            case OP_GET_GLOBAL: {
                STACK_PUSH(vm, table_get(&vm->global_variables, READ_TEMPORARY()));
                break;
            }
            case OP_GET_GLOBAL_WORD: {
                STACK_PUSH(vm, table_get(&vm->global_variables, READ_TEMPORARY_WORD()));
                break;
            }
            case OP_GET_GLOBAL_DWORD: {
                STACK_PUSH(vm, table_get(&vm->global_variables, READ_TEMPORARY_DWORD()));
                break;
            }
            case OP_GET_INSTANCE: {
                STACK_PUSH(vm, table_get(&vm->current->bound_method->bound_object->instance_variables, READ_TEMPORARY()));
                break;
            }
            case OP_GET_INSTANCE_WORD: {
                STACK_PUSH(vm, table_get(&vm->current->bound_method->bound_object->instance_variables, READ_TEMPORARY_WORD()));
                break;
            }
            case OP_GET_INSTANCE_DWORD: {
                STACK_PUSH(vm, table_get(&vm->current->bound_method->bound_object->instance_variables, READ_TEMPORARY_DWORD()));
                break;
            }
            case OP_GET_LOCAL: {
                STACK_PUSH(vm, table_get(&vm->current->local_variables, READ_TEMPORARY()));
                break;
            }
            case OP_GET_LOCAL_WORD: {
                STACK_PUSH(vm, table_get(&vm->current->local_variables, READ_TEMPORARY_WORD()));
                break;
            }
            case OP_GET_LOCAL_DWORD: {
                STACK_PUSH(vm, table_get(&vm->current->local_variables, READ_TEMPORARY_DWORD()));
                break;
            }

            case OP_SEND: {
                op_send_helper(vm, READ_TEMPORARY());
                break;
            }
            case OP_SEND_WORD: {
                op_send_helper(vm, READ_TEMPORARY_WORD());
                break;
            }
            case OP_SEND_DWORD: {
                op_send_helper(vm, READ_TEMPORARY_DWORD());
                break;
            }
            case OP_EXIT_ACTIVATION_RECORD: {
                /* Reset proc's IP */
                vm->current->ip = vm->current->bytecode->items;
                /* Reset parameter table */
                table_init(&vm->current->parameters);
                /* Reset back to enclosing bound proc */
                vm->current = vm->current->bound_proc;
                if(on_explicit_send)
                    goto exit_explicit_send;
                break;
            }

            case OP_PUTS: {
                MargValue object = STACK_POP(vm);
                STACK_POP(vm);
                if(IS_STRING_CLONE(object)) {
                    printf("%s\n", AS_STRING(object)->chars);
                }
                else {
                    if(op_prim_to_string_helper(vm, object)) {
                        STACK_PUSH(vm, object);
                        STACK_PUSH(vm, MARG_INTEGER(0));
                        op_send_helper(vm, MARG_STRING("to_string"));

                        /**
                         * `puts` either prints the characters of a string or
                         * tries to send `to_string` to the object in question.
                         * When sending a new message in the middle of execution
                         * of an opcode, we need to store a panic state where
                         * sending the `to_string` message modifies the stack
                         * and then returns back to finish execution of `puts`.
                         * We first enable an `explicit_send` flag before
                         * directly jumping to the beginning of the jump table
                         * executing `to_string`, and then we jump back to
                         * continue with printf'ing the top of the stack.
                         * We make sure that OP_EXIT_ACTIVATION_RECORD checks
                         * for an explicit_send state to either jump here or
                         * continue normally.
                         */
                        on_explicit_send = true;
                        goto enter_explicit_send;
                        exit_explicit_send:;
                        on_explicit_send = false;
                    }
                    printf("%s\n", AS_STRING(STACK_POP(vm))->chars);
                }
                STACK_PUSH(vm, object);
                break;
            }

            case OP_INCLUDE: {
                chunk *previous_bytecode = vm->current->bytecode;
                uint8_t *previous_position = vm->current->ip;

                MargValue filename = STACK_POP(vm);
                STACK_POP(vm);
                string *chars = LOAD(AS_STRING(filename)->chars);
                TokenTable *tokens = READ(chars);
                vector *formal_bytecode = FORMALIZE(tokens);
                vm->current->bytecode = chunk_new();
                vm = EMIT(vm, formal_bytecode);
                vm = OPTIMIZE(vm);
                EVAL(vm);

                vm->current->bytecode = previous_bytecode;
                vm->current->ip = previous_position;
                vm->sp++;
                break;
            }

            case OP_PROC_CALL: {
                MargValue proc = STACK_POP(vm);
                // STACK_POP(vm);
                if(IS_PROC_CLONE(proc)) {
                    vm->current = AS_PROC(proc);
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }

            case OP_PROC_CALL_PARAMS: {
                MargHash *parameters = AS_HASH(STACK_POP(vm));
                MargValue proc = STACK_POP(vm);
                // STACK_POP(vm);

                if(IS_PROC_CLONE(proc)) {

                    /* Inject proc parameters */
                    for(size_t i = 0; i < parameters->alloced; i++) {
                        MargHashEntry *entry = &parameters->entries[i];
                        if(!IS_NOT_INTERNED(entry->key))
                            table_set(&AS_PROC(proc)->local_variables, entry->key, entry->value);
                    }

                    vm->current = AS_PROC(proc);
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }

            case OP_PRIM_MESSAGES: {
                MargValue object = STACK_POP(vm);
                STACK_POP(vm);
                if(!IS_UNDEFINED(object))
                    STACK_PUSH(vm, retrieve_all_messages_in_delegation_chain(vm, MARG_TENSOR(32), AS_OBJECT(object)));
                else
                    STACK_PUSH(vm, MARG_NIL);
                break;
            }

            case OP_PRIM_OBJECT_ID: {
                MargValue object = STACK_POP(vm);
                STACK_POP(vm);
                if(!IS_UNDEFINED(object)) {
                    char qnan_encoded_value[20];
                    sprintf(qnan_encoded_value, "0x%016" PRIx64, (uint64_t)object);
                    STACK_PUSH(vm, MARG_STRING(qnan_encoded_value));
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }

            case OP_PRIM_TO_STRING: {
                MargValue object = STACK_POP(vm);
                STACK_POP(vm);
                op_prim_to_string_helper(vm, object);
                break;
            }

            case OP_PRIM_EQUALS: {
                MargValue obj1 = STACK_POP(vm);
                MargValue obj2 = STACK_POP(vm);
                STACK_POP(vm);
                obj1 == obj2 ? STACK_PUSH(vm, MARG_TRUE) : STACK_PUSH(vm, MARG_FALSE);
                break;
            }

            case OP_PRIM_EQUALS_NUMERIC: {
                numeric_binary_comparison_helper(==);
                break;
            }

            case OP_PRIM_DNU: {
                MargValue message_name = STACK_POP(vm);
                MargValue object = STACK_POP(vm);
                STACK_POP(vm);
                if(!IS_UNDEFINED(object) && IS_STRING_CLONE(message_name)) {
                    string *dnu_message = string_new("");
                    string_addf(dnu_message, "Object `%s` or any other object in the delegation chain does not understand: `%s`", AS_OBJECT(object)->name, AS_STRING(message_name)->chars);
                    STACK_PUSH(vm, MARG_STRING(string_get(dnu_message)));
                }
                else {
                    // TODO Instead of pushing a nil, we should throw an error.
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }

            case OP_PRIM_CLONE_OBJECT: {
                MargValue new_object_name = STACK_POP(vm);
                MargValue parent_object = STACK_POP(vm);
                STACK_POP(vm);
                if(!IS_UNDEFINED(parent_object) && IS_STRING_CLONE(new_object_name)) {
                    MargValue child_object = MARG_OBJECT(AS_STRING(new_object_name)->chars);
                    AS_OBJECT(child_object)->parent = AS_OBJECT(parent_object);
                    table_set(&AS_OBJECT(child_object)->instance_variables, MARG_STRING("@self"), child_object);
                    table_set(&AS_OBJECT(child_object)->instance_variables, MARG_STRING("@super"), parent_object);
                    STACK_PUSH(vm, child_object);
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }

            case OP_PRIM_BIND_METHOD: {
                MargValue object = STACK_POP(vm);
                MargValue method = STACK_POP(vm);
                STACK_POP(vm);
                if(!IS_UNDEFINED(object) && IS_METHOD_CLONE(method)) {
                    table_set(&AS_OBJECT(object)->messages, AS_METHOD(method)->message_name, method);
                    AS_METHOD(method)->bound_object = AS_OBJECT(object);
                    STACK_PUSH(vm, method);
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }

            case OP_PRIM_ADD: {
                numeric_binary_operation_helper(+);
                break;
            }

            case OP_PRIM_SUB: {
                numeric_binary_operation_helper(-);
                break;
            }

            case OP_PRIM_MUL: {
                numeric_binary_operation_helper(*);
                break;
            }

            case OP_PRIM_DIV: {
                numeric_binary_operation_helper(/);
                break;
            }

            case OP_PRIM_ABS: {
                MargValue number = STACK_POP(vm);
                STACK_POP(vm);
                if(IS_INTEGER(number))
                    STACK_PUSH(vm, MARG_INTEGER((AS_INTEGER(number)->value < 0) ? -AS_INTEGER(number)->value : AS_INTEGER(number)->value));
                else if(IS_FLOAT(number))
                    STACK_PUSH(vm, MARG_FLOAT((AS_FLOAT(number)->value < 0) ? -AS_FLOAT(number)->value : AS_FLOAT(number)->value));
                else
                    STACK_PUSH(vm, MARG_NIL);
                break;
            }

            case OP_PRIM_LT: {
                numeric_binary_comparison_helper(<);
                break;
            }

            case OP_PRIM_GT: {
                numeric_binary_comparison_helper(>);
                break;
            }

            case OP_PRIM_LTE: {
                numeric_binary_comparison_helper(<=);
                break;
            }

            case OP_PRIM_GTE: {
                numeric_binary_comparison_helper(>=);
                break;
            }

            case OP_PRIM_INCR: {
                integer_unary_operation_helper(+ 1);
                break;
            }

            case OP_PRIM_DECR: {
                integer_unary_operation_helper(- 1);
                break;
            }

            case OP_PRIM_DOUBLE: {
                integer_unary_operation_helper(* 2);
                break;
            }
        }
    }
}

MargValue evaluator_evaluate(VM *vm) {
    evaluator_run(vm);
    return STACK_PEEK(vm, -1);
}
