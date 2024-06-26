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
  });

  it("contains message normal and syntax symbols", {
    assert_that_int(TOKEN_MESSAGE_SYMBOL equals to 1001);
    assert_that_int(TOKEN_SYNTAX_SYMBOL equals to 1002);
  });
})

#endif
