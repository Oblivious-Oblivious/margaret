#ifndef __FORMAL_MESSAGES_OPCODES_H_
#define __FORMAL_MESSAGES_OPCODES_H_

#include "../base/marg_string.h"

#define OP_PUSH_NIL                      marg_string_new("PUSH_NIL")
#define OP_PUSH_TRUE                     marg_string_new("PUSH_TRUE")
#define OP_PUSH_FALSE                    marg_string_new("PUSH_FALSE")
#define OP_PUSH_SELF                     marg_string_new("PUSH_SELF")
#define OP_PUSH_SUPER                    marg_string_new("PUSH_SUPER")
#define OP_PUSH_0                        marg_string_new("PUSH_0")
#define OP_PUSH_1                        marg_string_new("PUSH_1")
#define OP_PUSH_MINUS_1                  marg_string_new("PUSH_MINUS_1")
#define OP_PUSH_2                        marg_string_new("PUSH_2")
#define OP_PUSH_INTEGER                  marg_string_new("PUSH_INTEGER")
#define OP_PUSH_FLOAT                    marg_string_new("PUSH_FLOAT")
#define OP_PUSH_CHAR                     marg_string_new("PUSH_CHAR")
#define OP_PUSH_STRING                   marg_string_new("PUSH_STRING")
#define OP_PUSH_VARIABLE                 marg_string_new("PUSH_VARIABLE")
#define OP_PUSH_INSTANCE                 marg_string_new("PUSH_INSTANCE")
#define OP_PUSH_TENSOR                   marg_string_new("PUSH_TENSOR")
#define OP_PUSH_TUPLE                    marg_string_new("PUSH_TUPLE")
#define OP_PUSH_BITSTRING                marg_string_new("PUSH_BITSTRING")
#define OP_PUSH_HASH                     marg_string_new("PUSH_HASH")

#define OP_PUSH_ANY_OBJECT               marg_string_new("PUSH_ANY_OBJECT")
#define OP_PUSH_METHOD_PARAMETER         marg_string_new("PUSH_METHOD_PARAMETER")

#define OP_START_PUSH_PROC               marg_string_new("START_PUSH_PROC")
#define OP_END_PUSH_PROC                 marg_string_new("END_PUSH_PROC")
#define OP_START_PUSH_C_FUNCTION         marg_string_new("START_PUSH_C_FUNCTION")
#define OP_END_PUSH_C_FUNCTION           marg_string_new("END_PUSH_C_FUNCTION")

#define OP_POP                           marg_string_new("POP")

#define OP_STORE                         marg_string_new("STORE")
#define OP_STORE_INSTANCE                marg_string_new("STORE_INSTANCE")

#define OP_UNARY                         marg_string_new("UNARY")
#define OP_METHOD_UNARY                  marg_string_new("METHOD_UNARY")

#define OP_BINARY                        marg_string_new("BINARY")
#define OP_METHOD_BINARY                 marg_string_new("METHOD_BINARY")

#define OP_KEYWORD                       marg_string_new("KEYWORD")
#define OP_METHOD_KEYWORD                marg_string_new("METHOD_KEYWORD")

#endif
