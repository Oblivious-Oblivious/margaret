#ifndef __CHUNK_SPEC_H_
#define __CHUNK_SPEC_H_

#include "../../src/opcode/Chunk.h"
#include "../cSpec.h"

module(ChunkSpec, {
    describe("Chunk", {
        Chunk *v = NULL;
        int8_t a;
        int8_t b;
        int8_t c;

        before({
            v = NULL;
            a = 1;
            b = 2;
            c = 3;
        });

        it("creates a new vector", {
            v = chunk_new();
            assert_that(v isnot NULL);
        });

        it("adds exactly three elements to the vector", {
            chunk_add(v, a);
            chunk_add(v, b);
            chunk_add(v, c);
            assert_that_int(chunk_size(v) equals to 3);
        });

        it("peeks the second element of the vector", {
            uint8_t first = chunk_get(v, 1);
            assert_that_int(first equals to b);
        });

        it("counts the length correctly on additions", {
            Chunk *vv = chunk_new();

            assert_that_int(chunk_size(vv) equals to 0);
            chunk_add(vv, 0);
            chunk_add(vv, 0);
            assert_that_int(chunk_size(vv) equals to 2);
            chunk_add(vv, 0);
            assert_that_int(chunk_size(vv) equals to 3);
        });
    });
})

#endif
