#ifndef __ERRORS_SPEC_H_
#define __ERRORS_SPEC_H_

#include "_helpers.h"

module(errors_spec, {
  it("enumerable literal errors", {
    error("(", "missing closing parenthesis on group.");
    error(")", "missing opening parenthesis on group.");
    error("(()", "missing closing parenthesis on group.");
    error("())", "reached end of program.");
    error("[", "missing closing bracket on tensor.");
    error("]", "missing opening bracket on tensor.");
    error("{", "missing closing curly brace on hash.");
    error("}", "missing opening curly brace on hash.");
  });

  it(
    "other syntax errors",
    {
      // TODO -
    }
  );
})

#endif
