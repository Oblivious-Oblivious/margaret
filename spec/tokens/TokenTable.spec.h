#ifndef __TOKEN_TABLE_SPEC_H_
#define __TOKEN_TABLE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/tokens/TokenTable.h"

static Token **t;
static void token_table_spec_setup(void) {
  t = NULL;
  vector_add(
    t, token_new(string_new("a"), TOKEN_IDENTIFIER, 1, 1, "file1.marg")
  );
  vector_add(
    t, token_new(string_new("+"), TOKEN_MESSAGE_SYMBOL, 1, 1, "file1.marg")
  );
  vector_add(t, token_new(string_new("2"), TOKEN_INTEGER, 1, 1, "file1.marg"));
  vector_add(t, token_new(string_new("eof"), TOKEN_EOF, 1, 1, "file1.marg"));
}

module(TokenTableSpec, {
  before_each(&token_table_spec_setup);

  it("is not nil", { assert_that(t isnot NULL); });

  it("counts 4 elements in the list", {
    assert_that_int(vector_size(t) equals to 4);
  });

  it("peeks a token at the current position on the array", {
    assert_that_charptr(t[0]->value equals to "a");
    assert_that_charptr(t[1]->value equals to "+");
    assert_that_charptr(t[2]->value equals to "2");
    assert_that_charptr(t[3]->value equals to "eof");
  });

  it("consumes a token and returns the value", {
    assert_that_charptr(token_table_consume(t)->value equals to "a");
    assert_that_charptr(token_table_consume(t)->value equals to "+");
    assert_that_charptr(token_table_consume(t)->value equals to "2");
    assert_that_charptr(token_table_consume(t)->value equals to "eof");

    assert_that_charptr(token_table_consume(t)->value equals to "eof");
    assert_that_charptr(token_table_consume(t)->value equals to "eof");
  });

  it("gets a list element by index", {
    assert_that_charptr(t[1]->value equals to "+");
    assert_that_charptr(t[0]->value equals to "a");
    assert_that_charptr(t[3]->value equals to "eof");
    assert_that_charptr(t[2]->value equals to "2");
  });

  it("ensures it consumes a specific value", {
    assert_that_charptr(token_table_ensure_value(t, "a", "") equals to "a");
    assert_that_charptr(token_table_ensure_value(t, "+", "") equals to "+");
    assert_that_charptr(token_table_ensure_value(t, "2", "") equals to "2");
    assert_that_charptr(token_table_ensure_value(t, "eof", "") equals to "eof");
  });

  it("ensures it consumes of a specific token type", {
    assert_that_charptr(token_table_ensure_type(t, TOKEN_IDENTIFIER, "")
                          equals to "a");
    assert_that_charptr(token_table_ensure_type(t, TOKEN_MESSAGE_SYMBOL, "")
                          equals to "+");
    assert_that_charptr(token_table_ensure_type(t, TOKEN_INTEGER, "") equals to
                        "2");
    assert_that_charptr(token_table_ensure_type(t, TOKEN_EOF, "") equals to
                        "eof");
  });
})

#endif
