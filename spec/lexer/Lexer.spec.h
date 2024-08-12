#ifndef __LEXER_SPEC_H_
#define __LEXER_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsReadHandler/export/EmeraldsReadHandler.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/lexer/Lexer.h"

#define tokenize_and_assert(str)                             \
  do {                                                       \
    VM *vm         = vm_new("file.marg");                    \
    Token **tokens = lexer_make_tokens(vm, string_new(str)); \
    assert_that_int(vector_size(tokens) equals to 2);        \
    assert_that_charptr(tokens[0]->value equals to str);     \
  } while(0)

#define tokenize_and_assert_res(str, res)                    \
  do {                                                       \
    VM *vm         = vm_new("file.marg");                    \
    Token **tokens = lexer_make_tokens(vm, string_new(str)); \
    assert_that_int(vector_size(tokens) equals to 2);        \
    assert_that_charptr(tokens[0]->value equals to res);     \
  } while(0)

#define tokenize_and_assert_multiline(str, no_lines)         \
  do {                                                       \
    VM *vm         = vm_new("file.marg");                    \
    Token **tokens = lexer_make_tokens(vm, string_new(str)); \
    assert_that_int(vector_size(tokens) equals to 2);        \
    assert_that_int(vm->lineno equals to no_lines);          \
    assert_that_charptr(tokens[0]->value equals to str);     \
  } while(0)

#define tokenize_and_assert_multiline_res(str, res, no_lines) \
  do {                                                        \
    VM *vm         = vm_new("file.marg");                     \
    Token **tokens = lexer_make_tokens(vm, string_new(str));  \
    assert_that_int(vector_size(tokens) equals to 2);         \
    assert_that_int(vm->lineno equals to no_lines);           \
    assert_that_charptr(tokens[0]->value equals to res);      \
  } while(0)

