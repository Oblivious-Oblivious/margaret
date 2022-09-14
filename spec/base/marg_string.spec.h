#ifndef __MARG_STRING_SPEC_H_
#define __MARG_STRING_SPEC_H_

#include "../../src/base/marg_string.h"
#include "../cSpec.h"

module(marg_string_spec, {
    describe("string", {
        it("creates a new string", {
            marg_string *str = marg_string_new("");
            assert_that(str isnot NULL);
        });

        it("creates a string with an initial char*", {
            marg_string *str = marg_string_new("initial");
            assert_that(str isnot NULL);
        });

        context("when a string pointer is not NULL", {
            it("returns the char* when calling `string_get`", {
                marg_string *str = marg_string_new("initial");
                assert_that(sizeof(marg_string_get(str)) is sizeof(char*));
            });
        });

        context("when the initial value exitsts", {
            it("returns the correct char* when calling `string_get`", {
                marg_string *str = marg_string_new("initial");
                assert_that_charptr(marg_string_get(str) equals to "initial");
            });
        });

        /* TODO Write more tests */
    });
})

#endif
