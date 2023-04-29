#ifndef __TEMPORARIES_SPEC_H_
#define __TEMPORARIES_SPEC_H_

#include "../../src/base/temporaries.h"
#include "../cSpec.h"

module(temporaries_spec, {
    temporaries t;

    describe("temporaries", {
        it("adds exactly three elements to the vector", {
            temporaries_init(&t);
            temporaries_add(&t, 41);
            temporaries_add(&t, 42);
            temporaries_add(&t, 43);
            assert_that_int(temporaries_size(&t) equals to 3);
        });

        it("adds 2 elements and peeks the seconds element of the vector", {
            temporaries_init(&t);
            temporaries_add(&t, 0);
            temporaries_add(&t, 1);
            uint8_t second = temporaries_get(&t, 1);
            assert_that_int(second equals to 1);
        });

        it("counts the length correctly on additions", {
            temporaries_init(&t);
            assert_that_int(temporaries_size(&t) equals to 0);
            temporaries_add(&t, 99);
            temporaries_add(&t, 99);
            assert_that_int(temporaries_size(&t) equals to 2);
            temporaries_add(&t, 99);
            assert_that_int(temporaries_size(&t) equals to 3);
        });
    });
})

#endif
