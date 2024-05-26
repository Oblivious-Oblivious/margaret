#include "chunk.h"

chunk *chunk_new(void) {
  chunk *self = (chunk *)collected_malloc(sizeof(chunk));

  self->alloced = 32;
  self->size    = 0;
  self->items   = (uint8_t *)collected_malloc(sizeof(uint8_t) * self->alloced);
  self->lines   = (size_t *)collected_malloc(sizeof(size_t) * self->alloced);
  self->temp_vector = NULL;

  return self;
}
