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
      assert_that_int(vm->charno equals to 0);
    });

    context("on #make_tokens", {
      it("correctly counts the number of lines", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(42 factorial\nx = 2 + 3\ny = 5)");
        lexer_make_tokens(vm);
        assert_that_int(vm->tokens.linenos[11] equals to 3);
      });

      it("tokenizes symbols", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(% ^ & *)");
        lexer_make_tokens(vm);
        assert_that_int(vector_size(vm->tokens.values) equals to 7);
        assert_that_charptr(vm->tokens.values[1] equals to "%");
      });

      it("tokenizes integers", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(42 msg)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[1] equals to "42");
        assert_that_int(vm->tokens.types[1] equals to TOKEN_INTEGER);
        assert_that_int(vm->tokens.linenos[0] equals to 1);

        vm         = vm_new("file.marg");
        vm->source = string_new("4_200");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[0] equals to "4200");

        vm         = vm_new("file.marg");
        vm->source = string_new("4_2_0_0");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[0] equals to "4200");
      });

      it("tokenizes zero", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(0 is_zero?)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[1] equals to "0");
        assert_that_int(vm->tokens.types[1] equals to TOKEN_INTEGER);
        assert_that_int(vm->tokens.linenos[0] equals to 1);
      });

      it("correctly parses code that the parser will drop later", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("042 msg");
        lexer_make_tokens(vm);
        assert_that_int(vector_size(vm->tokens.values) equals to 4);
        assert_that_charptr(vm->tokens.values[0] equals to "0");
        assert_that_charptr(vm->tokens.values[1] equals to "42");
        assert_that_charptr(vm->tokens.values[2] equals to "msg");
        assert_that(vm->tokens.values[3] is NULL);
      });

      it("tokenizes floats", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("0.0");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[0] equals to "0.0");
        assert_that_int(vm->tokens.types[0] equals to TOKEN_FLOAT);
        assert_that_int(vm->tokens.linenos[0] equals to 1);

        vm         = vm_new("file.marg");
        vm->source = string_new("(42.7 msg)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[1] equals to "42.7");
        assert_that_int(vm->tokens.types[1] equals to TOKEN_FLOAT);
        assert_that_int(vm->tokens.linenos[0] equals to 1);

        vm         = vm_new("file.marg");
        vm->source = string_new("(0.7 msg)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[1] equals to "0.7");
        assert_that_int(vm->tokens.types[1] equals to TOKEN_FLOAT);
        assert_that_int(vm->tokens.linenos[0] equals to 1);

        vm         = vm_new("file.marg");
        vm->source = string_new("(0.7+0.5+0.23)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[1] equals to "0.7");
        assert_that_charptr(vm->tokens.values[2] equals to "+");
        assert_that_charptr(vm->tokens.values[3] equals to "0.5");
        assert_that_charptr(vm->tokens.values[4] equals to "+");
        assert_that_charptr(vm->tokens.values[5] equals to "0.23");

        vm         = vm_new("file.marg");
        vm->source = string_new("(.7 msg)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[0] equals to "(");
        assert_that_charptr(vm->tokens.values[1] equals to ".");
        assert_that_charptr(vm->tokens.values[2] equals to "7");
        assert_that_charptr(vm->tokens.values[3] equals to "msg");
        assert_that_charptr(vm->tokens.values[4] equals to ")");

        vm         = vm_new("file.marg");
        vm->source = string_new("(124.0 msg)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[1] equals to "124.0");
        assert_that_charptr(vm->tokens.values[2] equals to "msg");
      });

      it("tokenizes binary literals", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(0b1010 + 0B0100)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[0] equals to "(");
        assert_that_charptr(vm->tokens.values[1] equals to "10");
        assert_that_charptr(vm->tokens.values[2] equals to "+");
        assert_that_charptr(vm->tokens.values[3] equals to "4");
        assert_that_charptr(vm->tokens.values[4] equals to ")");

        assert_that_int(vm->tokens.types[1] equals to TOKEN_INTEGER);
        assert_that_int(vm->tokens.types[3] equals to TOKEN_INTEGER);
      });

      it("tokenizes hexadecimal literals", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(0xfeed42 + 0Xbeef41)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[0] equals to "(");
        assert_that_charptr(vm->tokens.values[1] equals to "16706882");
        assert_that_charptr(vm->tokens.values[2] equals to "+");
        assert_that_charptr(vm->tokens.values[3] equals to "12513089");
        assert_that_charptr(vm->tokens.values[4] equals to ")");

        assert_that_int(vm->tokens.types[1] equals to TOKEN_INTEGER);
        assert_that_int(vm->tokens.types[3] equals to TOKEN_INTEGER);
      });

      it("tokenizes octal literals", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(0o752 + 0O52)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[0] equals to "(");
        assert_that_charptr(vm->tokens.values[1] equals to "490");
        assert_that_charptr(vm->tokens.values[2] equals to "+");
        assert_that_charptr(vm->tokens.values[3] equals to "42");
        assert_that_charptr(vm->tokens.values[4] equals to ")");

        assert_that_int(vm->tokens.types[1] equals to TOKEN_INTEGER);
        assert_that_int(vm->tokens.types[3] equals to TOKEN_INTEGER);
      });

      it("tokenizes character literals", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("('a' puts)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[1] equals to "a");
        assert_that_int(vm->tokens.types[1] equals to TOKEN_STRING);
      });

      it("tokenizes string literals", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(\"hello\" puts)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[1] equals to "hello");

        vm         = vm_new("file.marg");
        vm->source = string_new("(\"multi\nline\nstring\" puts)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[1] equals to "multi\nline\nstring"
        );
      });

      it("tokenizes identifiers", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("(42 factorial\nx = (2 times: 3)\n3 plus: 4)");
        lexer_make_tokens(vm);
        assert_that_int(vector_size(vm->tokens.values) equals to 17);
        assert_that_charptr(vm->tokens.values[2] equals to "factorial");
        assert_that_charptr(vm->tokens.values[3] equals to "x");
        assert_that_charptr(vm->tokens.values[7] equals to "times");
        assert_that_charptr(vm->tokens.values[12] equals to "plus");
      });

      it("tokenizes identifiers starting with an underscore", {
        VM *vm     = vm_new("file.marg");
        vm->source = string_new("((1 2 3) __msg)");
        lexer_make_tokens(vm);
        assert_that_charptr(vm->tokens.values[6] equals to "__msg");
      });
    });
  });

  it("prints postcard", {
    VM *vm = vm_new("./examples/postcard.marg");
    loader_load(vm);
    lexer_make_tokens(vm);

    printf("[");
    for(size_t i = 0; i < vector_size(vm->tokens.values) - 1; i++) {
      printf("\"%s\", ", vm->tokens.values[i]);
    }
    printf("\"%s\"]\n", vm->tokens.values[vector_size(vm->tokens.values) - 1]);
  });
})

#endif
