#include "byte_conversions.h"

#include "../base/memory.h" /* IWYU pragma: keep */

uint8_t *word_to_bytes(uint16_t word) {
  uint8_t *bytes = (uint8_t *)malloc(sizeof(uint8_t) * 2);

  bytes[0] = (word >> 8) & 0xff;
  bytes[1] = word & 0xff;

  return bytes;
}

uint8_t *dword_to_bytes(uint32_t dword) {
  uint8_t *bytes = (uint8_t *)malloc(sizeof(uint8_t) * 4);

  uint8_t *lhs_bytes = word_to_bytes((dword >> 16) & 0xffff);
  uint8_t *rhs_bytes = word_to_bytes(dword & 0xffff);

  bytes[0] = lhs_bytes[0];
  bytes[1] = lhs_bytes[1];

  bytes[2] = rhs_bytes[0];
  bytes[3] = rhs_bytes[1];

  return bytes;
}

uint16_t bytes_to_word(uint8_t *bytes) {
  return (uint16_t)bytes[0] << 8 | bytes[1];
}

uint32_t bytes_to_dword(uint8_t *bytes) {
  return (uint32_t)bytes[0] << 24 | (uint32_t)bytes[1] << 16 |
         (uint16_t)bytes[2] << 8 | bytes[3];
}
