#ifndef __FMCODES_H_
#define __FMCODES_H_

#include "../../libs/EmeraldsString/export/EmeraldsString.h"

#define FM_NIL               string_new("NIL")
#define FM_TRUE              string_new("TRUE")
#define FM_FALSE             string_new("FALSE")
#define FM_SELF              string_new("SELF")
#define FM_SUPER             string_new("SUPER")
#define FM_LABEL             string_new("LABEL")
#define FM_INTEGER           string_new("INTEGER")
#define FM_FLOAT             string_new("FLOAT")
#define FM_STRING            string_new("STRING")
#define FM_TENSOR            string_new("TENSOR")
#define FM_TUPLE             string_new("TUPLE")
#define FM_BITSTRING         string_new("BITSTRING")
#define FM_HASH              string_new("HASH")
#define FM_GLOBAL            string_new("GLOBAL")
#define FM_INSTANCE          string_new("INSTANCE")
#define FM_LOCAL             string_new("LOCAL")
#define FM_PROC_START        string_new("PROC_START")
#define FM_PROC_END          string_new("PROC_END")
#define FM_PROC_PARAMETER    string_new("PROC_PARAMETER")
#define FM_METHOD_START      string_new("METHOD_START")
#define FM_METHOD_END        string_new("METHOD_END")
#define FM_METHOD_ANY_OBJECT string_new("FM_METHOD_ANY_OBJECT")
#define FM_METHOD_RECEIVER   string_new("FM_METHOD_RECEIVER")
#define FM_METHOD_PARAMETER  string_new("FM_METHOD_PARAMETER")
#define FM_METHOD_NAME       string_new("FM_METHOD_NAME")
#define FM_KEYWORD           string_new("KEYWORD")
#define FM_BINARY            string_new("BINARY")
#define FM_UNARY             string_new("UNARY")
#define FM_LHS               string_new("LHS")

#endif
