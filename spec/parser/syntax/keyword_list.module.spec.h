#ifndef __KEYWORD_LIST_MODULE_SPEC_H_
#define __KEYWORD_LIST_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(keyword_list, {
  it("parses keyword lists", {
    parse(
      "#add: element at: position => 42",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("element"),
        FM_METHOD_ARGUMENT,
        string_new("position"),
        FM_METHOD_NAME,
        string_new("add:at:_KEYWORD"),
        FM_INTEGER,
        string_new("42"),
        FM_METHOD_END
      )
    );
  });
})

#endif
