#ifndef __TOKEN_SPEC_H_
#define __TOKEN_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/tokens/Token.h"

module(TokenSpec, {
  it("has a type and a value", {
    Token *tok =
      token_new(string_new("42"), TOKEN_INTEGER, 125, 0, "file1.marg");
    assert_that_charptr(tok->value equals to "42");
    assert_that_int(tok->type equals to TOKEN_INTEGER);
    assert_that_int(tok->line_number equals to 125);
    assert_that_charptr(tok->filename equals to "file1.marg");
  });

  it("has an equals message for values", {
    Token *tok =
      token_new(string_new("hello"), TOKEN_STRING, 10, 0, "file2.marg");
    assert_that(token_equals_values(tok, string_new("hello")));
  });
})

#endif
