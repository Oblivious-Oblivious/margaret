#include "TokenTable.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../libs/EmeraldsVector/export/EmeraldsVector.h"

#include <stdio.h> /* printf */

/**
 * @brief Displays an error message (grabs latest line and column)
 * @param vm -> The vm containing the token table
 * @param token -> The token where the error occured at
 * @param message -> The message to display
 * @return string* -> NULL pointer
 */
static char *error(VM *vm, Token *token, const char *message) {
  printf(
    "%s:%zu:%zu \033[1;31merror:\033[0m %s  Token: \033[1;31m`%s`\033[0m\n",
    vm->filename,
    vm->lineno,
    vm->charno,
    message,
    token->value
  );
  return NULL;
}

Token *token_table_consume(VM *vm) {
  if(vector_size(vm->tokens) == 0) {
    return token_new(string_new("eof"), TOKEN_EOF);
  } else {
    Token *token = vm->tokens[0];
    vector_remove(vm->tokens, 0);
    return token;
  }
}

char *
token_table_ensure_value(VM *vm, const char *value, const char *error_message) {
  Token *token = token_table_consume(vm);
  if(token_equals_values(token, string_new(value))) {
    return token->value;
  } else {
    return error(vm, token, error_message);
  }
}

char *token_table_ensure_type(VM *vm, Type type, const char *error_message) {
  Token *token = token_table_consume(vm);
  if(token->type == type) {
    return token->value;
  } else {
    return error(vm, token, error_message);
  }
}
