#ifndef __FMCODES_H_
#define __FMCODES_H_

#include "../base/string.h"

#define FM_POP                    string_new("POP")

#define FM_NIL                    string_new("NIL")
#define FM_TRUE                   string_new("TRUE")
#define FM_FALSE                  string_new("FALSE")

#define FM_SELF                   string_new("SELF")
#define FM_SUPER                  string_new("SUPER")

#define FM_INTEGER                string_new("INTEGER")
#define FM_FLOAT                  string_new("FLOAT")

#define FM_STRING                 string_new("STRING")

#define FM_TENSOR                 string_new("TENSOR")
#define FM_TUPLE                  string_new("TUPLE")
#define FM_BITSTRING              string_new("BITSTRING")
#define FM_HASH                   string_new("HASH")

#define FM_GLOBAL                 string_new("GLOBAL")
#define FM_INSTANCE               string_new("INSTANCE")
#define FM_LOCAL                  string_new("LOCAL")

#define FM_STORE_LOCAL            string_new("STORE_LOCAL")
#define FM_STORE_INSTANCE         string_new("STORE_INSTANCE")
#define FM_STORE_GLOBAL           string_new("STORE_GLOBAL")

#define FM_START_PROC             string_new("START_PROC")
#define FM_END_PROC               string_new("END_PROC")
// #define FM_PROC_PARAMETER         string_new("PROC_PARAMETER")

#define FM_START_C_FUNCTION       string_new("START_C_FUNCTION")
#define FM_END_C_FUNCTION         string_new("END_C_FUNCTION")

#define FM_START_UNARY_METHOD     string_new("START_UNARY_METHOD")
#define FM_END_UNARY_METHOD       string_new("END_UNARY_METHOD")
#define FM_START_BINARY_METHOD    string_new("START_BINARY_METHOD")
#define FM_END_BINARY_METHOD      string_new("END_BINARY_METHOD")
#define FM_START_KEYWORD_METHOD   string_new("START_KEYWORD_METHOD")
#define FM_END_KEYWORD_METHOD     string_new("END_KEYWORD_METHOD")

#define FM_ANY_OBJECT             string_new("ANY_OBJECT")
#define FM_METHOD_PARAMETER       string_new("METHOD_PARAMETER")
// #define FM_METHOD_RECEIVER        string_new("METHOD_RECEIVER")

#define FM_UNARY                  string_new("UNARY")
#define FM_BINARY                 string_new("BINARY")
#define FM_KEYWORD                string_new("KEYWORD")

#endif
