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
            case OP_POP: {
                STACK_POP(vm);
                break;
            }
            case TEST_OP_PRINT: {
                printf("%s\n", string_get(marg_value_format(STACK_PEEK(vm, 0))));
                // STACK_POP(vm);
                // STACK_POP(vm);
                break;
            }

            case OP_HALT:
                return;

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
                int64_t number_of_elements = AS_INTEGER(READ_LONG_TEMPORARY())->value;
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
                MargProc *proc = AS_PROC(STACK_PEEK(vm, 0));
                table_add_all(&vm->current->local_variables, &proc->local_variables);
                vm->current = proc;
                break;
            }
            case OP_EXIT_PROC: {
                vm->current = vm->current->bound_proc;
                break;
            }

            default: {}
        }
    }
}

MargValue evaluator_evaluate(VM *vm) {
    evaluator_run(vm);
    return STACK_PEEK(vm, -1);
}
