#ifndef __NAN_TAGGING_H_
#define __NAN_TAGGING_H_

/** QNAN = 0b    0     11111111111       1            1       ('0' * 50)
              (sign) (exponent bits) (qnan bit) (qnan fp ind)   (rest) */
#define SIGN_BIT  ((size_t)0x8000000000000000)
#define EXPONENTS ((size_t)0x7ff0000000000000)
#define QNAN      ((size_t)0x0008000000000000)
#define FP_IND    ((size_t)0x0004000000000000)
#define ENCODING  (EXPONENTS | QNAN | FP_IND)

#define QNAN_BOX(pointer) ((MargValue)(ENCODING | (size_t)(uintptr_t)(pointer)))
#define QNAN_UNBOX(value) ((MargObject *)(uintptr_t)((value) & ~(ENCODING)))

#define UNDEFINED_TAG (0x00)
#define MARG_UNDEFINED \
  ((MargValue)(size_t)(SIGN_BIT | ENCODING | UNDEFINED_TAG))
#define IS_UNDEFINED(value) ((value) == MARG_UNDEFINED)

#define MARG_NIL()         G("$nil")
#define MARG_FALSE()       G("$false")
#define MARG_TRUE()        G("$true")
#define MARG_NUMBER(value) (QNAN_BOX(value_number_new(vm, (value))))
#define MARG_STRING(value) (QNAN_BOX(value_string_new(vm, string_new((value)))))
#define MARG_LABEL(name)   (QNAN_BOX(value_label_new(vm, name)))
#define MARG_METHOD(bound_object, bound_method, message_name) \
  (QNAN_BOX(value_method_new(vm, bound_object, bound_method, message_name)))
#define MARG_PRIMITIVE(name, prim) \
  (QNAN_BOX(value_primitive_new(vm, name, prim)))
#define MARG_OBJECT(proto, name) \
  (QNAN_BOX(value_object_new(vm, sizeof(MargObject), proto, string_new(name))))

#define AS_NIL(value)       ((MargNil *)QNAN_UNBOX(value))
#define AS_FALSE(value)     ((MargFalse *)QNAN_UNBOX(value))
#define AS_TRUE(value)      ((MargTrue *)QNAN_UNBOX(value))
#define AS_NUMBER(value)    ((MargNumber *)QNAN_UNBOX(value))
#define AS_STRING(value)    ((MargString *)QNAN_UNBOX(value))
#define AS_LABEL(value)     ((MargLabel *)QNAN_UNBOX(value))
#define AS_METHOD(value)    ((MargMethod *)QNAN_UNBOX(value))
#define AS_PRIMITIVE(value) ((MargPrimitive *)QNAN_UNBOX(value))
#define AS_OBJECT(value)    ((MargObject *)QNAN_UNBOX(value))

#define IS_NIL(value) \
  (!IS_UNDEFINED(value) && string_equals(AS_OBJECT(value)->name, "$nil"))
#define IS_FALSE(value) \
  (!IS_UNDEFINED(value) && string_equals(AS_OBJECT(value)->name, "$false"))
#define IS_TRUE(value) \
  (!IS_UNDEFINED(value) && string_equals(AS_OBJECT(value)->name, "$true"))
#define IS_NUMBER(value)                                                  \
  (!IS_UNDEFINED(value) && AS_OBJECT(value) && AS_OBJECT(value)->proto && \
   string_equals(AS_OBJECT(value)->proto->name, "$Number"))
#define IS_STRING(value)                                                  \
  (!IS_UNDEFINED(value) && AS_OBJECT(value) && AS_OBJECT(value)->proto && \
   string_equals(AS_OBJECT(value)->proto->name, "$String"))
#define IS_LABEL(value)                                                   \
  (!IS_UNDEFINED(value) && AS_OBJECT(value) && AS_OBJECT(value)->proto && \
   string_equals(AS_OBJECT(value)->proto->name, "$Label"))
#define IS_METHOD(value)                                                  \
  (!IS_UNDEFINED(value) && AS_OBJECT(value) && AS_OBJECT(value)->proto && \
   string_equals(AS_OBJECT(value)->proto->name, "$Method"))
#define IS_PRIMITIVE(value) \
  (!IS_UNDEFINED(value) &&  \
   string_equals(AS_OBJECT(value)->proto->name, "Primitive"))

#endif
