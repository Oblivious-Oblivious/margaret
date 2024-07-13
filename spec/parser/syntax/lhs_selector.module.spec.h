#ifndef __LHS_SELECTOR_MODULE_SPEC_H_
#define __LHS_SELECTOR_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(lhs_selector, {
  it("parses lhs messages", {
    parse("!$false", vector_new(FM_FALSE, FM_LHS, string_new("!")));
    parse(
      "-42 - 42",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_LHS,
        string_new("-"),
        FM_INTEGER,
        string_new("42"),
        FM_BINARY,
        string_new("-")
      )
    );
  });
})

#endif
