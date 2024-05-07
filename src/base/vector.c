#include "vector.h"

#include <stdarg.h> /* va_start, va_end, va_list, va_arg */

vector *__internal_vector_new(size_t argc, ...) {
  vector *self = vector_new_empty();

  va_list vars;
  va_start(vars, argc)
    ;
    for(size_t i = 0; i < argc; i++) {
      vector_add(self, va_arg(vars, void *));
    }
  va_end(vars);

  return self;
}

vector *vector_new_empty(void) {
  vector *self = (vector *)collected_malloc(sizeof(vector));

  self->alloced = 32;
  self->size    = 0;
  self->items   = (void **)collected_malloc(sizeof(void *) * self->alloced);

  return self;
}
