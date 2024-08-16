#ifndef __TOKEN_TABLE_SPEC_H_
#define __TOKEN_TABLE_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/tokens/TokenTable.h"

static VM *vm;
static void token_table_spec_setup(void) {
  vm = vm_new("file1.marg");
  vector_add(vm->tokens, token_new(string_new("a"), TOKEN_IDENTIFIER));
  vector_add(vm->tokens, token_new(string_new("+"), TOKEN_MESSAGE_SYMBOL));
  vector_add(vm->tokens, token_new(string_new("2"), TOKEN_INTEGER));
  vector_add(vm->tokens, token_new(string_new("eof"), TOKEN_EOF));
}

module(TokenTableSpec, {
  before_each(&token_table_spec_setup);

  it("is not nil", { assert_that(vm->tokens isnot NULL); });

  it("counts 4 elements in the list", {
    assert_that_int(vector_size(vm->tokens) equals to 4);
  });

  it("peeks a token at the current position on the array", {
    assert_that_charptr(vm->tokens[0]->value equals to "a");
    assert_that_charptr(vm->tokens[1]->value equals to "+");
    assert_that_charptr(vm->tokens[2]->value equals to "2");
    assert_that_charptr(vm->tokens[3]->value equals to "eof");
  });

  it("consumes a token and returns the value", {
    assert_that_charptr(token_table_consume(vm)->value equals to "a");
    assert_that_charptr(token_table_consume(vm)->value equals to "+");
    assert_that_charptr(token_table_consume(vm)->value equals to "2");
    assert_that_charptr(token_table_consume(vm)->value equals to "eof");

    assert_that_charptr(token_table_consume(vm)->value equals to "eof");
    assert_that_charptr(token_table_consume(vm)->value equals to "eof");
  });

  it("gets a list element by index", {
    assert_that_charptr(vm->tokens[1]->value equals to "+");
    assert_that_charptr(vm->tokens[0]->value equals to "a");
    assert_that_charptr(vm->tokens[3]->value equals to "eof");
    assert_that_charptr(vm->tokens[2]->value equals to "2");
  });

  it("ensures it consumes a specific value", {
    assert_that_charptr(token_table_ensure_value(vm, "a", "") equals to "a");
    assert_that_charptr(token_table_ensure_value(vm, "+", "") equals to "+");
    assert_that_charptr(token_table_ensure_value(vm, "2", "") equals to "2");
    assert_that_charptr(token_table_ensure_value(vm, "eof", "") equals to "eof"
    );
  });

  it("ensures it consumes of a specific token type", {
    assert_that_charptr(token_table_ensure_type(vm, TOKEN_IDENTIFIER, "")
                          equals to "a");
    assert_that_charptr(token_table_ensure_type(vm, TOKEN_MESSAGE_SYMBOL, "")
                          equals to "+");
    assert_that_charptr(token_table_ensure_type(vm, TOKEN_INTEGER, "") equals to
                        "2");
    assert_that_charptr(token_table_ensure_type(vm, TOKEN_EOF, "") equals to
                        "eof");
  });
})

#endif
