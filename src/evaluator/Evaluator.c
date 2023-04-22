#include "Evaluator.h"

#include <stdio.h>

#include "../opcode/Opcodes.h"

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
            case OP_NIL: {
                STACK_PUSH(self, MARG_NIL);
                break;
            }
            case OP_TRUE: {
                STACK_PUSH(self, MARG_BOOL(true));
                break;
            }
            case OP_FALSE: {
                STACK_PUSH(self, MARG_BOOL(false));
                break;
            }

            // TODO Rename CONSTANT to LITERAL or OBJECT
            case OP_CONSTANT: {
                STACK_PUSH(self, READ_CONSTANT());
                break;
            }
            case OP_LONG_CONSTANT: {
                STACK_PUSH(self, READ_LONG_CONSTANT());
                break;
            }

            case OP_RETURN: {
                return EVALUATOR_OK;
            }
        }
    }
}

MargValue evaluator_evaluate(VM *self) {
    self->ip = self->bytecode->items;
    EvaluatorResult result = evaluator_run(self);
    (void)result;

    return STACK_PEEK(self);
}
