#include "Lexer.h"

#include "../../libs/EmeraldsBool/export/EmeraldsBool.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "alternate_to_dec.h"

#define is_included_in(s, c) ((c) != '\0' && strchr((s), (c)))

#define is_numeric_start(c) (is_included_in("0123456789", (c)))
#define is_ascii_start(c) \
  (is_included_in("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_", (c)))

#define utf8_char_length(input)        \
  ((((input)[0] & 0x80) == 0x00)   ? 1 \
   : (((input)[0] & 0xE0) == 0xC0) ? 2 \
   : (((input)[0] & 0xF0) == 0xE0) ? 3 \
   : (((input)[0] & 0xF8) == 0xF0) ? 4 \
                                   : 0)
#define is_unicode(input) (utf8_char_length(input) > 1)
#define is_non_base_10(char_set, check)         \
  (string_size(input) > 2 && input[0] == '0' && \
   is_included_in(char_set, input[1]) && check(input[2]))

#define is_newline(c)            ((c) == '\n')
#define is_ascii(c)              (is_ascii_start(c) || is_numeric(c))
#define is_numeric(c)            (is_numeric_start(c) || (c) == '_')
#define is_binary(c)             (is_included_in("01_", (c)))
#define is_octal(c)              (is_included_in("01234567_", (c)))
#define is_hex(c)                (is_included_in("0123456789abcdefABCDEF_", (c)))
#define is_special_identifier(c) (is_included_in("!?", (c)))
#define is_message_symbol(c)     (is_included_in("!?+\\-*/~<>=|&^;.`", (c)))
#define is_string_quote(c)       (is_included_in("'\"", (c)))
#define is_rocket_symbol() \
  (string_size(input) > 1 && input[0] == '=' && input[1] == '>')

#define next_charn(char_len)            \
  do {                                  \
    string_skip_first(input, char_len); \
    vm->charno += char_len;             \
  } while(0)
#define append_charn(char_len)                 \
  do {                                         \
    string_addn(token_value, input, char_len); \
    next_charn(char_len);                      \
  } while(0)
#define next_char()   next_charn(1)
#define append_char() append_charn(1)

#define generate_token()                                                   \
  vector_add(                                                              \
    vm->tokens, token_new(token_value, token_type, vm->lineno, vm->charno) \
  )

#define append_integer_part(check) \
  do {                             \
    while(check(input[0])) {       \
      if(input[0] == '_') {        \
        next_char();               \
      } else {                     \
        append_char();             \
      }                            \
    }                              \
  } while(0)

#define append_identifier_part()                     \
  do {                                               \
    while(is_ascii(input[0]) || is_unicode(input)) { \
      append_charn(utf8_char_length(input));         \
    }                                                \
    if(is_special_identifier(input[0])) {            \
      append_char();                                 \
    }                                                \
  } while(0)

#define append_non_base_10_part(check, converter) \
  do {                                            \
    next_char();                                  \
    next_char();                                  \
    append_integer_part(check);                   \
    converter(token_value);                       \
    token_type = TOKEN_INTEGER;                   \
  } while(0)

VM *lexer_make_tokens(VM *vm) {
  char *input = vm->source;

  while(input && *input) {
    char *token_value = string_new("");
    Type token_type   = vm->eof_token->type;

    if(is_newline(input[0])) {
      next_char();
      vm->lineno++;
      vm->charno = 0;
      continue;
    } else if(is_non_base_10("bB", is_binary)) {
      append_non_base_10_part(is_binary, bin_to_dec);
    } else if(is_non_base_10("oO", is_octal)) {
      append_non_base_10_part(is_octal, oct_to_dec);
    } else if(is_non_base_10("xX", is_hex)) {
      append_non_base_10_part(is_hex, hex_to_dec);
    } else if(is_numeric_start(input[0])) {
      if(string_size(input) > 1 && input[0] == '0' && input[1] != '.') {
        append_char();
        token_type = TOKEN_INTEGER;
      } else {
        append_integer_part(is_numeric);
        if(input[0] == '.') {
          append_char();
          append_integer_part(is_numeric);
          token_type = TOKEN_FLOAT;
        } else {
          token_type = TOKEN_INTEGER;
        }
      }
    } else if(string_size(input) > 1 && input[0] == '@' &&
              (is_ascii_start(input[1]) || is_unicode(input + 1))) {
      append_char();
      append_identifier_part();
      token_type = TOKEN_INSTANCE;
    } else if(string_size(input) > 1 && input[0] == '$' &&
              (is_ascii_start(input[1]) || is_unicode(input + 1))) {
      append_char();
      append_identifier_part();
      token_type = TOKEN_GLOBAL;
    } else if(is_ascii_start(input[0]) || is_unicode(input)) {
      append_identifier_part();
      token_type = TOKEN_IDENTIFIER;
    } else if(is_rocket_symbol()) {
      append_char();
      append_char();
      token_type = TOKEN_ROCKET;
    } else if(is_message_symbol(input[0])) {
      while(is_message_symbol(input[0])) {
        append_char();
      }
      token_type = TOKEN_MESSAGE_SYMBOL;
    } else if(input[0] == '(') {
      append_char();
      token_type = TOKEN_LPAREN;
    } else if(input[0] == ')') {
      append_char();
      token_type = TOKEN_RPAREN;
    } else if(input[0] == '[') {
      append_char();
      token_type = TOKEN_LBRACKET;
    } else if(input[0] == ']') {
      append_char();
      token_type = TOKEN_RBRACKET;
    } else if(input[0] == '{') {
      append_char();
      token_type = TOKEN_LCURLY;
    } else if(input[0] == '}') {
      append_char();
      token_type = TOKEN_RCURLY;
    } else if(input[0] == ':') {
      append_char();
      token_type = TOKEN_COLON;
    } else if(input[0] == ',') {
      append_char();
      token_type = TOKEN_COMMA;
    } else if(input[0] == '#') {
      append_char();
      token_type = TOKEN_HASH;
    } else if(input[0] == '%') {
      append_char();
      token_type = TOKEN_PERCENT;
    } else if(is_string_quote(input[0])) {
      char quote = input[0];
      next_char();
      while(input[0] != '\0' && input[0] != quote) {
        if(input[0] == '\n') {
          vm->lineno++;
          vm->charno = 0;
        }
        append_char();
      }
      if(input[0] == quote) {
        next_char();
      }
      /* NOTE - One for the quote and one for the newline */
      vm->charno -= 2;
      token_type = TOKEN_STRING;
    } else {
      next_char();
      continue;
    }

    generate_token();
  }

  vm->eof_token->lineno = vm->lineno;
  /* TODO - Figure out why the charno is off by 3 */
  vm->eof_token->charno = vm->charno + 3;
  vector_add(vm->tokens, vm->eof_token);

  vm_free_source();

  return vm;
}
