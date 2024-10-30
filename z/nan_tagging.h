#ifndef __NAN_TAGGING_H_
#define __NAN_TAGGING_H_

#include "../libs/EmeraldsString/export/EmeraldsString.h"

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

#define MARG_NIL()         (QNAN_BOX(value_nil_new(vm)))
#define MARG_FALSE()       (QNAN_BOX(value_false_new(vm)))
#define MARG_TRUE()        (QNAN_BOX(value_true_new(vm)))
#define MARG_NUMBER(value) (QNAN_BOX(value_number_new(vm, (value))))
#define MARG_STRING(value) (QNAN_BOX(value_string_new(vm, string_new((value)))))

#define AS_MARG_NIL(value)    ((Nil *)QNAN_UNBOX(value))
#define AS_MARG_FALSE(value)  ((False *)QNAN_UNBOX(value))
#define AS_MARG_TRUE(value)   ((True *)QNAN_UNBOX(value))
#define AS_MARG_NUMBER(value) ((Number *)QNAN_UNBOX(value))
#define AS_MARG_STRING(value) ((String *)QNAN_UNBOX(value))
#define AS_MARG_OBJECT(value) ((Object *)QNAN_UNBOX(value))

#define IS_MARG_NIL(value)    (AS_MARG_OBJECT(value)->type == TYPE_MARG_NIL)
#define IS_MARG_FALSE(value)  (AS_MARG_OBJECT(value)->type == TYPE_MARG_FALSE)
#define IS_MARG_TRUE(value)   (AS_MARG_OBJECT(value)->type == TYPE_MARG_TRUE)
#define IS_MARG_NUMBER(value) (AS_MARG_OBJECT(value)->type == TYPE_MARG_NUMBER)
#define IS_MARG_STRING(value) (AS_MARG_OBJECT(value)->type == TYPE_MARG_STRING)

#endif
