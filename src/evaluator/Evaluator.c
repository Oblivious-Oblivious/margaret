#include "Evaluator.h"

#include <stdio.h>

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

/**
 * @brief Typechecks object that came from primitive.  Primitives
    neither send nor execute any bytecode so we have to ensure
    we send to the appropriate object at runtime.
 * 
 * @param object -> Object to typecheck
 * @param type -> String version of type (we check MargObject name)
 * @param true
 * @param false
 */
static bool type_of_object_is(MargValue object, char *type) {
    return !strncmp(AS_OBJECT(object)->name, type, strlen(type));
}

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

static MargMethod *dispatch_method_from_delegation_chain(MargObject *object, MargValue message_name) {
    MargValue method_value = table_get(&object->messages, message_name);
    if(IS_UNDEFINED(method_value)) {
        if(!strncmp(object->name, "$Margaret", 10)) {
            printf("no object in the delegation chain understands message: `%s`\n", AS_STRING(message_name)->chars);
            exit(1);
        }
        else {
            return dispatch_method_from_delegation_chain(object->parent, message_name);
        }
    }
    else {
        return AS_METHOD(table_get(&object->messages, message_name));
    }
}

static void op_send_helper(VM *vm, MargValue temporary) {
    /* Read temporary values */
    MargValue message_name = temporary;
    int64_t number_of_parameters = AS_INTEGER(STACK_POP(vm))->value;

    /* Pop all parameters first */
    MargValue *actual_parameters = collected_malloc(sizeof(MargValue) * number_of_parameters);
    for(int64_t i = number_of_parameters-1; i >= 0; i--)
        actual_parameters[i] = STACK_POP(vm);

    /* Pop object after parameters */
    MargObject *object = AS_OBJECT(STACK_POP(vm));
    MargMethod *method = dispatch_method_from_delegation_chain(object, message_name);

    /* Close over local variables */
    table_add_all(&vm->current->local_variables, &method->proc->local_variables);

    /* Inject method parameters */
    for(int64_t i = 0; i < number_of_parameters; i++) {
        MargValue parameter_name = marg_tensor_get(AS_TENSOR(method->parameter_names), i);
        table_set(&method->proc->local_variables, parameter_name, actual_parameters[i]);
    }

    method->proc->bound_proc = vm->current;
    vm->current = method->proc;
}

#define numeric_binary_operation_helper(operation) do { \
    MargValue op2 = STACK_POP(vm); \
    MargValue op1 = STACK_POP(vm); \
    if(type_of_object_is(op1, "$Integer") && type_of_object_is(op2, "$Integer")) \
        STACK_PUSH(vm, MARG_INTEGER(AS_INTEGER(op1)->value operation AS_INTEGER(op2)->value)); \
    else if(type_of_object_is(op1, "$Integer") && type_of_object_is(op2, "$Float")) \
        STACK_PUSH(vm, MARG_FLOAT(AS_INTEGER(op1)->value operation AS_FLOAT(op2)->value)); \
    else if(type_of_object_is(op1, "$Float") && type_of_object_is(op2, "$Integer")) \
        STACK_PUSH(vm, MARG_FLOAT(AS_FLOAT(op1)->value operation AS_INTEGER(op2)->value)); \
    else if(type_of_object_is(op1, "$Float") && type_of_object_is(op2, "$Float")) \
        STACK_PUSH(vm, MARG_FLOAT(AS_FLOAT(op1)->value operation AS_FLOAT(op2)->value)); \
    else \
        STACK_PUSH(vm, MARG_NIL); \
} while(0)

