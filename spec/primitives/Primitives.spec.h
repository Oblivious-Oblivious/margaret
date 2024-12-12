#ifndef __PRIMITIVES_SPEC_H_
#define __PRIMITIVES_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/primitives/Primitives.h"

module(PrimitivesSpec, {
  describe("built-in methods", {
    it("defines the +, -, * and / methods", {
      VM *vm = vm_new("file.marg");

      fail("TODO - Test all primitives");

      assert_that(AS_PRIMITIVE(table_get(&vm->primitives, "+")) isnot NULL);
      assert_that(AS_PRIMITIVE(table_get(&vm->primitives, "-")) isnot NULL);
      assert_that(AS_PRIMITIVE(table_get(&vm->primitives, "*")) isnot NULL);
      assert_that(AS_PRIMITIVE(table_get(&vm->primitives, "/")) isnot NULL);
      assert_that(AS_PRIMITIVE(table_get(&vm->primitives, "]")) isnot NULL);
    });
  });
})

#endif
