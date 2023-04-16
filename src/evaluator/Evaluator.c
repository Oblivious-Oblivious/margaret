#include "Evaluator.h"

#include "../base/memory.h"

#define opcode_case(opstr) if(opcode == opstr)

/**
 * @brief Runs the iterator that evaluates
    the result of the generated opcodes
 * @param self -> The Evaluator object
 */
static void evaluator_run(Evaluator *self) {
    size_t bytecodes_size = chunk_size(self->bytecode);
    for(size_t ip = 0; ip < bytecodes_size; ip++) {
        uint8_t opcode = chunk_get(self->bytecode, ip);

        // TODO Use actual opcodes
        opcode_case(0x0) {}
    }
}

Evaluator *evaluator_new(Chunk *bytecode) {
    Evaluator *self = (Evaluator*)collected_malloc(sizeof(Evaluator));

    // self->stack.top = -1;
    self->bytecode = bytecode;

    return self;
}

marg_string *evaluator_evaluate(Evaluator *self) {
    evaluator_run(self);

    // if(marg_stack_is_empty(&self->stack)) {
    //     return marg_string_new("nil");
    // }
    // else
    //     return marg_stack_peek(&self->stack, 0);
    return marg_string_new("nil");
}
