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
            case OP_CONSTANT: {
                MargValue constant = READ_CONSTANT();
                STACK_PUSH(self, constant);
                break;
            }
            case OP_LONG_CONSTANT: {}
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
