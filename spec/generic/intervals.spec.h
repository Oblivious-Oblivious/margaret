#ifndef __INTERVALS_SPEC_H_
#define __INTERVALS_SPEC_H_

#include "_helpers.h"

module(intervals_spec, {
  it("parses intervals", {
    parse(
      "x = Interval from: 5 to: 10",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("Interval"),
        FM_INTEGER,
        string_new("5"),
        FM_INTEGER,
        string_new("10"),
        FM_KEYWORD,
        string_new("from:to:"),
        string_new("2"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = Interval from: 5 to: 10 by: 2",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("Interval"),
        FM_INTEGER,
        string_new("5"),
        FM_INTEGER,
        string_new("10"),
        FM_INTEGER,
        string_new("2"),
        FM_KEYWORD,
        string_new("from:to:by:"),
        string_new("3"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = 5 to: 10",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("5"),
        FM_INTEGER,
        string_new("10"),
        FM_KEYWORD,
        string_new("to:"),
        string_new("1"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = 5 to: 10 by: 2",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("5"),
        FM_INTEGER,
        string_new("10"),
        FM_INTEGER,
        string_new("2"),
        FM_KEYWORD,
        string_new("to:by:"),
        string_new("2"),
        FM_ASSIGNMENT
      )
    );
  });
})

#endif
