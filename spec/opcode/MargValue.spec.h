#ifndef __MARG_VALUE_SPEC_H_
#define __MARG_VALUE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/opcode/MargValue.h"

module(MargValueSpec, {
  describe("tests NaN boxing", {
    it("boxes the same value producing the same result", {
      int *arr     = (int *)malloc(sizeof(int) * 10);
      MargValue v1 = QNAN_BOX(arr);
      MargValue v2 = QNAN_BOX(arr);
      MargValue v3 = QNAN_BOX(arr);

      assert_that_size_t(v1 equals to v2);
      assert_that_size_t(v2 equals to v3);
    });

    it("boxes and unboxes producing the same result", {
      int *arr     = (int *)malloc(sizeof(int) * 10);
      MargValue v1 = QNAN_BOX(arr);
      MargValue v2 = QNAN_BOX(arr);
      MargValue v3 = QNAN_BOX(arr);

      assert_that_size_t(QNAN_BOX(QNAN_UNBOX(v1)) equals to v1);
      assert_that_size_t(QNAN_BOX(QNAN_UNBOX(v2)) equals to v2);
      assert_that_size_t(QNAN_BOX(QNAN_UNBOX(v3)) equals to v3);
    });

    it("ensures that UNDEFINED is a static value", {
      assert_that_size_t(MARG_UNDEFINED equals to 18445618173802708992ull);
      assert_that_size_t(MARG_UNDEFINED equals to 18445618173802708992ull);
      assert_that_size_t(MARG_UNDEFINED equals to 18445618173802708992ull);
    });
  });
})

#endif
