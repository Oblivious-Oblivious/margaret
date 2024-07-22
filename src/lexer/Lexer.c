#include "Lexer.h"

#include "../../libs/EmeraldsBool/export/EmeraldsBool.h" /* IWYU pragma: keep */
#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "../base/memory.h"
#include "alternate_to_dec.h"
#include "Regex.h"

#include <stdio.h> /* printf */

Lexer *lexer_new(const char *filename) {
  Lexer *self = (Lexer *)collected_malloc(sizeof(Lexer));

  self->filename = filename;
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

static ptrdiff_t matcher(UChar *pattern, UChar *input_string) {
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
  ptrdiff_t res      = onig_search(
    regex, input_string, end, input_string, end, region, ONIG_OPTION_NONE
  );

  ptrdiff_t output = res >= 0 && region->beg[0] == 0 ? region->end[0] : -1;
  onig_region_free(region, 1);
  onig_free(regex);

  return output;
}

static char *normalize_integer(char *token) {
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

  return token;
}

Token **lexer_make_tokens(Lexer *self, char *text) {
  Token **token_table = NULL;

  OnigEncoding encodings[1] = {ONIG_ENCODING_ASCII};
  onig_initialize(encodings, 1);

  char *token          = NULL;
  bool has_lexer_error = false;

  while(string_size(text) > 0) {
    bool is_not_matched = true;

    for(size_t i = 0; i < sizeof(REGEX_LIST) / sizeof(Regex); i++) {
      Regex *r            = &REGEX_LIST[i];
      ptrdiff_t end_index = matcher(r->pattern, (UChar *)text);
      if(end_index != -1) {
        is_not_matched = false;
        token          = string_substring(text, 0, end_index);
        self->charno += end_index;
        string_skip_first(text, end_index);

        Type token_type = REGEX_LIST[i].type;
        if(token_type == TOKEN_NEWLINE) {
          self->lineno++;
          self->charno = 0;
          continue;
        } else if(token_type == TOKEN_WHITESPACE) {
          continue;
        } else if((token_type == TOKEN_IDENTIFIER ||
                   token_type == TOKEN_INSTANCE ||
                   token_type == TOKEN_GLOBAL) &&
                  (text[0] == '!' || text[0] == '?')) {
          string_add_char(token, text[0]);
          string_skip_first(text, 1);
        } else if(token_type == TOKEN_FLOAT) {
          token = string_remove_underscores(token);
        } else if(token_type == TOKEN_INTEGER) {
          token = normalize_integer(token);
        } else if(token_type == TOKEN_STRING) {
          string_skip_first(token, 1);
          string_ignore_last(token, 1);
          self->lineno += vector_size(string_split(token, '\n'));
        }

        vector_add(
          token_table,
          token_new(
            token, token_type, self->lineno, self->charno, self->filename
          )
        );
        break;
      }
    }

    if(is_not_matched) {
      has_lexer_error = true;
      lexer_error(self, "Unexpected character.", string_split(text, '\n')[0]);
      string_skip_first(text, 1);
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
