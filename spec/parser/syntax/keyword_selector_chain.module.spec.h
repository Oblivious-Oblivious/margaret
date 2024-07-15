#ifndef __KEYWORD_SELECTOR_CHAIN_MODULE_SPEC_H_
#define __KEYWORD_SELECTOR_CHAIN_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(keyword_selector_chain, {
  it("parses headless keyword selectors", {
    parse(
      "puts: 42",
      vector_new(
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_INTEGER,
        string_new("42"),
        FM_KEYWORD,
        string_new("puts:"),
        string_new("1")
      )
    );
  });

  it("parses keyword selectors", {
    parse(
      "[] add: 42 at: 0",
      vector_new(
        FM_TENSOR,
        string_new("0"),
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("0"),
        FM_KEYWORD,
        string_new("add:at:"),
        string_new("2")
      )
    );
  });
})

#endif
