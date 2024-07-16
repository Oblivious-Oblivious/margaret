#ifndef __PROCS_SPEC_H_
#define __PROCS_SPEC_H_

#include "_helpers.h"

module(procs_spec, {
  it("parses procs", {
    parse(
      "{ x = (x = 1, y = 2) }",
      vector_new(
        FM_PROC_START,
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("="),
        FM_LOCAL,
        string_new("y"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("="),
        FM_BINARY,
        string_new("="),
        FM_PROC_END
      )
    ); // x = Proc
    parse(
      "x = { \
        v1, v2 | ( \
          v1 += 1, \
          v1 += 2, \
          v1 * v2 \
        ) \
      }",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_PROC_START,
        FM_PROC_PARAMETER,
        string_new("v1"),
        FM_PROC_PARAMETER,
        string_new("v2"),
        FM_LOCAL,
        string_new("v1"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("+="),
        FM_LOCAL,
        string_new("v1"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("+="),
        FM_LOCAL,
        string_new("v1"),
        FM_LOCAL,
        string_new("v2"),
        FM_BINARY,
        string_new("*"),
        FM_PROC_END,
        FM_BINARY,
        string_new("=")
      )
    );
  });

  it("parses parameterized procs and procs returning literals", {
    parse("{}", vector_new(FM_PROC_START, FM_NIL, FM_PROC_END));
    parse(
      "{ 42 }",
      vector_new(FM_PROC_START, FM_INTEGER, string_new("42"), FM_PROC_END)
    );
    parse(
      "{ a | a puts }",
      vector_new(
        FM_PROC_START,
        FM_PROC_PARAMETER,
        string_new("a"),
        FM_LOCAL,
        string_new("a"),
        FM_UNARY,
        string_new("puts"),
        FM_PROC_END
      )
    );
    parse(
      "{ 2 + 3 }",
      vector_new(
        FM_PROC_START,
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_BINARY,
        string_new("+"),
        FM_PROC_END
      )
    );
    parse(
      "{ (x = 1, y = 2, x + y) }",
      vector_new(
        FM_PROC_START,
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("="),
        FM_LOCAL,
        string_new("y"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("="),
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("y"),
        FM_BINARY,
        string_new("+"),
        FM_PROC_END
      )
    );
    parse(
      "{ param | param puts }",
      vector_new(
        FM_PROC_START,
        FM_PROC_PARAMETER,
        string_new("param"),
        FM_LOCAL,
        string_new("param"),
        FM_UNARY,
        string_new("puts"),
        FM_PROC_END
      )
    );
    parse(
      "{ a | a }",
      vector_new(
        FM_PROC_START,
        FM_PROC_PARAMETER,
        string_new("a"),
        FM_LOCAL,
        string_new("a"),
        FM_PROC_END
      )
    );
    parse(
      "{ x = 2 } call",
      vector_new(
        FM_PROC_START,
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("="),
        FM_PROC_END,
        FM_UNARY,
        string_new("call")
      )
    );
    parse(
      "{ param | param puts } call: %{a: 42}",
      vector_new(
        FM_PROC_START,
        FM_PROC_PARAMETER,
        string_new("param"),
        FM_LOCAL,
        string_new("param"),
        FM_UNARY,
        string_new("puts"),
        FM_PROC_END,
        FM_STRING,
        string_new("a"),
        FM_INTEGER,
        string_new("42"),
        FM_HASH,
        string_new("2"),
        FM_KEYWORD,
        string_new("call:"),
        string_new("1")
      )
    );
  });
})

#endif
