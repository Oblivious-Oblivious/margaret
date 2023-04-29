#ifndef __CHUNK_SPEC_H_
#define __CHUNK_SPEC_H_

#include "../../src/base/chunk.h"
#include "../cSpec.h"

static chunk *c = NULL;
static void create_new_chunk(void) {
    c = chunk_new();
}

module(chunk_spec, {
    describe("chunk", {
        before_each(&create_new_chunk);

        it("creates a new chunk", {
            assert_that(c isnot NULL);
        });

        it("adds exactly three elements to the vector", {
            chunk_add(c, 41, 123);
            chunk_add(c, 42, 124);
            chunk_add(c, 43, 125);
            assert_that_int(chunk_size(c) equals to 3);
        });

        it("ensures that lines are added accordingly", {
            chunk_add(c, 43, 999);
            assert_that_int(c->lines[0] equals to 999);
        });

        it("adds 2 elements and peeks the seconds element of the vector", {
            chunk_add(c, 0, 123);
            chunk_add(c, 1, 123);
            uint8_t second = chunk_get(c, 1);
            assert_that_int(second equals to 1);
        });

        it("counts the length correctly on additions", {
            assert_that_int(chunk_size(c) equals to 0);
            chunk_add(c, 99, 123);
            chunk_add(c, 99, 123);
            assert_that_int(chunk_size(c) equals to 2);
            chunk_add(c, 99, 123);
            assert_that_int(chunk_size(c) equals to 3);
        });
    });
})

#endif
