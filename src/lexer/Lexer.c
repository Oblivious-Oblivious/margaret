#include "Lexer.h"

#include "../../libs/EmeraldsBool/export/EmeraldsBool.h" /* IWYU pragma: keep */
#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "../base/memory.h"
#include "alternate_to_dec.h"
#include "Regex.h"

#include <stdio.h> /* printf */

Lexer *lexer_new(const char *filename, char *text) {
  Lexer *self = (Lexer *)collected_malloc(sizeof(Lexer));

  self->filename = filename;
  self->text     = text;
  self->lineno   = 1;
  self->charno   = 0;

  return self;
}

void *lexer_error(Lexer *self, const char *message, char *token) {
  if(self->charno == 0) {
    self->charno = 1;
  }

  printf(
    "%s:%zu:%zu: \033[1;31merror:\033[0m %s on `%s`\n",
    self->filename,
    self->lineno,
    self->charno,
    message,
    token
  );
  return NULL;
}

static int matcher(UChar *pattern, UChar *input_string) {
  regex_t *regex = NULL;
  OnigErrorInfo error_info;
  onig_new(
    &regex,
    pattern,
    pattern + strlen((char *)pattern),
    ONIG_OPTION_MULTILINE,
    ONIG_ENCODING_ASCII,
    ONIG_SYNTAX_DEFAULT,
    &error_info
  );

  OnigRegion *region = onig_region_new();
  OnigUChar *end     = input_string + string_size(input_string);
  int res            = onig_search(
    regex, input_string, end, input_string, end, region, ONIG_OPTION_NONE
  );

  int output = res >= 0 && region->beg[0] == 0 ? region->end[0] : -1;
  onig_region_free(region, 1);
  onig_free(regex);

  return output;
}

Token **lexer_make_tokens(Lexer *self) {
  Token **token_table = NULL;

  OnigEncoding encodings[1] = {ONIG_ENCODING_ASCII};
  onig_initialize(encodings, 1);

  char *token          = NULL;
  bool has_lexer_error = false;

  while(string_size(self->text) > 0) {
    bool is_not_matched = true;

    for(size_t i = 0; i < sizeof(REGEX_LIST) / sizeof(Regex); i++) {
      Regex *r      = &REGEX_LIST[i];
      int end_index = matcher(r->pattern, (UChar *)self->text);
      if(end_index != -1) {
        is_not_matched = false;
        token          = string_substring(self->text, 0, end_index);
        self->charno += end_index;
        string_skip_first(self->text, end_index);
        if(REGEX_LIST[i].type == TOKEN_NEWLINE) {
          self->lineno++;
          self->charno = 0;
        } else if(REGEX_LIST[i].type == TOKEN_WHITESPACE) {
          ; // skip
        } else if((REGEX_LIST[i].type == TOKEN_IDENTIFIER ||
                   REGEX_LIST[i].type == TOKEN_INSTANCE ||
                   REGEX_LIST[i].type == TOKEN_GLOBAL) &&
                  (self->text[0] == '!' || self->text[0] == '?')) {
          string_add_char(token, self->text[0]);
          string_skip_first(self->text, 1);
          goto new_token;
        } else if(REGEX_LIST[i].type == TOKEN_FLOAT) {
          token = string_remove_underscores(token);
          goto new_token;
        } else if(REGEX_LIST[i].type == TOKEN_INTEGER) {
          token = string_remove_underscores(token);

          if(token[0] == '0' && (token[1] == 'b' || token[1] == 'B')) {
            string_skip_first(token, 2);
            token = string_new(bin_to_dec(token));
          } else if(token[0] == '0' && (token[1] == 'o' || token[1] == 'O')) {
            string_skip_first(token, 2);
            token = string_new(oct_to_dec(token));
          } else if(token[0] == '0' && (token[1] == 'x' || token[1] == 'X')) {
            string_skip_first(token, 2);
            token = string_new(hex_to_dec(token));
          }
          goto new_token;
        } else if(REGEX_LIST[i].type == TOKEN_STRING) {
          string_skip_first(token, 1);
          string_ignore_last(token, 1);
          self->lineno += vector_size(string_split(token, "\n"));
          goto new_token;
        } else {
        new_token:
          vector_add(
            token_table,
            token_new(
              token,
              REGEX_LIST[i].type,
              self->lineno,
              self->charno,
              self->filename
            )
          );
        }
        break;
      }
    }

    if(is_not_matched) {
      has_lexer_error = true;
      lexer_error(
        self, "Unexpected character.", string_split(self->text, "\n")[0]
      );
      string_skip_first(self->text, 1);
    }
  }

  if(has_lexer_error) {
    vector_free(token_table);
  }

  vector_add(
    token_table,
    token_new(
      string_new("eof"), TOKEN_EOF, self->lineno, self->charno, self->filename
    )
  );

  onig_end();

  return token_table;
}
