#ifndef __BINARY_SELECTOR_CHAIN_MODULE_SPEC_H_
#define __BINARY_SELECTOR_CHAIN_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(binary_selector_chain, {
  it("parses binary selectors", {
    parse(
      "42 + 41",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("41"),
        FM_BINARY,
        string_new("+")
      )
    );

    parse(
      "1 + 2 * 3",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("3"),
        FM_BINARY,
        string_new("*")
      )
    );
  });
})

#endif
