#ifndef __NAN_TAGGING_H_
#define __NAN_TAGGING_H_

#include <stddef.h> /* size_t */

/** @brief Ex nihilo value */
typedef size_t Value;

/** QNAN = 0b    0     11111111111       1            1       ('0' * 50)
              (sign) (exponent bits) (qnan bit) (qnan fp ind)   (rest) */
#define SIGN_BIT  ((size_t)0x8000000000000000)
#define EXPONENTS ((size_t)0x7ff0000000000000)
#define QNAN      ((size_t)0x0008000000000000)
#define FP_IND    ((size_t)0x0004000000000000)
#define ENCODING  (EXPONENTS | QNAN | FP_IND)

#define QNAN_BOX(pointer) ((Value)(ENCODING | (size_t)(uintptr_t)(pointer)))
#define QNAN_UNBOX(value) ((Object *)(uintptr_t)((value) & ~(ENCODING)))

#define NIL()         (QNAN_BOX(value_nil_new(vm)))
#define FALSE()       (QNAN_BOX(value_false_new(vm)))
#define TRUE()        (QNAN_BOX(value_true_new(vm)))
#define NUMBER(value) (QNAN_BOX(value_number_new(vm, (value))))
#define STRING(value) (QNAN_BOX(value_string_new(vm, string_new((value)))))

#define AS_NIL(value)    ((Nil *)QNAN_UNBOX(value))
#define AS_FALSE(value)  ((False *)QNAN_UNBOX(value))
#define AS_TRUE(value)   ((True *)QNAN_UNBOX(value))
#define AS_NUMBER(value) ((Number *)QNAN_UNBOX(value))
#define AS_STRING(value) ((String *)QNAN_UNBOX(value))
#define AS_OBJECT(value) ((Object *)QNAN_UNBOX(value))

#define IS_NIL(value)    (AS_OBJECT(value)->type == TYPE_NIL)
#define IS_FALSE(value)  (AS_OBJECT(value)->type == TYPE_FALSE)
#define IS_TRUE(value)   (AS_OBJECT(value)->type == TYPE_TRUE)
#define IS_NUMBER(value) (AS_OBJECT(value)->type == TYPE_NUMBER)
#define IS_STRING(value) (AS_OBJECT(value)->type == TYPE_STRING)

#endif
