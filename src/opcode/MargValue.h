#ifndef __MARG_VALUE_H_
#define __MARG_VALUE_H_

#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "MargFloat.h"
#include "MargHash.h"
#include "MargInteger.h"
#include "MargMethod.h"
#include "MargObject.h"
#include "MargProc.h"
#include "MargString.h"
#include "MargTensor.h"
#include "MargValueType.h"

/* QNAN = 0b    0     11111111111       1            1       ('0' * 50)
             (sign) (exponent bits) (qnan bit) (qnan fp ind)   (rest)        */
#define SIGN_BIT  ((uint64_t)0x8000000000000000)
#define EXPONENTS ((uint64_t)0x7ff0000000000000)
#define QNAN      ((uint64_t)0x0008000000000000)
#define FP_IND    ((uint64_t)0x0004000000000000)
#define ENCODING  (EXPONENTS | QNAN | FP_IND)

#define QNAN_BOX(pointer) \
  ((MargValue)(ENCODING | (uint64_t)(uintptr_t)(pointer)))
#define QNAN_UNBOX(value) ((MargObject *)(uintptr_t)((value) & ~(ENCODING)))

// sign = 1
// rest =  ('0' * 48)    0       0
//          (Pointer) (tag1)  (tag0)
// Allows for 4 distinct values (00, 01, 10, 11) that are not objects
#define UNDEFINED_TAG 0x00
#define MARG_UNDEFINED \
  ((MargValue)(uint64_t)(SIGN_BIT | ENCODING | UNDEFINED_TAG))
#define IS_UNDEFINED(value) ((value) == MARG_UNDEFINED)

#define NOT_INTERNED_TAG 0x01
#define MARG_NOT_INTERNED \
  ((MargValue)(uint64_t)(SIGN_BIT | ENCODING | NOT_INTERNED_TAG))
#define IS_NOT_INTERNED(value) ((value) == MARG_NOT_INTERNED)

#define MARG_NIL             (table_get(&vm->global_variables, "$nil"))
#define MARG_FALSE           (table_get(&vm->global_variables, "$false"))
#define MARG_TRUE            (table_get(&vm->global_variables, "$true"))
#define MARG_INTEGER(number) (QNAN_BOX(marg_integer_new(vm, (number))))
#define MARG_FLOAT(number)   (QNAN_BOX(marg_float_new(vm, (number))))
#define MARG_STRING(chars)   (QNAN_BOX(marg_string_new(vm, string_new(chars))))
#define MARG_STRING_INTERNED(chars) \
  (QNAN_BOX(table_get(&vm->interned_strings, (chars))))
#define MARG_TENSOR(initial_alloced) \
  (QNAN_BOX(marg_tensor_new(vm, (initial_alloced))))
#define MARG_HASH (QNAN_BOX(marg_hash_new(vm)))
#define MARG_OBJECT(name) \
  (QNAN_BOX(marg_object_new(vm, sizeof(MargObject), string_new(name))))
#define MARG_METHOD(bound_object, message_name) \
  (QNAN_BOX(marg_method_new(vm, (bound_object), (message_name))))
#define MARG_PROC(bound_method) (QNAN_BOX(marg_proc_new(vm, (bound_method))))

#define AS_INTEGER(value) ((MargInteger *)QNAN_UNBOX(value))
#define AS_FLOAT(value)   ((MargFloat *)QNAN_UNBOX(value))
#define AS_STRING(value)  ((MargString *)QNAN_UNBOX(value))
#define AS_TENSOR(value)  ((MargTensor *)QNAN_UNBOX(value))
#define AS_HASH(value)    ((MargHash *)QNAN_UNBOX(value))
#define AS_OBJECT(value)  ((MargObject *)QNAN_UNBOX(value))
#define AS_METHOD(value)  ((MargMethod *)QNAN_UNBOX(value))
#define AS_PROC(value)    ((MargProc *)QNAN_UNBOX(value))

