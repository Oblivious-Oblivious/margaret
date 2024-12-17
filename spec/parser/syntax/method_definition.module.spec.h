#ifndef __METHOD_DEFINITION_MODULE_SPEC_H_
#define __METHOD_DEFINITION_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "keyword_list.module.spec.h"
#include "method_body.module.spec.h"

module(method_definition, {
  it("parses method definitions", {
    parse(
      "# ! => @self",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_RECEIVER,
        FM_METHOD_ANY_OBJECT,
        FM_METHOD_NAME,
        string_new("!"),
        FM_SELF,
        FM_METHOD_END
      )
    );

    parse(
      "# $false ! => $true",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_RECEIVER,
        FM_FALSE,
        FM_METHOD_NAME,
        string_new("!"),
        FM_TRUE,
        FM_METHOD_END
      )
    );

    parse(
      "# fact => 0",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_RECEIVER,
        FM_METHOD_ANY_OBJECT,
        FM_METHOD_NAME,
        string_new("fact"),
        FM_INTEGER,
        string_new("0"),
        FM_METHOD_END
      )
    );

    parse(
      "# 0 fact => 1",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_RECEIVER,
        FM_INTEGER,
        string_new("0"),
        FM_METHOD_NAME,
        string_new("fact"),
        FM_INTEGER,
        string_new("1"),
        FM_METHOD_END
      )
    );

    parse(
      "# ** 0 => 1",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_RECEIVER,
        FM_METHOD_ANY_OBJECT,
        FM_INTEGER,
        string_new("0"),
        FM_METHOD_PARAMETER,
        FM_METHOD_NAME,
        string_new("**"),
        FM_INTEGER,
        string_new("1"),
        FM_METHOD_END
      )
    );

    parse(
      "# 0 ** 0 => $nil",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_RECEIVER,
        FM_INTEGER,
        string_new("0"),
        FM_INTEGER,
        string_new("0"),
        FM_METHOD_PARAMETER,
        FM_METHOD_NAME,
        string_new("**"),
        FM_NIL,
        FM_METHOD_END
      )
    );

    parse(
      "#add: element at: position => 42",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_RECEIVER,
        FM_METHOD_ANY_OBJECT,
        FM_LOCAL,
        string_new("element"),
        FM_METHOD_PARAMETER,
        FM_LOCAL,
        string_new("position"),
        FM_METHOD_PARAMETER,
        FM_METHOD_NAME,
        string_new("add:at:"),
        FM_INTEGER,
        string_new("42"),
        FM_METHOD_END
      )
    );

    parse(
      "#%{} add: 42 at: 'a' => $true",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_RECEIVER,
        FM_TABLE,
        string_new("0"),
        FM_INTEGER,
        string_new("42"),
        FM_METHOD_PARAMETER,
        FM_STRING,
        string_new("a"),
        FM_METHOD_PARAMETER,
        FM_METHOD_NAME,
        string_new("add:at:"),
        FM_TRUE,
        FM_METHOD_END
      )
    );
  });

  method_body();
  keyword_list();
})

#endif
