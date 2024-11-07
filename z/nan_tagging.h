#ifndef __NAN_TAGGING_H_
#define __NAN_TAGGING_H_

#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "object.h"

/** QNAN = 0b    0     11111111111       1            1       ('0' * 50)
              (sign) (exponent bits) (qnan bit) (qnan fp ind)   (rest) */
#define SIGN_BIT  ((size_t)0x8000000000000000)
#define EXPONENTS ((size_t)0x7ff0000000000000)
#define QNAN      ((size_t)0x0008000000000000)
#define FP_IND    ((size_t)0x0004000000000000)
#define ENCODING  (EXPONENTS | QNAN | FP_IND)

#define QNAN_BOX(pointer) ((Value)(ENCODING | (size_t)(uintptr_t)(pointer)))
#define QNAN_UNBOX(value) ((Object *)(uintptr_t)((value) & ~(ENCODING)))

#define UNDEFINED_TAG            (0x00)
#define MARG_UNDEFINED           ((Value)(size_t)(SIGN_BIT | ENCODING | UNDEFINED_TAG))
#define IS_MARG_UNDEFINED(value) ((value) == MARG_UNDEFINED)

#define MARG_NIL()         (table_get(&vm->global_variables, "$nil"))
#define MARG_FALSE()       (table_get(&vm->global_variables, "$false"))
#define MARG_TRUE()        (table_get(&vm->global_variables, "$true"))
#define MARG_NUMBER(value) (QNAN_BOX(value_number_new(vm, (value))))
#define MARG_STRING(value) (QNAN_BOX(value_string_new(vm, string_new((value)))))
#define MARG_METHOD(bound_object, bound_method, message_name) \
  (QNAN_BOX(value_method_new(vm, bound_object, bound_method, message_name)))
#define MARG_OBJECT(proto, name) \
  (QNAN_BOX(value_object_new(vm, sizeof(Object), proto, string_new(name))))

#define AS_MARG_NIL(value)    ((Nil *)QNAN_UNBOX(value))
#define AS_MARG_FALSE(value)  ((False *)QNAN_UNBOX(value))
#define AS_MARG_TRUE(value)   ((True *)QNAN_UNBOX(value))
#define AS_MARG_NUMBER(value) ((Number *)QNAN_UNBOX(value))
#define AS_MARG_STRING(value) ((String *)QNAN_UNBOX(value))
#define AS_MARG_METHOD(value) ((Method *)QNAN_UNBOX(value))
#define AS_MARG_OBJECT(value) ((Object *)QNAN_UNBOX(value))

#define IS_MARG_NIL(value) (string_equals(AS_MARG_OBJECT(value)->name, "$nil"))
#define IS_MARG_FALSE(value) \
  (string_equals(AS_MARG_OBJECT(value)->name, "$false"))
#define IS_MARG_TRUE(value) \
  (string_equals(AS_MARG_OBJECT(value)->name, "$true"))
#define IS_MARG_NUMBER(value) \
  (string_equals(AS_MARG_OBJECT(value)->name, "$Number"))
#define IS_MARG_STRING(value) \
  (string_equals(AS_MARG_OBJECT(value)->name, "$String"))
#define IS_MARG_METHOD(value) \
  (string_equals(AS_MARG_OBJECT(value)->name, "$Method"))

#endif
