#ifndef __MARG_VALUE_H_
#define __MARG_VALUE_H_

#include <string.h> /* strcmp */

#include "../base/string.h"
#include "../base/fnv_1a_64_hash.h"

typedef uint64_t MargValue;

/* QNAN = 0b    0     11111111111       1            1       ('0' * 50)
             (sign) (exponent bits) (qnan bit) (qnan fp ind)   (rest)        */
#define SIGN_BIT   ((uint64_t)0x8000000000000000)
#define EXPONENTS  ((uint64_t)0x7ff0000000000000)
#define QNAN       ((uint64_t)0x0008000000000000)
#define FP_IND     ((uint64_t)0x0004000000000000)
#define ENCODING   (EXPONENTS | QNAN | FP_IND)

#define QNAN_BOX(pointer)                            ((MargValue)(ENCODING | (uint64_t)(uintptr_t)(pointer)))
#define QNAN_UNBOX(value)                            ((MargObject*)(uintptr_t)((value) & ~(ENCODING)))

// sign = 1
// rest =  ('0' * 48)    0       0
//          (Pointer) (tag1)  (tag0)
// Allows for 4 distinct values (00, 01, 10, 11) that are not objects
#define UNDEFINED_TAG                                0x00
#define MARG_UNDEFINED                               ((MargValue)(uint64_t)(SIGN_BIT | ENCODING | UNDEFINED_TAG))
#define IS_UNDEFINED(value)                          ((value) == MARG_UNDEFINED)

#define NOT_INTERNED_TAG                             0x01
#define MARG_NOT_INTERNED                            ((MargValue)(uint64_t)(SIGN_BIT | ENCODING | NOT_INTERNED_TAG))
#define IS_NOT_INTERNED(value)                       ((value) == MARG_NOT_INTERNED)

// Objects
#define MARG_NIL                                     (table_get(&vm->global_variables, MARG_STRING("$nil")))
#define MARG_FALSE                                   (table_get(&vm->global_variables, MARG_STRING("$false")))
#define MARG_TRUE                                    (table_get(&vm->global_variables, MARG_STRING("$true")))
#define MARG_INTEGER(number)                         (QNAN_BOX(marg_integer_new(vm, (number))))
#define MARG_MINUS_1                                 (QNAN_BOX(marg_integer_new(vm, -1)))
#define MARG_0                                       (QNAN_BOX(marg_integer_new(vm, 0)))
#define MARG_1                                       (QNAN_BOX(marg_integer_new(vm, 1)))
#define MARG_2                                       (QNAN_BOX(marg_integer_new(vm, 2)))
#define MARG_FLOAT(number)                           (QNAN_BOX(marg_float_new(vm, (number))))
#define MARG_STRING(chars)                           (QNAN_BOX(marg_string_new(vm, (chars))))
#define MARG_STRING_INTERNED(chars, size)            (QNAN_BOX(table_find_string(&vm->interned_strings, (chars), (size), fnv_1a_64_hash((chars), (size)))))
#define MARG_TENSOR(initial_alloced)                 (QNAN_BOX(marg_tensor_new(vm, (initial_alloced))))
#define MARG_HASH                                    (QNAN_BOX(marg_hash_new(vm)))
#define MARG_OBJECT(name)                            (QNAN_BOX(marg_object_new(vm, sizeof(MargObject), (name))))
#define MARG_METHOD(bound_object, message_name)      (QNAN_BOX(marg_method_new(vm, (bound_object), (message_name))))
#define MARG_PROC(bound_method)                      (QNAN_BOX(marg_proc_new(vm, (bound_method))))

#define AS_NIL(value)                                ((MargNil*)QNAN_UNBOX(value))
#define AS_FALSE(value)                              ((MargFalse*)QNAN_UNBOX(value))
#define AS_TRUE(value)                               ((MargTrue*)QNAN_UNBOX(value))
#define AS_INTEGER(value)                            ((MargInteger*)QNAN_UNBOX(value))
#define AS_FLOAT(value)                              ((MargFloat*)QNAN_UNBOX(value))
#define AS_STRING(value)                             ((MargString*)QNAN_UNBOX(value))
#define AS_TENSOR(value)                             ((MargTensor*)QNAN_UNBOX(value))
#define AS_HASH(value)                               ((MargHash*)QNAN_UNBOX(value))
#define AS_OBJECT(value)                             ((MargObject*)QNAN_UNBOX(value))
#define AS_METHOD(value)                             ((MargMethod*)QNAN_UNBOX(value))
#define AS_PROC(value)                               ((MargProc*)QNAN_UNBOX(value))

// TODO Eventually remove predefined types
// TODO $nil, $true, $false -> Singleton objects
#define IS_NIL(value)                                (!strcmp(QNAN_UNBOX(value)->name, "$nil"))
#define IS_FALSE(value)                              (!strcmp(QNAN_UNBOX(value)->name, "$false"))
#define IS_TRUE(value)                               (!strcmp(QNAN_UNBOX(value)->name, "$true"))
#define IS_INTEGER(value)                            (!strcmp(QNAN_UNBOX(value)->name, "$Integer"))
#define IS_FLOAT(value)                              (!strcmp(QNAN_UNBOX(value)->name, "$Float"))
#define IS_STRING(value)                             (!strcmp(QNAN_UNBOX(value)->name, "$String"))
#define IS_TENSOR(value)                             (!strcmp(QNAN_UNBOX(value)->name, "$Tensor"))
#define IS_HASH(value)                               (!strcmp(QNAN_UNBOX(value)->name, "$Hash"))
#define IS_OBJECT(value)                             (!strcmp(QNAN_UNBOX(value)->name, "$Object"))
#define IS_METHOD(value)                             (!strcmp(QNAN_UNBOX(value)->name, "$Method"))
#define IS_PROC(value)                               (!strcmp(QNAN_UNBOX(value)->name, "$Proc"))

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