#define numeric_binary_comparison_helper(operation) do { \
    MargValue op2 = STACK_POP(vm); \
    MargValue op1 = STACK_POP(vm); \
    if(type_of_object_is(op1, "$Integer") && type_of_object_is(op2, "$Integer")) { \
        if(AS_INTEGER(op1)->value operation AS_INTEGER(op2)->value) \
            STACK_PUSH(vm, MARG_TRUE); \
        else \
            STACK_PUSH(vm, MARG_FALSE); \
    } \
    else if(type_of_object_is(op1, "$Integer") && type_of_object_is(op2, "$Float")) { \
        if(AS_INTEGER(op1)->value operation AS_FLOAT(op2)->value) \
            STACK_PUSH(vm, MARG_TRUE); \
        else \
            STACK_PUSH(vm, MARG_FALSE); \
    } \
    else if(type_of_object_is(op1, "$Float") && type_of_object_is(op2, "$Integer")) { \
        if(AS_FLOAT(op1)->value operation AS_INTEGER(op2)->value) \
            STACK_PUSH(vm, MARG_TRUE); \
        else \
            STACK_PUSH(vm, MARG_FALSE); \
    } \
    else if(type_of_object_is(op1, "$Float") && type_of_object_is(op2, "$Float")) { \
        if(AS_FLOAT(op1)->value operation AS_FLOAT(op2)->value) \
            STACK_PUSH(vm, MARG_TRUE); \
        else \
            STACK_PUSH(vm, MARG_FALSE); \
    } \
    else \
        STACK_PUSH(vm, MARG_NIL); \
} while(0)

/**
 * @brief Runs the iterator that evaluates
    the result of the generated opcodes
 * @param vm -> result enum
 */
