#include "Lexer.h"

#include "../../libs/EmeraldsBool/export/EmeraldsBool.h" /* IWYU pragma: keep */
#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "../base/memory.h"

#include <ctype.h> /* tolower */
#include <stdio.h> /* fprintf */

Lexer *lexer_new(const char *filename, char *text) {
  Lexer *self = (Lexer *)collected_malloc(sizeof(Lexer));

  self->filename = filename;
  self->text     = text;
  self->pos      = 0;
  self->lineno   = 1;

  return self;
}

void *lexer_error(Lexer *self, const char *message, char *token) {
  fprintf(
    stderr,
    "%s:%zu: \033[1;31merror:\033[0m %s on `%s`\n",
    self->filename,
    self->lineno,
    message,
    token
  );
  return NULL;
}

char lexer_next_character(Lexer *self) {
  self->pos++;
  return self->text[self->pos - 1];
}

char lexer_peek_character(Lexer *self, size_t i) {
  return self->text[self->pos + i - 1];
}

static Token *lexer_tokenize_integer(Lexer *self, char c) {
  char *final_number = string_new("");
  while(true) {
    string_add_char(final_number, c);
    c = lexer_peek_character(self, 1);
    if(c == '_') {
      c = lexer_next_character(self);
      continue;
    }

    if(c == '\0' || !regex_matches(c, REGEX_NUMBER)) {
      break;
    }

    c = lexer_next_character(self);
  }

  return token_new(final_number, TOKEN_INTEGER, self->lineno, self->filename);
}

static Token *lexer_tokenize_number_special(
  Lexer *self, char *final_number, const char *matcher, Type type
) {
  // Fraction part
  char c = lexer_next_character(self);
  string_add_char(final_number, tolower(c));

  // Rest of number
  c = lexer_next_character(self);
  while(true) {
    string_add_char(final_number, tolower(c));
    c = lexer_peek_character(self, 1);
    if(c == '_') {
      c = lexer_next_character(self);
      continue;
    }

    if(c == '\0' || !regex_matches(c, matcher)) {
      break;
    }

    c = lexer_next_character(self);
  }

  return token_new(final_number, type, self->lineno, self->filename);
}

static Token *lexer_tokenize_integer_or_float(Lexer *self, char c) {
  Token *int_token = lexer_tokenize_integer(self, c);

  c = lexer_peek_character(self, 1);
  if(c == '.') {
    return lexer_tokenize_number_special(
      self, int_token->value, REGEX_NUMBER, TOKEN_FLOAT
    );
  } else {
    return int_token;
  }
}

static Token *lexer_tokenize_number(Lexer *self, char c) {
  char *final_number = string_new("");
  string_add_char(final_number, c);

  // TODO Refactor to work with multiple zeros
  // "0", "-0", "+0", "0b0", "-0b0", "+0b0", "0b00", "-0b00", "+0b00", "0o0",
  // "-0o0", "+0o0", "0o000", "-0o000", "+0o000", "0x0", "-0x0", "+0x0", "0x00",
  // "-0x00", "+0x00" "1", "+1", "0b1", "+0b1", "0b01", "+0b01", "0o1", "+0o1",
  // "0o001", "+0o001", "0x1", "+0x1", "0x01", "+0x01"
  // "-1", "-0b1", "-0b01", "-0o1", "-0o001", "-0x1", "-0x01"
  // "2", "+2", "0b10", "+0b10", "0b010", "+0b010", "0o2", "+0o2", "0o002",
  // "+0o002", "0x2", "+0x2", "0x02", "+0x02"
  if(c == '0') {
    c = lexer_peek_character(self, 1);
    if(c == '.') {
      return lexer_tokenize_number_special(
        self, final_number, REGEX_NUMBER, TOKEN_FLOAT
      );
    } else if(c == 'b' || c == 'B') {
      return lexer_tokenize_number_special(
        self, final_number, REGEX_BINARY, TOKEN_INTEGER
      );
    } else if(c == 'x' || c == 'X') {
      return lexer_tokenize_number_special(
        self, final_number, REGEX_HEXADECIMAL, TOKEN_INTEGER
      );
    } else if(c == 'o' || c == 'O') {
      return lexer_tokenize_number_special(
        self, final_number, REGEX_OCTAL, TOKEN_INTEGER
      );
    } else if(!regex_matches(c, REGEX_NUMBER)) {
      return token_new(
        string_new("0"), TOKEN_INTEGER, self->lineno, self->filename
      );
    } else {
      return lexer_error(self, "invalid number format", final_number);
    }
  } else {
    return lexer_tokenize_integer_or_float(self, c);
  }
}

