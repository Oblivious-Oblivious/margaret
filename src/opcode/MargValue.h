#ifndef __MARG_VALUE_H_
#define __MARG_VALUE_H_

#include "../base/marg_string.h"

typedef double MargValue;

/**
 * @brief Formats a marg value using QNAN boxing
 * @param self -> The MargValue represented as a double
 * @return marg_string*
 */
marg_string *marg_value_format(MargValue self);

/**
 * @brief Splits a 32 bit constant into 4, 8-bit parts
 * @param constant -> The 32 bit value
 * @return uint8_t* -> The 4*8 bit vector
 */
uint8_t *long_constant_to_bytes(uint32_t constant);

/**
 * @brief Joins 4, 8-bit parts into a single 32 bit integer
 * @param bytes -> The list of bytes
 * @return uint32_t -> The 32 bit result
 */
uint32_t bytes_to_long_constant(uint8_t *bytes);

#endif
