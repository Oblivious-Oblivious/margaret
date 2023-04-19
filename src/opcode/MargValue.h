#ifndef __MARG_VALUE_H_
#define __MARG_VALUE_H_

#include "../base/marg_string.h"
#include "../base/marg_boolean.h"

typedef enum MargValueType {
    MARG_TYPE_NIL,
    MARG_TYPE_BOOL,
    MARG_TYPE_NUMBER,
} MargValueType;

typedef uint64_t MargValue;

/* QNAN = 0b    0     11111111111       1            1       ('0' * 50)
             (sign) (exponent bits) (qnan bit) (intel value)   (rest)        */
#define QNAN       ((uint64_t)0x7ffc000000000000)
#define SIGN_BIT   ((uint64_t)0x8000000000000000)

#define TAG_NIL    1 /* 01 -> last bits of `rest` */
#define TAG_FALSE  2 /* 10 -> last bits of `rest` */
#define TAG_TRUE   3 /* 11 -> last bits of `rest` */

static inline double value_to_num(MargValue value) {
    union {
        MargValue bits;
        double num;
    } data;
    data.bits = value;
    return data.num;
}

static inline MargValue num_to_value(double num) {
    union {
        double bits;
        MargValue value;
    } data;
    data.bits = num;
    return data.value;
}

#define MARG_NIL                 ((MargValue)(uint64_t)(QNAN | TAG_NIL))
#define MARG_FALSE               ((MargValue)(uint64_t)(QNAN | TAG_FALSE))
#define MARG_TRUE                ((MargValue)(uint64_t)(QNAN | TAG_TRUE))
#define MARG_BOOL(b)             ((b) ? MARG_TRUE : MARG_FALSE)
#define MARG_NUMBER(num)         num_to_value(num)

#define AS_BOOL(value)           ((value) == MARG_TRUE)
#define AS_NUMBER(value)         value_to_num(value)

#define IS_NIL(value)            ((value) == MARG_NIL)
#define IS_BOOL(value)           (((value) | 1) == MARG_TRUE)
#define IS_NUMBER(value)         (((value) & QNAN) != QNAN)

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
