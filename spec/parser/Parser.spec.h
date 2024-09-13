#ifndef __PARSER_SPEC_H_
#define __PARSER_SPEC_H_

#include "../generic/_helpers.h"
#include "syntax/first_unit.module.spec.h"

static VM *vm;
static void token_table_spec_setup(void) {
  vm = vm_new("file1.marg");
  tokens_add(&vm->tokens, string_new("a"), TOKEN_IDENTIFIER, 1, 0);
  tokens_add(&vm->tokens, string_new("+"), TOKEN_MESSAGE_SYMBOL, 1, 0);
  tokens_add(&vm->tokens, string_new("2"), TOKEN_INTEGER, 1, 0);
  tokens_add(&vm->tokens, string_new(NULL), TOKEN_EOF, 1, 0);
}

module(ParserSpec, {
  describe("Token Table", {
    before_each(&token_table_spec_setup);

    it("is not nil", { assert_that(&vm->tokens isnot NULL); });

    it("counts 4 elements in the list", {
      assert_that_int(vector_size(vm->tokens.values) equals to 4);
      assert_that_int(vector_size(vm->tokens.types) equals to 4);
      assert_that_int(vector_size(vm->tokens.linenos) equals to 4);
      assert_that_int(vector_size(vm->tokens.charnos) equals to 4);
    });

    it("peeks a token at the current position on the array", {
      assert_that_charptr(vm->tokens.values[0] equals to "a");
      assert_that_charptr(vm->tokens.values[1] equals to "+");
      assert_that_charptr(vm->tokens.values[2] equals to "2");
      assert_that(vm->tokens.values[3] is NULL);
    });

    it("consumes a token and returns the value", {
      assert_that_charptr(parser_consume(vm, TOKEN_IDENTIFIER, "") equals to "a"
      );
      assert_that_charptr(parser_consume(vm, TOKEN_MESSAGE_SYMBOL, "") equals to
                          "+");
      assert_that_charptr(parser_consume(vm, TOKEN_INTEGER, "") equals to "2");
      assert_that(parser_consume(vm, TOKEN_EOF, "") is NULL);

      assert_that(parser_consume(vm, TOKEN_EOF, "") is NULL);
      assert_that(parser_consume(vm, TOKEN_EOF, "") is NULL);
    });

    it("gets a list element by index", {
      assert_that_charptr(vm->tokens.values[1] equals to "+");
      assert_that_charptr(vm->tokens.values[0] equals to "a");
      assert_that(vm->tokens.values[3] is NULL);
      assert_that_charptr(vm->tokens.values[2] equals to "2");
    });

    it("ensures it consumes a specific value", {
      assert_that_charptr(parser_consume(vm, TOKEN_IDENTIFIER, "") equals to "a"
      );
      assert_that_charptr(parser_consume(vm, TOKEN_MESSAGE_SYMBOL, "") equals to
                          "+");
      assert_that_charptr(parser_consume(vm, TOKEN_INTEGER, "") equals to "2");
      assert_that(parser_consume(vm, TOKEN_EOF, "") is NULL);
    });

    it("ensures it consumes of a specific token type", {
      assert_that_charptr(parser_consume(vm, TOKEN_IDENTIFIER, "") equals to "a"
      );
      assert_that_charptr(parser_consume(vm, TOKEN_MESSAGE_SYMBOL, "") equals to
                          "+");
      assert_that_charptr(parser_consume(vm, TOKEN_INTEGER, "") equals to "2");
      assert_that(parser_consume(vm, TOKEN_EOF, "") is NULL);
    });

    it("peeks on top of the token table", {
      assert_that_size_t(vector_size(vm->tokens.values) equals to 4);
      assert_that_charptr(vm->tokens.values[1] equals to "+");
      assert_that_charptr(vm->tokens.values[2] equals to "2");
      assert_that_charptr(vm->tokens.values[0] equals to "a");
      assert_that(vm->tokens.values[3] is NULL);
      assert_that_size_t(vector_size(vm->tokens.values) equals to 4);
    });
  });

  describe("Lexxed Token Table", {
    it("traverses through the token table", {
      VM *vm2     = vm_new("file1.marg");
      vm2->source = string_new("(42 factorial)");
      lexer_make_tokens(vm2);
      assert_that_size_t(vector_size(vm2->tokens.values) equals to 5);
      assert_that_size_t(vm2->tid equals to 0);
      assert_that_charptr(parser_consume(vm2, TOKEN_LPAREN, "") equals to "(");
      assert_that_charptr(parser_consume(vm2, TOKEN_INTEGER, "") equals to "42"
      );
      assert_that_charptr(parser_consume(vm2, TOKEN_IDENTIFIER, "") equals to
                          "factorial");
      assert_that_charptr(parser_consume(vm2, TOKEN_RPAREN, "") equals to ")");
      assert_that_size_t(vector_size(vm2->tokens.values) equals to 5);
      assert_that_size_t(vm2->tid equals to 4);
      assert_that(parser_consume(vm2, TOKEN_EOF, "") is NULL);
      assert_that_size_t(vector_size(vm2->tokens.values) equals to 5);
      assert_that_size_t(vm2->tid equals to 5);
      assert_that(parser_consume(vm2, TOKEN_EOF, "") is NULL);
      assert_that(parser_consume(vm2, TOKEN_EOF, "") is NULL);
      assert_that(parser_consume(vm2, TOKEN_EOF, "") is NULL);
      assert_that_size_t(vector_size(vm2->tokens.values) equals to 5);
      assert_that_size_t(vm2->tid equals to 5);
    });
  });

  first_unit();
})

#endif
