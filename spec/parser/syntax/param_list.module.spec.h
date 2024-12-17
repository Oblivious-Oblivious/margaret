#ifndef __PARAM_LIST_MODULE_SPEC_H_
#define __PARAM_LIST_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(param_list, {
  it("parses param lists", {
    parse(
      "{ a, b, c | (a, b, c) }",
      vector_new(
        FM_METHOD_START,
        FM_LOCAL,
        string_new("a"),
        FM_METHOD_PARAMETER,
        FM_LOCAL,
        string_new("b"),
        FM_METHOD_PARAMETER,
        FM_LOCAL,
        string_new("c"),
        FM_METHOD_PARAMETER,
        FM_LOCAL,
        string_new("a"),
        FM_LOCAL,
        string_new("b"),
        FM_LOCAL,
        string_new("c"),
        FM_METHOD_END
      )
    );
  });
})

#endif
