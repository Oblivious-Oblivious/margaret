#include "Lexer.h"

#include "../../libs/EmeraldsBool/export/EmeraldsBool.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "alternate_to_dec.h"

#define is_valid(s, c) ((c) != '\0' && strchr((s), (c)))

#define is_decimal(c) (is_valid("0123456789", (c)))
#define is_identifier_start(c) \
  (is_valid("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_", (c)))
#define is_identifier_rest(c) (is_identifier_start(c) || is_decimal(c))

#define is_newline(c) ((c) == '\n')
#define is_whitespace(c) \
  ((c) == ' ' || (c) == '\t' || (c) == '\v' || (c) == '\f' || (c) == '\r')
#define is_identifier(c)         (is_identifier_start(c) || is_identifier_rest(c))
#define is_numeric(c)            (is_valid("0123456789abcdefABCDEF_", (c)))
#define is_non_base_10(c)        (is_valid("bBoOxX", (c)))
#define is_special_identifier(c) (is_valid("!?", (c)))
#define is_message_symbol(c)     (is_valid("!?+\\-*/~<>=|&^;.`", (c)))
#define is_string_quote(c)       (is_valid("'\"", (c)))

#define next_char()              \
  do {                           \
    string_skip_first(input, 1); \
    vm->charno++;                \
  } while(0)
#define append_char()                          \
  do {                                         \
    string_addf(&token_value, "%c", input[0]); \
    next_char();                               \
  } while(0)
#define generate_token()                                           \
  (vector_add(                                                     \
    vm->tokens,                                                    \
    token_value == NULL                                            \
      ? vm->eof_token                                              \
      : token_new(token_value, token_type, vm->lineno, vm->charno) \
  ))

#define append_integer_part()       \
  do {                              \
    while(is_decimal(input[0])) {   \
      append_char();                \
    }                               \
    while(input[0] == '_') {        \
      append_char();                \
      if(!is_decimal(input[0])) {   \
        break;                      \
      }                             \
      while(is_decimal(input[0])) { \
        append_char();              \
      }                             \
    }                               \
  } while(0)

#define append_identifier_part()          \
  do {                                    \
    while(is_identifier(input[0])) {      \
      append_char();                      \
    }                                     \
    if(is_special_identifier(input[0])) { \
      append_char();                      \
    }                                     \
  } while(0)

#define normalize_integer(token)                                         \
  do {                                                                   \
    if(token[0] == '0' && (token[1] == 'b' || token[1] == 'B')) {        \
      string_skip_first(token, 2);                                       \
      bin_to_dec(token);                                                 \
    } else if(token[0] == '0' && (token[1] == 'o' || token[1] == 'O')) { \
      string_skip_first(token, 2);                                       \
      oct_to_dec(token);                                                 \
    } else if(token[0] == '0' && (token[1] == 'x' || token[1] == 'X')) { \
      string_skip_first(token, 2);                                       \
      hex_to_dec(token);                                                 \
    }                                                                    \
  } while(0)

VM *lexer_make_tokens(VM *vm) {
  char *input = vm->source;

  while(*input) {
    char *token_value = string_new("");
    Type token_type   = vm->eof_token->type;

    if(is_newline(input[0])) {
      next_char();
      vm->lineno++;
      vm->charno = 0;
      continue;
    } else if(is_whitespace(input[0])) {
      while(is_whitespace(input[0])) {
        next_char();
      }
      continue;
    } else if(input[0] == '0' && string_size(input) > 1 &&
              is_non_base_10(input[1]) && string_size(input) > 2 &&
              is_numeric(input[2])) {
      append_char();
      append_char();
      while(is_numeric(input[0])) {
        append_char();
      }
      string_remove_underscores(token_value);
      normalize_integer(token_value);
      token_type = TOKEN_INTEGER;
    } else if(is_decimal(input[0])) {
      if(input[0] == '0' && string_size(input) > 1 &&
         (is_decimal(input[1]) || input[1] == '_')) {
        append_char();
        token_type = TOKEN_INTEGER;
      } else {
        append_integer_part();
        if(input[0] == '.') {
          append_char();
          append_integer_part();
          string_remove_underscores(token_value);
          token_type = TOKEN_FLOAT;
        } else {
          string_remove_underscores(token_value);
          token_type = TOKEN_INTEGER;
        }
      }
    } else if(input[0] == '@' && string_size(input) > 1 &&
              is_identifier_start(input[1])) {
      append_char();
      append_identifier_part();
      token_type = TOKEN_INSTANCE;
    } else if(input[0] == '$' && string_size(input) > 1 &&
              is_identifier_start(input[1])) {
      append_char();
      append_identifier_part();
      token_type = TOKEN_GLOBAL;
    } else if(is_identifier_start(input[0])) {
      append_identifier_part();
      token_type = TOKEN_IDENTIFIER;
    } else if(is_message_symbol(input[0])) {
      while(is_message_symbol(input[0])) {
        append_char();
      }
      if(string_size(token_value) == 2 && token_value[0] == '=' &&
         token_value[1] == '>') {
        token_type = TOKEN_ROCKET;
      } else {
        token_type = TOKEN_MESSAGE_SYMBOL;
      }
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
  /* NOTE - Figure out why the charno is off by 3 */
  vm->eof_token->charno = vm->charno + 3;
  vector_add(vm->tokens, vm->eof_token);

  return vm;
}
