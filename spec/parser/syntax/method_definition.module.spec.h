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
        FM_METHOD_NAME,
        string_new("!_LHS"),
        FM_SELF,
        FM_METHOD_END
      )
    );

    parse(
      "# fact => 0",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_NAME,
        string_new("fact_UNARY"),
        FM_INTEGER,
        string_new("0"),
        FM_METHOD_END
      )
    );

    parse(
      "#add: element at: position => 42",
      vector_new(
        FM_METHOD_START,
        FM_METHOD_ARGUMENT,
        string_new("element"),
        FM_METHOD_ARGUMENT,
        string_new("position"),
        FM_METHOD_NAME,
        string_new("add:at:_KEYWORD"),
        FM_INTEGER,
        string_new("42"),
        FM_METHOD_END
      )
    );
  });

  method_body();
  keyword_list();
})

#endif
