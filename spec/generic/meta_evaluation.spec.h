#ifndef __META_EVALUATION_SPEC_H_
#define __META_EVALUATION_SPEC_H_

#include "_helpers.h"

module(meta_evaluation_spec, {
  it("compiles and calls messages dynamically", {
    parse(
      "send: \"msg\" to: $IntegerClone",
      vector_new(
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_STRING,
        string_new("msg"),
        FM_GLOBAL,
        string_new("$IntegerClone"),
        FM_KEYWORD,
        string_new("send:to:"),
        string_new("2")
      )
    );
  });

  it("parses metaclass messages", {
    parse(
      "(x = String name)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("name"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String category)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("category"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String description)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("description"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String kind_of_subclass)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("kind_of_subclass"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String definition)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("definition"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String field_names)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("field_names"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String all_field_names)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("all_field_names"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String selectors)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("selectors"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String source_code_at: \"message\")",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_STRING,
        string_new("message"),
        FM_KEYWORD,
        string_new("source_code_at:"),
        string_new("1"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String all_instances)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("all_instances"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String superclass)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("superclass"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String all_superclasses)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("all_superclasses"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String subclasses)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("subclasses"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String all_subclasses)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("all_subclasses"),
        FM_BINARY,
        string_new("=")
      )
    );
    parse(
      "(x = String number_of_instances)",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("String"),
        FM_UNARY,
        string_new("number_of_instances"),
        FM_BINARY,
        string_new("=")
      )
    );
  });
})

#endif
