#ifndef __ASSIGNMENT_CHAIN_MODULE_SPEC_H_
#define __ASSIGNMENT_CHAIN_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(assignment_chain, {
  it("parses assignments", {
    parse(
      "x = 4",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("4"),
        FM_BINARY,
        string_new("=")
      )
    );

    parse(
      "x = y = z = 6",
      vector_new(
        FM_LOCAL,
        string_new("z"),
        FM_INTEGER,
        string_new("6"),
        FM_BINARY,
        string_new("="),
        FM_LOCAL,
        string_new("y"),
        FM_BINARY,
        string_new("="),
        FM_LOCAL,
        string_new("x"),
        FM_BINARY,
        string_new("=")
      )
    );
  });
})

#endif
