#ifndef __BYTES_H_
#define __BYTES_H_

#include <stdint.h> /* uint8_t, uint16_t, uint32_t, uint64_t */

/**
 * @brief Splits a 16 bit word into 2, 8-bit parts
 * @param word -> A 16 bit value
 * @param bytes -> A 2*8 bit vector
 */
#define word_to_bytes(word, bytes)     \
  do {                                 \
    (bytes)[0] = ((word) >> 8) & 0xff; \
    (bytes)[1] = (word) & 0xff;        \
  } while(0)

/**
 * @brief Splits a 32 bit dword into 4, 8-bit parts
 * @param dword -> A 32 bit value
 * @param bytes -> A 4*8 bit vector
 */
#define dword_to_bytes(dword, bytes)                  \
  do {                                                \
    word_to_bytes(((dword) >> 16) & 0xffff, (bytes)); \
    word_to_bytes((dword) & 0xffff, (bytes) + 2);     \
  } while(0)

/**
 * @brief Joins 2, 8-bit parts into a single 16 bit integer
 * @param bytes -> The list of bytes
 * @return uint16_t -> The 16 bit result
 */
#define bytes_to_word(bytes) (uint16_t)(bytes)[0] << 8 | (bytes)[1]

/**
 * @brief Joins 4, 8-bit parts into a single 32 bit integer
 * @param bytes -> The list of bytes
 * @return uint32_t -> The 32 bit result
 */
#define bytes_to_dword(bytes)                               \
  (uint32_t)(bytes)[0] << 24 | (uint32_t)(bytes)[1] << 16 | \
    (uint16_t)(bytes)[2] << 8 | (bytes)[3]

#endif