static Token *lexer_tokenize_identifier(Lexer *self, char c) {
  char *final_identifier = string_new("");

  // TODO Add unicode support for identifier names (APL or Julia style)
  while(true) {
    string_add_char(final_identifier, c);
    c = lexer_peek_character(self, 1);
    if(c == '\0' || !(regex_matches(c, REGEX_NUMBER) || c == '_' ||
                      regex_matches(c, REGEX_LETTER))) {
      break;
    }
    c = lexer_next_character(self);
  }

  return token_new(
    final_identifier, TOKEN_IDENTIFIER, self->lineno, self->filename
  );
}

static Token *lexer_tokenize_message_symbol(Lexer *self, char c) {
  char *final_symbol = string_new("");

  while(true) {
    string_add_char(final_symbol, c);
    c = lexer_peek_character(self, 1);
    if(c == '\0' || !(regex_matches(c, REGEX_MESSAGE_SYMBOL))) {
      break;
    }
    c = lexer_next_character(self);
  }
  char maybe_id_symb = final_symbol[0];
  if(string_size(final_symbol) == 1 &&
     regex_matches(maybe_id_symb, REGEX_ID_SYMBOL)) {
    return token_new(
      final_symbol, TOKEN_ID_SYMBOL, self->lineno, self->filename
    );
  } else {
    return token_new(
      final_symbol, TOKEN_MESSAGE_SYMBOL, self->lineno, self->filename
    );
  }
}

static Token *lexer_tokenize_string(Lexer *self, char c) {
  char *final_string = string_new("");
  string_add_char(final_string, c);
  c = lexer_next_character(self);
  // TODO Separate pairs of single and double quotes -> avoid "str', or 'str"
  while(!regex_matches(c, REGEX_SINGLE_QUOTE) &&
        !regex_matches(c, REGEX_DOUBLE_QUOTE)) {
    string_add_char(final_string, c);
    c = lexer_next_character(self);
    if(c == '\0') {
      return lexer_error(self, "unterminated string literal", final_string);
    } else if(regex_matches(c, REGEX_NEWLINE)) {
      self->lineno++;
    }
  }
  string_add_char(final_string, c);
  return token_new(final_string, TOKEN_STRING, self->lineno, self->filename);
}

TokenTable *lexer_make_tokens(Lexer *self) {
  TokenTable *token_table = token_table_new();

  char c;
  while(true) {
    c = lexer_next_character(self);
    if(c == '\0') {
      break;
    } else if(regex_matches(c, REGEX_NEWLINE)) {
      self->lineno++;
    } else if(regex_matches(c, REGEX_WHITESPACE))
      ; // Skip
    else if(regex_matches(c, REGEX_NUMBER)) {
      token_table_add(token_table, lexer_tokenize_number(self, c));
    } else if(regex_matches(c, REGEX_LETTER) || c == '_') {
      token_table_add(token_table, lexer_tokenize_identifier(self, c));
    } else if(regex_matches(c, REGEX_MESSAGE_SYMBOL)) {
      token_table_add(token_table, lexer_tokenize_message_symbol(self, c));
    } else if(regex_matches(c, REGEX_SYNTAX_SYMBOL)) {
      char *symb = string_new("");
      string_add_char(symb, c);
      token_table_add(
        token_table,
        token_new(symb, TOKEN_SYNTAX_SYMBOL, self->lineno, self->filename)
      );
    } else if(regex_matches(c, REGEX_SINGLE_QUOTE) ||
              regex_matches(c, REGEX_DOUBLE_QUOTE)) {
      Token *tok = lexer_tokenize_string(self, c);
      if(tok == NULL) {
        break;
      }
      token_table_add(token_table, tok);
    } else {
      char *err = string_new("");
      string_add_char(err, c);
      lexer_error(self, "Unexpected character.", err);
      break;
    }
  }

  token_table_add(
    token_table,
    token_new(string_new("eof"), TOKEN_EOF, self->lineno, self->filename)
  );

  return token_table;
}
