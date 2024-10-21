#include "Lexer.h"

#include "../../libs/EmeraldsBool/export/EmeraldsBool.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "alternate_to_dec.h"

#define utf8_char_length(input)        \
  ((((input)[0] & 0x80) == 0x00)   ? 1 \
   : (((input)[0] & 0xE0) == 0xC0) ? 2 \
   : (((input)[0] & 0xF0) == 0xE0) ? 3 \
   : (((input)[0] & 0xF8) == 0xF0) ? 4 \
                                   : 0)

bool is_included_in(const char *s, const char *c) {
  int target_len = utf8_char_length(c);
  int len        = utf8_char_length(s);

  for(; *s; s += len) {
    if(strncmp(s, c, target_len) == 0) {
      return true;
    }
  }
  return false;
}

#define is_numeric_start(c) (is_included_in("0123456789", (c)))
#define is_ascii_start(c) \
  (is_included_in("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_", (c)))
#define is_unicode(input)     (utf8_char_length(input) > 1)
#define is_identfier_start(c) (is_ascii_start(c) || is_unicode(c))
#define is_non_base_10(char_set, check)       \
  (string_size(input) > 2 && *input == '0' && \
   is_included_in(char_set, input + 1) && check(input + 2))

#define is_newline(c)            ((*c) == '\n')
#define is_ascii(c)              (is_ascii_start(c) || is_numeric(c))
#define is_numeric(c)            (is_numeric_start(c) || (*c) == '_')
#define is_binary(c)             (is_included_in("01_", (c)))
#define is_octal(c)              (is_included_in("01234567_", (c)))
#define is_hex(c)                (is_included_in("0123456789abcdefABCDEF_", (c)))
#define is_special_identifier(c) (is_included_in("!?", (c)))
#define is_math_symbol1(c)                                                                                                                                                                                                     \
  (is_included_in(                                                                                                                                                                                                             \
    "∀∁∂∃∄∅∆∇∈∉∊∋∌∍∎∏∐∑−∓∔∕∖∗∘∙√∛∜∝∞∟∠∡∢∣∤∥∦∧∨∩∪∫∬∭∮∯∰∱∲∳∴∵∶∷∸∹∺∻∼∽∾∿≀≁≂≃≄≅≆≇" \
    "≈≉≊≋≌≍≎≏≐≑≒≓≔≕≖≗",                                                                                                                                                                                                        \
    (c)                                                                                                                                                                                                                        \
  ))
#define is_math_symbol2(c)                                                                                                                                                                                                     \
  (is_included_in(                                                                                                                                                                                                             \
    "≘≙≚≛≜≝≞≟≠≡≢≣≤≥≦≧≨≩≪≫≬≭≮≯≰≱≲≳≴≵≶≷≸≹≺≻≼≽≾≿⊀⊁⊂⊃⊄⊅⊆⊇⊈⊉⊊⊋⊌⊍⊎⊏⊐⊑⊒⊓⊔⊕⊖⊗⊘⊙⊚⊛⊜⊝⊞⊟" \
    "⊠⊡⊢⊣⊤⊥⊦⊧⊨⊩⊪⊫⊬⊭⊮⊯⊰⊱⊲⊳⊴⊵⊶⊷⊸⊹⊺⊻⊼⊽⊾⊿⋀⋁⋂⋃⋄⋅⋆⋇⋈⋉⋊⋋⋌⋍⋎⋏⋐⋑⋒⋓⋔⋕⋖⋗⋘⋙⋚⋛⋜⋝⋞⋟⋠⋡⋢⋣⋤⋥⋦⋧" \
    "⋨⋩⋪⋫⋬⋭⋮⋯⋰⋱⋲⋳⋴⋵⋶⋷⋸⋹⋺⋻⋼⋽⋾⋿",                                                                                                                                                                                                \
    (c)                                                                                                                                                                                                                        \
  ))
#define is_ascii_message_symbol(c) (is_included_in("!?+\\-*/~<>=|&^;.`", (c)))
#define is_unicode_message_symbol(c)                                \
  (is_included_in(                                                  \
    "¡¦§¨¬«¯°±´·º»¿×÷†‡•…‰′″‹›‼←↑→↓↔↕↖↗↘↙▲△▴▵▶▷▸▹►▻▼▽▾▿◀◁◂◃◄◅", (c) \
  ))
