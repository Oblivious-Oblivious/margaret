#include "Token.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "../base/memory.h"

Token *token_new(
  char *value,
  Type type,
  size_t line_number,
  size_t char_number,
  const char *filename
) {
  Token *t = (Token *)collected_malloc(sizeof(Token));

  t->value       = value;
  t->type        = type;
  t->line_number = line_number;
  t->char_number = char_number;
  t->filename    = filename;

  return t;
}

bool token_equals_values(Token *tok, char *value) {
  return string_equals(tok->value, value);
}
