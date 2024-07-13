#ifndef __KEYWORD_LIST_MODULE_SPEC_H_
#define __KEYWORD_LIST_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(keyword_list, {
  it("parses keyword lists", {
    parse(
      "#add: element at: position => 42",
      vector_new(
        FM_START_KEYWORD_METHOD,
        FM_METHOD_RECEIVER,
        FM_METHOD_ANY_OBJECT,
        string_new("add:at:"),
        FM_METHOD_PARAMETER,
        string_new("element"),
        FM_METHOD_PARAMETER,
        string_new("position"),
        FM_INTEGER,
        string_new("42"),
        FM_END_KEYWORD_METHOD
      )
    );
  });
})

#endif
