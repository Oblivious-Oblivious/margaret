#ifndef __BIT_MODULE_SPEC_H_
#define __BIT_MODULE_SPEC_H_

#include "../../generic/_helpers.h"

module(bit, {
  it("parses bits", {
    parse(
      "%(0::1, 0::1, 1::1, 1::1)",
      vector_new(
        FM_INTEGER,
        string_new("0"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("0"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("1"),
        FM_BITSTRING,
        string_new("8")
      )
    );
  });
})

#endif
