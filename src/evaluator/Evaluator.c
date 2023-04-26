#include "Evaluator.h"

#include <stdio.h>

#include "../opcode/Opcodes.h"
#include "../opcode/MargValue.h"

/**
 * @brief Runs the iterator that evaluates
    the result of the generated opcodes
 * @param self -> result enum
 */
static EvaluatorResult evaluator_run(VM *self) {
    // TODO Branch table, computed goto
    while(1) {
        uint8_t instruction;
        switch(instruction = READ_BYTE()) {
            case TEST_OP_PRINT: {
                printf("%s\n", string_get(marg_value_format(STACK_PEEK(self, 0))));
                STACK_POP(self);
                break;
            }
            case OP_NIL: {
                STACK_PUSH(self, MARG_NIL);
                break;
            }
            case OP_TRUE: {
                STACK_PUSH(self, MARG_TRUE);
                break;
            }
            case OP_FALSE: {
                STACK_PUSH(self, MARG_FALSE);
                break;
            }

            // TODO Rename CONSTANT to LITERAL or OBJECT
            case OP_CONSTANT: {
                STACK_PUSH(self, READ_CONSTANT());
                break;
            }
            case OP_CONSTANT_LONG: {
                STACK_PUSH(self, READ_LONG_CONSTANT());
                break;
            }

            case OP_POP: {
                STACK_POP(self);
                break;
            }

            case OP_STORE_GLOBAL: {
                marg_hash_set(&self->global_variables, READ_STRING(), STACK_PEEK(self, 0));
                STACK_POP(self);
                break;
            }
            case OP_STORE_GLOBAL_LONG: {
                marg_hash_set(&self->global_variables, READ_LONG_STRING(), STACK_PEEK(self, 0));
                STACK_POP(self);
                break;
            }

            case OP_GLOBAL: {
                MargValue variable;
                marg_hash_get(&self->global_variables, READ_STRING(), &variable);
                STACK_PUSH(self, variable);
                break;
            }
            case OP_GLOBAL_LONG: {
                MargValue variable;
                marg_hash_get(&self->global_variables, READ_LONG_STRING(), &variable);
                STACK_PUSH(self, variable);
                break;
            }

            case OP_RETURN: {
                return EVALUATOR_OK;
            }

            default: {}
        }
    }
}

MargValue evaluator_evaluate(VM *self) {
    self->ip = self->bytecode->items;
    EvaluatorResult result = evaluator_run(self);
    (void)result;

    return STACK_PEEK(self, 0);
}
