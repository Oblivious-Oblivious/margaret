#ifndef __TYPE_SPEC_H_
#define __TYPE_SPEC_H_

#include "../../src/tokens/Type.h"
#include "../cSpec.h"

module(TypeSpec, {
  it("contains an EOF syntax symbol", {
    assert_that_int(TOKEN_EOF equals to 0);
  });

  it("contains message normal and syntax symbols", {
    assert_that_int(TOKEN_MESSAGE_SYMBOL equals to 1);
    assert_that_int(TOKEN_ID_SYMBOL equals to 2);
    assert_that_int(TOKEN_SYNTAX_SYMBOL equals to 3);
  });

  it("contains all terminal literal types", {
    assert_that_int(TOKEN_INTEGER equals to 11);
    assert_that_int(TOKEN_FLOAT equals to 12);

    assert_that_int(TOKEN_STRING equals to 111);
  });

  it("contains non terminal literal types", {
    assert_that_int(TOKEN_IDENTIFIER equals to 201);
  });
})

#endif
