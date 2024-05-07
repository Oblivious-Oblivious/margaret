#ifndef __PROCS_SPEC_H_
#define __PROCS_SPEC_H_

#include "../_helpers.h"

module(procs_spec, {
  it("parses procs", {
    parse(
      "{ x = (x = 1, y = 2) }",
      vector_new(
        FM_START_PROC,
        FM_INTEGER,
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP,
        FM_INTEGER,
        string_new("2"),
        FM_STORE_LOCAL,
        string_new("y"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_END_PROC,
        FM_POP
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
        FM_START_PROC,
        FM_LOCAL,
        string_new("v1"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("+="),
        FM_POP,
        FM_LOCAL,
        string_new("v1"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("+="),
        FM_POP,
        FM_LOCAL,
        string_new("v1"),
        FM_LOCAL,
        string_new("v2"),
        FM_BINARY,
        string_new("*"),
        FM_END_PROC,
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP
      )
    );
  });

  it("parses parameterized procs and procs returning literals", {
    parse("{|}", vector_new(FM_START_PROC, FM_NIL, FM_END_PROC, FM_POP));
    parse(
      "{ 42 }",
      vector_new(
        FM_START_PROC, FM_INTEGER, string_new("42"), FM_END_PROC, FM_POP
      )
    );
    parse(
      "{ a | a puts }",
      vector_new(
        FM_START_PROC,
        FM_LOCAL,
        string_new("a"),
        FM_UNARY,
        string_new("puts"),
        FM_END_PROC,
        FM_POP
      )
    );
    parse(
      "{ 2 + 3 }",
      vector_new(
        FM_START_PROC,
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_BINARY,
        string_new("+"),
        FM_END_PROC,
        FM_POP
      )
    );
    parse(
      "{ (x = 1, y = 2, x + y) }",
      vector_new(
        FM_START_PROC,
        FM_INTEGER,
        string_new("1"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_POP,
        FM_INTEGER,
        string_new("2"),
        FM_STORE_LOCAL,
        string_new("y"),
        FM_POP,
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("y"),
        FM_BINARY,
        string_new("+"),
        FM_END_PROC,
        FM_POP
      )
    );
    parse(
      "{ param | param puts }",
      vector_new(
        FM_START_PROC,
        FM_LOCAL,
        string_new("param"),
        FM_UNARY,
        string_new("puts"),
        FM_END_PROC,
        FM_POP
      )
    );
    parse(
      "{ a | a }",
      vector_new(FM_START_PROC, FM_LOCAL, string_new("a"), FM_END_PROC, FM_POP)
    );
    parse(
      "{ x = 2 } call",
      vector_new(
        FM_START_PROC,
        FM_INTEGER,
        string_new("2"),
        FM_STORE_LOCAL,
        string_new("x"),
        FM_END_PROC,
        FM_UNARY,
        string_new("call"),
        FM_POP
      )
    );
    parse(
      "{ param | param puts } call: {a: 42}",
      vector_new(
        FM_START_PROC,
        FM_LOCAL,
        string_new("param"),
        FM_UNARY,
        string_new("puts"),
        FM_END_PROC,
        FM_STRING,
        string_new("a"),
        FM_INTEGER,
        string_new("42"),
        FM_HASH,
        string_new("2"),
        FM_KEYWORD,
        string_new("call:"),
        string_new("1"),
        FM_POP
      )
    );
  });
})

#endif
