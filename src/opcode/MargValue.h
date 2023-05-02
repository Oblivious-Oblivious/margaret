#ifndef __MARG_VALUE_H_
#define __MARG_VALUE_H_

#include "../base/string.h"
#include "../base/fnv_1a_64_hash.h"

typedef uint64_t MargValue;

/* QNAN = 0b    0     11111111111       1            1       ('0' * 50)
             (sign) (exponent bits) (qnan bit) (intel value)   (rest)        */
#define QNAN       ((uint64_t)0x7ffc000000000000)
#define SIGN_BIT   ((uint64_t)0x8000000000000000)

#define UNDEFINED_TAG                                1
#define NOT_INTERNED_TAG                             2

#define QNAN_BOX(pointer)                            ((MargValue)(SIGN_BIT | QNAN | (uint64_t)(uintptr_t)(pointer)))
#define QNAN_UNBOX(value)                            ((MargPointer*)(uintptr_t)((value) & ~(SIGN_BIT | QNAN)))

#define MARG_UNDEFINED                               ((MargValue)(uint64_t)(QNAN | SIGN_BIT | UNDEFINED_TAG))
#define MARG_NOT_INTERNED                            ((MargValue)(uint64_t)(QNAN | SIGN_BIT | NOT_INTERNED_TAG))

#define MARG_NIL                                     (QNAN_BOX(marg_nil_new()))
#define MARG_FALSE                                   (QNAN_BOX(marg_false_new()))
#define MARG_TRUE                                    (QNAN_BOX(marg_true_new()))
#define MARG_INTEGER(number)                         (QNAN_BOX(marg_integer_new((number))))
#define MARG_MINUS_1                                 (QNAN_BOX(marg_integer_new(-1)))
#define MARG_0                                       (QNAN_BOX(marg_integer_new(0)))
#define MARG_1                                       (QNAN_BOX(marg_integer_new(1)))
#define MARG_2                                       (QNAN_BOX(marg_integer_new(2)))
#define MARG_FLOAT(number)                           (QNAN_BOX(marg_float_new((number))))
#define MARG_STRING(chars, size)                     (QNAN_BOX(marg_string_new((chars), (size))))
#define MARG_STRING_INTERNED(vm, chars, size)        (QNAN_BOX(table_find_string(&(vm)->interned_strings, (chars), (size), fnv_1a_64_hash((chars), (size)))))
#define MARG_OBJECT(name, name_size)                 (QNAN_BOX(marg_object_new(&vm->global_variables, sizeof(MargObject), (name), (name_size))))

#define AS_NIL(value)                                ((MargNil*)QNAN_UNBOX(value))
#define AS_FALSE(value)                              ((MargFalse*)QNAN_UNBOX(value))
#define AS_TRUE(value)                               ((MargTrue*)QNAN_UNBOX(value))
#define AS_INTEGER(value)                            ((MargInteger*)QNAN_UNBOX(value))
#define AS_FLOAT(value)                              ((MargFloat*)QNAN_UNBOX(value))
#define AS_STRING(value)                             ((MargString*)QNAN_UNBOX(value))
#define AS_OBJECT(value)                             ((MargObject*)QNAN_UNBOX(value))

#define IS_UNDEFINED(value)                          ((value) == MARG_UNDEFINED)
#define IS_NOT_INTERNED(value)                       ((value) == MARG_NOT_INTERNED)

#define IS_NIL(value)                                (QNAN_UNBOX(value)->type == MARG_NIL_TYPE)
#define IS_FALSE(value)                              (QNAN_UNBOX(value)->type == MARG_FALSE_TYPE)
#define IS_TRUE(value)                               (QNAN_UNBOX(value)->type == MARG_TRUE_TYPE)
#define IS_INTEGER(value)                            (QNAN_UNBOX(value)->type == MARG_INTEGER_TYPE)
#define IS_FLOAT(value)                              (QNAN_UNBOX(value)->type == MARG_FLOAT_TYPE)
#define IS_STRING(value)                             (QNAN_UNBOX(value)->type == MARG_STRING_TYPE)

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

#endif
