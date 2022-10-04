#ifndef __OPCODE_H_
#define __OPCODE_H_

#include "../base/marg_string.h"

#define OP_DECLARE_VARIABLE              marg_string_new("COMP - declare_variable")
#define OP_GENERATE_IDENTIFIER_POSITION  marg_string_new("COMP - generate_identifier_position")
#define OP_ADD_VARIABLE_TO_VECTOR        marg_string_new("COMP - add_variable_to_vector")
#define OP_MAKE_VARIABLE                 marg_string_new("COMP - make_variable")
#define OP_COMPILER_NEW                  marg_string_new("COMP - compiler_new")
#define OP_SCOPE_BEGIN                   marg_string_new("COMP - scope_begin")
#define OP_SCOPE_END                     marg_string_new("COMP - scope_end")

//-------------------------------------------

#define OP_PUSH_NIL                      marg_string_new("push_nil")
#define OP_PUSH_TRUE                     marg_string_new("push_true")
#define OP_PUSH_FALSE                    marg_string_new("push_false")
#define OP_PUSH_SELF                     marg_string_new("push_self")
#define OP_PUSH_SUPER                    marg_string_new("push_super")
#define OP_PUSH_0                        marg_string_new("push_0")
#define OP_PUSH_1                        marg_string_new("push_1")
#define OP_PUSH_MINUS_1                  marg_string_new("push_minus 1")
#define OP_PUSH_2                        marg_string_new("push_2")
#define OP_PUSH_INTEGER                  marg_string_new("push_integer")
#define OP_PUSH_FLOAT                    marg_string_new("push_float")
#define OP_PUSH_CHAR                     marg_string_new("push_char")
#define OP_PUSH_STRING                   marg_string_new("push_string")
#define OP_PUSH_VARIABLE                 marg_string_new("push_variable")
#define OP_PUSH_INSTANCE                 marg_string_new("push_instance")
#define OP_PUSH_TENSOR                   marg_string_new("push_tensor")
#define OP_PUSH_HASH                     marg_string_new("push_hash")

#define OP_START_PUSH_PROC               marg_string_new("start_push_proc")
#define OP_END_PUSH_PROC                 marg_string_new("end_push_proc")

#define OP_START_PUSH_C_FUNCTION         marg_string_new("start_push_c_function")
#define OP_END_PUSH_C_FUNCTION           marg_string_new("end_push_c_function")

#define OP_START_PUSH_UNARY_METHOD       marg_string_new("start_push_unary_method")
#define OP_END_PUSH_UNARY_METHOD         marg_string_new("end_push_unary_method")
#define OP_START_PUSH_BINARY_METHOD      marg_string_new("start_push_binary_method")
#define OP_END_PUSH_BINARY_METHOD        marg_string_new("end_push_binary_method")
#define OP_START_PUSH_KEYWORD_METHOD     marg_string_new("start_push_keyword_method")
#define OP_END_PUSH_KEYWORD_METHOD       marg_string_new("end_push_keyword_method")

#define OP_POP                           marg_string_new("pop")
// #define OP_POPN                          marg_string_new("popn")

#define OP_STORE                         marg_string_new("store")
// #define OP_STORE_LOCAL                   marg_string_new("store_local")
// #define OP_STORE_GLOBAL                  marg_string_new("store_global")
// #define OP_STORE_UPVALUE                 marg_string_new("store_upvalue")
#define OP_STORE_INSTANCE                marg_string_new("store_instance")

// #define OP_LABEL                         marg_string_new("label")

// #define OP_JUMP                          marg_string_new("jump")
// #define OP_JUMP_IF_ZERO                  marg_string_new("jump_if_zero")
// #define OP_JUMP_IF_NOT_ZERO              marg_string_new("jump_if_not_zero")
// #define OP_JUMP_IF_TRUE                  marg_string_new("jump_if_true")
// #define OP_JUMP_IF_FALSE                 marg_string_new("jump_if_false")

// #define OP_LONGJUMP                      marg_string_new("longjump")
// #define OP_LONGJUMP_IF_ZERO              marg_string_new("longjump_if_zero")
// #define OP_LONGJUMP_IF_NOT_ZERO          marg_string_new("longjump_if_not_zero")
// #define OP_LONGJUMP_IF_TRUE              marg_string_new("longjump_if_true")
// #define OP_LONGJUMP_IF_FALSE             marg_string_new("longjump_if_false")

// #define OP_RETURN                        marg_string_new("return")
// #define OP_RETURN_NIL                    marg_string_new("return_nil")
// #define OP_RETURN_TRUE                   marg_string_new("return_true")
// #define OP_RETURN_FALSE                  marg_string_new("return_false")
// #define OP_RETURN_STACK_TOP              marg_string_new("return_stack top")

#define OP_UNARY                         marg_string_new("unary")
// ... most used unaries
// ...
// ...
#define OP_BINARY                        marg_string_new("binary")
// ... most used binaries
// ...
// ...
#define OP_KEYWORD                       marg_string_new("keyword")
// ... most used keywords
// ...
// ...

// #define OP_SELF_UNARY                    marg_string_new("self_unary")
// #define OP_SELF_BINARY                   marg_string_new("self_binary")
// #define OP_SELF_KEYWORD                  marg_string_new("self_keyword")

// #define OP_SUPER_UNARY                   marg_string_new("super_unary")
// #define OP_SUPER_BINARY                  marg_string_new("super_binary")
// #define OP_SUPER_KEYWORD                 marg_string_new("super_keyword")

#endif
