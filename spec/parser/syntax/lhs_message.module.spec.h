#ifndef __LHS_MESSAGE_MODULE_SPEC_H_
#define __LHS_MESSAGE_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "literal.module.spec.h"

module(lhs_message, {
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

  literal();
})

#endif
