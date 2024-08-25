#include "Token.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h"

Token *token_new(char *value, Type type) {
  Token *t = (Token *)malloc(sizeof(Token));

  t->value = value;
  t->type  = type;

  return t;
}
