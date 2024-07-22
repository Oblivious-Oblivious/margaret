#include "alternate_to_dec.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */

#include <stdint.h>

char *bin_to_dec(const char *bin) {
  char *res  = NULL;
  size_t dec = 0;

  size_t len = string_size(bin);
  for(size_t i = 0; i < len; i++) {
    dec = dec * 2 + (bin[i] - '0');
  }

  string_addf(res, "%zu", dec);
  return res;
}

char *oct_to_dec(const char *oct) {
  char *res  = NULL;
  size_t dec = 0;

  size_t len = string_size(oct);
  for(size_t i = 0; i < len; i++) {
    dec = dec * 8 + (oct[i] - '0');
  }

  string_addf(res, "%zu", dec);
  return res;
}

char *hex_to_dec(const char *hex) {
  char *res  = NULL;
  size_t dec = 0;
  size_t len = string_size(hex);

  for(size_t i = 0; i < len; i++) {
    if(hex[i] >= '0' && hex[i] <= '9') {
      dec = dec * 16 + hex[i] - '0';
    } else if(hex[i] >= 'A' && hex[i] <= 'Z') {
      dec = dec * 16 + hex[i] - 'A' + 10;
    } else if(hex[i] >= 'a' && hex[i] <= 'z') {
      dec = dec * 16 + hex[i] - 'a' + 10;
    }
  }

  string_addf(res, "%zu", dec);
  return res;
}
