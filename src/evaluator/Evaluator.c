#include "Evaluator.h"

#include <stdio.h>

#include "../opcode/Opcodes.h"
#include "../opcode/MargValue.h"

#include "../opcode/MargNil.h"
#include "../opcode/MargFalse.h"
#include "../opcode/MargTrue.h"
#include "../opcode/MargInteger.h"
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
            case TEST_OP_PRINT: {
                printf("%s\n", string_get(marg_value_format(STACK_PEEK(vm, 0))));
                break;
            }

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
            case OP_PUT_OBJECT_LONG: {
                STACK_PUSH(vm, READ_LONG_TEMPORARY());
                break;
            }

            case OP_PUT_TENSOR: {
                int64_t number_of_elements = AS_INTEGER(READ_TEMPORARY())->value;
                MargValue tensor_value = MARG_TENSOR(number_of_elements);
                MargTensor *tensor_object = AS_TENSOR(tensor_value);

                for(int64_t i = number_of_elements-1; i >= 0; i--)
                    marg_tensor_add_at(tensor_object, STACK_POP(vm), i);

                STACK_PUSH(vm, tensor_value);
                break;
            }
            case OP_PUT_TENSOR_LONG: {
                int64_t number_of_elements = AS_INTEGER(READ_LONG_TEMPORARY())->value;
                MargValue tensor_value = MARG_TENSOR(number_of_elements);
                MargTensor *tensor_object = AS_TENSOR(tensor_value);

                for(int64_t i = number_of_elements-1; i >= 0; i--)
                    marg_tensor_add_at(tensor_object, STACK_POP(vm), i);

                STACK_PUSH(vm, tensor_value);
                break;
            }
            case OP_PUT_HASH: {
                int64_t number_of_elements = AS_INTEGER(READ_TEMPORARY())->value / 2;
                MargValue hash_value = MARG_HASH;
                MargHash *hash_object = AS_HASH(hash_value);

                for(int64_t i = 0; i < number_of_elements; i++) {
                    MargValue value = STACK_POP(vm);
                    MargValue key = STACK_POP(vm);
                    marg_hash_add(hash_object, key, value);
                }

                STACK_PUSH(vm, hash_value);
                break;
            }
            case OP_PUT_HASH_LONG: {
                int64_t number_of_elements = AS_INTEGER(READ_LONG_TEMPORARY())->value / 2;
                MargValue hash_value = MARG_HASH;
                MargHash *hash_object = AS_HASH(hash_value);

                for(int64_t i = 0; i < number_of_elements; i++) {
                    MargValue value = STACK_POP(vm);
                    MargValue key = STACK_POP(vm);
                    marg_hash_add(hash_object, key, value);
                }

                STACK_PUSH(vm, hash_value);
                break;
            }

            case OP_SET_GLOBAL: {
                table_set(&vm->global_variables, READ_TEMPORARY(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_GLOBAL_LONG: {
                table_set(&vm->global_variables, READ_LONG_TEMPORARY(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_INSTANCE: {
                table_set(vm->current->instance_variables, READ_TEMPORARY(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_INSTANCE_LONG: {
                table_set(vm->current->instance_variables, READ_LONG_TEMPORARY(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_LOCAL: {
                table_set(&vm->current->local_variables, READ_TEMPORARY(), STACK_PEEK(vm, 0));
                break;
            }
            case OP_SET_LOCAL_LONG: {
                table_set(&vm->current->local_variables, READ_LONG_TEMPORARY(), STACK_PEEK(vm, 0));
                break;
            }

            case OP_GET_GLOBAL: {
                STACK_PUSH(vm, table_get(&vm->global_variables, READ_TEMPORARY()));
                break;
            }
            case OP_GET_GLOBAL_LONG: {
                STACK_PUSH(vm, table_get(&vm->global_variables, READ_LONG_TEMPORARY()));
                break;
            }
            case OP_GET_INSTANCE: {
                STACK_PUSH(vm, table_get(vm->current->instance_variables, READ_TEMPORARY()));
                break;
            }
            case OP_GET_INSTANCE_LONG: {
                STACK_PUSH(vm, table_get(vm->current->instance_variables, READ_LONG_TEMPORARY()));
                break;
            }
            case OP_GET_LOCAL: {
                STACK_PUSH(vm, table_get(&vm->current->local_variables, READ_TEMPORARY()));
                break;
            }
            case OP_GET_LOCAL_LONG: {
                STACK_PUSH(vm, table_get(&vm->current->local_variables, READ_LONG_TEMPORARY()));
                break;
            }

            case OP_CALL_PROC: {
                MargProc *proc = AS_PROC(STACK_POP(vm));
                table_add_all(&vm->current->local_variables, &proc->local_variables);
                vm->current = proc;
                break;
            }
            case OP_CALL_PROC_PARAMS: {
                MargHash *parameters = AS_HASH(STACK_POP(vm));
                MargProc *proc = AS_PROC(STACK_POP(vm));

                /* Close over local variables*/
                table_add_all(&vm->current->local_variables, &proc->local_variables);

                /* Inject proc parameters */
                for(size_t i = 0; i < parameters->alloced; i++) {
                    MargHashEntry *entry = &parameters->entries[i];
                    if(!IS_NOT_INTERNED(entry->key))
                        table_set(&proc->local_variables, entry->key, entry->value);
                }

                vm->current = proc;
                break;
            }
            case OP_EXIT_ACTIVATION_RECORD: {
                /* Reset proc's IP */
                vm->current->ip = vm->current->bytecode->items;
                /* Reset proc local and parameter table */
                // TODO Care for dangling pointer (GC)
                table_init(&vm->current->local_variables);
                table_init(&vm->current->parameters);
                /* Reset back to enclosing bound proc */
                vm->current = vm->current->bound_proc;
                break;
            }

            case OP_BIND_METHOD: {
                MargValue method = STACK_POP(vm);
                MargValue object = STACK_PEEK(vm, 0);
                table_set(&AS_OBJECT(object)->messages, AS_METHOD(method)->message_name, method);
                AS_METHOD(method)->bound_object = AS_OBJECT(object);
                table_set(&AS_METHOD(method)->bound_object->instance_variables, MARG_STRING("@self"), object);
                break;
            }

            case OP_SEND: {
                /* Read temporary values */
                MargValue message_name = READ_TEMPORARY();
                int64_t number_of_parameters = AS_INTEGER(STACK_POP(vm))->value;

                /* Pop all parameters first */
                MargValue *actual_parameters = collected_malloc(sizeof(MargValue) * number_of_parameters);
                for(int64_t i = number_of_parameters-1; i >= 0; i--)
                    actual_parameters[i] = STACK_POP(vm);

                /* Pop object after parameters */
                MargObject *object = AS_OBJECT(STACK_POP(vm));
                MargMethod *method = AS_METHOD(table_get(&object->messages, message_name));

                /* Close over local variables */
                table_add_all(&vm->current->local_variables, &method->proc->local_variables);

                /* Inject method parameters */
                for(int64_t i = 0; i < number_of_parameters; i++) {
                    MargValue parameter_name = marg_tensor_get(AS_TENSOR(method->parameter_names), i);
                    table_set(&method->proc->local_variables, parameter_name, actual_parameters[i]);
                }

                vm->current = method->proc;
                break;
            }
            case OP_SEND_LONG: {
                /* Read temporary values */
                MargValue message_name = READ_LONG_TEMPORARY();
                int64_t number_of_parameters = AS_INTEGER(STACK_POP(vm))->value;

                /* Pop all parameters first */
                MargValue *actual_parameters = collected_malloc(sizeof(MargValue) * number_of_parameters);
                for(int64_t i = number_of_parameters-1; i >= 0; i--)
                    actual_parameters[i] = STACK_POP(vm);

                /* Pop object after parameters */
                MargObject *object = AS_OBJECT(STACK_POP(vm));
                MargMethod *method = AS_METHOD(table_get(&object->messages, message_name));

                /* Close over local variables */
                table_add_all(&vm->current->local_variables, &method->proc->local_variables);

                /* Inject method parameters */
                for(int64_t i = 0; i < number_of_parameters; i++) {
                    MargValue parameter_name = marg_tensor_get(AS_TENSOR(method->parameter_names), i);
                    table_set(&method->proc->local_variables, parameter_name, actual_parameters[i]);
                }

                vm->current = method->proc;
                break;
            }

            case OP_CLONE_OBJECT: {
                MargValue new_object_name = STACK_POP(vm);
                STACK_PUSH(vm, MARG_OBJECT(AS_STRING(new_object_name)->chars));
                break;
            }

            case OP_PRIM_INTEGER_ADD: {
                MargValue op2 = STACK_POP(vm);
                MargValue op1 = STACK_POP(vm);
                if(type_of_object_is(op1, "$Integer"))
                    STACK_PUSH(vm, MARG_INTEGER(AS_INTEGER(op1)->value + AS_INTEGER(op2)->value));
                else
                    STACK_PUSH(vm, MARG_NIL);
                break;
            }
            case OP_PRIM_INTEGER_SUB: {
                MargValue op2 = STACK_POP(vm);
                MargValue op1 = STACK_POP(vm);
                if(type_of_object_is(op1, "$Integer"))
                    STACK_PUSH(vm, MARG_INTEGER(AS_INTEGER(op1)->value - AS_INTEGER(op2)->value));
                else
                    STACK_PUSH(vm, MARG_NIL);
                break;
            }
            case OP_PRIM_INTEGER_MUL: {
                MargValue op2 = STACK_POP(vm);
                MargValue op1 = STACK_POP(vm);
                if(type_of_object_is(op1, "$Integer"))
                    STACK_PUSH(vm, MARG_INTEGER(AS_INTEGER(op1)->value * AS_INTEGER(op2)->value));
                else
                    STACK_PUSH(vm, MARG_NIL);
                break;
            }
            case OP_PRIM_INTEGER_DIV: {
                MargValue op2 = STACK_POP(vm);
                MargValue op1 = STACK_POP(vm);
                if(type_of_object_is(op1, "$Integer")) {
                    if(op2 == 0)
                        STACK_PUSH(vm, MARG_NIL);
                    else
                        STACK_PUSH(vm, MARG_INTEGER(AS_INTEGER(op1)->value / AS_INTEGER(op2)->value));
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }
            case OP_PRIM_INTEGER_ABS: {
                MargValue number = STACK_POP(vm);
                if(type_of_object_is(number, "$Integer"))
                    STACK_PUSH(vm, MARG_INTEGER((AS_INTEGER(number)->value < 0) ? -AS_INTEGER(number)->value : AS_INTEGER(number)->value));
                else
                    STACK_PUSH(vm, MARG_NIL);
                break;
            }
            case OP_PRIM_INTEGER_EQUALS: {
                MargValue op2 = STACK_POP(vm);
                MargValue op1 = STACK_POP(vm);
                if(type_of_object_is(op1, "$Integer")) {
                    if(AS_INTEGER(op1)->value == AS_INTEGER(op2)->value)
                        STACK_PUSH(vm, MARG_TRUE);
                    else
                        STACK_PUSH(vm, MARG_FALSE);
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }
            case OP_PRIM_INTEGER_LT: {
                MargValue op2 = STACK_POP(vm);
                MargValue op1 = STACK_POP(vm);
                if(type_of_object_is(op1, "$Integer")) {
                    if(AS_INTEGER(op1)->value < AS_INTEGER(op2)->value)
                        STACK_PUSH(vm, MARG_TRUE);
                    else
                        STACK_PUSH(vm, MARG_FALSE);
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }
            case OP_PRIM_INTEGER_GT: {
                MargValue op2 = STACK_POP(vm);
                MargValue op1 = STACK_POP(vm);
                if(type_of_object_is(op1, "$Integer")) {
                    if(AS_INTEGER(op1)->value > AS_INTEGER(op2)->value)
                        STACK_PUSH(vm, MARG_TRUE);
                    else
                        STACK_PUSH(vm, MARG_FALSE);
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }
            case OP_PRIM_INTEGER_LTE: {
                MargValue op2 = STACK_POP(vm);
                MargValue op1 = STACK_POP(vm);
                if(type_of_object_is(op1, "$Integer")) {
                    if(AS_INTEGER(op1)->value <= AS_INTEGER(op2)->value)
                        STACK_PUSH(vm, MARG_TRUE);
                    else
                        STACK_PUSH(vm, MARG_FALSE);
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }
            case OP_PRIM_INTEGER_GTE: {
                MargValue op2 = STACK_POP(vm);
                MargValue op1 = STACK_POP(vm);
                if(type_of_object_is(op1, "$Integer")) {
                    if(AS_INTEGER(op1)->value >= AS_INTEGER(op2)->value)
                        STACK_PUSH(vm, MARG_TRUE);
                    else
                        STACK_PUSH(vm, MARG_FALSE);
                }
                else {
                    STACK_PUSH(vm, MARG_NIL);
                }
                break;
            }
        }
    }
}

MargValue evaluator_evaluate(VM *vm) {
    evaluator_run(vm);
    return STACK_PEEK(vm, -1);
}
