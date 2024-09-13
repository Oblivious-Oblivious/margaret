#ifndef __ALTERNATE_TO_DEC_H_
#define __ALTERNATE_TO_DEC_H_

#include "../../libs/EmeraldsString/export/EmeraldsString.h"

#define convert_to_dec(str, base)              \
  do {                                         \
    size_t len = string_size(str);             \
    if(len > 0) {                              \
      size_t i   = 0;                          \
      size_t dec = 0;                          \
      for(i = 0; i < len; i++) {               \
        size_t c = str[i];                     \
        if(c >= '0' && c <= '9') {             \
          dec = dec * (base) + (c - '0');      \
        } else if(c >= 'A' && c <= 'F') {      \
          dec = dec * (base) + (c - 'A' + 10); \
        } else if(c >= 'a' && c <= 'f') {      \
          dec = dec * (base) + (c - 'a' + 10); \
        }                                      \
      }                                        \
      string_free(str);                        \
      string_addf(&(str), "%zu", dec);         \
    }                                          \
  } while(0)

/**
 * @brief Converts character representations
    of non base 10 numbers into base 10 ones
 */
#define bin_to_dec(bin) convert_to_dec(bin, 2)
#define oct_to_dec(oct) convert_to_dec(oct, 8)
#define hex_to_dec(hex) convert_to_dec(hex, 16)

#endif
