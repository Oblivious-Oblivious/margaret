#ifndef __BYTES_H_
#define __BYTES_H_

#include <stdint.h> /* uint8_t, uint16_t, uint32_t, uint64_t */

/**
 * @brief Splits a 16 bit word into 2, 8-bit parts
 * @param word -> A 16 bit value
 * @return uint8_t* -> A 2*8 bit vector
 */
uint8_t *word_to_bytes(uint16_t word);

/**
 * @brief Splits a 32 bit dword into 4, 8-bit parts
 * @param dword -> A 32 bit value
 * @return uint8_t* -> A 4*8 bit vector
 */
uint8_t *dword_to_bytes(uint32_t dword);

/**
 * @brief Splits a 64 bit qword into 8, 8-bit parts
 * @param qword -> A 64 bit value
 * @return uint8_t* -> An 8*8 bit vector
 */
uint8_t *qword_to_bytes(uint64_t qword);

/**
 * @brief Joins 2, 8-bit parts into a single 16 bit integer
 * @param bytes -> The list of bytes
 * @return uint16_t -> The 16 bit result
 */
uint16_t bytes_to_word(uint8_t *bytes);

/**
 * @brief Joins 4, 8-bit parts into a single 32 bit integer
 * @param bytes -> The list of bytes
 * @return uint32_t -> The 32 bit result
 */
uint32_t bytes_to_dword(uint8_t *bytes);

/**
 * @brief Joins 8, 8-bit parts into a single 64 bit integer
 * @param bytes -> The list of bytes
 * @return uint64_t -> The 64 bit result
 */
uint64_t bytes_to_qword(uint8_t *bytes);

#endif
