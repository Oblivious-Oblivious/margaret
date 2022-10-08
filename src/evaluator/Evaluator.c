#include "Evaluator.h"

#include <stdlib.h> /* size_t */
#include "../base/memory.h"
#include "../opcode/Opcode.h"

#define opcode_case(opstr) if(marg_string_equals(opcode, (opstr)))

/**
 * @brief Runs the iterator that evaluates
    the result of the generated opcodes
 * @param self -> The Evaluator object
 */
static void evaluator_run(Evaluator *self) {
    size_t bytecodes_size = marg_vector_size(self->bytecodes);
    for(size_t ip = 0; ip < bytecodes_size; ip++) {
        marg_string *opcode = marg_vector_get(self->bytecodes, ip);

        opcode_case(OP_PUSH_NIL) {}
        opcode_case(OP_PUSH_TRUE) {}
        opcode_case(OP_PUSH_FALSE) {}
        opcode_case(OP_PUSH_SELF) {}
        opcode_case(OP_PUSH_SUPER) {}
        opcode_case(OP_PUSH_0) {
            marg_stack_push(&self->stack, marg_string_new("0"));
        }
        opcode_case(OP_PUSH_1) {
            marg_stack_push(&self->stack, marg_string_new("1"));
        }
        opcode_case(OP_PUSH_MINUS_1) {
            marg_stack_push(&self->stack, marg_string_new("-1"));
        }
        opcode_case(OP_PUSH_2) {
            marg_stack_push(&self->stack, marg_string_new("2"));
        }
        opcode_case(OP_PUSH_INTEGER) {
            ip += 1;
            marg_string *number = marg_vector_get(self->bytecodes, ip);
            marg_stack_push(&self->stack, number);
        }
        opcode_case(OP_PUSH_FLOAT) {
            ip += 1;
            marg_string *f = marg_vector_get(self->bytecodes, ip);
            marg_stack_push(&self->stack, f);
        }
        opcode_case(OP_PUSH_CHAR) {
            ip += 1;
            marg_string *c = marg_vector_get(self->bytecodes, ip);
            marg_stack_push(&self->stack, c);
        }
        opcode_case(OP_PUSH_STRING) {
            ip += 1;
            marg_string *str = marg_vector_get(self->bytecodes, ip);
            marg_stack_push(&self->stack, str);
        }
        opcode_case(OP_PUSH_VARIABLE) {}
        opcode_case(OP_PUSH_INSTANCE) {}
        opcode_case(OP_PUSH_TENSOR) {}
        opcode_case(OP_PUSH_HASH) {}

        // TODO procs, methods and functions return tensors of bytecodes
        opcode_case(OP_START_PUSH_PROC) {}
        opcode_case(OP_END_PUSH_PROC) {}
        opcode_case(OP_START_PUSH_C_FUNCTION) {}
        opcode_case(OP_END_PUSH_C_FUNCTION) {}
        opcode_case(OP_START_PUSH_UNARY_METHOD) {}
        opcode_case(OP_END_PUSH_UNARY_METHOD) {}
        opcode_case(OP_START_PUSH_BINARY_METHOD) {}
        opcode_case(OP_END_PUSH_BINARY_METHOD) {}
        opcode_case(OP_START_PUSH_KEYWORD_METHOD) {}
        opcode_case(OP_END_PUSH_KEYWORD_METHOD) {}

        opcode_case(OP_POP) {
            marg_stack_pop(&self->stack);
        }
        opcode_case(OP_STORE) {}
        opcode_case(OP_STORE_INSTANCE) {}
        opcode_case(OP_UNARY) {}
        opcode_case(OP_BINARY) {}
        opcode_case(OP_KEYWORD) {}
    }
}

Evaluator *evaluator_new(marg_vector *bytecodes) {
    Evaluator *self = (Evaluator*)collected_malloc(sizeof(Evaluator));

    self->stack.top = -1;
    self->bytecodes = bytecodes;

    return self;
}

marg_string *evaluator_evaluate(Evaluator *self) {
    evaluator_run(self);
    if(marg_stack_is_empty(&self->stack)) {
        return marg_string_new("nil");
    }
    else
        return marg_stack_peek(&self->stack, 0);
}
