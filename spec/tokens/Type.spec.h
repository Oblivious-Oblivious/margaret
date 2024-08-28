#ifndef __TYPE_SPEC_H_
#define __TYPE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../src/tokens/Type.h"

module(TypeSpec, {
  it("contains an EOF syntax symbol", {
    assert_that_int(TOKEN_EOF equals to 0);
  });

  it("contains whitespace symbols", {
    assert_that_int(TOKEN_NEWLINE equals to 1);
    assert_that_int(TOKEN_WHITESPACE equals to 2);
  });

  it("contains all terminal literal types", {
    assert_that_int(TOKEN_FLOAT equals to 11);
    assert_that_int(TOKEN_INTEGER equals to 12);
    assert_that_int(TOKEN_STRING equals to 111);
  });

  it("contains non terminal literal types", {
    assert_that_int(TOKEN_IDENTIFIER equals to 201);
    assert_that_int(TOKEN_INSTANCE equals to 202);
    assert_that_int(TOKEN_GLOBAL equals to 203);
  });

  it("contains message normal and syntax symbols", {
    assert_that_int(TOKEN_MESSAGE_SYMBOL equals to 1001);
    assert_that_int(TOKEN_SYNTAX_SYMBOL equals to 1002);
    assert_that_int(TOKEN_LPAREN equals to 1003);
    assert_that_int(TOKEN_RPAREN equals to 1004);
    assert_that_int(TOKEN_LBRACKET equals to 1005);
    assert_that_int(TOKEN_RBRACKET equals to 1006);
    assert_that_int(TOKEN_LCURLY equals to 1007);
    assert_that_int(TOKEN_RCURLY equals to 1008);
    assert_that_int(TOKEN_COMMA equals to 1009);
    assert_that_int(TOKEN_COLON equals to 1010);
    assert_that_int(TOKEN_HASH equals to 1011);
    assert_that_int(TOKEN_PERCENT equals to 1012);
  });

  it("contains special tokens that affect syntax", {
    assert_that_int(TOKEN_ROCKET equals to 2001);
  });
})

#endif
