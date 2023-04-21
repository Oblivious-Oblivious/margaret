#ifndef __VECTOR_SPEC_H_
#define __VECTOR_SPEC_H_

#include "../../src/base/vector.h"
#include "../cSpec.h"

module(vector_spec, {
    describe("vector", {
        vector *v = NULL;
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
            v = vector_new_empty();
            assert_that(v isnot NULL);
        });

        it("adds exactly three elements to the vector", {
            vector_add(v, a);
            vector_add(v, b);
            vector_add(v, c);
            assert_that_int(vector_size(v) equals to 3);
        });

        it("creates a new vector with initial elements", {
            v = vector_new(a, b, c);
            assert_that_int(vector_size(v) equals to 3);
        });

        it("peeks the second element of the vector", {
            int *first = (int*)vector_get(v, 1);
            assert_that_int(*first equals to *b);
        });

        it("counts the length correctly on additions", {
            vector *vv = vector_new_empty();

            assert_that_int(vector_size(vv) equals to 0);
            vector_add(vv, NULL);
            vector_add(vv, NULL);
            assert_that_int(vector_size(vv) equals to 2);
            vector_add(vv, NULL);
            assert_that_int(vector_size(vv) equals to 3);
        });

        after({
            free(a);
            free(b);
            free(c);
        });
    });
})

#endif
