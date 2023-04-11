#ifndef __EVALUATOR_H_
#define __EVALUATOR_H_

#include "../base/marg_stack.h"
#include "../base/marg_string.h"
#include "../base/marg_vector.h"

typedef struct Evaluator {
    marg_stack stack;
    marg_vector *bytecodes;
} Evaluator;

/**
 * @brief Creates a new evaluator object
 * @param bytecodes -> The generated opcodes from the parser
 * @return Evaluator*
 */
Evaluator *evaluator_new(marg_vector *bytecodes);

/**
 * @brief Evaluates a set of bytecodes.
    Leaves the final result on top of the stack
 * @param self -> The Evaluator object
 * @return marg_string* -> The top of the stack
 */
marg_string *evaluator_evaluate(Evaluator *self);

#endif