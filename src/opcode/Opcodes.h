#ifndef __OPCODES_H_
#define __OPCODES_H_

#include "../base/marg_string.h"

// ------ Formal Messages Opcodes ------
#define OP_NIL               marg_string_new("NIL")
#define OP_TRUE              marg_string_new("TRUE")
#define OP_FALSE             marg_string_new("FALSE")

#define OP_SELF              marg_string_new("SELF")
#define OP_SUPER             marg_string_new("SUPER")

#define OP_0                 marg_string_new("0")
#define OP_1                 marg_string_new("1")
#define OP_MINUS_1           marg_string_new("MINUS_1")
#define OP_2                 marg_string_new("2")

#define OP_VARIABLE          marg_string_new("VARIABLE")
#define OP_INSTANCE          marg_string_new("INSTANCE")

#define OP_INTEGER           marg_string_new("INTEGER")
#define OP_FLOAT             marg_string_new("FLOAT")
#define OP_CHAR              marg_string_new("CHAR")
#define OP_STRING            marg_string_new("STRING")
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

#define OP_STORE             marg_string_new("STORE")
#define OP_STORE_INSTANCE    marg_string_new("STORE_INSTANCE")

#define OP_METHOD_UNARY      marg_string_new("METHOD_UNARY")
#define OP_METHOD_BINARY     marg_string_new("METHOD_BINARY")
#define OP_METHOD_KEYWORD    marg_string_new("METHOD_KEYWORD")

#define OP_UNARY             marg_string_new("UNARY")
#define OP_BINARY            marg_string_new("BINARY")
#define OP_KEYWORD           marg_string_new("KEYWORD")

// ------ Emmited Opcodes ------
// #define OP_DECLARE_VARIABLE              marg_string_new("DECLARE_VARIABLE")
// #define OP_GENERATE_IDENTIFIER_POSITION  marg_string_new("GENERATE_IDENTIFIER_POSITION")
// #define OP_ADD_VARIABLE_TO_VECTOR        marg_string_new("ADD_VARIABLE_TO_VECTOR")
// #define OP_MAKE_VARIABLE                 marg_string_new("MAKE_VARIABLE")
// #define OP_COMPILER_NEW                  marg_string_new("COMPILER_NEW")
// #define OP_SCOPE_BEGIN                   marg_string_new("SCOPE_BEGIN")
// #define OP_SCOPE_END                     marg_string_new("SCOPE_END")

// #define OP_NIL                           marg_string_new("NIL")
// #define OP_TRUE                          marg_string_new("TRUE")
// #define OP_FALSE                         marg_string_new("FALSE")
// #define OP_SELF                          marg_string_new("SELF")
// #define OP_SUPER                         marg_string_new("SUPER")
// #define OP_0                             marg_string_new("0")
// #define OP_1                             marg_string_new("1")
// #define OP_MINUS_1                       marg_string_new("MINUS_1")
// #define OP_2                             marg_string_new("2")
// #define OP_INTEGER                       marg_string_new("INTEGER")
// #define OP_FLOAT                         marg_string_new("FLOAT")
// #define OP_CHAR                          marg_string_new("CHAR")
// #define OP_STRING                        marg_string_new("STRING")
// #define OP_VARIABLE                      marg_string_new("VARIABLE")
// #define OP_INSTANCE                      marg_string_new("INSTANCE")
// #define OP_TENSOR                        marg_string_new("TENSOR")
// #define OP_TUPLE                         marg_string_new("TUPLE")
// #define OP_BITSTRING                     marg_string_new("BITSTRING")
// #define OP_HASH                          marg_string_new("HASH")

// #define OP_ANY_OBJECT                    marg_string_new("ANY_OBJECT")
// #define OP_METHOD_PARAMETER              marg_string_new("METHOD_PARAMETER")

// #define OP_START_PROC                    marg_string_new("START_PROC")
// #define OP_END_PROC                      marg_string_new("END_PROC")
// #define OP_START_C_FUNCTION              marg_string_new("START_C_FUNCTION")
// #define OP_END_C_FUNCTION                marg_string_new("END_C_FUNCTION")

// #define OP_POP                           marg_string_new("POP")
// #define OP_POPN                          marg_string_new("POPN")

// #define OP_STORE                         marg_string_new("STORE")
// #define OP_STORE_LOCAL                   marg_string_new("STORE_LOCAL")
// #define OP_STORE_GLOBAL                  marg_string_new("STORE_GLOBAL")
// #define OP_STORE_UPVALUE                 marg_string_new("STORE_UPVALUE")

// #define OP_LABEL                         marg_string_new("LABEL")

// #define OP_JUMP                          marg_string_new("JUMP")
// #define OP_JUMP_IF_ZERO                  marg_string_new("JUMP_IF_ZERO")
// #define OP_JUMP_IF_NOT_ZERO              marg_string_new("JUMP_IF_NOT_ZERO")
// #define OP_JUMP_IF_TRUE                  marg_string_new("JUMP_IF_TRUE")
// #define OP_JUMP_IF_FALSE                 marg_string_new("JUMP_IF_FALSE")

// #define OP_LONGJUMP                      marg_string_new("LONGJUMP")
// #define OP_LONGJUMP_IF_ZERO              marg_string_new("LONGJUMP_IF_ZERO")
// #define OP_LONGJUMP_IF_NOT_ZERO          marg_string_new("LONGJUMP_IF_NOT_ZERO")
// #define OP_LONGJUMP_IF_TRUE              marg_string_new("LONGJUMP_IF_TRUE")
// #define OP_LONGJUMP_IF_FALSE             marg_string_new("LONGJUMP_IF_FALSE")

// #define OP_RETURN                        marg_string_new("RETURN")
// #define OP_RETURN_NIL                    marg_string_new("RETURN_NIL")
// #define OP_RETURN_TRUE                   marg_string_new("RETURN_TRUE")
// #define OP_RETURN_FALSE                  marg_string_new("RETURN_FALSE")
// #define OP_RETURN_STACK_TOP              marg_string_new("RETURN_STACK_TOP")

// ... most used unaries
// ...
// ...

// ... most used binaries
// ...
// ...

// ... most used keywords
// ...
// ...

// #define OP_SELF_UNARY                    marg_string_new("SELF_UNARY")
// #define OP_SELF_BINARY                   marg_string_new("SELF_BINARY")
// #define OP_SELF_KEYWORD                  marg_string_new("SELF_KEYWORD")

// #define OP_SUPER_UNARY                   marg_string_new("SUPER_UNARY")
// #define OP_SUPER_BINARY                  marg_string_new("SUPER_BINARY")
// #define OP_SUPER_KEYWORD                 marg_string_new("SUPER_KEYWORD")

#endif
