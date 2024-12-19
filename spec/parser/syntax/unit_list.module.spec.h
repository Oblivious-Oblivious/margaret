#ifndef __UNIT_LIST_MODULE_SPEC_H_
#define __UNIT_LIST_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "unit.module.spec.h"

module(unit_list, {
  it("parses a list of empty groups", {
    char **empty = NULL;
    parse("", empty);
    parse(",", empty);
    parse(",,,,,", empty);
    parse("()", vector_new(FM_NIL));
    parse("(,)", vector_new(FM_NIL));
    parse("(,),", vector_new(FM_NIL));
    parse("(,,(),),", vector_new(FM_NIL, FM_POP));
    parse("(,(),(),),", vector_new(FM_NIL, FM_POP, FM_NIL, FM_POP));
    parse("(),(),", vector_new(FM_NIL, FM_NIL));
    parse("(), (), (), ()", vector_new(FM_NIL, FM_NIL, FM_NIL, FM_NIL));
    parse(
      "((), (42), (), ())",
      vector_new(
        FM_NIL,
        FM_POP,
        FM_INTEGER,
        string_new("42"),
        FM_POP,
        FM_NIL,
        FM_POP,
        FM_NIL
      )
    );
  });

  unit();
})

#endif