#define is_message_symbol(c)                                     \
  (is_ascii_message_symbol(c) || is_unicode_message_symbol(c) || \
   is_math_symbol1(c) || is_math_symbol2(c))
#define is_string_quote(c) (is_included_in("'\"", (c)))

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

#define generate_token(token_value, token_type, lineno, charno) \
  tokens_add(&vm->tokens, (token_value), (token_type), (lineno), (charno))

#define append_integer_part(check) \
  do {                             \
    while(check(input)) {          \
      if(*input == '_') {          \
        next_char();               \
      } else {                     \
        append_char();             \
      }                            \
    }                              \
  } while(0)

#define append_identifier_part()                  \
  do {                                            \
    while(is_ascii(input) || is_unicode(input)) { \
      append_charn(utf8_char_length(input));      \
    }                                             \
    if(is_special_identifier(input)) {            \
      append_char();                              \
    }                                             \
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
    Type token_type   = TOKEN_EOF;

    if(is_newline(input)) {
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
    } else if(is_numeric_start(input)) {
      if(string_size(input) > 1 && *input == '0' && *(input + 1) != '.') {
        append_char();
        token_type = TOKEN_INTEGER;
      } else {
        append_integer_part(is_numeric);
        if(*input == '.' && is_numeric(input + 1)) {
          append_char();
          append_integer_part(is_numeric);
          token_type = TOKEN_FLOAT;
        } else {
          token_type = TOKEN_INTEGER;
        }
      }
    } else if(string_size(input) > 1 && *input == '=' && *(input + 1) == '>') {
      append_char();
      append_char();
      token_type = TOKEN_ROCKET;
    } else if(is_message_symbol(input)) {
      while(is_message_symbol(input)) {
        append_char();
      }
      token_type = TOKEN_MESSAGE_SYMBOL;
    } else if(*input == '(') {
      append_char();
      token_type = TOKEN_LPAREN;
    } else if(*input == ')') {
      append_char();
      token_type = TOKEN_RPAREN;
    } else if(*input == '[') {
      append_char();
      token_type = TOKEN_LBRACKET;
    } else if(*input == ']') {
      append_char();
      token_type = TOKEN_RBRACKET;
    } else if(*input == '{') {
      append_char();
      token_type = TOKEN_LCURLY;
    } else if(*input == '}') {
      append_char();
      token_type = TOKEN_RCURLY;
    } else if(*input == ':') {
      append_char();
      token_type = TOKEN_COLON;
    } else if(*input == ',') {
      append_char();
      token_type = TOKEN_COMMA;
    } else if(*input == '#') {
      append_char();
      token_type = TOKEN_TABLE;
    } else if(*input == '%') {
      append_char();
      token_type = TOKEN_PERCENT;
    } else if(is_string_quote(input)) {
      char quote = *input;
      next_char();
      while(*input != '\0' && *input != quote) {
        if(*input == '\n') {
          vm->lineno++;
          vm->charno = 0;
        }
        append_char();
      }
      if(*input == quote) {
        next_char();
        /* NOTE - One for the quote and one for the newline */
        vm->charno -= 2;
        token_type = TOKEN_STRING;
      } else {
        /* NOTE - Handles the case of non-terminated strings */
        string_addf(&token_value, "%c", quote);
        token_type = -1;
      }
    } else if(string_size(input) > 1 && *input == '@' &&
              (is_identfier_start(input + 1))) {
      append_char();
      append_identifier_part();
      token_type = TOKEN_INSTANCE;
    } else if(string_size(input) > 1 && *input == '$' &&
              (is_identfier_start(input + 1))) {
      append_char();
      append_identifier_part();
      token_type = TOKEN_GLOBAL;
    } else if(is_identfier_start(input)) {
      append_identifier_part();
      token_type = TOKEN_IDENTIFIER;
    } else {
      next_char();
      continue;
    }

    generate_token(token_value, token_type, vm->lineno, vm->charno);
  }

  /* TODO - Figure out why the charno is off by 3 */
  generate_token(NULL, TOKEN_EOF, vm->lineno, vm->charno + 3);

  vm_free_source();

  return vm;
}
