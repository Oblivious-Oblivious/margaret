#ifndef __OPCODES_H_
#define __OPCODES_H_

#include "../base/string.h"

// ------ Formal Messages Opcodes ------
#define FM_VARIABLE          string_new("VARIABLE")
#define FM_INSTANCE          string_new("INSTANCE")

#define FM_STORE             string_new("STORE")
#define FM_STORE_INSTANCE    string_new("STORE_INSTANCE")

#define FM_NIL               string_new("NIL")
#define FM_TRUE              string_new("TRUE")
#define FM_FALSE             string_new("FALSE")

#define FM_SELF              string_new("SELF")
#define FM_SUPER             string_new("SUPER")

#define FM_INTEGER           string_new("INTEGER")
#define FM_FLOAT             string_new("FLOAT")
#define FM_CHAR              string_new("CHAR")
#define FM_STRING            string_new("STRING")
#define FM_TENSOR            string_new("TENSOR")
#define FM_TUPLE             string_new("TUPLE")
#define FM_BITSTRING         string_new("BITSTRING")
#define FM_HASH              string_new("HASH")

#define FM_ANY_OBJECT        string_new("ANY_OBJECT")
#define FM_METHOD_PARAMETER  string_new("METHOD_PARAMETER")

#define FM_START_PROC        string_new("START_PROC")
#define FM_END_PROC          string_new("END_PROC")
#define FM_START_C_FUNCTION  string_new("START_C_FUNCTION")
#define FM_END_C_FUNCTION    string_new("END_C_FUNCTION")

#define FM_UNARY             string_new("UNARY")
#define FM_BINARY            string_new("BINARY")
#define FM_KEYWORD           string_new("KEYWORD")

// ------ Emmited Opcodes ------
#define OP_RETURN                           0x00

#define OP_NIL                              0x01
#define OP_TRUE                             0x02
#define OP_FALSE                            0x03

#define OP_CONSTANT                         0x04
#define OP_LONG_CONSTANT                    0x05

// #define OP_SELF                             0xff
// #define OP_SUPER                            0xff

// #define OP_0                                0xff
// #define OP_1                                0xff
// #define OP_MINUS_1                          0xff
// #define OP_2                                0xff

// #define FM_METHOD_UNARY                     0xff
// #define FM_METHOD_BINARY                    0xff
// #define FM_METHOD_KEYWORD                   0xff


// #define OP_DECLARE_VARIABLE              string_new("DECLARE_VARIABLE")
// #define OP_GENERATE_IDENTIFIER_POSITION  string_new("GENERATE_IDENTIFIER_POSITION")
// #define OP_ADD_VARIABLE_TO_VECTOR        string_new("ADD_VARIABLE_TO_VECTOR")
// #define OP_MAKE_VARIABLE                 string_new("MAKE_VARIABLE")
// #define OP_COMPILER_NEW                  string_new("COMPILER_NEW")
// #define OP_SCOPE_BEGIN                   string_new("SCOPE_BEGIN")
// #define OP_SCOPE_END                     string_new("SCOPE_END")

// #define OP_NIL                           string_new("NIL")
// #define OP_TRUE                          string_new("TRUE")
// #define OP_FALSE                         string_new("FALSE")
// #define OP_SELF                          string_new("SELF")
// #define OP_SUPER                         string_new("SUPER")
// #define OP_0                             string_new("0")
// #define OP_1                             string_new("1")
// #define OP_MINUS_1                       string_new("MINUS_1")
// #define OP_2                             string_new("2")
// #define OP_INTEGER                       string_new("INTEGER")
// #define OP_FLOAT                         string_new("FLOAT")
// #define OP_CHAR                          string_new("CHAR")
// #define OP_STRING                        string_new("STRING")
// #define OP_VARIABLE                      string_new("VARIABLE")
// #define OP_INSTANCE                      string_new("INSTANCE")
// #define OP_TENSOR                        string_new("TENSOR")
// #define OP_TUPLE                         string_new("TUPLE")
// #define OP_BITSTRING                     string_new("BITSTRING")
// #define OP_HASH                          string_new("HASH")

// #define OP_ANY_OBJECT                    string_new("ANY_OBJECT")
// #define OP_METHOD_PARAMETER              string_new("METHOD_PARAMETER")

// #define OP_START_PROC                    string_new("START_PROC")
// #define OP_END_PROC                      string_new("END_PROC")
// #define OP_START_C_FUNCTION              string_new("START_C_FUNCTION")
// #define OP_END_C_FUNCTION                string_new("END_C_FUNCTION")

// #define OP_POP                           string_new("POP")
// #define OP_POPN                          string_new("POPN")

// #define OP_STORE                         string_new("STORE")
// #define OP_STORE_LOCAL                   string_new("STORE_LOCAL")
// #define OP_STORE_GLOBAL                  string_new("STORE_GLOBAL")
// #define OP_STORE_UPVALUE                 string_new("STORE_UPVALUE")

// #define OP_LABEL                         string_new("LABEL")

// #define OP_JUMP                          string_new("JUMP")
// #define OP_JUMP_IF_ZERO                  string_new("JUMP_IF_ZERO")
// #define OP_JUMP_IF_NOT_ZERO              string_new("JUMP_IF_NOT_ZERO")
// #define OP_JUMP_IF_TRUE                  string_new("JUMP_IF_TRUE")
// #define OP_JUMP_IF_FALSE                 string_new("JUMP_IF_FALSE")

// #define OP_LONGJUMP                      string_new("LONGJUMP")
// #define OP_LONGJUMP_IF_ZERO              string_new("LONGJUMP_IF_ZERO")
// #define OP_LONGJUMP_IF_NOT_ZERO          string_new("LONGJUMP_IF_NOT_ZERO")
// #define OP_LONGJUMP_IF_TRUE              string_new("LONGJUMP_IF_TRUE")
// #define OP_LONGJUMP_IF_FALSE             string_new("LONGJUMP_IF_FALSE")

// #define OP_RETURN                        string_new("RETURN")
// #define OP_RETURN_NIL                    string_new("RETURN_NIL")
// #define OP_RETURN_TRUE                   string_new("RETURN_TRUE")
// #define OP_RETURN_FALSE                  string_new("RETURN_FALSE")
// #define OP_RETURN_STACK_TOP              string_new("RETURN_STACK_TOP")

// ... most used unaries
// ...
// ...

// ... most used binaries
// ...
// ...

// ... most used keywords
// ...
// ...

// #define OP_SELF_UNARY                    string_new("SELF_UNARY")
// #define OP_SELF_BINARY                   string_new("SELF_BINARY")
// #define OP_SELF_KEYWORD                  string_new("SELF_KEYWORD")

// #define OP_SUPER_UNARY                   string_new("SUPER_UNARY")
// #define OP_SUPER_BINARY                  string_new("SUPER_BINARY")
// #define OP_SUPER_KEYWORD                 string_new("SUPER_KEYWORD")

#endif
