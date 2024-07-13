#ifndef __ASSOCIATION_LIST_MODULE_SPEC_H_
#define __ASSOCIATION_LIST_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(association_list, {
  it("parses association lists", {
    parse(
      "%{a: 1, b: 2, c: 3}",
      vector_new(
        FM_STRING,
        string_new("a"),
        FM_INTEGER,
        string_new("1"),
        FM_STRING,
        string_new("b"),
        FM_INTEGER,
        string_new("2"),
        FM_STRING,
        string_new("c"),
        FM_INTEGER,
        string_new("3"),
        FM_HASH,
        string_new("6")
      )
    );
  });
})

#endif
