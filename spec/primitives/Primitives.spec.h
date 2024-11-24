#ifndef __PRIMITIVES_SPEC_H_
#define __PRIMITIVES_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/primitives/Primitives.h"

module(PrimitivesSpec, {
  describe("built-in methods", {
    it("defines the +, -, * and / methods", {
      VM *vm = vm_new("file.marg");

      MargObject *number = AS_OBJECT(G("$Numeric"));
      assert_that_charptr(number->name equals to "$Numeric");
      assert_that_size_t(number->name_hash equals to 12111199799677591582u);
      MargPrimitive *add = AS_PRIMITIVE(table_get(&number->primitives, "+"));
      MargPrimitive *sub = AS_PRIMITIVE(table_get(&number->primitives, "-"));
      MargPrimitive *mul = AS_PRIMITIVE(table_get(&number->primitives, "*"));
      MargPrimitive *div = AS_PRIMITIVE(table_get(&number->primitives, "/"));
      MargPrimitive *err = AS_PRIMITIVE(table_get(&number->primitives, "]"));
      assert_that(add isnot NULL);
      assert_that(sub isnot NULL);
      assert_that(mul isnot NULL);
      assert_that(div isnot NULL);
      assert_that(err isnot NULL);
    });
  });
})

#endif
