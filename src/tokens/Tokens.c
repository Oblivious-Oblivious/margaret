#include "Tokens.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h"

void tokens_init(Tokens *self) {
  self->values  = NULL;
  self->types   = NULL;
  self->linenos = NULL;
  self->charnos = NULL;
}

void tokens_add(
  Tokens *self, char *value, Type type, size_t lineno, size_t charno
) {
  vector_add(self->values, value);
  vector_add(self->types, type);
  vector_add(self->linenos, lineno);
  vector_add(self->charnos, charno);
}

void tokens_deinit(Tokens *self) {
  vector_free(self->values);
  vector_free(self->types);
  vector_free(self->linenos);
  vector_free(self->charnos);
}
