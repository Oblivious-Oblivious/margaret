#ifndef __MARGARET_MESSAGES_SPEC_H_
#define __MARGARET_MESSAGES_SPEC_H_

#include "_helpers.h"

module(margaret_messages_spec, {
  it("parses messages without an object", {
    parse(
      "if: $true then: {|} else: {|}",
      vector_new(
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_TRUE,
        FM_START_PROC,
        FM_NIL,
        FM_END_PROC,
        FM_START_PROC,
        FM_NIL,
        FM_END_PROC,
        FM_KEYWORD,
        string_new("if:then:else:"),
        string_new("3"),
        FM_POP
      )
    );

    parse(
      "puts: \"Hello, World!\"",
      vector_new(
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_STRING,
        string_new("Hello, World!"),
        FM_KEYWORD,
        string_new("puts:"),
        string_new("1"),
        FM_POP
      )
    );
  });

  it("parses standalone identifiers as variables and not unary messages", {
    parse("myvar", vector_new(FM_LOCAL, string_new("myvar"), FM_POP));
  });

  it("fails on parsing standalone binary messages", { error("++", ""); });

  it("binds to the Margaret object using standalone margaret messages", {
    parse(
      "$Margaret bind: # while: condition_block do: block => \
            if: condition_block eval then: {(\
                block eval, \
                while: condition_block do: block \
            )} \
        ",
      vector_new(
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_START_KEYWORD_METHOD,
        string_new("while:do:"),
        FM_METHOD_PARAMETER,
        string_new("condition_block"),
        FM_METHOD_PARAMETER,
        string_new("block"),
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_LOCAL,
        string_new("condition_block"),
        FM_UNARY,
        string_new("eval"),
        FM_START_PROC,
        FM_LOCAL,
        string_new("block"),
        FM_UNARY,
        string_new("eval"),
        FM_POP,
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_LOCAL,
        string_new("condition_block"),
        FM_LOCAL,
        string_new("block"),
        FM_KEYWORD,
        string_new("while:do:"),
        string_new("2"),
        FM_END_PROC,
        FM_KEYWORD,
        string_new("if:then:"),
        string_new("2"),
        FM_END_KEYWORD_METHOD,
        FM_KEYWORD,
        string_new("bind:"),
        string_new("1"),
        FM_POP
      )
    );
  });
})

#endif
