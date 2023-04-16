#include "Evaluator.h"

#include "../base/memory.h"

Evaluator *evaluator_new(marg_vector *bytecodes) {
    (void)bytecodes;
    Evaluator *self = (Evaluator*)collected_malloc(sizeof(Evaluator));

    return self;
}
