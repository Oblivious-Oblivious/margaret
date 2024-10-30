#ifndef __ASSIGNMENT_MESSAGE_MODULE_SPEC_H_
#define __ASSIGNMENT_MESSAGE_MODULE_SPEC_H_

#include "../../generic/_helpers.h"
#include "keyword_message.module.spec.h"

module(assignment_message, {
  it("parses assignments", {
    parse(
      "x = 4",
      vector_new(
        FM_LOCAL, string_new("x"), FM_INTEGER, string_new("4"), FM_ASSIGNMENT
      )
    );

    parse(
      "x = y = z = 6",
      vector_new(
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("y"),
        FM_LOCAL,
        string_new("z"),
        FM_INTEGER,
        string_new("6"),
        FM_ASSIGNMENT,
        FM_ASSIGNMENT,
        FM_ASSIGNMENT
      )
    );
  });

  keyword_message();
})

#endif
