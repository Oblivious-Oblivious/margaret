#include "Lexer.h"

#include "../../libs/EmeraldsBool/export/EmeraldsBool.h"
#include "../../libs/EmeraldsOniguruma/export/EmeraldsOniguruma.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "alternate_to_dec.h"
#include "Regex.h"

#include <stdio.h> /* printf */

static ptrdiff_t matcher(const char *pattern, const char *input_string) {
  regex_t *regex = NULL;
  OnigErrorInfo error_info;
  OnigRegion *region = NULL;
  OnigUChar *end     = NULL;
  ptrdiff_t res;
  ptrdiff_t output;

  onig_new(
    &regex,
    (UChar *)pattern,
    (UChar *)(pattern + strlen(pattern)),
    ONIG_OPTION_MULTILINE,
    ONIG_ENCODING_ASCII,
    ONIG_SYNTAX_DEFAULT,
    &error_info
  );

  region = onig_region_new();
  end    = (UChar *)(input_string + strlen(input_string));
  res    = onig_search(
    regex,
    (UChar *)input_string,
    end,
    (UChar *)input_string,
    end,
    region,
    ONIG_OPTION_NONE
  );

  output = res >= 0 && region->beg[0] == 0 ? region->end[0] : -1;
  onig_region_free(region, 1);
  onig_free(regex);

  return output;
}

static char *normalize_integer(char *token) {
  string_remove_underscores(token);

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

/**
 * @brief Tokenizes the next token from the source code
 * @param vm -> The VM object
 * @return Token* -> A token object
 */
static Token *tokenize(VM *vm) {
  size_t i;
  char *token     = vm->eof_token->value;
  Type token_type = vm->eof_token->type;

  OnigEncoding encodings[1] = {ONIG_ENCODING_ASCII};
  onig_initialize(encodings, 1);

  for(i = 0; i < sizeof(REGEX_LIST) / sizeof(Regex); i++) {
    const Regex *r      = &REGEX_LIST[i];
    char *text          = vm->source + vm->index;
    ptrdiff_t end_index = matcher(r->pattern, text);
    if(end_index != -1) {
      token = string_substring(text, 0, end_index);
      vm->charno += end_index;
      vm->index += end_index;
      text       = vm->source + vm->index;
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
        string_addf(&token, "%c", text[0]);
        vm->index++;
      } else if(token_type == TOKEN_FLOAT) {
        string_remove_underscores(token);
      } else if(token_type == TOKEN_INTEGER) {
        token = normalize_integer(token);
      } else if(token_type == TOKEN_STRING) {
        string_skip_first(token, 1);
        string_ignore_last(token, 1);
        vm->lineno += vector_size(string_split(token, '\n')) - 1;
      } else if(token_type == TOKEN_MESSAGE_SYMBOL) {
        if(string_size(token) == 2 && token[0] == '=' && token[1] == '>') {
          token_type = TOKEN_ROCKET;
        }
      } else if(token_type == TOKEN_SYNTAX_SYMBOL) {
        if(token[0] == '(') {
          token_type = TOKEN_LPAREN;
        } else if(token[0] == ')') {
          token_type = TOKEN_RPAREN;
        } else if(token[0] == '[') {
          token_type = TOKEN_LBRACKET;
        } else if(token[0] == ']') {
          token_type = TOKEN_RBRACKET;
        } else if(token[0] == '{') {
          token_type = TOKEN_LCURLY;
        } else if(token[0] == '}') {
          token_type = TOKEN_RCURLY;
        } else if(token[0] == ',') {
          token_type = TOKEN_COMMA;
        } else if(token[0] == ':') {
          token_type = TOKEN_COLON;
        } else if(token[0] == '#') {
          token_type = TOKEN_HASH;
        } else if(token[0] == '%') {
          token_type = TOKEN_PERCENT;
        }
      }

      goto __end;
    }
  }
  /* Skips an unknown character */
  vm->charno++;
  vm->index++;
__end:

  onig_end();

  return token_new(token, token_type, vm->lineno, vm->charno);
}

VM *lexer_make_tokens(VM *vm) {
  while(vm->index < string_size(vm->source)) {
    Token *token = tokenize(vm);
    if(token == NULL) {
      vector_free(vm->tokens);
      break;
    } else if(token->type > 10) {
      vector_add(vm->tokens, token);
    }
  }

  vm->eof_token->lineno = vm->lineno;
  /* NOTE - Figure out why the charno is off by 3 */
  vm->eof_token->charno = vm->charno + 3;
  vector_add(vm->tokens, vm->eof_token);

  onig_end();

  return vm;
}
