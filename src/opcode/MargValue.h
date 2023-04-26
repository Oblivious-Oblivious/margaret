#ifndef __MARG_VALUE_H_
#define __MARG_VALUE_H_

#include <string.h> /* memcpy */

#include "../base/boolean.h"
#include "../base/string.h"

#include "MargObject.h"
#include "MargString.h"

typedef uint64_t MargValue;

/* QNAN = 0b    0     11111111111       1            1       ('0' * 50)
             (sign) (exponent bits) (qnan bit) (intel value)   (rest)        */
#define QNAN       ((uint64_t)0x7ffc000000000000)
#define SIGN_BIT   ((uint64_t)0x8000000000000000)

#define TAG_NIL    1 /* 01 -> last bits of `rest` */
#define TAG_FALSE  2 /* 10 -> last bits of `rest` */
#define TAG_TRUE   3 /* 11 -> last bits of `rest` */

static inline long double marg_value_as_number(MargValue value) {
    long double number;
    memcpy(&number, &value, sizeof(MargValue));
    return number;
}

static inline MargValue marg_number_from_value(long double number) {
    MargValue value;
    memcpy(&value, &number, sizeof(long double));
    return value;
}

#define MARG_NIL                 ((MargValue)(uint64_t)(QNAN | TAG_NIL))
#define MARG_FALSE               ((MargValue)(uint64_t)(QNAN | TAG_FALSE))
#define MARG_TRUE                ((MargValue)(uint64_t)(QNAN | TAG_TRUE))
#define MARG_BOOL(b)             ((b) ? MARG_TRUE : MARG_FALSE)
#define MARG_NUMBER(num)         marg_number_from_value(num)
#define MARG_OBJECT(obj)         (MargValue)(SIGN_BIT | QNAN | (uint64_t)(uintptr_t)(obj))

#define AS_BOOL(value)           ((value) == MARG_TRUE)
#define AS_NUMBER(value)         marg_value_as_number(value)
#define AS_OBJECT(value)         ((MargObject*)(uintptr_t)((value) & ~(SIGN_BIT | QNAN)))
#define AS_STRING(value)         ((MargString*)AS_OBJECT(value))
#define AS_CSTRING(value)        (((MargString*)AS_OBJECT(value))->chars)

#define OBJECT_TYPE(value)       (AS_OBJECT(value)->type)

#define IS_NIL(value)            ((value) == MARG_NIL)
#define IS_BOOL(value)           (((value) | 1) == MARG_TRUE)
#define IS_NUMBER(value)         (((value) & QNAN) != QNAN)
#define IS_OBJECT(value)         (((value) & (QNAN | SIGN_BIT)) == (QNAN | SIGN_BIT))
#define IS_STRING(value)         IS_OBJECT(value) && OBJECT_TYPE(value) == MARG_STRING

/**
 * @brief Formats a marg value using QNAN boxing
 * @param self -> The MargValue represented as a double
 * @return string*
 */
string *marg_value_format(MargValue self);

/**
 * @brief Formats a marg value as a margaret variable
 * @param self 
 * @return string* 
 */
string *marg_value_as_variable(MargValue self);

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
 * @brief Joins 8, 8-bit parats into a single 64 bit integer
 * @param bytes -> The list of bytes
 * @return uint64_t -> The 64 bit result
 */
uint64_t bytes_to_qword(uint8_t *bytes);

#endif
