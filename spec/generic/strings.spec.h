#ifndef __STRINGS_SPEC_H_
#define __STRINGS_SPEC_H_

#include "_helpers.h"

module(strings_spec, {
  it("parses empty strings", {
    parse("'\"'", vector_new(FM_STRING, string_new("\"")));
    parse("\"'\"", vector_new(FM_STRING, string_new("'")));
  });

  it("parses string literals", {
    parse(
      "\"hello\" puts",
      vector_new(FM_STRING, string_new("hello"), FM_UNARY, string_new("puts"))
    );
    parse(
      "\"multi\n\
        line\n\
        string\"",
      vector_new(FM_STRING, string_new("multi\n        line\n        string"))
    );
  });

  it("parses escape strings", {
    parse("\"foo\tbar\"", vector_new(FM_STRING, string_new("foo\tbar")));
    parse(
      "\"a string lit\"", vector_new(FM_STRING, string_new("a string lit"))
    );
    parse("\"str\"", vector_new(FM_STRING, string_new("str")));

    parse("\"\a\"", vector_new(FM_STRING, string_new("\a")));
    parse("\"\b\"", vector_new(FM_STRING, string_new("\b")));
    parse("\"\t\"", vector_new(FM_STRING, string_new("\t")));
    parse("\"\n\"", vector_new(FM_STRING, string_new("\n")));
    parse("\"\v\"", vector_new(FM_STRING, string_new("\v")));
    parse("\"\f\"", vector_new(FM_STRING, string_new("\f")));
    parse("\"\r\"", vector_new(FM_STRING, string_new("\r")));
    parse("\"\\\"", vector_new(FM_STRING, string_new("\\")));
  });

  it("parses string messages", {
    parse(
      "b = s is_empty?",
      vector_new(
        FM_LOCAL,
        string_new("b"),
        FM_LOCAL,
        string_new("s"),
        FM_UNARY,
        string_new("is_empty?"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = s size",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("s"),
        FM_UNARY,
        string_new("size"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = s at: 2",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("s"),
        FM_INTEGER,
        string_new("2"),
        FM_KEYWORD,
        string_new("at:"),
        string_new("1"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = s copy_from: 2 to: 4",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("s"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("4"),
        FM_KEYWORD,
        string_new("copy_from:to:"),
        string_new("2"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = s index_of: 'a' if_absent: 0",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("s"),
        FM_STRING,
        string_new("a"),
        FM_INTEGER,
        string_new("0"),
        FM_KEYWORD,
        string_new("index_of:if_absent:"),
        string_new("2"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "s at: 1 put: 'a', s at: 2 put: 'b', s at: 3 put: 'c'",
      vector_new(
        FM_LOCAL,
        string_new("s"),
        FM_INTEGER,
        string_new("1"),
        FM_STRING,
        string_new("a"),
        FM_KEYWORD,
        string_new("at:put:"),
        string_new("2"),
        FM_LOCAL,
        string_new("s"),
        FM_INTEGER,
        string_new("2"),
        FM_STRING,
        string_new("b"),
        FM_KEYWORD,
        string_new("at:put:"),
        string_new("2"),
        FM_LOCAL,
        string_new("s"),
        FM_INTEGER,
        string_new("3"),
        FM_STRING,
        string_new("c"),
        FM_KEYWORD,
        string_new("at:put:"),
        string_new("2")
      )
    );
    parse(
      "s << 'a' << 'b' << 'c' << 'd'",
      vector_new(
        /* OP_MOV, RA, s */
        FM_LOCAL,
        string_new("s"),

        /* OP_MESSAGE, CONST("<<"), RA, CONST(MARG_TENSOR("a")) */
        FM_STRING,
        string_new("a"),
        FM_BINARY,
        string_new("<<"),

        /* OP_MESSAGE, CONST("<<"), RA, CONST(MARG_TENSOR("b")) */
        FM_STRING,
        string_new("b"),
        FM_BINARY,
        string_new("<<"),

        /* OP_MESSAGE, CONST("<<"), RA, CONST(MARG_TENSOR("c")) */
        FM_STRING,
        string_new("c"),
        FM_BINARY,
        string_new("<<"),

        /* OP_MESSAGE, CONST("<<"), RA, CONST(MARG_TENSOR("d")) */
        FM_STRING,
        string_new("d"),
        FM_BINARY,
        string_new("<<")
      )
    );
    parse(
      "s add: 'a' add: 'b' add: 'c' add: 'd'",
      vector_new(
        FM_LOCAL,
        string_new("s"),
        FM_STRING,
        string_new("a"),
        FM_STRING,
        string_new("b"),
        FM_STRING,
        string_new("c"),
        FM_STRING,
        string_new("d"),
        FM_KEYWORD,
        string_new("add:add:add:add:"),
        string_new("4")
      )
    );
    parse(
      "s each_char: {a | a puts}",
      vector_new(
        FM_LOCAL,
        string_new("s"),
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("a"),
        FM_LOCAL,
        string_new("a"),
        FM_UNARY,
        string_new("puts"),
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("each_char:"),
        string_new("1")
      )
    );
    parse(
      "b = s conform: {a | (a >= 'a') && (a <= 'z')}",
      vector_new(
        FM_LOCAL,
        string_new("b"),
        FM_LOCAL,
        string_new("s"),
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("a"),
        FM_LOCAL,
        string_new("a"),
        FM_STRING,
        string_new("a"),
        FM_BINARY,
        string_new(">="),
        FM_LOCAL,
        string_new("a"),
        FM_STRING,
        string_new("z"),
        FM_BINARY,
        string_new("<="),
        FM_BINARY,
        string_new("&&"),
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("conform:"),
        string_new("1"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = s select: { a | a > 'a'}",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("s"),
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("a"),
        FM_LOCAL,
        string_new("a"),
        FM_STRING,
        string_new("a"),
        FM_BINARY,
        string_new(">"),
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("select:"),
        string_new("1"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = s to_list",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("s"),
        FM_UNARY,
        string_new("to_list"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = s to_symbol",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("s"),
        FM_UNARY,
        string_new("to_symbol"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = \"abcd\" to_byte_array",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_STRING,
        string_new("abcd"),
        FM_UNARY,
        string_new("to_byte_array"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x = s shuffled",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("s"),
        FM_UNARY,
        string_new("shuffled"),
        FM_ASSIGNMENT
      )
    );
  });
})

#endif
