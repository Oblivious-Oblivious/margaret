#ifndef __COMPLEX_SPEC_H_
#define __COMPLEX_SPEC_H_

#include "_helpers.h"

module(complex_spec, {
  it("parses complex literals", {
    parse(
      "1i",
      vector_new(FM_INTEGER, string_new("1"), FM_UNARY, string_new("i"), FM_POP)
    );
    parse(
      "1i * 1i",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_UNARY,
        string_new("i"),
        FM_INTEGER,
        string_new("1"),
        FM_UNARY,
        string_new("i"),
        FM_BINARY,
        string_new("*"),
        FM_POP
      )
    );
    parse(
      "12.3r i",
      vector_new(
        FM_FLOAT,
        string_new("12.3"),
        FM_UNARY,
        string_new("r"),
        FM_UNARY,
        string_new("i"),
        FM_POP
      )
    );
  });

  it(
    "parses complex literal messages",
    {
      // TODO
    }
  );
})

#endif
