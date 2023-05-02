#include "Evaluator.h"

#include <stdio.h>

#include "../opcode/Opcodes.h"
#include "../opcode/MargValue.h"

#include "../opcode/MargNil.h"
#include "../opcode/MargFalse.h"
#include "../opcode/MargTrue.h"
#include "../opcode/MargInteger.h"
/**
 * @brief Runs the iterator that evaluates
    the result of the generated opcodes
 * @param vm -> result enum
 */
static EvaluatorResult evaluator_run(VM *vm) {
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
                MargValue nilv = MARG_NIL;
                STACK_PUSH(vm, nilv);
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

            case OP_GET_GLOBAL: {
                STACK_PUSH(vm, table_get(&vm->global_variables, READ_TEMPORARY()));
                break;
            }
            case OP_GET_GLOBAL_LONG: {
                STACK_PUSH(vm, table_get(&vm->global_variables, READ_LONG_TEMPORARY()));
                break;
            }

            default: {}
        }
    }
}

MargValue evaluator_evaluate(VM *vm) {
    vm->main->ip = vm->main->bytecode->items;
    EvaluatorResult result = evaluator_run(vm);
    (void)result; // TODO

    return STACK_PEEK(vm, 0);
}
