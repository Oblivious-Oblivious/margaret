#ifndef __METHOD_DEFINITION_MODULE_SPEC_H_
#define __METHOD_DEFINITION_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "keyword_list.module.spec.h"

module(method_definition, {
  it("parses method definitions", {
    it("parses method definitions", {
      parse(
        "# 0 fact => 1",
        vector_new(
          FM_START_UNARY_METHOD,
          FM_METHOD_RECEIVER,
          FM_INTEGER,
          string_new("0"),
          string_new("fact"),
          FM_INTEGER,
          string_new("1"),
          FM_END_UNARY_METHOD
        )
      );

      parse(
        "# 0 ** 0 => $nil",
        vector_new(
          FM_START_BINARY_METHOD,
          FM_METHOD_RECEIVER,
          FM_INTEGER,
          string_new("0"),
          string_new("**"),
          FM_METHOD_PARAMETER,
          string_new("0"),
          FM_NIL,
          FM_END_BINARY_METHOD
        )
      );

      parse(
        "#add: element at: position => 42",
        vector_new(
          FM_START_KEYWORD_METHOD,
          FM_METHOD_RECEIVER,
          FM_METHOD_ANY_OBJECT,
          string_new("add:at:"),
          FM_METHOD_PARAMETER,
          string_new("element"),
          FM_METHOD_PARAMETER,
          string_new("position"),
          FM_INTEGER,
          string_new("42"),
          FM_END_KEYWORD_METHOD
        )
      );
    });
  });

  keyword_list();
})

#endif
