#ifndef __MARG_BOOLEAN_SPEC_H_
#define __MARG_BOOLEAN_SPEC_H_

#include "../../src/base/marg_boolean.h"
#include "../cSpec.h"

module(marg_boolean_spec, {
    describe("Bool", {
        it("returns true", {
            bool v = true;
            assert_that(v is true);
        });

        it("returns false", {
            bool v = false;
            assert_that(v is false);
        });
    });
})

#endif