#define IS_NIL(value) \
  (!IS_UNDEFINED((value)) && (string_equals(QNAN_UNBOX(value)->name, "$nil")))
#define IS_FALSE(value) \
  (!IS_UNDEFINED((value)) && (string_equals(QNAN_UNBOX(value)->name, "$false")))
#define IS_TRUE(value) \
  (!IS_UNDEFINED((value)) && (string_equals(QNAN_UNBOX(value)->name, "$true")))
#define IS_INTEGER(value)    \
  (!IS_UNDEFINED((value)) && \
   (string_equals(QNAN_UNBOX(value)->name, "$Integer")))
#define IS_FLOAT(value) \
  (!IS_UNDEFINED((value)) && (string_equals(QNAN_UNBOX(value)->name, "$Float")))
#define IS_STRING(value)     \
  (!IS_UNDEFINED((value)) && \
   (string_equals(QNAN_UNBOX(value)->name, "$String")))
#define IS_TENSOR(value)     \
  (!IS_UNDEFINED((value)) && \
   (string_equals(QNAN_UNBOX(value)->name, "$Tensor")))
#define IS_HASH(value) \
  (!IS_UNDEFINED((value)) && (string_equals(QNAN_UNBOX(value)->name, "$Hash")))
#define IS_OBJECT(value)     \
  (!IS_UNDEFINED((value)) && \
   (string_equals(QNAN_UNBOX(value)->name, "$Object")))
#define IS_METHOD(value)     \
  (!IS_UNDEFINED((value)) && \
   (string_equals(QNAN_UNBOX(value)->name, "$Method")))
#define IS_PROC(value) \
  (!IS_UNDEFINED((value)) && (string_equals(QNAN_UNBOX(value)->name, "$Proc")))

#define IS_NIL_CLONE(value)   (!IS_UNDEFINED((value)) && IS_NIL((value)))
#define IS_FALSE_CLONE(value) (!IS_UNDEFINED((value)) && IS_FALSE((value)))
#define IS_TRUE_CLONE(value)  (!IS_UNDEFINED((value)) && IS_TRUE((value)))
#define IS_INTEGER_CLONE(value) \
  (!IS_UNDEFINED((value)) &&    \
   (string_equals(QNAN_UNBOX(value)->name, "$IntegerClone")))
#define IS_FLOAT_CLONE(value) \
  (!IS_UNDEFINED((value)) &&  \
   (string_equals(QNAN_UNBOX(value)->name, "$FloatClone")))
#define IS_STRING_CLONE(value) \
  (!IS_UNDEFINED((value)) &&   \
   (string_equals(QNAN_UNBOX(value)->name, "$StringClone")))
#define IS_TENSOR_CLONE(value) \
  (!IS_UNDEFINED((value)) &&   \
   (string_equals(QNAN_UNBOX(value)->name, "$TensorClone")))
#define IS_HASH_CLONE(value) \
  (!IS_UNDEFINED((value)) && \
   (string_equals(QNAN_UNBOX(value)->name, "$HashClone")))
#define IS_OBJECT_CLONE(value) \
  (!IS_UNDEFINED((value)) &&   \
   (string_equals(QNAN_UNBOX(value)->name, "$ObjectClone")))
#define IS_METHOD_CLONE(value) \
  (!IS_UNDEFINED((value)) &&   \
   (string_equals(QNAN_UNBOX(value)->name, "$MethodClone")))
#define IS_PROC_CLONE(value) \
  (!IS_UNDEFINED((value)) && \
   (string_equals(QNAN_UNBOX(value)->name, "$ProcClone")))

/**
 * @brief Formats a marg value using QNAN boxing
 * @param self -> The MargValue represented as a double
 * @return string*
 */
char *marg_value_format(MargValue self);

/**
 * @brief Formats a marg value as a margaret variable
 * @param self
 * @return string*
 */
char *marg_value_as_variable(MargValue self);

#endif
