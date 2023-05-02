#ifndef __MARG_VALUE_H_
#define __MARG_VALUE_H_

#include <string.h> /* strcmp */

#include "../base/string.h"
#include "../base/fnv_1a_64_hash.h"

typedef uint64_t MargValue;
typedef struct VM VM;

/* QNAN = 0b    0     11111111111       1            1       ('0' * 50)
             (sign) (exponent bits) (qnan bit) (intel value)   (rest)        */
#define QNAN       ((uint64_t)0x7ffc000000000000)
#define SIGN_BIT   ((uint64_t)0x8000000000000000)

#define UNDEFINED_TAG                                1
#define NOT_INTERNED_TAG                             2

#define QNAN_BOX(pointer)                            ((MargValue)(SIGN_BIT | QNAN | (uint64_t)(uintptr_t)(pointer)))
#define QNAN_UNBOX(value)                            ((MargObject*)(uintptr_t)((value) & ~(SIGN_BIT | QNAN)))

#define MARG_UNDEFINED                               ((MargValue)(uint64_t)(QNAN | SIGN_BIT | UNDEFINED_TAG))
#define MARG_NOT_INTERNED                            ((MargValue)(uint64_t)(QNAN | SIGN_BIT | NOT_INTERNED_TAG))

#define MARG_NIL                                     (QNAN_BOX(marg_nil_new(&vm->global_variables)))
#define MARG_FALSE                                   (QNAN_BOX(marg_false_new(&vm->global_variables)))
#define MARG_TRUE                                    (QNAN_BOX(marg_true_new(&vm->global_variables)))
#define MARG_INTEGER(number)                         (QNAN_BOX(marg_integer_new(&vm->global_variables, (number))))
#define MARG_MINUS_1                                 (QNAN_BOX(marg_integer_new(&vm->global_variables, -1)))
#define MARG_0                                       (QNAN_BOX(marg_integer_new(&vm->global_variables, 0)))
#define MARG_1                                       (QNAN_BOX(marg_integer_new(&vm->global_variables, 1)))
#define MARG_2                                       (QNAN_BOX(marg_integer_new(&vm->global_variables, 2)))
#define MARG_FLOAT(number)                           (QNAN_BOX(marg_float_new(&vm->global_variables, (number))))
#define MARG_STRING(chars, size)                     (QNAN_BOX(marg_string_new(&vm->global_variables, (chars), (size))))
#define MARG_STRING_INTERNED(chars, size)            (QNAN_BOX(table_find_string(&vm->interned_strings, (chars), (size), fnv_1a_64_hash((chars), (size)))))
#define MARG_OBJECT(name, name_size)                 (QNAN_BOX(marg_object_new(&vm->global_variables, sizeof(MargObject), (name), (name_size))))
#define MARG_METHOD(bound_object)                    (QNAN_BOX(marg_method_new(&vm->global_variables, (bound_object))))
#define MARG_PROC(bound_method)                      (QNAN_BOX(marg_proc_new(&vm->global_variables, (bound_method))))

#define AS_NIL(value)                                ((MargNil*)QNAN_UNBOX(value))
#define AS_FALSE(value)                              ((MargFalse*)QNAN_UNBOX(value))
#define AS_TRUE(value)                               ((MargTrue*)QNAN_UNBOX(value))
#define AS_INTEGER(value)                            ((MargInteger*)QNAN_UNBOX(value))
#define AS_FLOAT(value)                              ((MargFloat*)QNAN_UNBOX(value))
#define AS_STRING(value)                             ((MargString*)QNAN_UNBOX(value))
#define AS_OBJECT(value)                             ((MargObject*)QNAN_UNBOX(value))
#define AS_METHOD(value)                             ((MargMethod*)QNAN_UNBOX(value))
#define AS_PROC(value)                               ((MargProc*)QNAN_UNBOX(value))

#define IS_UNDEFINED(value)                          ((value) == MARG_UNDEFINED)
#define IS_NOT_INTERNED(value)                       ((value) == MARG_NOT_INTERNED)

// TODO Eventually remove predefined types
// TODO $nil, $true, $false -> Singleton objects
// TODO Atomic value objects like (integer, float, string) return self on clone
#define IS_NIL(value)                                (!strcmp(QNAN_UNBOX(value)->name, "$nil"))
#define IS_FALSE(value)                              (!strcmp(QNAN_UNBOX(value)->name, "$false"))
#define IS_TRUE(value)                               (!strcmp(QNAN_UNBOX(value)->name, "$true"))
#define IS_INTEGER(value)                            (!strcmp(QNAN_UNBOX(value)->name, "$Integer"))
#define IS_FLOAT(value)                              (!strcmp(QNAN_UNBOX(value)->name, "$Float"))
#define IS_STRING(value)                             (!strcmp(QNAN_UNBOX(value)->name, "$String"))

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
