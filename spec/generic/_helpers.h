#ifndef ___HELPERS_H_
#define ___HELPERS_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../libs/EmeraldsVector/export/EmeraldsVector.h"
#include "../../src/lexer/Lexer.h"
#include "../../src/opcode/fmcodes.h"
#include "../../src/parser/Parser.h"

#define parse(code, expected_result)                                             \
  do {                                                                           \
    Lexer *l                         = lexer_new("file.marg", string_new(code)); \
    Parser *p                        = parser_new(lexer_make_tokens(l));         \
    char **res                       = parser_analyze_syntax(p);                 \
    size_t size_of_res               = vector_size(res);                         \
    size_t the_same_size_as_expected = vector_size(expected_result);             \
                                                                                 \
    assert_that_int(size_of_res equals to the_same_size_as_expected);            \
                                                                                 \
    if(size_of_res <= the_same_size_as_expected) {                               \
      for(size_t i = 0; i < size_of_res; i++) {                                  \
        assert_that_charptr(res[i] equals to expected_result[i]);                \
      }                                                                          \
    }                                                                            \
  } while(0)

#define debug(code, expected_result)                                             \
  do {                                                                           \
    Lexer *l                         = lexer_new("file.marg", string_new(code)); \
    Parser *p                        = parser_new(lexer_make_tokens(l));         \
    char **res                       = parser_analyze_syntax(p);                 \
    size_t size_of_res               = vector_size(res);                         \
    size_t the_same_size_as_expected = vector_size(expected_result);             \
    printf("[");                                                                 \
    for(size_t i = 0; i < size_of_res - 1; i++) {                                \
      if(res == NULL || res[i] == NULL || res[i] == NULL) {                      \
        printf("(NULL), ");                                                      \
      } else {                                                                   \
        printf("%s, ", res[i]);                                                  \
      }                                                                          \
    }                                                                            \
    if(res == NULL || res[size_of_res - 1] == NULL ||                            \
       res[size_of_res - 1] == NULL) {                                           \
      printf("(NULL), ");                                                        \
    } else {                                                                     \
      printf("%s]\n", res[size_of_res - 1]);                                     \
    }                                                                            \
                                                                                 \
    assert_that_int(size_of_res equals to the_same_size_as_expected);            \
                                                                                 \
    if(size_of_res <= the_same_size_as_expected) {                               \
      for(size_t i = 0; i < size_of_res; i++) {                                  \
        assert_that_charptr(res[i] equals to expected_result[i]);                \
      }                                                                          \
    }                                                                            \
  } while(0)

#define error(code, error_message)                         \
  do {                                                     \
    Lexer *l   = lexer_new("file.marg", string_new(code)); \
    Parser *p  = parser_new(lexer_make_tokens(l));         \
    char **res = parser_analyze_syntax(p);                 \
    (void)res;                                             \
  } while(0)

#endif