static void evaluator_run(VM *vm) {
    vm->current->ip = vm->current->bytecode->items;

    // TODO Branch table, computed goto
    while(1) {
        uint8_t instruction;
        switch(instruction = READ_BYTE()) {
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
                STACK_PUSH(vm, table_get(&vm->current->bound_method->bound_object->instance_variables, MARG_STRING("@self")));
                break;
            }
            case OP_PUT_SUPER: {
                STACK_PUSH(vm, table_get(&vm->current->bound_method->bound_object->instance_variables, MARG_STRING("@super")));
                break;
            }

            case OP_PUT_MINUS_1: {
                STACK_PUSH(vm, MARG_MINUS_1);
                break;
            }
            case OP_PUT_0: {
                STACK_PUSH(vm, MARG_0);
                break;
            }
            case OP_PUT_1: {
                STACK_PUSH(vm, MARG_1);
                break;
            }
            case OP_PUT_2: {
                STACK_PUSH(vm, MARG_2);
                break;
            }

            case OP_PUT_OBJECT: {
                STACK_PUSH(vm, READ_TEMPORARY());
                break;
            }
            case OP_PUT_OBJECT_WORD: {
                STACK_PUSH(vm, READ_TEMPORARY_WORD());
                break;
            }
            case OP_PUT_OBJECT_DWORD: {
                STACK_PUSH(vm, READ_TEMPORARY_DWORD());
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
            case OP_CLONE_OBJECT: {
                MargValue new_object_name = STACK_POP(vm);
                MargValue parent_object = STACK_POP(vm);
                MargValue child_object = MARG_OBJECT(AS_STRING(new_object_name)->chars);
                AS_OBJECT(child_object)->parent = AS_OBJECT(parent_object);
                table_set(&AS_OBJECT(child_object)->instance_variables, MARG_STRING("@self"), child_object);
                table_set(&AS_OBJECT(child_object)->instance_variables, MARG_STRING("@super"), parent_object);
                STACK_PUSH(vm, child_object);
                break;
            }
            case OP_BIND_METHOD: {
                MargValue method = STACK_POP(vm);
                MargValue object = STACK_POP(vm);
                table_set(&AS_OBJECT(object)->messages, AS_METHOD(method)->message_name, method);
                AS_METHOD(method)->bound_object = AS_OBJECT(object);
                STACK_PUSH(vm, method);
                break;
            }
            case OP_EXIT_ACTIVATION_RECORD: {
                /* Reset proc's IP */
                vm->current->ip = vm->current->bytecode->items;
                /* Reset proc local and parameter table */
                table_init(&vm->current->local_variables);
                table_init(&vm->current->parameters);
                /* Reset back to enclosing bound proc */
                vm->current = vm->current->bound_proc;
                break;
            }

            case OP_PRIM_6_PUTS: {
                MargValue object = STACK_POP(vm);
                STACK_POP(vm);
                if(!IS_UNDEFINED(object)) {
                    printf("%s\n", string_get(marg_value_format(object)));
                    STACK_PUSH(vm, object);
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }

            case OP_PRIM_PROC_CALL: {
                MargValue proc = STACK_POP(vm);
                if(IS_PROC(proc)) {
                    table_add_all(&vm->current->local_variables, &AS_PROC(proc)->local_variables);
                    vm->current = AS_PROC(proc);
                }
                break;
            }
            case OP_PRIM_PROC_CALL_PARAMS: {
                MargHash *parameters = AS_HASH(STACK_POP(vm));
                MargValue proc = STACK_POP(vm);

                if(IS_PROC(proc)) {
                    /* Close over local variables*/
                    table_add_all(&vm->current->local_variables, &AS_PROC(proc)->local_variables);

                    /* Inject proc parameters */
                    for(size_t i = 0; i < parameters->alloced; i++) {
                        MargHashEntry *entry = &parameters->entries[i];
                        if(!IS_NOT_INTERNED(entry->key))
                            table_set(&AS_PROC(proc)->local_variables, entry->key, entry->value);
                    }

                    vm->current = AS_PROC(proc);
                }
                break;
            }

            case OP_PRIM_NUMERIC_ADD: {
                numeric_binary_operation_helper(+);
                break;
            }
            case OP_PRIM_NUMERIC_SUB: {
                numeric_binary_operation_helper(-);
                break;
            }
            case OP_PRIM_NUMERIC_MUL: {
                numeric_binary_operation_helper(*);
                break;
            }
            case OP_PRIM_NUMERIC_DIV: {
                numeric_binary_operation_helper(/);
                break;
            }
            case OP_PRIM_NUMERIC_ABS: {
                MargValue number = STACK_POP(vm);
                if(type_of_object_is(number, "$Integer"))
                    STACK_PUSH(vm, MARG_INTEGER((AS_INTEGER(number)->value < 0) ? -AS_INTEGER(number)->value : AS_INTEGER(number)->value));
                else if(type_of_object_is(number, "$Float"))
                    STACK_PUSH(vm, MARG_FLOAT((AS_FLOAT(number)->value < 0) ? -AS_FLOAT(number)->value : AS_FLOAT(number)->value));
                else
                    STACK_PUSH(vm, MARG_NIL);
                break;
            }
            case OP_PRIM_NUMERIC_EQUALS: {
                numeric_binary_comparison_helper(==);
                break;
            }
            case OP_PRIM_NUMERIC_LT: {
                numeric_binary_comparison_helper(<);
                break;
            }
            case OP_PRIM_NUMERIC_GT: {
                numeric_binary_comparison_helper(>);
                break;
            }
            case OP_PRIM_NUMERIC_LTE: {
                numeric_binary_comparison_helper(<=);
                break;
            }
            case OP_PRIM_NUMERIC_GTE: {
                numeric_binary_comparison_helper(>=);
                break;
            }

            case OP_PRIM_INTEGER_INCR: {
                MargValue number = STACK_POP(vm);
                if(type_of_object_is(number, "$Integer"))
                    STACK_PUSH(vm, MARG_INTEGER(AS_INTEGER(number)->value + 1));
                else
                    STACK_PUSH(vm, MARG_NIL);
                break;
            }
            case OP_PRIM_INTEGER_DECR: {
                MargValue number = STACK_POP(vm);
                if(type_of_object_is(number, "$Integer"))
                    STACK_PUSH(vm, MARG_INTEGER(AS_INTEGER(number)->value - 1));
                else
                    STACK_PUSH(vm, MARG_NIL);
                break;
            }
            case OP_PRIM_INTEGER_DOUBLE: {
                MargValue number = STACK_POP(vm);
                if(type_of_object_is(number, "$Integer"))
                    STACK_PUSH(vm, MARG_INTEGER(AS_INTEGER(number)->value * 2));
                else
                    STACK_PUSH(vm, MARG_NIL);
                break;
            }
        }
    }
}

MargValue evaluator_evaluate(VM *vm) {
    evaluator_run(vm);
    return STACK_PEEK(vm, -1);
}
