#ifndef __SPEC_HELPER_H_
#define __SPEC_HELPER_H_

// Base
#include "base/marg_vector.spec.h"
#include "base/marg_stack.spec.h"

#include "cSpec.h"

spec_suite({
    marg_vector_spec();
    marg_stack_spec();
})

int main(void) {
    run_spec_suite("all");
}

#endif
