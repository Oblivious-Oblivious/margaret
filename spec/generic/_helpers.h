#ifndef ___HELPERS_H_
#define ___HELPERS_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../libs/EmeraldsVector/export/EmeraldsVector.h"
#include "../../src/lexer/Lexer.h"
#include "../../src/opcode/fmcodes.h"
#include "../../src/parser/Parser.h"

#define parse(code, expected_result)                                          \
  do {                                                                        \
    VM *vm     = vm_new("file.marg");                                         \
    vm->source = string_new(code);                                            \
    lexer_make_tokens(vm);                                                    \
    parser_analyze_syntax(vm);                                                \
    char **res                     = vm->formal_bytecode;                     \
    size_t size_of_formal_bytecode = vector_size(res);                        \
    size_t same_size_as_expected   = vector_size(expected_result);            \
    assert_that_int(size_of_formal_bytecode equals to same_size_as_expected); \
                                                                              \
    if(size_of_formal_bytecode == same_size_as_expected) {                    \
      for(size_t i = 0; i < size_of_formal_bytecode; i++) {                   \
        assert_that_charptr(res[i] equals to(expected_result)[i]);            \
      }                                                                       \
    } else {                                                                  \
      fail("formal bytecode has different size than expected.");              \
    }                                                                         \
  } while(0)

#define debug(code, expected_result)                                          \
  do {                                                                        \
    VM *vm     = vm_new("file.marg");                                         \
    vm->source = string_new(code);                                            \
    lexer_make_tokens(vm);                                                    \
    parser_analyze_syntax(vm);                                                \
    char **res                     = vm->formal_bytecode;                     \
    size_t size_of_formal_bytecode = vector_size(res);                        \
    size_t same_size_as_expected   = vector_size(expected_result);            \
    printf("[");                                                              \
    for(size_t i = 0; i < size_of_formal_bytecode - 1; i++) {                 \
      if(res == NULL || res[i] == NULL || res[i] == NULL) {                   \
        printf("(NULL), ");                                                   \
      } else {                                                                \
        printf("%s, ", res[i]);                                               \
      }                                                                       \
    }                                                                         \
    if(res == NULL || res[size_of_formal_bytecode - 1] == NULL ||             \
       res[size_of_formal_bytecode - 1] == NULL) {                            \
      printf("(NULL), ");                                                     \
    } else {                                                                  \
      printf("%s]\n", res[size_of_formal_bytecode - 1]);                      \
    }                                                                         \
                                                                              \
    assert_that_int(size_of_formal_bytecode equals to same_size_as_expected); \
                                                                              \
    if(size_of_formal_bytecode == same_size_as_expected) {                    \
      for(size_t i = 0; i < size_of_formal_bytecode; i++) {                   \
        assert_that_charptr(res[i] equals to(expected_result)[i]);            \
      }                                                                       \
    } else {                                                                  \
      fail("formal bytecode has different size than expected.");              \
    }                                                                         \
  } while(0)

/* TODO - Throw when error occurs */
#define error(code, error_message)    \
  do {                                \
    VM *vm     = vm_new("file.marg"); \
    vm->source = string_new(code);    \
    lexer_make_tokens(vm);            \
    parser_analyze_syntax(vm);        \
  } while(0)

#endif
