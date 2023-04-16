#ifndef __FORMAL_MESSAGES_OPCODES_H_
#define __FORMAL_MESSAGES_OPCODES_H_

#include "../base/marg_string.h"

#define OP_NIL               marg_string_new("NIL")
#define OP_TRUE              marg_string_new("TRUE")
#define OP_FALSE             marg_string_new("FALSE")
#define OP_SELF              marg_string_new("SELF")
#define OP_SUPER             marg_string_new("SUPER")
#define OP_0                 marg_string_new("0")
#define OP_1                 marg_string_new("1")
#define OP_MINUS_1           marg_string_new("MINUS_1")
#define OP_2                 marg_string_new("2")
#define OP_INTEGER           marg_string_new("INTEGER")
#define OP_FLOAT             marg_string_new("FLOAT")
#define OP_CHAR              marg_string_new("CHAR")
#define OP_STRING            marg_string_new("STRING")
#define OP_VARIABLE          marg_string_new("VARIABLE")
#define OP_INSTANCE          marg_string_new("INSTANCE")
#define OP_TENSOR            marg_string_new("TENSOR")
#define OP_TUPLE             marg_string_new("TUPLE")
#define OP_BITSTRING         marg_string_new("BITSTRING")
#define OP_HASH              marg_string_new("HASH")

#define OP_ANY_OBJECT        marg_string_new("ANY_OBJECT")
#define OP_METHOD_PARAMETER  marg_string_new("METHOD_PARAMETER")

#define OP_START_PROC        marg_string_new("START_PROC")
#define OP_END_PROC          marg_string_new("END_PROC")
#define OP_START_C_FUNCTION  marg_string_new("START_C_FUNCTION")
#define OP_END_C_FUNCTION    marg_string_new("END_C_FUNCTION")

// #define OP_POP               marg_string_new("POP")

#define OP_STORE             marg_string_new("STORE")
#define OP_STORE_INSTANCE    marg_string_new("STORE_INSTANCE")

#define OP_UNARY             marg_string_new("UNARY")
#define OP_METHOD_UNARY      marg_string_new("METHOD_UNARY")

#define OP_BINARY            marg_string_new("BINARY")
#define OP_METHOD_BINARY     marg_string_new("METHOD_BINARY")

#define OP_KEYWORD           marg_string_new("KEYWORD")
#define OP_METHOD_KEYWORD    marg_string_new("METHOD_KEYWORD")

#endif
