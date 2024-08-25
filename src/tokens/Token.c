#include "Token.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h"

Token *token_new(char *value, Type type, size_t lineno, size_t charno) {
  Token *t = (Token *)malloc(sizeof(Token));

  t->value  = value;
  t->type   = type;
  t->lineno = lineno;
  t->charno = charno;

  return t;
}
