#ifndef __POSTCARD_SPEC_H_
#define __POSTCARD_SPEC_H_

#include "../../src/loader/Loader.h"
#include "_helpers.h"

module(postcard_spec, {
  it("parses postcard snippet", {
    VM *vm = vm_new("./examples/postcard.marg");
    loader_load(vm);
    char *postcard = vm->source;

    parse(
      postcard,
      vector_new(
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_METHOD_START,
        FM_METHOD_RECEIVER,
        FM_METHOD_ANY_OBJECT,
        FM_METHOD_PARAMETER,
        FM_LOCAL,
        string_new("x"),
        FM_METHOD_NAME,
        string_new("ultimate_answer:"),
        FM_TRUE,
        FM_FALSE,
        FM_LHS,
        string_new("!"),
        FM_UNARY,
        string_new("not"),
        FM_UNARY,
        string_new("not"),
        FM_BINARY,
        string_new("&&"),
        FM_NIL,
        FM_UNARY,
        string_new("is_nil?"),
        FM_BINARY,
        string_new("&&"),
        FM_METHOD_START,
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_INTEGER,
        string_new("0"),
        FM_KEYWORD,
        string_new("exit:"),
        string_new("1"),
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("if_false:"),
        string_new("1"),
        FM_LOCAL,
        string_new("y"),
        FM_SELF,
        FM_UNARY,
        string_new("methods"),
        FM_UNARY,
        string_new("size"),
        FM_SUPER,
        FM_UNARY,
        string_new("to_string"),
        FM_UNARY,
        string_new("length"),
        FM_BINARY,
        string_new("+"),
        FM_INTEGER,
        string_new("42"),
        FM_BINARY,
        string_new("*"),
        FM_BINARY,
        string_new("="),
        FM_LABEL,
        string_new("label"),
        FM_INTEGER,
        string_new("42"),
        FM_FLOAT,
        string_new("42.2"),
        FM_STRING,
        string_new("str"),
        FM_INTEGER,
        string_new("6"),
        FM_INTEGER,
        string_new("48879"),
        FM_INTEGER,
        string_new("481"),
        FM_LOCAL,
        string_new("y"),
        FM_INTEGER,
        string_new("42"),
        FM_STRING,
        string_new("val"),
        FM_TUPLE,
        string_new("3"),
        FM_STRING,
        string_new("k1"),
        FM_INTEGER,
        string_new("42"),
        FM_LHS,
        string_new("-"),
        FM_STRING,
        string_new("k2"),
        FM_INTEGER,
        string_new("43"),
        FM_HASH,
        string_new("4"),
        FM_INTEGER,
        string_new("42"),
        FM_INTEGER,
        string_new("8"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("1"),
        FM_INTEGER,
        string_new("0"),
        FM_INTEGER,
        string_new("1"),
        FM_BITSTRING,
        string_new("6"),
        FM_TENSOR,
        string_new("10"),
        FM_METHOD_START,
        FM_METHOD_PARAMETER,
        string_new("elem"),
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_LOCAL,
        string_new("elem"),
        FM_UNARY,
        string_new("object_id"),
        FM_KEYWORD,
        string_new("puts:"),
        string_new("1"),
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("each:"),
        string_new("1"),
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_LOCAL,
        string_new("x"),
        FM_LOCAL,
        string_new("y"),
        FM_BINARY,
        string_new("<"),
        FM_METHOD_START,
        FM_LOCAL,
        string_new("x"),
        FM_METHOD_END,
        FM_METHOD_START,
        FM_LOCAL,
        string_new("y"),
        FM_METHOD_END,
        FM_KEYWORD,
        string_new("if:then:else:"),
        string_new("3"),
        FM_METHOD_END,
        FM_BINARY,
        string_new("--"),
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_GLOBAL,
        string_new("$Margaret"),
        FM_INTEGER,
        string_new("42"),
        FM_KEYWORD,
        string_new("ultimate_answer:"),
        string_new("1"),
        FM_KEYWORD,
        string_new("puts:"),
        string_new("1")
      )
    );
  });
})

#endif
