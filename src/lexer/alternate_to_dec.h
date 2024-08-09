#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */

/**
 * @brief Converts character representations
    of non base 10 numbers into base 10 ones
 */
#define bin_to_dec(bin)               \
  do {                                \
    size_t dec = 0;                   \
                                      \
    size_t len = string_size(bin);    \
    for(size_t i = 0; i < len; i++) { \
      dec = dec * 2 + (bin[i] - '0'); \
    }                                 \
                                      \
    string_free(bin);                 \
    string_addf(bin, "%zu", dec);     \
  } while(0)

#define oct_to_dec(oct)               \
  do {                                \
    size_t dec = 0;                   \
                                      \
    size_t len = string_size(oct);    \
    for(size_t i = 0; i < len; i++) { \
      dec = dec * 8 + (oct[i] - '0'); \
    }                                 \
                                      \
    string_free(oct);                 \
    string_addf(oct, "%zu", dec);     \
  } while(0)

#define hex_to_dec(hex)                           \
  do {                                            \
    size_t dec = 0;                               \
    size_t len = string_size(hex);                \
                                                  \
    for(size_t i = 0; i < len; i++) {             \
      if(hex[i] >= '0' && hex[i] <= '9') {        \
        dec = dec * 16 + hex[i] - '0';            \
      } else if(hex[i] >= 'A' && hex[i] <= 'Z') { \
        dec = dec * 16 + hex[i] - 'A' + 10;       \
      } else if(hex[i] >= 'a' && hex[i] <= 'z') { \
        dec = dec * 16 + hex[i] - 'a' + 10;       \
      }                                           \
    }                                             \
                                                  \
    string_free(hex);                             \
    string_addf(hex, "%zu", dec);                 \
  } while(0)
