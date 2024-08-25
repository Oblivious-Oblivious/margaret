#ifndef __PARSER_SPEC_H_
#define __PARSER_SPEC_H_

#include "../generic/_helpers.h"
#include "syntax/first_unit.module.spec.h"

static VM *vm;
static void token_table_spec_setup(void) {
  vm = vm_new("file1.marg");
  vector_add(vm->tokens, token_new(string_new("a"), TOKEN_IDENTIFIER, 1, 0));
  vector_add(
    vm->tokens, token_new(string_new("+"), TOKEN_MESSAGE_SYMBOL, 1, 0)
  );
  vector_add(vm->tokens, token_new(string_new("2"), TOKEN_INTEGER, 1, 0));
  vector_add(vm->tokens, token_new(string_new("eof"), TOKEN_EOF, 1, 0));
}

module(ParserSpec, {
  describe("Token Table", {
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
      assert_that_charptr(parser_ensure_value(vm, "a", "") equals to "a");
      assert_that_charptr(parser_ensure_value(vm, "+", "") equals to "+");
      assert_that_charptr(parser_ensure_value(vm, "2", "") equals to "2");
      assert_that_charptr(parser_ensure_value(vm, "eof", "") equals to "eof");

      assert_that_charptr(parser_ensure_value(vm, "eof", "") equals to "eof");
      assert_that_charptr(parser_ensure_value(vm, "eof", "") equals to "eof");
    });

    it("gets a list element by index", {
      assert_that_charptr(vm->tokens[1]->value equals to "+");
      assert_that_charptr(vm->tokens[0]->value equals to "a");
      assert_that_charptr(vm->tokens[3]->value equals to "eof");
      assert_that_charptr(vm->tokens[2]->value equals to "2");
    });

    it("ensures it consumes a specific value", {
      assert_that_charptr(parser_ensure_value(vm, "a", "") equals to "a");
      assert_that_charptr(parser_ensure_value(vm, "+", "") equals to "+");
      assert_that_charptr(parser_ensure_value(vm, "2", "") equals to "2");
      assert_that_charptr(parser_ensure_value(vm, "eof", "") equals to "eof");
    });

    it("ensures it consumes of a specific token type", {
      assert_that_charptr(parser_ensure_type(vm, TOKEN_IDENTIFIER, "") equals to
                          "a");
      assert_that_charptr(parser_ensure_type(vm, TOKEN_MESSAGE_SYMBOL, "")
                            equals to "+");
      assert_that_charptr(parser_ensure_type(vm, TOKEN_INTEGER, "") equals to
                          "2");
      assert_that_charptr(parser_ensure_type(vm, TOKEN_EOF, "") equals to "eof"
      );
    });

    it("peeks on top of the token table", {
      Token **tokens = vm->tokens;
      assert_that_size_t(vector_size(tokens) equals to 4);
      assert_that_charptr(tokens[1]->value equals to "+");
      assert_that_charptr(tokens[2]->value equals to "2");
      assert_that_charptr(tokens[0]->value equals to "a");
      assert_that_charptr(tokens[3]->value equals to "eof");
      assert_that_size_t(vector_size(tokens) equals to 4);
    });
  });

  describe("Lexxed Token Table", {
    it("traverses through the token table", {
      VM *vm2     = vm_new("file1.marg");
      vm2->source = string_new("(42 factorial)");
      lexer_make_tokens(vm2);
      assert_that_size_t(vector_size(vm2->tokens) equals to 5);
      assert_that_charptr(parser_ensure_value(vm2, "(", "") equals to "(");
      assert_that_charptr(parser_ensure_value(vm2, "42", "") equals to "42");
      assert_that_charptr(parser_ensure_value(vm2, "factorial", "") equals to
                          "factorial");
      assert_that_charptr(parser_ensure_value(vm2, ")", "") equals to ")");
      assert_that_size_t(vector_size(vm2->tokens) equals to 1);
      assert_that_charptr(parser_ensure_value(vm2, "eof", "") equals to "eof");
      assert_that_size_t(vector_size(vm2->tokens) equals to 0);
      assert_that_charptr(parser_ensure_value(vm2, "eof", "") equals to "eof");
      assert_that_charptr(parser_ensure_value(vm2, "eof", "") equals to "eof");
      assert_that_charptr(parser_ensure_value(vm2, "eof", "") equals to "eof");
      assert_that_size_t(vector_size(vm2->tokens) equals to 0);
    });
  });

  first_unit();
})

#endif
