#ifndef __UNIT_LIST_MODULE_SPEC_H_
#define __UNIT_LIST_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "unit.module.spec.h"

module(unit_list, {
  it("parses a list of empty groups", {
    parse("()", vector_new(FM_NIL));
    parse("(), (), (), ()", vector_new(FM_NIL, FM_NIL, FM_NIL, FM_NIL));
  });

  unit();
})

#endif
