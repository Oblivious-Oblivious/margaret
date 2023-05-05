#include "Evaluator.h"

#include <stdio.h>

#include "../opcode/Opcodes.h"
#include "../opcode/MargValue.h"

#include "../opcode/MargNil.h"
#include "../opcode/MargFalse.h"
#include "../opcode/MargTrue.h"
#include "../opcode/MargInteger.h"
#include "../opcode/MargString.h"

static ActivationRecord *get_margaret_main_activation_record(VM *vm) {
    MargObject *margaret_object = AS_OBJECT(table_get(&vm->global_variables, MARG_STRING("$Margaret")));
    MargMethod *main_method = AS_METHOD(table_get(&margaret_object->messages, MARG_STRING("main:")));
    return main_method->proc->activation_record;
}

/**
 * @brief Runs the iterator that evaluates
    the result of the generated opcodes
 * @param vm -> result enum
 */
static EvaluatorResult evaluator_run(VM *vm) {
    vm->current = get_margaret_main_activation_record(vm);
    vm->current->ip = vm->current->bytecode->items;

    // TODO Branch table, computed goto
    while(1) {
        uint8_t instruction;
        switch(instruction = READ_BYTE()) {
            case OP_POP: {
                STACK_POP(vm);
                break;
            }
            case OP_RETURN: {
                return EVALUATOR_OK;
            }
            case TEST_OP_PRINT: {
                printf("%s\n", string_get(marg_value_format(STACK_PEEK(vm, 0))));
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

            case OP_SET_GLOBAL: {
                table_set(&vm->global_variables, READ_TEMPORARY(), STACK_PEEK(vm, 0));
                STACK_POP(vm);
                break;
            }
            case OP_SET_GLOBAL_LONG: {
                table_set(&vm->global_variables, READ_LONG_TEMPORARY(), STACK_PEEK(vm, 0));
                STACK_POP(vm);
                break;
            }
            case OP_SET_INSTANCE: {
                table_set(vm->current->instance_variables, READ_TEMPORARY(), STACK_PEEK(vm, 0));
                STACK_POP(vm);
                break;
            }
            case OP_SET_INSTANCE_LONG: {
                table_set(vm->current->instance_variables, READ_LONG_TEMPORARY(), STACK_PEEK(vm, 0));
                STACK_POP(vm);
                break;
            }
            case OP_SET_LOCAL: {
                table_set(&vm->current->local_variables, READ_TEMPORARY(), STACK_PEEK(vm, 0));
                STACK_POP(vm);
                break;
            }
            case OP_SET_LOCAL_LONG: {
                table_set(&vm->current->local_variables, READ_LONG_TEMPORARY(), STACK_PEEK(vm, 0));
                STACK_POP(vm);
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
                MargProc *proc = AS_PROC(table_get(&vm->current->local_variables, READ_TEMPORARY()));
                table_add_all(&vm->current->local_variables, &proc->activation_record->local_variables);
                vm->current = proc->activation_record;
                break;
            }
            case OP_EXIT_PROC: {
                vm->current = get_margaret_main_activation_record(vm);
                break;
            }

            default: {}
        }
    }
}

MargValue evaluator_evaluate(VM *vm) {
    EvaluatorResult result = evaluator_run(vm);
    (void)result; // TODO

    return STACK_PEEK(vm, 0);
}
