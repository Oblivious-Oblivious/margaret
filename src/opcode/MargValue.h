#ifndef __MARG_VALUE_H_
#define __MARG_VALUE_H_

#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "MargObject.h"
#include "MargValueType.h"

/** QNAN = 0b    0     11111111111       1            1       ('0' * 50)
              (sign) (exponent bits) (qnan bit) (qnan fp ind)   (rest)        */
#define SIGN_BIT  ((size_t)0x8000000000000000)
#define EXPONENTS ((size_t)0x7ff0000000000000)
#define QNAN      ((size_t)0x0008000000000000)
#define FP_IND    ((size_t)0x0004000000000000)
#define ENCODING  (EXPONENTS | QNAN | FP_IND)

#define QNAN_BOX(pointer) ((MargValue)(ENCODING | (size_t)(uintptr_t)(pointer)))
#define QNAN_UNBOX(value) ((MargObject *)(uintptr_t)((value) & ~(ENCODING)))

/**
 * sign = 1
 * rest =  ('0' * 48)    0       0
 *          (Pointer) (tag1)  (tag0)
 * Allows for 4 distinct values (00, 01, 10, 11) that are not objects
 */
#define UNDEFINED_TAG (0x00)
#define MARG_UNDEFINED \
  ((MargValue)(size_t)(SIGN_BIT | ENCODING | UNDEFINED_TAG))
#define IS_UNDEFINED(value) ((value) == MARG_UNDEFINED)

#define MARG_NIL            (G("$nil"))
#define MARG_FALSE          (G("$false"))
#define MARG_TRUE           (G("$true"))
#define MARG_INTEGER(value) (QNAN_BOX(marg_integer_init(vm, (value))))
#define MARG_FLOAT(value)   (QNAN_BOX(marg_float_init(vm, (value))))
#define MARG_LABEL(value)   (QNAN_BOX(marg_label_init(vm, (value))))
#define MARG_SYMBOL(value)  (QNAN_BOX(marg_symbol_init(vm, (value))))
#define MARG_STRING(value)  (QNAN_BOX(marg_string_init(vm, value)))
#define MARG_TENSOR()       (QNAN_BOX(marg_tensor_init(vm)))
#define MARG_TUPLE()        (QNAN_BOX(marg_tuple_init(vm)))
#define MARG_TABLE()        (QNAN_BOX(marg_table_init(vm)))
#define MARG_BITSTRING()    (QNAN_BOX(marg_bitstring_init(vm)))
#define MARG_METHOD(bound_object, bound_method, message_name)            \
  (QNAN_BOX(                                                             \
    marg_method_init(vm, (bound_object), (bound_method), (message_name)) \
  ))
#define MARG_PRIMITIVE(name, prim) \
  (QNAN_BOX(marg_primitive_init(vm, (name), (prim))))
#define MARG_VARIABLE(name, value, type) \
  (QNAN_BOX(marg_variable_init(vm, (name), (value), (type))))
#define MARG_OBJECT(proto, name) \
  (QNAN_BOX(marg_object_init(vm, sizeof(MargObject), proto, string_new(name))))

#define AS_NIL(value)       ((MargNil *)QNAN_UNBOX(value))
#define AS_FALSE(value)     ((MargFalse *)QNAN_UNBOX(value))
#define AS_TRUE(value)      ((MargTrue *)QNAN_UNBOX(value))
#define AS_INTEGER(value)   ((MargInteger *)QNAN_UNBOX(value))
#define AS_FLOAT(value)     ((MargFloat *)QNAN_UNBOX(value))
#define AS_LABEL(value)     ((MargLabel *)QNAN_UNBOX(value))
#define AS_STRING(value)    ((MargString *)QNAN_UNBOX(value))
#define AS_SYMBOL(value)    ((MargSymbol *)QNAN_UNBOX(value))
#define AS_TENSOR(value)    ((MargTensor *)QNAN_UNBOX(value))
#define AS_TUPLE(value)     ((MargTuple *)QNAN_UNBOX(value))
#define AS_TABLE(value)     ((MargTable *)QNAN_UNBOX(value))
#define AS_BITSTRING(value) ((MargBitstring *)QNAN_UNBOX(value))
#define AS_METHOD(value)    ((MargMethod *)QNAN_UNBOX(value))
#define AS_PRIMITIVE(value) ((MargPrimitive *)QNAN_UNBOX(value))
#define AS_VARIABLE(value)  ((MargVariable *)QNAN_UNBOX(value))
#define AS_OBJECT(value)    ((MargObject *)QNAN_UNBOX(value))

#define IS_MARGARET(value) \
  (!IS_UNDEFINED(value) && AS_OBJECT(value)->name_hash == 4789181502764186150u)
#define IS_NIL(value) \
  (!IS_UNDEFINED(value) && AS_OBJECT(value)->name_hash == 18110527515211709592u)
#define IS_FALSE(value) \
  (!IS_UNDEFINED(value) && AS_OBJECT(value)->name_hash == 11637356562211384420u)
#define IS_TRUE(value) \
  (!IS_UNDEFINED(value) && AS_OBJECT(value)->name_hash == 4514072750546140253u)
#define IS_INTEGER(value)  \
  (!IS_UNDEFINED(value) && \
   AS_OBJECT(value)->proto->name_hash == 14144276635994577966u)
#define IS_FLOAT(value)    \
  (!IS_UNDEFINED(value) && \
   AS_OBJECT(value)->proto->name_hash == 2469771440552657146u)
#define IS_LABEL(value)    \
  (!IS_UNDEFINED(value) && \
   AS_OBJECT(value)->proto->name_hash == 8423524640085775522u)
#define IS_SYMBOL(value)   \
  (!IS_UNDEFINED(value) && \
   AS_OBJECT(value)->proto->name_hash == 1818524332596311193u)
#define IS_STRING(value)   \
  (!IS_UNDEFINED(value) && \
   AS_OBJECT(value)->proto->name_hash == 1247353075981998467u)
#define IS_TENSOR(value)   \
  (!IS_UNDEFINED(value) && \
   AS_OBJECT(value)->proto->name_hash == 15050516650501159152u)
#define IS_TUPLE(value)    \
  (!IS_UNDEFINED(value) && \
   AS_OBJECT(value)->proto->name_hash == 4125614011579643586u)
#define IS_TABLE(value)    \
  (!IS_UNDEFINED(value) && \
   AS_OBJECT(value)->proto->name_hash == 15861330017839918915u)
#define IS_BITSTRING(value) \
  (!IS_UNDEFINED(value) &&  \
   AS_OBJECT(value)->proto->name_hash == 9672314682457977727u)
#define IS_METHOD(value)   \
  (!IS_UNDEFINED(value) && \
   AS_OBJECT(value)->proto->name_hash == 15255530546787031708u)
#define IS_PRIMITIVE(value) \
  (!IS_UNDEFINED(value) &&  \
   AS_OBJECT(value)->proto->name_hash == 5694381430705705196u)
#define IS_VARIABLE(value) \
  (!IS_UNDEFINED(value) && \
   AS_OBJECT(value)->proto->name_hash == 14314061641483853064u)

/**
 * @brief Formats a marg value using QNAN boxing
 * @param vm -> Current VM
 * @param self -> The MargValue represented as a double
 * @return string*
 */
char *marg_value_format(VM *vm, MargValue self);

#endif
