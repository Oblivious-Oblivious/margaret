#ifndef __OPCODE_H_
#define __OPCODE_H_

#include "../base/marg_string.h"

#define OP_DECLARE_VARIABLE              marg_string_new("0x01")
#define OP_GENERATE_IDENTIFIER_POSITION  marg_string_new("0x02")
#define OP_ADD_VARIABLE_TO_VECTOR        marg_string_new("0x03")
#define OP_MAKE_VARIABLE                 marg_string_new("0x04")
#define OP_COMPILER_NEW                  marg_string_new("0x05")
#define OP_SCOPE_BEGIN                   marg_string_new("0x06")
#define OP_SCOPE_END                     marg_string_new("0x07")

//-------------------------------------------

#define OP_PUSH_NIL                      marg_string_new("0x00")
#define OP_PUSH_TRUE                     marg_string_new("0x01")
#define OP_PUSH_FALSE                    marg_string_new("0x02")
#define OP_PUSH_SELF                     marg_string_new("0x03")
#define OP_PUSH_SUPER                    marg_string_new("0x04")
#define OP_PUSH_0                        marg_string_new("0x05")
#define OP_PUSH_1                        marg_string_new("0x06")
#define OP_PUSH_MINUS_1                  marg_string_new("0x07")
#define OP_PUSH_2                        marg_string_new("0x08")
#define OP_PUSH_INTEGER                  marg_string_new("0x09")
#define OP_PUSH_FLOAT                    marg_string_new("0x0a")
#define OP_PUSH_CHAR                     marg_string_new("0x0b")
#define OP_PUSH_STRING                   marg_string_new("0x0c")
#define OP_PUSH_VARIABLE                 marg_string_new("0x0d")
#define OP_PUSH_INSTANCE                 marg_string_new("0x0e")
#define OP_PUSH_TENSOR                   marg_string_new("0x0f")
#define OP_PUSH_HASH                     marg_string_new("0x10")

#define OP_START_PUSH_PROC               marg_string_new("0x11")
#define OP_END_PUSH_PROC                 marg_string_new("0x12")

#define OP_START_PUSH_C_FUNCTION         marg_string_new("0x13")
#define OP_END_PUSH_C_FUNCTION           marg_string_new("0x14")

#define OP_START_PUSH_UNARY_METHOD       marg_string_new("0x15")
#define OP_END_PUSH_UNARY_METHOD         marg_string_new("0x16")
#define OP_START_PUSH_BINARY_METHOD      marg_string_new("0x17")
#define OP_END_PUSH_BINARY_METHOD        marg_string_new("0x18")
#define OP_START_PUSH_KEYWORD_METHOD     marg_string_new("0x19")
#define OP_END_PUSH_KEYWORD_METHOD       marg_string_new("0x1a")

#define OP_POP                           marg_string_new("0x1b")
// #define OP_POPN                          marg_string_new("0x1c")

#define OP_STORE                         marg_string_new("0x1d")
// #define OP_STORE_LOCAL                   marg_string_new("0x1e")
// #define OP_STORE_GLOBAL                  marg_string_new("0x1f")
// #define OP_STORE_UPVALUE                 marg_string_new("0x20")
#define OP_STORE_INSTANCE                marg_string_new("0x21")

// #define OP_LABEL                         marg_string_new("0x22")

// #define OP_JUMP                          marg_string_new("0x23")
// #define OP_JUMP_IF_ZERO                  marg_string_new("0x24")
// #define OP_JUMP_IF_NOT_ZERO              marg_string_new("0x25")
// #define OP_JUMP_IF_TRUE                  marg_string_new("0x26")
// #define OP_JUMP_IF_FALSE                 marg_string_new("0x27")

// #define OP_LONGJUMP                      marg_string_new("0x28")
// #define OP_LONGJUMP_IF_ZERO              marg_string_new("0x29")
// #define OP_LONGJUMP_IF_NOT_ZERO          marg_string_new("0x2a")
// #define OP_LONGJUMP_IF_TRUE              marg_string_new("0x2b")
// #define OP_LONGJUMP_IF_FALSE             marg_string_new("0x2c")

// #define OP_RETURN                        marg_string_new("0x2d")
// #define OP_RETURN_NIL                    marg_string_new("0x2e")
// #define OP_RETURN_TRUE                   marg_string_new("0x2f")
// #define OP_RETURN_FALSE                  marg_string_new("0x30")
// #define OP_RETURN_STACK_TOP              marg_string_new("0x31")

#define OP_UNARY                         marg_string_new("0x32")
// ... most used unaries
// ...
// ...
#define OP_BINARY                        marg_string_new("0x33")
// ... most used binaries
// ...
// ...
#define OP_KEYWORD                       marg_string_new("0x34")
// ... most used keywords
// ...
// ...

// #define OP_SELF_UNARY                    marg_string_new("0x35")
// #define OP_SELF_BINARY                   marg_string_new("0x36")
// #define OP_SELF_KEYWORD                  marg_string_new("0x37")

// #define OP_SUPER_UNARY                   marg_string_new("0x38")
// #define OP_SUPER_BINARY                  marg_string_new("0x39")
// #define OP_SUPER_KEYWORD                 marg_string_new("0x3a")

#endif
