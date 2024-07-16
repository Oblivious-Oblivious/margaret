#ifndef __UNIT_MODULE_SPEC_H_
#define __UNIT_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "assignment_message.module.spec.h"

module(unit, {
  it("parses empty group", {
    parse("42", vector_new(FM_INTEGER, string_new("42")));
  });

  assignment_message();
})

#endif
