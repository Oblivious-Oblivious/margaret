#ifndef __MARG_VALUE_H_
#define __MARG_VALUE_H_

#include <string.h> /* memcpy */

#include "../base/boolean.h"
#include "../base/string.h"

#include "MargObject.h"
#include "MargNil.h"
#include "MargFalse.h"
#include "MargTrue.h"
#include "MargString.h"

typedef uint64_t MargValue;

/* QNAN = 0b    0     11111111111       1            1       ('0' * 50)
             (sign) (exponent bits) (qnan bit) (intel value)   (rest)        */
#define QNAN       ((uint64_t)0x7ffc000000000000)
#define SIGN_BIT   ((uint64_t)0x8000000000000000)

static inline double marg_value_to_cdouble(MargValue value) {
    double number;
    memcpy(&number, &value, sizeof(MargValue));
    return number;
}

static inline MargValue cdouble_to_marg_value(double number) {
    MargValue value;
    memcpy(&value, &number, sizeof(double));
    return value;
}

#define MARG_NUMBER(number)                          cdouble_to_marg_value(number)
#define MARG_OBJECT(object)                          (MargValue)(SIGN_BIT | QNAN | (uint64_t)(uintptr_t)(object))
#define MARG_NIL                                     MARG_OBJECT(marg_nil_new())
#define MARG_FALSE                                   MARG_OBJECT(marg_false_new())
#define MARG_TRUE                                    MARG_OBJECT(marg_true_new())
#define MARG_STRING(chars, size)                     MARG_OBJECT(marg_string_new((chars), (size)))
#define MARG_STRING_INTERNED(vm, chars, size, hash)  MARG_OBJECT(marg_hash_find_string(&vm->interned_strings, chars, size, hash));

#define AS_NUMBER(value)                             marg_value_to_cdouble(value)

#define AS_OBJECT(value)                             ((MargObject*)(uintptr_t)((value) & ~(SIGN_BIT | QNAN)))
#define AS_NIL(value)                                ((MargNil*)AS_OBJECT(value))
#define AS_FALSE(value)                              ((MargFalse*)AS_OBJECT(value))
#define AS_TRUE(value)                               ((MargTrue*)AS_OBJECT(value))
#define AS_STRING(value)                             ((MargString*)AS_OBJECT(value))
#define AS_CSTRING(value)                            (((MargString*)AS_OBJECT(value))->chars)

#define OBJECT_TYPE(value)                           (AS_OBJECT(value)->type)

#define IS_NUMBER(value)                             (((value) & QNAN) != QNAN)
#define IS_OBJECT(value)                             (((value) & (QNAN | SIGN_BIT)) == (QNAN | SIGN_BIT))
#define IS_NIL(value)                                IS_OBJECT(value) && OBJECT_TYPE(value) == MARG_NIL_TYPE
#define IS_FALSE(value)                              IS_OBJECT(value) && OBJECT_TYPE(value) == MARG_FALSE_TYPE
#define IS_TRUE(value)                               IS_OBJECT(value) && OBJECT_TYPE(value) == MARG_TRUE_TYPE
#define IS_STRING(value)                             IS_OBJECT(value) && OBJECT_TYPE(value) == MARG_STRING_TYPE

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
