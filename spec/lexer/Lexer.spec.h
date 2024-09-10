#ifndef __LEXER_SPEC_H_
#define __LEXER_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/lexer/Lexer.h"
#include "../../src/loader/Loader.h"

module(LexerSpec, {
  describe("Lexer", {
    it("contains the input text, lexer position and current character", {
      VM *vm = vm_new("file.marg");
      assert_that_charptr(vm->filename equals to "file.marg");
      assert_that_int(vm->lineno equals to 1);
    });

    context("on #make_tokens", {
      it("correctly counts the number of lines", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(42 factorial\nx = 2 + 3\ny = 5)");
        lexer_make_tokens(vm);
        assert_that_int(vm->lineno equals to 3);
      });

      it("tokenizes symbols", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(% ^ & *)");
        lexer_make_tokens(vm);
        Token **tokens = vm->tokens;
        assert_that_int(vector_size(tokens) equals to 7);
        assert_that_charptr(tokens[1]->value equals to "%");
      });

      it("tokenizes integers", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(42 msg)");
        lexer_make_tokens(vm);
        Token **tokens = vm->tokens;
        assert_that_charptr(tokens[1]->value equals to "42");
        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(vm->lineno equals to 1);

        vm         = vm_new("file.marg");
        vm->source = string_new("4_200");
        lexer_make_tokens(vm);
        tokens = vm->tokens;
        assert_that_charptr(tokens[0]->value equals to "4200");
        vm         = vm_new("file.marg");
        vm->source = string_new("4_2_0_0");
        lexer_make_tokens(vm);
        tokens = vm->tokens;
        assert_that_charptr(tokens[0]->value equals to "4200");
      });

      it("tokenizes zero", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(0 is_zero?)");
        lexer_make_tokens(vm);
        Token **tokens = vm->tokens;

        assert_that_charptr(tokens[1]->value equals to "0");
        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(vm->lineno equals to 1);
      });

      it("correctly parses code that the parser will drop later", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("042 msg");
        lexer_make_tokens(vm);
        Token **table = vm->tokens;
        assert_that_charptr(table[0]->value equals to "0");
        assert_that_charptr(table[1]->value equals to "42");
        assert_that_charptr(table[2]->value equals to "msg");
        assert_that_charptr(table[3]->value equals to "eof");
      });

      it("tokenizes floats", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("0.0");
        lexer_make_tokens(vm);
        Token **tokens = vm->tokens;
        assert_that_charptr(tokens[0]->value equals to "0.0");
        assert_that_int(tokens[0]->type equals to TOKEN_FLOAT);
        assert_that_int(vm->lineno equals to 1);

        vm         = vm_new("file.marg");
        vm->source = string_new("(42.7 msg)");
        lexer_make_tokens(vm);
        tokens = vm->tokens;
        assert_that_charptr(tokens[1]->value equals to "42.7");
        assert_that_int(tokens[1]->type equals to TOKEN_FLOAT);
        assert_that_int(vm->lineno equals to 1);

        vm         = vm_new("file.marg");
        vm->source = string_new("(0.7 msg)");
        lexer_make_tokens(vm);
        tokens = vm->tokens;
        assert_that_charptr(tokens[1]->value equals to "0.7");
        assert_that_int(tokens[1]->type equals to TOKEN_FLOAT);
        assert_that_int(vm->lineno equals to 1);

        vm         = vm_new("file.marg");
        vm->source = string_new("(0.7+0.5+0.23)");
        lexer_make_tokens(vm);
        tokens = vm->tokens;
        assert_that_charptr(tokens[1]->value equals to "0.7");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "0.5");
        assert_that_charptr(tokens[4]->value equals to "+");
        assert_that_charptr(tokens[5]->value equals to "0.23");

        vm         = vm_new("file.marg");
        vm->source = string_new("(.7 msg)");
        lexer_make_tokens(vm);
        tokens = vm->tokens;
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to ".");
        assert_that_charptr(tokens[2]->value equals to "7");
        assert_that_charptr(tokens[3]->value equals to "msg");
        assert_that_charptr(tokens[4]->value equals to ")");

        vm         = vm_new("file.marg");
        vm->source = string_new("(124.0 msg)");
        lexer_make_tokens(vm);
        tokens = vm->tokens;
        assert_that_charptr(tokens[1]->value equals to "124.0");
        assert_that_charptr(tokens[2]->value equals to "msg");
      });

      it("tokenizes binary literals", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(0b1010 + 0B0100)");
        lexer_make_tokens(vm);
        Token **tokens = vm->tokens;
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to "10");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "4");
        assert_that_charptr(tokens[4]->value equals to ")");

        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[3]->type equals to TOKEN_INTEGER);
      });

      it("tokenizes hexadecimal literals", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(0xfeed42 + 0Xbeef41)");
        lexer_make_tokens(vm);
        Token **tokens = vm->tokens;
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to "16706882");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "12513089");
        assert_that_charptr(tokens[4]->value equals to ")");

        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[3]->type equals to TOKEN_INTEGER);
      });

      it("tokenizes octal literals", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(0o752 + 0O52)");
        lexer_make_tokens(vm);
        Token **tokens = vm->tokens;
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to "490");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "42");
        assert_that_charptr(tokens[4]->value equals to ")");

        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[3]->type equals to TOKEN_INTEGER);
      });

      it("tokenizes character literals", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("('a' puts)");
        lexer_make_tokens(vm);
        Token **tokens = vm->tokens;
        assert_that_charptr(tokens[1]->value equals to "a");
        assert_that_int(tokens[1]->type equals to TOKEN_STRING);
      });

      it("tokenizes string literals", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(\"hello\" puts)");
        lexer_make_tokens(vm);
        Token **tokens = vm->tokens;
        assert_that_charptr(tokens[1]->value equals to "hello");

        vm         = vm_new("file.marg");
        vm->source = string_new("(\"multi\nline\nstring\" puts)");
        lexer_make_tokens(vm);
        tokens = vm->tokens;
        assert_that_charptr(tokens[1]->value equals to "multi\nline\nstring");
      });

      it("tokenizes identifiers", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(42 factorial\nx = (2 times: 3)\n3 plus: 4)");
        lexer_make_tokens(vm);
        Token **tokens = vm->tokens;
        assert_that_int(vector_size(tokens) equals to 17);
        assert_that_charptr(tokens[2]->value equals to "factorial");
        assert_that_charptr(tokens[3]->value equals to "x");
        assert_that_charptr(tokens[7]->value equals to "times");
        assert_that_charptr(tokens[12]->value equals to "plus");
      });

      it("tokenizes identifiers starting with an underscore", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("((1 2 3) __msg)");
        lexer_make_tokens(vm);
        Token **tokens = vm->tokens;
        assert_that_charptr(tokens[6]->value equals to "__msg");
      });
    });
  });

  it("prints postcard", {
    VM *vm = vm_new("./examples/postcard.marg");
    loader_load(vm);
    lexer_make_tokens(vm);
    Token **tokens = vm->tokens;
    printf("[");
    for(size_t i = 0; i < vector_size(tokens) - 1; i++) {
      printf("\"%s\", ", tokens[i]->value);
    }
    printf("\"%s\"]\n", tokens[vector_size(tokens) - 1]->value);
  });
})

#endif
