#ifndef __KEY_MODULE_SPEC_H_
#define __KEY_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(key, {
  it("parses keys", {
    parse(
      "%{a: 42}",
      vector_new(
        FM_STRING,
        string_new("a"),
        FM_INTEGER,
        string_new("42"),
        FM_TABLE,
        string_new("2")
      )
    );
  });
})

#endif
