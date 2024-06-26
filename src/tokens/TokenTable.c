#include "TokenTable.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "../../libs/EmeraldsVector/export/EmeraldsVector.h" /* IWYU pragma: keep */

#include <stdio.h> /* fprintf */

/**
 * @brief
    TODO Abstract error somewhere closer to boundary
    TODO Name error messages or abstract to macros
 * @param token -> The token where the error occured at
 * @param message -> The message to display
 * @return string* -> NULL pointer
 */
static char *error(Token *token, const char *message) {
  fprintf(
    stderr,
    "%s:%zu:%zu \033[1;31merror:\033[0m %s  Token: \033[1;31m`%s`\033[0m\n",
    token->filename,
    token->line_number,
    token->char_number,
    message,
    token->value
  );
  return NULL;
}

Token *token_table_consume(Token **self) {
  if(vector_size(self) == 0) {
    return token_new(string_new("eof"), TOKEN_EOF, 0, 0, "");
  } else {
    Token *token = self[0];
    vector_remove(self, 0);
    return token;
  }
}

char *token_table_ensure_value(
  Token **self, const char *value, const char *error_message
) {
  Token *token = token_table_consume(self);
  if(token_equals_values(token, string_new(value))) {
    return token->value;
  } else {
    return error(token, error_message);
  }
}

char *
token_table_ensure_type(Token **self, Type type, const char *error_message) {
  Token *token = token_table_consume(self);
  if(token->type == type) {
    return token->value;
  } else {
    return error(token, error_message);
  }
}
