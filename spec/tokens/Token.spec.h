#ifndef __TOKEN_SPEC_H_
#define __TOKEN_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/tokens/Token.h"

module(TokenSpec, {
  it("has a type and a value", {
    Token *tok = token_new(string_new("42"), TOKEN_INTEGER);
    assert_that_charptr(tok->value equals to "42");
    assert_that_int(tok->type equals to TOKEN_INTEGER);
  });

  it("has an equals message for values", {
    Token *tok = token_new(string_new("hello"), TOKEN_STRING);
    assert_that(token_equals_values(tok, string_new("hello")));
  });
})

#endif