module(LexerSpec, {
  describe("Lexer", {
    it("contains the input text, lexer position and current character", {
      VM *vm = vm_new("file.marg");
      assert_that_charptr(vm->filename equals to "file.marg");
      assert_that_int(vm->lineno equals to 1);
    });

    it("prints error messages", {
      VM *vm         = vm_new("file.marg");
      void *response = lexer_error(vm, "random exception", string_new(""));
      assert_that(response is NULL);
    });

    context("on #make_tokens", {
      it("correctly counts the number of lines", {
        VM *vm = vm_new("file.marg");
        lexer_make_tokens(vm, string_new("(42 factorial\nx = 2 + 3\ny = 5)"));
        assert_that_int(vm->lineno equals to 3);
      });

      it("tokenizes symbols", {
        VM *vm         = vm_new("file.marg");
        Token **tokens = lexer_make_tokens(vm, string_new("(% ^ & *)"));
        assert_that_int(vector_size(tokens) equals to 7);
        assert_that_charptr(tokens[1]->value equals to "%");
      });

      it("tokenizes integers", {
        Token **tokens =
          lexer_make_tokens(vm_new("file.marg"), string_new("(42 msg)"));
        assert_that_charptr(tokens[1]->value equals to "42");
        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[1]->line_number equals to 1);

        tokens = lexer_make_tokens(vm_new("file.marg"), string_new("4_200"));
        assert_that_charptr(tokens[0]->value equals to "4200");
        tokens = lexer_make_tokens(vm_new("file.marg"), string_new("4_2_0_0"));
        assert_that_charptr(tokens[0]->value equals to "4200");
      });

      it("tokenizes zero", {
        VM *vm         = vm_new("file.marg");
        Token **tokens = lexer_make_tokens(vm, string_new("(0 is_zero?)"));

        assert_that_charptr(tokens[1]->value equals to "0");
        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[1]->line_number equals to 1);
      });

      it("correctly parses code that the parser will drop later", {
        VM *vm        = vm_new("file.marg");
        Token **table = lexer_make_tokens(vm, string_new("042 msg"));
        assert_that_charptr(table[0]->value equals to "0");
        assert_that_charptr(table[1]->value equals to "42");
        assert_that_charptr(table[2]->value equals to "msg");
        assert_that_charptr(table[3]->value equals to "eof");
      });

      it("tokenizes floats", {
        VM *vm         = vm_new("file.marg");
        Token **tokens = lexer_make_tokens(vm, string_new("0.0"));
        assert_that_charptr(tokens[0]->value equals to "0.0");
        assert_that_int(tokens[0]->type equals to TOKEN_FLOAT);
        assert_that_int(tokens[1]->line_number equals to 1);

        vm     = vm_new("file.marg");
        tokens = lexer_make_tokens(vm, string_new("(42.7 msg)"));
        assert_that_charptr(tokens[1]->value equals to "42.7");
        assert_that_int(tokens[1]->type equals to TOKEN_FLOAT);
        assert_that_int(tokens[1]->line_number equals to 1);

        vm     = vm_new("file.marg");
        tokens = lexer_make_tokens(vm, string_new("(0.7 msg)"));
        assert_that_charptr(tokens[1]->value equals to "0.7");
        assert_that_int(tokens[1]->type equals to TOKEN_FLOAT);
        assert_that_int(tokens[1]->line_number equals to 1);

        vm     = vm_new("file.marg");
        tokens = lexer_make_tokens(vm, string_new("(0.7+0.5+0.23)"));
        assert_that_charptr(tokens[1]->value equals to "0.7");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "0.5");

        vm     = vm_new("file.marg");
        tokens = lexer_make_tokens(vm, string_new("(.7 msg)"));
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to ".");
        assert_that_charptr(tokens[2]->value equals to "7");
        assert_that_charptr(tokens[3]->value equals to "msg");
        assert_that_charptr(tokens[4]->value equals to ")");

        vm     = vm_new("file.marg");
        tokens = lexer_make_tokens(vm, string_new("(124.0 msg)"));
        assert_that_charptr(tokens[1]->value equals to "124.0");
        assert_that_charptr(tokens[2]->value equals to "msg");
      });

      it("tokenizes binary literals", {
        VM *vm         = vm_new("file.marg");
        Token **tokens = lexer_make_tokens(vm, string_new("(0b1010 + 0B0100)"));
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to "10");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "4");
        assert_that_charptr(tokens[4]->value equals to ")");

        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[3]->type equals to TOKEN_INTEGER);
      });

      it("tokenizes hexadecimal literals", {
        VM *vm = vm_new("file.marg");
        Token **tokens =
          lexer_make_tokens(vm, string_new("(0xfeed42 + 0Xbeef41)"));
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to "16706882");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "12513089");
        assert_that_charptr(tokens[4]->value equals to ")");

        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[3]->type equals to TOKEN_INTEGER);
      });

      it("tokenizes octal literals", {
        VM *vm         = vm_new("file.marg");
        Token **tokens = lexer_make_tokens(vm, string_new("(0o752 + 0O52)"));
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to "490");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "42");
        assert_that_charptr(tokens[4]->value equals to ")");

        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[3]->type equals to TOKEN_INTEGER);
      });

      it("tokenizes character literals", {
        VM *vm         = vm_new("file.marg");
        Token **tokens = lexer_make_tokens(vm, string_new("('a' puts)"));
        assert_that_charptr(tokens[1]->value equals to "a");
        assert_that_int(tokens[1]->type equals to TOKEN_STRING);
      });

      it("tokenizes string literals", {
        VM *vm         = vm_new("file.marg");
        Token **tokens = lexer_make_tokens(vm, string_new("(\"hello\" puts)"));
        assert_that_charptr(tokens[1]->value equals to "hello");

        vm = vm_new("file.marg");
        tokens =
          lexer_make_tokens(vm, string_new("(\"multi\nline\nstring\" puts)"));
        assert_that_charptr(tokens[1]->value equals to "multi\nline\nstring");
      });

      it("tokenizes identifiers", {
        VM *vm         = vm_new("file.marg");
        Token **tokens = lexer_make_tokens(
          vm, string_new("(42 factorial\nx = (2 times: 3)\n3 plus: 4)")
        );
        assert_that_int(vector_size(tokens) equals to 17);
        assert_that_charptr(tokens[2]->value equals to "factorial");
        assert_that_charptr(tokens[3]->value equals to "x");
        assert_that_charptr(tokens[7]->value equals to "times");
        assert_that_charptr(tokens[12]->value equals to "plus");
      });

      it("tokenizes identifiers starting with an underscore", {
        VM *vm         = vm_new("file.marg");
        Token **tokens = lexer_make_tokens(vm, string_new("((1 2 3) __msg)"));
        assert_that_charptr(tokens[6]->value equals to "__msg");
      });
    });
  });

  describe("Different Types", {
    it("tokenizes around newlines", {
      VM *vm         = vm_new("file.marg");
      Token **tokens = lexer_make_tokens(vm, string_new("\n12\n"));
      assert_that_int(vector_size(tokens) equals to 2);
      assert_that_int(vm->lineno equals to 3);
      assert_that_charptr(tokens[0]->value equals to "12");
    });

    it("tokenizes around whitespace", {
      VM *vm         = vm_new("file.marg");
      Token **tokens = lexer_make_tokens(vm, string_new(" 12 "));
      assert_that_int(vector_size(tokens) equals to 2);
      assert_that_int(vm->lineno equals to 1);
      assert_that_charptr(tokens[0]->value equals to "12");
    });

    it("ignores multiple types of whitespace", {
      VM *vm         = vm_new("file.marg");
      Token **tokens = lexer_make_tokens(vm, string_new(" \t\r\v\f "));
      assert_that_int(vector_size(tokens) equals to 1);
      assert_that_int(vm->lineno equals to 1);
      assert_that_charptr(tokens[0]->value equals to "eof");
    });

    it("tokenizes different types of floats", {
      tokenize_and_assert("123.456");
      tokenize_and_assert("78910.11");
      tokenize_and_assert("5678.9012");
      tokenize_and_assert("123456.789");
      tokenize_and_assert("123.456");
      tokenize_and_assert("7890.12345678");
      tokenize_and_assert("12345.6789");
      tokenize_and_assert("0.1");
      tokenize_and_assert("987654.3210");
      tokenize_and_assert("456789.012");
    });

    it("tokenizes different types of integers", {
      tokenize_and_assert("0");
      tokenize_and_assert_res("0b0", "0");
      tokenize_and_assert_res("0b00", "0");
      tokenize_and_assert_res("0o0", "0");
      tokenize_and_assert_res("0o000", "0");
      tokenize_and_assert_res("0x0", "0");
      tokenize_and_assert_res("0x00", "0");
      tokenize_and_assert("1");
      tokenize_and_assert_res("0b1", "1");
      tokenize_and_assert_res("0b01", "1");
      tokenize_and_assert_res("0o1", "1");
      tokenize_and_assert_res("0o001", "1");
      tokenize_and_assert_res("0x1", "1");
      tokenize_and_assert_res("0x01", "1");
      tokenize_and_assert("2");
      tokenize_and_assert_res("0b10", "2");
      tokenize_and_assert_res("0b010", "2");
      tokenize_and_assert_res("0o2", "2");
      tokenize_and_assert_res("0o002", "2");
      tokenize_and_assert_res("0x2", "2");
      tokenize_and_assert_res("0x02", "2");
      tokenize_and_assert_res("0b1010_0110", "166");
      tokenize_and_assert_res("0B1101", "13");
      tokenize_and_assert_res("0o755", "493");
      tokenize_and_assert_res("0O123_456", "42798");
      tokenize_and_assert_res("0xDEAD_BEEF", "3735928559");
      tokenize_and_assert_res("0XFA12", "64018");
      tokenize_and_assert("0");
      tokenize_and_assert("123456");
      tokenize_and_assert("42");
      tokenize_and_assert("9876543");
    });

    it("tokenizes different types of identifiers", {
      tokenize_and_assert("a");
      tokenize_and_assert("a1");
      tokenize_and_assert("a1b");
      tokenize_and_assert("a1b2");
      tokenize_and_assert("a1b2c");
      tokenize_and_assert("a1b2c3");
      tokenize_and_assert("$var");
      tokenize_and_assert("@var");
      tokenize_and_assert("var");
      tokenize_and_assert("$variable!");
      tokenize_and_assert("@variable!");
      tokenize_and_assert("variable!");
      tokenize_and_assert("$variable?");
      tokenize_and_assert("@variable?");
      tokenize_and_assert("variable?");
      tokenize_and_assert("variableName");
      tokenize_and_assert("_privateVariable");
      tokenize_and_assert("$dollarVar");
      tokenize_and_assert("@specialChar");
      tokenize_and_assert("normal_var123");
      tokenize_and_assert("AnotherVariable");
      tokenize_and_assert("user_name");
      tokenize_and_assert("$configValue");
      tokenize_and_assert("_underscore");
      tokenize_and_assert("temp123");
    });

    it("tokenizes different types of messages", {
      tokenize_and_assert("!?+*-~<>=|&^;");
      tokenize_and_assert("*~&^;");
      tokenize_and_assert("<>|=;~");
      tokenize_and_assert(";.~!?`");
      tokenize_and_assert("|&<>!");
      tokenize_and_assert("+=~;*");
      tokenize_and_assert("<>=^|");
      tokenize_and_assert("+*-\\/");
      tokenize_and_assert("~;.|");
      tokenize_and_assert("!?<>");
      tokenize_and_assert("!?+*~<>=|&^;.");
      tokenize_and_assert(";<>+=*~/");
      tokenize_and_assert("?^~&|;=");
      tokenize_and_assert("!*<>|/~");
      tokenize_and_assert("+.-=;!?");
      tokenize_and_assert("<>^;!");
      tokenize_and_assert("|&+*.~");
      tokenize_and_assert(";!?^=<>");
      tokenize_and_assert("-~&=|");
      tokenize_and_assert("\\;.^!?");
    });

    it("tokenizes different types of syntax symbols", {
      tokenize_and_assert("(");
      tokenize_and_assert(")");
      tokenize_and_assert("[");
      tokenize_and_assert("]");
      tokenize_and_assert("{");
      tokenize_and_assert("}");
      tokenize_and_assert(",");
      tokenize_and_assert(":");
      tokenize_and_assert("#");
      tokenize_and_assert("%");
    });

    it("tokenizes different types of strings", {
      tokenize_and_assert_res("'hello'", "hello");
      tokenize_and_assert_res("\"world\"", "world");
      tokenize_and_assert_res("'test string'", "test string");
      tokenize_and_assert_res("\"another example\"", "another example");
      tokenize_and_assert_res("'a'", "a");
      tokenize_and_assert_res("\"simple\"", "simple");
      tokenize_and_assert_res("'pattern matching'", "pattern matching");
      tokenize_and_assert_res("\"regex\"", "regex");
      tokenize_and_assert_res("'quoted text'", "quoted text");
      tokenize_and_assert_res("\"with quotes\"", "with quotes");

      tokenize_and_assert_multiline_res("'hello\nworld'", "hello\nworld", 3);
      tokenize_and_assert_multiline_res(
        "\"multi\nline\nstring\"", "multi\nline\nstring", 4
      );
      tokenize_and_assert_multiline_res(
        "'example\nwith\nnewlines'", "example\nwith\nnewlines", 4
      );
      tokenize_and_assert_multiline_res(
        "\"another\nexample\"", "another\nexample", 3
      );
      tokenize_and_assert_multiline_res(
        "'this\nis a\ntest'", "this\nis a\ntest", 4
      );
      tokenize_and_assert_multiline_res(
        "\"multi\nline\nregex\npattern\"", "multi\nline\nregex\npattern", 5
      );
      tokenize_and_assert_multiline_res(
        "'quotes\nwith\nnewlines'", "quotes\nwith\nnewlines", 4
      );
      tokenize_and_assert_multiline_res(
        "\"new\nline\ntest\"", "new\nline\ntest", 4
      );
      tokenize_and_assert_multiline_res(
        "'string\nwith\nmultiple\nlines'", "string\nwith\nmultiple\nlines", 5
      );
      tokenize_and_assert_multiline_res(
        "\"testing\nnew\nline\nhandling\"", "testing\nnew\nline\nhandling", 5
      );
    });
  });

  it("prints postcard", {
    char *postcard =
      read_handler_load(read_handler_new(), "./examples/postcard.marg");
    VM *vm         = vm_new("postcard.marg");
    Token **tokens = lexer_make_tokens(vm, string_new(postcard));
    printf("[");
    for(size_t i = 0; i < vector_size(tokens) - 1; i++) {
      printf("\"%s\", ", tokens[i]->value);
    }
    printf("\"%s\"]\n", tokens[vector_size(tokens) - 1]->value);
  });
})

#endif
