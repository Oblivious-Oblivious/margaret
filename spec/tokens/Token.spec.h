#ifndef __TOKEN_SPEC_H_
#define __TOKEN_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/tokens/Tokens.h"

module(TokenSpec, {
  it("has a type and a value", {
    Tokens tok;
    tokens_init(&tok);
    tokens_add(&tok, string_new("42"), TOKEN_INTEGER, 1, 0);
    assert_that_charptr(tok.values[0] equals to "42");
    assert_that_int(tok.types[0] equals to TOKEN_INTEGER);
    assert_that_int(tok.linenos[0] equals to 1);
    assert_that_int(tok.charnos[0] equals to 0);
  });

  it("has an equals message for values", {
    Tokens tok;
    tokens_init(&tok);
    tokens_add(&tok, string_new("hello"), TOKEN_STRING, 1, 0);
    assert_that(string_equals(tok.values[0], "hello"));
    assert_that_int(tok.linenos[0] equals to 1);
    assert_that_int(tok.charnos[0] equals to 0);
  });
})

#endif
