#ifndef __OPCODE_H_
#define __OPCODE_H_

#include "../base/marg_string.h"

#define OP_DECLARE_VARIABLE              marg_string_new("COMP - 0x01 - declare variable")
#define OP_GENERATE_IDENTIFIER_POSITION  marg_string_new("COMP - 0x02 - generate identifier position")
#define OP_ADD_VARIABLE_TO_VECTOR        marg_string_new("COMP - 0x03 - add variable to vector")
#define OP_MAKE_VARIABLE                 marg_string_new("COMP - 0x04 - make variable")
#define OP_COMPILER_NEW                  marg_string_new("COMP - 0x05 - compiler new")
#define OP_SCOPE_BEGIN                   marg_string_new("COMP - 0x06 - scope begin")
#define OP_SCOPE_END                     marg_string_new("COMP - 0x07 - scope end")

//-------------------------------------------

#define OP_PUSH_NIL                      marg_string_new("0x00 - push nil")
#define OP_PUSH_TRUE                     marg_string_new("0x01 - push true")
#define OP_PUSH_FALSE                    marg_string_new("0x02 - push false")
#define OP_PUSH_SELF                     marg_string_new("0x03 - push self")
#define OP_PUSH_SUPER                    marg_string_new("0x04 - push super")
#define OP_PUSH_0                        marg_string_new("0x05 - push 0")
#define OP_PUSH_1                        marg_string_new("0x06 - push 1")
#define OP_PUSH_MINUS_1                  marg_string_new("0x07 - push minus 1")
#define OP_PUSH_2                        marg_string_new("0x08 - push 2")
#define OP_PUSH_INTEGER                  marg_string_new("0x09 - push integer")
#define OP_PUSH_FLOAT                    marg_string_new("0x0a - push float")
#define OP_PUSH_CHAR                     marg_string_new("0x0b - push char")
#define OP_PUSH_STRING                   marg_string_new("0x0c - push string")
#define OP_PUSH_VARIABLE                 marg_string_new("0x0d - push variable")
#define OP_PUSH_INSTANCE                 marg_string_new("0x0e - push instance")
#define OP_PUSH_TENSOR                   marg_string_new("0x0f - push tensor")
#define OP_PUSH_HASH                     marg_string_new("0x10 - push hash")

#define OP_START_PUSH_PROC               marg_string_new("0x11 - start push proc")
#define OP_END_PUSH_PROC                 marg_string_new("0x12 - end push proc")

#define OP_START_PUSH_C_FUNCTION         marg_string_new("0x13 - start push c function")
#define OP_END_PUSH_C_FUNCTION           marg_string_new("0x14 - end push c function")

#define OP_START_PUSH_UNARY_METHOD       marg_string_new("0x15 - start push unary method")
#define OP_END_PUSH_UNARY_METHOD         marg_string_new("0x16 - end push unary method")
#define OP_START_PUSH_BINARY_METHOD      marg_string_new("0x17 - start push binary method")
#define OP_END_PUSH_BINARY_METHOD        marg_string_new("0x18 - end push binary method")
#define OP_START_PUSH_KEYWORD_METHOD     marg_string_new("0x19 - start push keyword method")
#define OP_END_PUSH_KEYWORD_METHOD       marg_string_new("0x1a - end push keyword method")

#define OP_POP                           marg_string_new("0x1b - pop")
// #define OP_POPN                          marg_string_new("0x1c - popn")

#define OP_STORE                         marg_string_new("0x1d - store")
// #define OP_STORE_LOCAL                   marg_string_new("0x1e - store local")
// #define OP_STORE_GLOBAL                  marg_string_new("0x1f - store global")
// #define OP_STORE_UPVALUE                 marg_string_new("0x20 - store upvalue")
#define OP_STORE_INSTANCE                marg_string_new("0x21 - store instance")

// #define OP_LABEL                         marg_string_new("0x22 - label")

// #define OP_JUMP                          marg_string_new("0x23 - jump")
// #define OP_JUMP_IF_ZERO                  marg_string_new("0x24 - jump if zero")
// #define OP_JUMP_IF_NOT_ZERO              marg_string_new("0x25 - jump if not zero")
// #define OP_JUMP_IF_TRUE                  marg_string_new("0x26 - jump if true")
// #define OP_JUMP_IF_FALSE                 marg_string_new("0x27 - jump if false")

// #define OP_LONGJUMP                      marg_string_new("0x28 - longjump")
// #define OP_LONGJUMP_IF_ZERO              marg_string_new("0x29 - longjump if zero")
// #define OP_LONGJUMP_IF_NOT_ZERO          marg_string_new("0x2a - longjump if not zero")
// #define OP_LONGJUMP_IF_TRUE              marg_string_new("0x2b - longjump if true")
// #define OP_LONGJUMP_IF_FALSE             marg_string_new("0x2c - longjump if false")

// #define OP_RETURN                        marg_string_new("0x2d - return")
// #define OP_RETURN_NIL                    marg_string_new("0x2e - return nil")
// #define OP_RETURN_TRUE                   marg_string_new("0x2f - return true")
// #define OP_RETURN_FALSE                  marg_string_new("0x30 - return false")
// #define OP_RETURN_STACK_TOP              marg_string_new("0x31 - return stack top")

#define OP_UNARY                         marg_string_new("0x32 - unary")
// ... most used unaries
// ...
// ...
#define OP_BINARY                        marg_string_new("0x33 - binary")
// ... most used binaries
// ...
// ...
#define OP_KEYWORD                       marg_string_new("0x34 - keyword")
// ... most used keywords
// ...
// ...

// #define OP_SELF_UNARY                    marg_string_new("0x35 - self unary")
// #define OP_SELF_BINARY                   marg_string_new("0x36 - self binary")
// #define OP_SELF_KEYWORD                  marg_string_new("0x37 - self keyword")

// #define OP_SUPER_UNARY                   marg_string_new("0x38 - super unary")
// #define OP_SUPER_BINARY                  marg_string_new("0x39 - super binary")
// #define OP_SUPER_KEYWORD                 marg_string_new("0x3a - super keyword")

#endif
