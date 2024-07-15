#ifndef __UNARY_SELECTOR_CHAIN_MODULE_SPEC_H_
#define __UNARY_SELECTOR_CHAIN_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(unary_selector_chain, {
  it("parses unary selectors", {
    parse(
      "42 factorial",
      vector_new(
        FM_INTEGER, string_new("42"), FM_UNARY, string_new("factorial")
      )
    );

    parse(
      "40 incr incr",
      vector_new(
        FM_INTEGER,
        string_new("40"),
        FM_UNARY,
        string_new("incr"),
        FM_UNARY,
        string_new("incr")
      )
    );
  });
})

#endif
