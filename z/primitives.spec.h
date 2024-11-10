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

      Object *number =
        AS_MARG_OBJECT(table_get(&vm->global_variables, "$Number"));
      assert_that_charptr(number->name equals to "$Number");
      Primitive *add = AS_MARG_PRIMITIVE(table_get(&number->primitives, "+"));
      assert_that(add isnot NULL);
      assert_that_charptr(add->message_name equals to "+");
    });
  });
})

#endif
