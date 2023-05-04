#ifndef __OPCODES_H_
#define __OPCODES_H_

#include "../base/string.h"

// ------ Formal Messages Opcodes ------
#define FM_POP               string_new("POP")

#define FM_LOCAL             string_new("LOCAL")
#define FM_INSTANCE          string_new("INSTANCE")
#define FM_GLOBAL            string_new("GLOBAL")

#define FM_STORE_LOCAL       string_new("STORE_LOCAL")
#define FM_STORE_INSTANCE    string_new("STORE_INSTANCE")
#define FM_STORE_GLOBAL      string_new("STORE_GLOBAL")

#define FM_NIL               string_new("NIL")
#define FM_TRUE              string_new("TRUE")
#define FM_FALSE             string_new("FALSE")

#define FM_SELF              string_new("SELF")
#define FM_SUPER             string_new("SUPER")

#define FM_INTEGER           string_new("INTEGER")
#define FM_FLOAT             string_new("FLOAT")

#define FM_STRING            string_new("STRING")

#define FM_TENSOR            string_new("TENSOR")
#define FM_TUPLE             string_new("TUPLE")
#define FM_BITSTRING         string_new("BITSTRING")
#define FM_HASH              string_new("HASH")

#define FM_START_PROC        string_new("START_PROC")
#define FM_END_PROC          string_new("END_PROC")
#define FM_PROC_PARAMETER    string_new("PROC_PARAMETER")

#define FM_START_C_FUNCTION  string_new("START_C_FUNCTION")
#define FM_END_C_FUNCTION    string_new("END_C_FUNCTION")

#define FM_ANY_OBJECT        string_new("ANY_OBJECT")
#define FM_METHOD_PARAMETER  string_new("METHOD_PARAMETER")

#define FM_UNARY             string_new("UNARY")
#define FM_BINARY            string_new("BINARY")
#define FM_KEYWORD           string_new("KEYWORD")

// ------ Emmited Opcodes ------
#define OP_POP                              0xfd
#define TEST_OP_PRINT                       0xfe
#define OP_RETURN                           0xff

#define OP_PUT_NIL                          0x01
#define OP_PUT_TRUE                         0x02
#define OP_PUT_FALSE                        0x03

#define OP_PUT_MINUS_1                      0x04
#define OP_PUT_0                            0x05
#define OP_PUT_1                            0x06
#define OP_PUT_2                            0x07

#define OP_PUT_OBJECT                       0x08
#define OP_PUT_OBJECT_LONG                  0x09

#define OP_SET_GLOBAL                       0x0a
#define OP_SET_GLOBAL_LONG                  0x0b
#define OP_SET_INSTANCE                     0x0c
#define OP_SET_INSTANCE_LONG                0x0d
#define OP_SET_LOCAL                        0x0e
#define OP_SET_LOCAL_LONG                   0x0f

#define OP_GET_GLOBAL                       0x10
#define OP_GET_GLOBAL_LONG                  0x11
#define OP_GET_INSTANCE                     0x12
#define OP_GET_INSTANCE_LONG                0x13
#define OP_GET_LOCAL                        0x14
#define OP_GET_LOCAL_LONG                   0x15

// TODO Superinstructions for incrementing, decrementing and doubling
// TODO Superinstructions for comparing with zero
// #define OP_SELF                             0xff
// #define OP_SUPER                            0xff

// #define FM_METHOD_UNARY                     0xff
// #define FM_METHOD_BINARY                    0xff
// #define FM_METHOD_KEYWORD                   0xff

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
