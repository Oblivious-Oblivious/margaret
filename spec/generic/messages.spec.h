#ifndef __MESSAGES_SPEC_H_
#define __MESSAGES_SPEC_H_

#include "_helpers.h"

module(messages_spec, {
  it("parses unary messages", {
    parse(
      "42 factorial",
      vector_new(
        FM_INTEGER, string_new("42"), FM_UNARY, string_new("factorial")
      )
    );
    parse(
      "17 incr puts",
      vector_new(
        FM_INTEGER,
        string_new("17"),
        FM_UNARY,
        string_new("incr"),
        FM_UNARY,
        string_new("puts")
      )
    );
    parse(
      "23 one two three",
      vector_new(
        FM_INTEGER,
        string_new("23"),
        FM_UNARY,
        string_new("one"),
        FM_UNARY,
        string_new("two"),
        FM_UNARY,
        string_new("three")
      )
    );
    parse(
      "@inst one two three",
      vector_new(
        FM_INSTANCE,
        string_new("@inst"),
        FM_UNARY,
        string_new("one"),
        FM_UNARY,
        string_new("two"),
        FM_UNARY,
        string_new("three")
      )
    );
    parse(
      "42 puts",
      vector_new(FM_INTEGER, string_new("42"), FM_UNARY, string_new("puts"))
    );
    parse(
      "obj puts",
      vector_new(FM_LOCAL, string_new("obj"), FM_UNARY, string_new("puts"))
    );
    parse(
      "x = (obj puts)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("obj"),
        FM_UNARY,
        string_new("puts"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "(obj puts, 42 incr)",
      vector_new(
        FM_LOCAL,
        string_new("obj"),
        FM_UNARY,
        string_new("puts"),
        FM_INTEGER,
        string_new("42"),
        FM_UNARY,
        string_new("incr")
      )
    );
    parse(
      "((obj puts), (42 incr))",
      vector_new(
        FM_LOCAL,
        string_new("obj"),
        FM_UNARY,
        string_new("puts"),
        FM_INTEGER,
        string_new("42"),
        FM_UNARY,
        string_new("incr")
      )
    );
    parse(
      "42 incr incr decr decr",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_UNARY,
        string_new("incr"),
        FM_UNARY,
        string_new("incr"),
        FM_UNARY,
        string_new("decr"),
        FM_UNARY,
        string_new("decr")
      )
    );
    parse(
      "x = 42 incr incr decr decr",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("42"),
        FM_UNARY,
        string_new("incr"),
        FM_UNARY,
        string_new("incr"),
        FM_UNARY,
        string_new("decr"),
        FM_UNARY,
        string_new("decr"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x incr!",
      vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("incr!"))
    );
    parse(
      "x is_empty?",
      vector_new(FM_LOCAL, string_new("x"), FM_UNARY, string_new("is_empty?"))
    );
    parse(
      "(42 one, 43 two, 44 three, 45, 46 four)",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_UNARY,
        string_new("one"),
        FM_INTEGER,
        string_new("43"),
        FM_UNARY,
        string_new("two"),
        FM_INTEGER,
        string_new("44"),
        FM_UNARY,
        string_new("three"),
        FM_INTEGER,
        string_new("45"),
        FM_INTEGER,
        string_new("46"),
        FM_UNARY,
        string_new("four")
      )
    );
    parse(
      "p1 + p2 calc puts",
      vector_new(
        FM_LOCAL,
        string_new("p1"),
        FM_LOCAL,
        string_new("p2"),
        FM_UNARY,
        string_new("calc"),
        FM_UNARY,
        string_new("puts"),
        FM_BINARY,
        string_new("+")
      )
    );
    parse(
      "(p1 + p2 calc) puts",
      vector_new(
        FM_LOCAL,
        string_new("p1"),
        FM_LOCAL,
        string_new("p2"),
        FM_UNARY,
        string_new("calc"),
        FM_BINARY,
        string_new("+"),
        FM_UNARY,
        string_new("puts")
      )
    );
  });

  it("parses binary messages", {
    parse(
      "2 + 3",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_BINARY,
        string_new("+")
      )
    );
    parse(
      "2 + 3 + 4 + 5",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("4"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("5"),
        FM_BINARY,
        string_new("+")
      )
    );
    parse(
      "2 * 5",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("5"),
        FM_BINARY,
        string_new("*")
      )
    );
    parse(
      "a + b",
      vector_new(
        FM_LOCAL,
        string_new("a"),
        FM_LOCAL,
        string_new("b"),
        FM_BINARY,
        string_new("+")
      )
    );
    parse(
      "-5 - -3",
      vector_new(
        FM_INTEGER,
        string_new("5"),
        FM_LHS,
        string_new("-"),
        FM_INTEGER,
        string_new("3"),
        FM_LHS,
        string_new("-"),
        FM_BINARY,
        string_new("-")
      )
    );
    parse(
      "42 factorial + 17",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_UNARY,
        string_new("factorial"),
        FM_INTEGER,
        string_new("17"),
        FM_BINARY,
        string_new("+")
      )
    );
    parse(
      "41 factorial + 42 factorial + 43 factorial",
      vector_new(
        FM_INTEGER,
        string_new("41"),
        FM_UNARY,
        string_new("factorial"),
        FM_INTEGER,
        string_new("42"),
        FM_UNARY,
        string_new("factorial"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("43"),
        FM_UNARY,
        string_new("factorial"),
        FM_BINARY,
        string_new("+")
      )
    );
    parse(
      "(41 + 1, 42 + 0, 43 - 1)",
      vector_new(
        FM_INTEGER,
        string_new("41"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("0"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("43"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("-")
      )
    );
    parse(
      "((41 + 1), (42 + 0), (43 - 1))",
      vector_new(
        FM_INTEGER,
        string_new("41"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("0"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("43"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new("-")
      )
    );
    parse(
      "x = a + b * 2 - 5",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("a"),
        FM_LOCAL,
        string_new("b"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("*"),
        FM_INTEGER,
        string_new("5"),
        FM_BINARY,
        string_new("-"),
        FM_ASSIGNMENT
      )
    );
    parse(
      "x << item",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("item"),
        FM_BINARY,
        string_new("<<")
      )
    );
    parse(
      "x <<>>+-++-- 15",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("15"),
        FM_BINARY,
        string_new("<<>>+-++--")
      )
    );
    parse(
      "[1, 2, 3] ++ [4, 5]",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_TENSOR,
        string_new("3"),
        FM_INTEGER,
        string_new("4"),
        FM_INTEGER,
        string_new("5"),
        FM_TENSOR,
        string_new("2"),
        FM_BINARY,
        string_new("++")
      )
    );
    parse(
      "(4 + 3) * (5 + 6)",
      vector_new(
        FM_INTEGER,
        string_new("4"),
        FM_INTEGER,
        string_new("3"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("5"),
        FM_INTEGER,
        string_new("6"),
        FM_BINARY,
        string_new("+"),
        FM_BINARY,
        string_new("*")
      )
    );
  });

  it("parses keyword messages", {
    parse(
      "list put: 42 at: 5",
      vector_new(
        FM_LOCAL,
        string_new("list"),
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("5"),
        FM_KEYWORD,
        string_new("put:at:"),
        string_new("2")
      )
    );
    parse(
      "list put: (42 incr) at: 5",
      vector_new(
        FM_LOCAL,
        string_new("list"),
        FM_INTEGER,
        string_new("42"),
        FM_UNARY,
        string_new("incr"),
        FM_INTEGER,
        string_new("5"),
        FM_KEYWORD,
        string_new("put:at:"),
        string_new("2")
      )
    );
    parse(
      "( \
        list = List new, \
        list put: 42 at: 5, \
        x = list get: 2, \
        x puts \
      )",
      vector_new(
        FM_LOCAL,
        string_new("list"),
        FM_LOCAL,
        string_new("List"),
        FM_UNARY,
        string_new("new"),
        FM_ASSIGNMENT,
        FM_LOCAL,
        string_new("list"),
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("5"),
        FM_KEYWORD,
        string_new("put:at:"),
        string_new("2"),
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("list"),
        FM_INTEGER,
        string_new("2"),
        FM_KEYWORD,
        string_new("get:"),
        string_new("1"),
        FM_ASSIGNMENT,
        FM_LOCAL,
        string_new("x"),
        FM_UNARY,
        string_new("puts")
      )
    );
    parse(
      "2 + 3 incr add: 11",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("incr"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("11"),
        FM_KEYWORD,
        string_new("add:"),
        string_new("1")
      )
    );
    parse(
      "(1, 2, 3) reverse!: $true",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_TRUE,
        FM_KEYWORD,
        string_new("reverse!:"),
        string_new("1")
      )
    );
    parse(
      "$true then: 1 else: 2",
      vector_new(
        FM_TRUE,
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_KEYWORD,
        string_new("then:else:"),
        string_new("2")
      )
    );
    parse(
      "x ok?: $true otherwise!: $false",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_TRUE,
        FM_FALSE,
        FM_KEYWORD,
        string_new("ok?:otherwise!:"),
        string_new("2")
      )
    );
    parse(
      "(5 + 13) greater_than?: (11 + 2)",
      vector_new(
        FM_INTEGER,
        string_new("5"),
        FM_INTEGER,
        string_new("13"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("11"),
        FM_INTEGER,
        string_new("2"),
        FM_BINARY,
        string_new("+"),
        FM_KEYWORD,
        string_new("greater_than?:"),
        string_new("1")
      )
    );
    parse(
      "42 factorial and: (2 + 3)",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_UNARY,
        string_new("factorial"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_BINARY,
        string_new("+"),
        FM_KEYWORD,
        string_new("and:"),
        string_new("1")
      )
    );
    parse(
      "(list at: 3) + (list at: 5)",
      vector_new(
        FM_LOCAL,
        string_new("list"),
        FM_INTEGER,
        string_new("3"),
        FM_KEYWORD,
        string_new("at:"),
        string_new("1"),
        FM_LOCAL,
        string_new("list"),
        FM_INTEGER,
        string_new("5"),
        FM_KEYWORD,
        string_new("at:"),
        string_new("1"),
        FM_BINARY,
        string_new("+")
      )
    );
  });

  it("chains keyword messages of exactly the same selector", {
    parse(
      "arr add: 1 add: 2 add: 3",
      vector_new(
        FM_LOCAL,
        string_new("arr"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_KEYWORD,
        string_new("add:add:add:"),
        string_new("3")
      )
    );
    parse(
      "arr add: 'a' add: 'b' at: 3",
      vector_new(
        FM_LOCAL,
        string_new("arr"),
        FM_STRING,
        string_new("a"),
        FM_STRING,
        string_new("b"),
        FM_INTEGER,
        string_new("3"),
        FM_KEYWORD,
        string_new("add:add:at:"),
        string_new("3")
      )
    );
    parse(
      "arr add: 'a' at: 1 add: 'b' at: 2",
      vector_new(
        FM_LOCAL,
        string_new("arr"),
        FM_STRING,
        string_new("a"),
        FM_INTEGER,
        string_new("1"),
        FM_STRING,
        string_new("b"),
        FM_INTEGER,
        string_new("2"),
        FM_KEYWORD,
        string_new("add:at:add:at:"),
        string_new("4")
      )
    );
  });

  it("parses composit messages", {
    parse(
      "3 factorial + 4 factorial between: 10 and: 100",
      vector_new(
        FM_INTEGER,
        string_new("3"),
        FM_UNARY,
        string_new("factorial"),
        FM_INTEGER,
        string_new("4"),
        FM_UNARY,
        string_new("factorial"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("10"),
        FM_INTEGER,
        string_new("100"),
        FM_KEYWORD,
        string_new("between:and:"),
        string_new("2")
      )
    );
    parse(
      "( \
        origin <= point \
          if_true: { out goto } \
          if_false: { $false return }, \
        ::out \
      )",
      vector_new(
        FM_LOCAL,
        string_new("origin"),
        FM_LOCAL,
        string_new("point"),
        FM_BINARY,
        string_new("<="),
        FM_METHOD_START,
        FM_LOCAL,
        string_new("out"),
        FM_UNARY,
        string_new("goto"),
        FM_METHOD_END,
        FM_METHOD_START,
        FM_FALSE,
        FM_UNARY,
        string_new("return"),
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("if_true:if_false:"),
        string_new("2"),
        FM_LABEL_LOCAL,
        string_new("::out")
      )
    );
  });

  it("parses lhs messages", {
    parse("!$false", vector_new(FM_FALSE, FM_LHS, string_new("!")));
    parse(
      "-42 - 42",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_LHS,
        string_new("-"),
        FM_INTEGER,
        string_new("42"),
        FM_BINARY,
        string_new("-")
      )
    );
    parse(
      "-42 - - -41",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_LHS,
        string_new("-"),
        FM_INTEGER,
        string_new("41"),
        FM_LHS,
        string_new("-"),
        FM_LHS,
        string_new("-"),
        FM_BINARY,
        string_new("-")
      )
    );
    parse(
      "! + - !!42",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_LHS,
        string_new("!!"),
        FM_LHS,
        string_new("-"),
        FM_LHS,
        string_new("+"),
        FM_LHS,
        string_new("!")
      )
    );
    parse(
      "! + !!42 msg + 123 msg",
      vector_new(
        FM_INTEGER,
        string_new("42"),
        FM_LHS,
        string_new("!!"),
        FM_LHS,
        string_new("+"),
        FM_LHS,
        string_new("!"),
        FM_UNARY,
        string_new("msg"),
        FM_INTEGER,
        string_new("123"),
        FM_UNARY,
        string_new("msg"),
        FM_BINARY,
        string_new("+")
      )
    );
  });

  it("parses subscript messages", {
    parse(
      "arr[1]",
      vector_new(
        FM_LOCAL, string_new("arr"), FM_INTEGER, string_new("1"), FM_SUBSCRIPT
      )
    );
    parse(
      "arr[1, 2, 3]",
      vector_new(
        FM_LOCAL,
        string_new("arr"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_SUBSCRIPT
      )
    );
    parse(
      "arr[1, 2, 3][2]",
      vector_new(
        FM_LOCAL,
        string_new("arr"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_SUBSCRIPT,
        FM_INTEGER,
        string_new("2"),
        FM_SUBSCRIPT
      )
    );
    parse(
      "arr[1, 2, 3][2][1]",
      vector_new(
        FM_LOCAL,
        string_new("arr"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_SUBSCRIPT,
        FM_INTEGER,
        string_new("2"),
        FM_SUBSCRIPT,
        FM_INTEGER,
        string_new("1"),
        FM_SUBSCRIPT
      )
    );
    parse(
      "x = keyword: !arr[0][0] msg + 42",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_LOCAL,
        string_new("arr"),
        FM_INTEGER,
        string_new("0"),
        FM_SUBSCRIPT,
        FM_INTEGER,
        string_new("0"),
        FM_SUBSCRIPT,
        FM_LHS,
        string_new("!"),
        FM_UNARY,
        string_new("msg"),
        FM_INTEGER,
        string_new("42"),
        FM_BINARY,
        string_new("+"),
        FM_KEYWORD,
        string_new("keyword:"),
        string_new("1"),
        FM_ASSIGNMENT
      )
    );
  });

  it("parses unicode messages", {
    parse("√x", vector_new(FM_LOCAL, string_new("x"), FM_LHS, string_new("√")));
    parse("∛x", vector_new(FM_LOCAL, string_new("x"), FM_LHS, string_new("∛")));
    parse("∜x", vector_new(FM_LOCAL, string_new("x"), FM_LHS, string_new("∜")));
    parse(
      "[1, 2, 3] ∀ {x > 1}",
      vector_new(
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_TENSOR,
        string_new("3"),
        FM_METHOD_START,
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("1"),
        FM_BINARY,
        string_new(">"),
        FM_METHOD_END,
        FM_BINARY,
        string_new("∀")
      )
    );
    parse(
      "arr ∃ {x > 0}",
      vector_new(
        FM_LOCAL,
        string_new("arr"),
        FM_METHOD_START,
        FM_LOCAL,
        string_new("x"),
        FM_INTEGER,
        string_new("0"),
        FM_BINARY,
        string_new(">"),
        FM_METHOD_END,
        FM_BINARY,
        string_new("∃")
      )
    );
    parse(
      "%[2, 3, 5] ∈ %[3, 5]",
      vector_new(
        FM_INTEGER,
        string_new("2"),
        FM_INTEGER,
        string_new("3"),
        FM_INTEGER,
        string_new("5"),
        FM_TUPLE,
        string_new("3"),
        FM_INTEGER,
        string_new("3"),
        FM_INTEGER,
        string_new("5"),
        FM_TUPLE,
        string_new("2"),
        FM_BINARY,
        string_new("∈")
      )
    );
  });
})

#endif
