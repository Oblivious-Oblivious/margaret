#ifndef __TOKEN_TYPES_SPEC_H_
#define __TOKEN_TYPES_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../libs/EmeraldsVector/export/EmeraldsVector.h"
#include "../../src/lexer/Lexer.h"

#define tokenize_and_assert(str)                             \
  do {                                                       \
    VM *vm     = vm_new("file.marg");                        \
    vm->source = string_new(str);                            \
    lexer_make_tokens(vm);                                   \
    assert_that_int(vector_size(vm->tokens) equals to 2);    \
    assert_that_charptr(vm->tokens[0]->value equals to str); \
  } while(0)

#define tokenize_and_assert_res(str, res)                    \
  do {                                                       \
    VM *vm     = vm_new("file.marg");                        \
    vm->source = string_new(str);                            \
    lexer_make_tokens(vm);                                   \
    assert_that_int(vector_size(vm->tokens) equals to 2);    \
    assert_that_charptr(vm->tokens[0]->value equals to res); \
  } while(0)

#define tokenize_and_assert_multiline_res(str, res, no_lines, no_chars) \
  do {                                                                  \
    VM *vm     = vm_new("file.marg");                                   \
    vm->source = string_new(str);                                       \
    lexer_make_tokens(vm);                                              \
    assert_that_int(vector_size(vm->tokens) equals to 2);               \
    assert_that_int(vm->lineno equals to no_lines);                     \
    assert_that_int(vm->charno equals to no_chars);                     \
    assert_that_charptr(vm->tokens[0]->value equals to res);            \
  } while(0)

module(token_types_spec, {
  describe("Different Types", {
    it("tokenizes around newlines", {
      VM *vm     = vm_new("file.marg");
      vm->source = string_new("\n12\n");
      lexer_make_tokens(vm);
      Token **tokens = vm->tokens;
      assert_that_int(vector_size(tokens) equals to 2);
      assert_that_int(vm->lineno equals to 3);
      assert_that_charptr(tokens[0]->value equals to "12");
    });

    it("tokenizes around whitespace", {
      VM *vm     = vm_new("file.marg");
      vm->source = string_new(" 12 ");
      lexer_make_tokens(vm);
      Token **tokens = vm->tokens;
      assert_that_int(vector_size(tokens) equals to 2);
      assert_that_int(vm->lineno equals to 1);
      assert_that_charptr(tokens[0]->value equals to "12");
    });

    it("ignores multiple types of whitespace", {
      VM *vm     = vm_new("file.marg");
      vm->source = string_new(" \t\r\v\f ");
      lexer_make_tokens(vm);
      Token **tokens = vm->tokens;
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

      tokenize_and_assert_multiline_res("'hello\nworld'", "hello\nworld", 2, 5);
      tokenize_and_assert_multiline_res(
        "\"multi\nline\nstring\"", "multi\nline\nstring", 3, 6
      );
      tokenize_and_assert_multiline_res(
        "'example\nwith\nnewlines'", "example\nwith\nnewlines", 3, 8
      );
      tokenize_and_assert_multiline_res("'hello\n'", "hello\n", 2, 0);
      tokenize_and_assert_multiline_res(
        "\"another\nexample\"", "another\nexample", 2, 7
      );
      tokenize_and_assert_multiline_res(
        "'this\nis a\ntest'", "this\nis a\ntest", 3, 4
      );
      tokenize_and_assert_multiline_res(
        "\"multi\nline\nregex\npattern\"", "multi\nline\nregex\npattern", 4, 7
      );
      tokenize_and_assert_multiline_res(
        "'quotes\nwith\nnewlines'", "quotes\nwith\nnewlines", 3, 8
      );
      tokenize_and_assert_multiline_res(
        "\"new\nline\ntest\"", "new\nline\ntest", 3, 4
      );
      tokenize_and_assert_multiline_res(
        "'string\nwith\nmultiple\nlines'", "string\nwith\nmultiple\nlines", 4, 5
      );
      tokenize_and_assert_multiline_res(
        "\"testing\nnew\nline\nhandling\"", "testing\nnew\nline\nhandling", 4, 8
      );
    });
  });
})

#endif
