#ifndef __SPEC_HELPER_H_
#define __SPEC_HELPER_H_

// base
#include "base/marg_vector.spec.h"
#include "base/marg_stack.spec.h"
#include "base/marg_string.spec.h"
#include "base/marg_table.spec.h"

// tokens
#include "tokens/Token.spec.h"
#include "tokens/TokenTable.spec.h"
#include "tokens/Type.spec.h"

#include "cSpec.h"

spec_suite({
    marg_vector_spec();
    marg_stack_spec();
    marg_string_spec();
    marg_table_spec();

    TokenSpec();
    TokenTableSpec();
    TypeSpec();
})

int main(void) {
    run_spec_suite("failing");
}

#endif
