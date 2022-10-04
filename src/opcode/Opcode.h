#ifndef __OPCODE_H_
#define __OPCODE_H_

#include "../base/marg_string.h"

#define OP_COMP_DECLARE_VARIABLE              marg_string_new("COMP_DECLARE_VARIABLE")
#define OP_COMP_GENERATE_IDENTIFIER_POSITION  marg_string_new("COMP_GENERATE_IDENTIFIER_POSITION")
#define OP_COMP_ADD_VARIABLE_TO_VECTOR        marg_string_new("COMP_ADD_VARIABLE_TO_VECTOR")
#define OP_COMP_MAKE_VARIABLE                 marg_string_new("COMP_MAKE_VARIABLE")
#define OP_COMP_COMPILER_NEW                  marg_string_new("COMP_COMPILER_NEW")
#define OP_COMP_SCOPE_BEGIN                   marg_string_new("COMP_SCOPE_BEGIN")
#define OP_COMP_SCOPE_END                     marg_string_new("COMP_SCOPE_END")

//-------------------------------------------

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
#define OP_PUSH_HASH                     marg_string_new("PUSH_HASH")

#define OP_START_PUSH_PROC               marg_string_new("START_PUSH_PROC")
#define OP_END_PUSH_PROC                 marg_string_new("END_PUSH_PROC")

#define OP_START_PUSH_C_FUNCTION         marg_string_new("START_PUSH_C_FUNCTION")
#define OP_END_PUSH_C_FUNCTION           marg_string_new("END_PUSH_C_FUNCTION")

#define OP_START_PUSH_UNARY_METHOD       marg_string_new("START_PUSH_UNARY_METHOD")
#define OP_END_PUSH_UNARY_METHOD         marg_string_new("END_PUSH_UNARY_METHOD")
#define OP_START_PUSH_BINARY_METHOD      marg_string_new("START_PUSH_BINARY_METHOD")
#define OP_END_PUSH_BINARY_METHOD        marg_string_new("END_PUSH_BINARY_METHOD")
#define OP_START_PUSH_KEYWORD_METHOD     marg_string_new("START_PUSH_KEYWORD_METHOD")
#define OP_END_PUSH_KEYWORD_METHOD       marg_string_new("END_PUSH_KEYWORD_METHOD")

#define OP_POP                           marg_string_new("POP")
// #define OP_POPN                          marg_string_new("POPN")

#define OP_STORE                         marg_string_new("STORE")
// #define OP_STORE_LOCAL                   marg_string_new("STORE_LOCAL")
// #define OP_STORE_GLOBAL                  marg_string_new("STORE_GLOBAL")
// #define OP_STORE_UPVALUE                 marg_string_new("STORE_UPVALUE")
#define OP_STORE_INSTANCE                marg_string_new("STORE_INSTANCE")

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

#define OP_UNARY                         marg_string_new("UNARY")
// ... most used unaries
// ...
// ...
#define OP_BINARY                        marg_string_new("BINARY")
// ... most used binaries
// ...
// ...
#define OP_KEYWORD                       marg_string_new("KEYWORD")
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
