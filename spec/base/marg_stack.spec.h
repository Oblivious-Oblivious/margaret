#ifndef __MARG_STACK_SPEC_H_
#define __MARG_STACK_SPEC_H_

#include "../../src/base/marg_stack.h"
#include "../cSpec.h"

marg_stack st;
static void setup(void) {
    st.top = -1;
}

module(marg_stack_spec, {
    before_each(&setup);

    describe("stack", {
        it("asserts that a new stack is empty", {
            assert_that(marg_stack_is_empty(&st));
        });

        it("is empty after 1 push and 1 pop", {
            marg_stack_push(&st, 0);
            marg_stack_pop(&st);
            assert_that(marg_stack_is_empty(&st));
        });

        it("is not empty after 2 pushes and 1 pop", {
            marg_stack_push(&st, 0);
            marg_stack_push(&st, 0);
            marg_stack_pop(&st);
            nassert_that(marg_stack_is_empty(&st));
        });

        it("pops `x` after pushing `x`", {
            int *v1 = (int*)malloc(sizeof(int) * 64);
            int *v2 = (int*)malloc(sizeof(int) * 64);

            *v1 = 99;
            marg_stack_push(&st, v1);
            int *actual1 = marg_stack_pop(&st);
            assert_that_int(*actual1 equals to 99);

            assert_that(marg_stack_is_empty(&st));

            *v2 = 88;
            marg_stack_push(&st, v2);
            int *actual2 = marg_stack_pop(&st);
            assert_that_int(*actual2 equals to 88);

            free(v1);
            free(v2);
        });

        it("pops `y` then `x` after pushing `x` then `y`", {
            int *v1 = (int*)malloc(sizeof(int) *64); *v1 = 99;
            int *v2 = (int*)malloc(sizeof(int) *64); *v2 = 88;
            int *v3 = (int*)malloc(sizeof(int) *64); *v3 = 77;

            marg_stack_push(&st, v1);
            marg_stack_push(&st, v2);
            marg_stack_push(&st, v3);

            int *actual3 = marg_stack_pop(&st);
            int *actual2 = marg_stack_pop(&st);
            int *actual1 = marg_stack_pop(&st);
            assert_that_int(*actual3 equals to 77);
            assert_that_int(*actual2 equals to 88);
            assert_that_int(*actual1 equals to 99);

            free(v1);
            free(v2);
            free(v3);
        });

        it("peeks three elements deep", {
            int *v1 = (int*)malloc(sizeof(int) *64); *v1 = 99;
            int *v2 = (int*)malloc(sizeof(int) *64); *v2 = 88;
            int *v3 = (int*)malloc(sizeof(int) *64); *v3 = 77;

            marg_stack_push(&st, v1);
            marg_stack_push(&st, v2);
            marg_stack_push(&st, v3);

            int *peeked = marg_stack_peek(&st, 0);
            assert_that_int(*peeked equals to 77);
            peeked = marg_stack_peek(&st, 1);
            assert_that_int(*peeked equals to 88);
            peeked = marg_stack_peek(&st, 2);
            assert_that_int(*peeked equals to 99);

            free(v1);
            free(v2);
            free(v3);
        });
    });
})

#endif
