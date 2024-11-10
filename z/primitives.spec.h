#ifndef __PRIMITIVES_SPEC_H_
#define __PRIMITIVES_SPEC_H_

#include "../libs/cSpec/export/cSpec.h"
#include "helpers.spec.h"
#include "nan_tagging.h"
#include "primitives.h"

module(primitives_spec, {
  describe("built-in methods", {
    it("defines the +, -, * and / methods", {
      vm_init(vm);

      MargObject *number =
        AS_OBJECT(table_get(&vm->global_variables, "$Number"));
      assert_that_charptr(number->name equals to "$Number");
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
