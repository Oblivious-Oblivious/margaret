#include "Lexer.h"

#include "../../libs/EmeraldsBool/export/EmeraldsBool.h" /* IWYU pragma: keep */
#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "alternate_to_dec.h"
#include "Regex.h"

#include <stdio.h> /* printf */

void *lexer_error(VM *vm, const char *message, char *token) {
  if(vm->charno == 0) {
    vm->charno = 1;
  }

  printf(
    "%s:%zu:%zu: \033[1;31merror:\033[0m %s on `%s`\n",
    vm->filename,
    vm->lineno,
    vm->charno,
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
  OnigUChar *end     = input_string + strlen((char *)input_string);
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
    bin_to_dec(token);
  } else if(token[0] == '0' && (token[1] == 'o' || token[1] == 'O')) {
    string_skip_first(token, 2);
    oct_to_dec(token);
  } else if(token[0] == '0' && (token[1] == 'x' || token[1] == 'X')) {
    string_skip_first(token, 2);
    hex_to_dec(token);
  }

  return token;
}

Token *tokenize(VM *vm, char *text) {
  OnigEncoding encodings[1] = {ONIG_ENCODING_ASCII};
  onig_initialize(encodings, 1);

  Type token_type;
  char *token         = NULL;
  bool is_not_matched = true;

  for(size_t i = 0; i < sizeof(REGEX_LIST) / sizeof(Regex); i++) {
    const Regex *r      = &REGEX_LIST[i];
    ptrdiff_t end_index = matcher(r->pattern, (UChar *)text);
    if(end_index != -1) {
      is_not_matched = false;
      token          = string_substring(text, 0, end_index);
      vm->charno += end_index;
      string_skip_first(text, end_index);

      token_type = REGEX_LIST[i].type;
      if(token_type == TOKEN_NEWLINE) {
        vm->lineno++;
        vm->charno = 0;
        continue;
      } else if(token_type == TOKEN_WHITESPACE) {
        continue;
      } else if((token_type == TOKEN_IDENTIFIER ||
                 token_type == TOKEN_INSTANCE || token_type == TOKEN_GLOBAL) &&
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
        vm->lineno += vector_size(string_split(token, '\n'));
      }

      break;
    }
  }

  onig_end();

  if(is_not_matched) {
    lexer_error(vm, "Unexpected character.", string_split(text, '\n')[0]);
    string_skip_first(text, 1);
    return NULL;
  } else {
    return token_new(token, token_type, vm->lineno, vm->charno, vm->filename);
  }
}

Token **lexer_make_tokens(VM *vm, char *text) {
  Token **token_table = NULL;

  while(string_size(text) > 0) {
    Token *token = tokenize(vm, text);
    if(token == NULL) {
      vector_free(token_table);
      break;
    } else if(token->type > 10) {
      vector_add(token_table, token);
    }
  }

  vector_add(
    token_table,
    token_new(
      string_new("eof"), TOKEN_EOF, vm->lineno, vm->charno, vm->filename
    )
  );

  onig_end();

  return token_table;
}
