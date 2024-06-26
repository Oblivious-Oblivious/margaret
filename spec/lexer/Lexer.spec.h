#ifndef __LEXER_SPEC_H_
#define __LEXER_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/lexer/Lexer.h"

#define tokenize_and_assert(str)                              \
  do {                                                        \
    Lexer *l       = lexer_new("file.marg", string_new(str)); \
    Token **tokens = lexer_make_tokens(l);                    \
    assert_that_int(vector_size(tokens) equals to 2);         \
    assert_that_charptr(tokens[0]->value equals to str);      \
  } while(0)

#define tokenize_and_assert_multiline(str, no_lines)          \
  do {                                                        \
    Lexer *l       = lexer_new("file.marg", string_new(str)); \
    Token **tokens = lexer_make_tokens(l);                    \
    assert_that_int(vector_size(tokens) equals to 2);         \
    assert_that_int(l->lineno equals to no_lines);            \
    assert_that_charptr(tokens[0]->value equals to str);      \
  } while(0)

module(LexerSpec, {
  describe("Lexer", {
    it("contains the input text, lexer position and current character", {
      Lexer *l = lexer_new("file.marg", string_new("(42 factorial)"));
      assert_that_charptr(l->filename equals to "file.marg");
      assert_that_charptr(l->text equals to "(42 factorial)");
      assert_that_int(l->lineno equals to 1);
    });

    it("prints error messages", {
      Lexer *l       = lexer_new("file.marg", string_new("(42 factorial)"));
      void *response = lexer_error(l, "random exception", string_new(""));
      assert_that(response is NULL);
    });

    context("on #make_tokens", {
      it("correctly counts the number of lines", {
        Lexer *l = lexer_new(
          "file.marg", string_new("(42 factorial\nx = 2 + 3\ny = 5)")
        );
        lexer_make_tokens(l);

        assert_that_int(l->lineno equals to 3);
      });

      it("tokenizes symbols", {
        Lexer *l       = lexer_new("file.marg", string_new("(% ^ & *)"));
        Token **tokens = lexer_make_tokens(l);
        assert_that_int(vector_size(tokens) equals to 7);
        assert_that_charptr(tokens[1]->value equals to "%");
      });

      it("tokenizes integers", {
        Token **tokens =
          lexer_make_tokens(lexer_new("file.marg", string_new("(42 msg)")));
        assert_that_charptr(tokens[1]->value equals to "42");
        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[1]->line_number equals to 1);

        tokens = lexer_make_tokens(lexer_new("file.marg", string_new("4_200")));
        assert_that_charptr(tokens[0]->value equals to "4_200");
        tokens =
          lexer_make_tokens(lexer_new("file.marg", string_new("4_2_0_0")));
        assert_that_charptr(tokens[0]->value equals to "4_2_0_0");
      });

      it("tokenizes zero", {
        Lexer *l       = lexer_new("file.marg", string_new("(0 is_zero?)"));
        Token **tokens = lexer_make_tokens(l);

        assert_that_charptr(tokens[1]->value equals to "0");
        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[1]->line_number equals to 1);
      });

      it("draws an error when trying to tokenize an integer starting with 0", {
        Lexer *l      = lexer_new("file.marg", string_new("042 msg"));
        Token **table = lexer_make_tokens(l);
        assert_that_charptr(table[0]->value equals to "eof");
      });

      it("tokenizes floats", {
        Lexer *l       = lexer_new("file.marg", string_new("0.0"));
        Token **tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[0]->value equals to "0.0");
        assert_that_int(tokens[0]->type equals to TOKEN_FLOAT);
        assert_that_int(tokens[1]->line_number equals to 1);

        l      = lexer_new("file.marg", string_new("(42.7 msg)"));
        tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[1]->value equals to "42.7");
        assert_that_int(tokens[1]->type equals to TOKEN_FLOAT);
        assert_that_int(tokens[1]->line_number equals to 1);

        l      = lexer_new("file.marg", string_new("(0.7 msg)"));
        tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[1]->value equals to "0.7");
        assert_that_int(tokens[1]->type equals to TOKEN_FLOAT);
        assert_that_int(tokens[1]->line_number equals to 1);

        l      = lexer_new("file.marg", string_new("(0.7+0.5+0.23)"));
        tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[1]->value equals to "0.7");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "0.5");

        l      = lexer_new("file.marg", string_new("(.7 msg)"));
        tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to ".");
        assert_that_charptr(tokens[2]->value equals to "7");
        assert_that_charptr(tokens[3]->value equals to "msg");
        assert_that_charptr(tokens[4]->value equals to ")");

        l      = lexer_new("file.marg", string_new("(124.0 msg)"));
        tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[1]->value equals to "124.0");
        assert_that_charptr(tokens[2]->value equals to "msg");
      });

      it("tokenizes binary literals", {
        Lexer *l = lexer_new("file.marg", string_new("(0b1010 + 0B0100)"));
        Token **tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to "0b1010");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "0B0100");
        assert_that_charptr(tokens[4]->value equals to ")");

        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[3]->type equals to TOKEN_INTEGER);
      });

      it("tokenizes hexadecimal literals", {
        Lexer *l = lexer_new("file.marg", string_new("(0xfeed42 + 0Xbeef41)"));
        Token **tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to "0xfeed42");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "0Xbeef41");
        assert_that_charptr(tokens[4]->value equals to ")");

        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[3]->type equals to TOKEN_INTEGER);
      });

      it("tokenizes octal literals", {
        Lexer *l       = lexer_new("file.marg", string_new("(0o752 + 0O52)"));
        Token **tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[0]->value equals to "(");
        assert_that_charptr(tokens[1]->value equals to "0o752");
        assert_that_charptr(tokens[2]->value equals to "+");
        assert_that_charptr(tokens[3]->value equals to "0O52");
        assert_that_charptr(tokens[4]->value equals to ")");

        assert_that_int(tokens[1]->type equals to TOKEN_INTEGER);
        assert_that_int(tokens[3]->type equals to TOKEN_INTEGER);
      });

      it("tokenizes character literals", {
        Lexer *l       = lexer_new("file.marg", string_new("('a' puts)"));
        Token **tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[1]->value equals to "'a'");
        assert_that_int(tokens[1]->type equals to TOKEN_STRING);
      });

      it("tokenizes string literals", {
        Lexer *l       = lexer_new("file.marg", string_new("(\"hello\" puts)"));
        Token **tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[1]->value equals to "\"hello\"");

        l =
          lexer_new("file.marg", string_new("(\"multi\nline\nstring\" puts)"));
        tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[1]->value equals to "\"multi\nline\nstring\""
        );
      });

      it("tokenizes identifiers", {
        Lexer *l = lexer_new(
          "file.marg", string_new("(42 factorial\nx = (2 times: 3)\n3 plus: 4)")
        );
        Token **tokens = lexer_make_tokens(l);
        assert_that_int(vector_size(tokens) equals to 17);
        assert_that_charptr(tokens[2]->value equals to "factorial");
        assert_that_charptr(tokens[3]->value equals to "x");
        assert_that_charptr(tokens[7]->value equals to "times");
        assert_that_charptr(tokens[12]->value equals to "plus");
      });

      it("tokenizes identifiers starting with an underscore", {
        Lexer *l       = lexer_new("file.marg", string_new("((1 2 3) __msg)"));
        Token **tokens = lexer_make_tokens(l);
        assert_that_charptr(tokens[6]->value equals to "__msg");
      });
    });
  });

  describe("Different Types", {
    it("tokenizes around newlines", {
      Lexer *l       = lexer_new("file.marg", string_new("\n12\n"));
      Token **tokens = lexer_make_tokens(l);
      assert_that_int(vector_size(tokens) equals to 2);
      assert_that_int(l->lineno equals to 3);
      assert_that_charptr(tokens[0]->value equals to "12");
    });

    it("tokenizes around whitespace", {
      Lexer *l       = lexer_new("file.marg", string_new(" 12 "));
      Token **tokens = lexer_make_tokens(l);
      assert_that_int(vector_size(tokens) equals to 2);
      assert_that_int(l->lineno equals to 1);
      assert_that_charptr(tokens[0]->value equals to "12");
    });

    it("ignores multiple types of whitespace", {
      Lexer *l       = lexer_new("file.marg", string_new(" \t\r\v\f\b "));
      Token **tokens = lexer_make_tokens(l);
      assert_that_int(vector_size(tokens) equals to 1);
      assert_that_int(l->lineno equals to 1);
      assert_that_charptr(tokens[0]->value equals to "eof");
    });

    it("tokenizes different types of floats", {
      tokenize_and_assert("123.456");
      tokenize_and_assert("789_10.11");
      tokenize_and_assert("56_78.90_12");
      tokenize_and_assert("123456.789");
      tokenize_and_assert("1_2_3.4_5_6");
      tokenize_and_assert("7890.1234_5678");
      tokenize_and_assert("12345.6789");
      tokenize_and_assert("0.1");
      tokenize_and_assert("987_654.321_0");
      tokenize_and_assert("456_789.012");
    });

    it("tokenizes different types of integers", {
      tokenize_and_assert("0");
      tokenize_and_assert("0b0");
      tokenize_and_assert("0b00");
      tokenize_and_assert("0o0");
      tokenize_and_assert("0o000");
      tokenize_and_assert("0x0");
      tokenize_and_assert("0x00");
      tokenize_and_assert("1");
      tokenize_and_assert("0b1");
      tokenize_and_assert("0b01");
      tokenize_and_assert("0o1");
      tokenize_and_assert("0o001");
      tokenize_and_assert("0x1");
      tokenize_and_assert("0x01");
      tokenize_and_assert("2");
      tokenize_and_assert("0b10");
      tokenize_and_assert("0b010");
      tokenize_and_assert("0o2");
      tokenize_and_assert("0o002");
      tokenize_and_assert("0x2");
      tokenize_and_assert("0x02");
      tokenize_and_assert("0b1010_0110");
      tokenize_and_assert("0B1101");
      tokenize_and_assert("0o755");
      tokenize_and_assert("0O123_456");
      tokenize_and_assert("0xDEAD_BEEF");
      tokenize_and_assert("0XFA12");
      tokenize_and_assert("0");
      tokenize_and_assert("123_456");
      tokenize_and_assert("42");
      tokenize_and_assert("9_876_543");
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
      tokenize_and_assert("!?+*-~<>%=|&^;");
      tokenize_and_assert("*~&^;");
      tokenize_and_assert("<>|=;~");
      tokenize_and_assert(";.~!?`");
      tokenize_and_assert("%|&<>!");
      tokenize_and_assert("+=~;*");
      tokenize_and_assert("<>=%^|");
      tokenize_and_assert("+*-\\/");
      tokenize_and_assert("~;.|");
      tokenize_and_assert("!?<>");
      tokenize_and_assert("!?+*~<>%=|&^;.");
      tokenize_and_assert(";<>+=*~/");
      tokenize_and_assert("?^~&|;=%");
      tokenize_and_assert("!*<>|/~");
      tokenize_and_assert("+.-=;!?");
      tokenize_and_assert("<>%^;!");
      tokenize_and_assert("|&+*.~");
      tokenize_and_assert(";!?^=<>");
      tokenize_and_assert("-~&%=|");
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
    });

    it("tokenizes different types of strings", {
      tokenize_and_assert("'hello'");
      tokenize_and_assert("\"world\"");
      tokenize_and_assert("'test string'");
      tokenize_and_assert("\"another example\"");
      tokenize_and_assert("'a'");
      tokenize_and_assert("\"simple\"");
      tokenize_and_assert("'pattern matching'");
      tokenize_and_assert("\"regex\"");
      tokenize_and_assert("'quoted text'");
      tokenize_and_assert("\"with quotes\"");

      tokenize_and_assert_multiline("'hello\nworld'", 3);
      tokenize_and_assert_multiline("\"multi\nline\nstring\"", 4);
      tokenize_and_assert_multiline("'example\nwith\nnewlines'", 4);
      tokenize_and_assert_multiline("\"another\nexample\"", 3);
      tokenize_and_assert_multiline("'this\nis a\ntest'", 4);
      tokenize_and_assert_multiline("\"multi\nline\nregex\npattern\"", 5);
      tokenize_and_assert_multiline("'quotes\nwith\nnewlines'", 4);
      tokenize_and_assert_multiline("\"new\nline\ntest\"", 4);
      tokenize_and_assert_multiline("'string\nwith\nmultiple\nlines'", 5);
      tokenize_and_assert_multiline("\"testing\nnew\nline\nhandling\"", 5);
    });
  });
})

#endif
