#ifndef __MARG_VECTOR_SPEC_H_
#define __MARG_VECTOR_SPEC_H_

#include "../../src/base/marg_vector.h"
#include "../cSpec.h"

module(marg_vector_spec, {
    describe("vector", {
        marg_vector *v = NULL;
        int *a = NULL;
        int *b = NULL;
        int *c = NULL;

        before({
            v = NULL;
            a = (int*)malloc(sizeof(int) * 64); *a = 1;
            b = (int*)malloc(sizeof(int) * 64); *b = 2;
            c = (int*)malloc(sizeof(int) * 64); *c = 3;
        });

        it("creates a new vector", {
            v = marg_vector_new_empty();
            assert_that(v isnot NULL);
        });

        it("adds exactly three elements to the vector", {
            marg_vector_add(v, a);
            marg_vector_add(v, b);
            marg_vector_add(v, c);
            assert_that_int(marg_vector_size(v) equals to 3);
        });

        it("creates a new vector with initial elements", {
            v = marg_vector_new(a, b, c);
            assert_that_int(marg_vector_size(v) equals to 3);
        });

        it("peeks the second element of the vector", {
            int *first = (int*)marg_vector_get(v, 1);
            assert_that_int(*first equals to *b);
        });

        it("counts the length correctly on additions", {
            marg_vector *vv = marg_vector_new_empty();

            assert_that_int(marg_vector_size(vv) equals to 0);
            marg_vector_add(vv, NULL);
            marg_vector_add(vv, NULL);
            assert_that_int(marg_vector_size(vv) equals to 2);
            marg_vector_add(vv, NULL);
            assert_that_int(marg_vector_size(vv) equals to 3);
        });

        it("frees vector items without error", {
            marg_vector_free(v);
            assert_that(true is true);
        });

        after({
            free(a);
            free(b);
            free(c);
        });
    });
})

#endif
