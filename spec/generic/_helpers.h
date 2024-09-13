#ifndef ___HELPERS_H_
#define ___HELPERS_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../libs/EmeraldsVector/export/EmeraldsVector.h"
#include "../../src/lexer/Lexer.h"
#include "../../src/opcode/fmcodes.h"
#include "../../src/parser/Parser.h"

#define assert_that_vector(actual, expected)                                \
  size_t size_of_formal_bytecode = vector_size(actual);                     \
  size_t same_size_as_expected   = vector_size(expected);                   \
  assert_that_int(size_of_formal_bytecode equals to same_size_as_expected); \
  do {                                                                      \
    if(size_of_formal_bytecode == same_size_as_expected) {                  \
      for(size_t i = 0; i < size_of_formal_bytecode; i++) {                 \
        assert_that_charptr((actual)[i] equals to(expected)[i]);            \
      }                                                                     \
    } else {                                                                \
      fail("formal bytecode has different size than expected.");            \
    }                                                                       \
  } while(0)

#define parse(code, expected_result)                          \
  do {                                                        \
    VM *vm     = vm_new("file.marg");                         \
    vm->source = string_new(code);                            \
    lexer_make_tokens(vm);                                    \
    parser_analyze_syntax(vm);                                \
    assert_that_vector(vm->formal_bytecode, expected_result); \
  } while(0)

#define debug(code, expected_result)           \
  do {                                         \
    VM *vm     = vm_new("file.marg");          \
    vm->source = string_new(code);             \
    lexer_make_tokens(vm);                     \
    parser_analyze_syntax(vm);                 \
    vector_display(vm->formal_bytecode, "%s"); \
  } while(0)

#define error(code, error_message, token)                     \
  do {                                                        \
    VM *vm     = vm_new("file.marg");                         \
    vm->source = string_new(code);                            \
    lexer_make_tokens(vm);                                    \
    parser_analyze_syntax(vm);                                \
    if(vm->error && vm->error_token) {                        \
      assert_that_charptr(vm->error equals to error_message); \
      assert_that_charptr(vm->error_token equals to token);   \
    } else {                                                  \
      char *failstr = string_new("expected error message: "); \
      string_addf(&failstr, "'%s'", error_message);           \
      fail(failstr);                                          \
    }                                                         \
  } while(0)

#endif
