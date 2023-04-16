#ifndef ___HELPERS_H_
#define ___HELPERS_H_

#include "cSpec.h"

#include "../src/base/marg_string.h"
#include "../src/base/marg_vector.h"
#include "../src/lexer/Lexer.h"
#include "../src/opcode/Opcodes.h"
#include "../src/parser/Parser.h"

#define parse(code, expected_result) do { \
    Lexer *l = lexer_new("file.marg", marg_string_new((code))); \
    Parser *p = parser_new(lexer_make_tokens(l)); \
    marg_vector *res = parser_analyze_syntax(p); \
    size_t size_of_res = marg_vector_size(res); \
    size_t the_same_size_as_expected = marg_vector_size((expected_result)); \
    \
    assert_that_int(size_of_res equals to the_same_size_as_expected); \
    \
    if(size_of_res <= the_same_size_as_expected) \
        for(size_t i = 0; i < size_of_res; i++) \
            assert_that_charptr(marg_string_get(marg_vector_get(res, i)) equals to marg_string_get(marg_vector_get((expected_result), i))); \
} while(0)

#define debug(code, expected_result) do { \
    Lexer *l = lexer_new("file.marg", marg_string_new((code))); \
    Parser *p = parser_new(lexer_make_tokens(l)); \
    marg_vector *res = parser_analyze_syntax(p); \
    size_t size_of_res = marg_vector_size(res); \
    size_t the_same_size_as_expected = marg_vector_size((expected_result)); \
    printf("["); \
    for(size_t i = 0; i < size_of_res-1; i++) { \
        if(res == NULL || marg_vector_get(res, i) == NULL or marg_string_get(marg_vector_get(res, i)) == NULL) \
            printf("(NULL), "); \
        else \
            printf("%s, ", marg_string_get(marg_vector_get(res, i))); \
    } \
    if(res == NULL || marg_vector_get(res, size_of_res-1) == NULL or marg_string_get(marg_vector_get(res, size_of_res-1)) == NULL) \
        printf("(NULL), "); \
    else \
        printf("%s]\n", marg_string_get(marg_vector_get(res, size_of_res-1))); \
    \
    assert_that_int(size_of_res equals to the_same_size_as_expected); \
    \
    if(size_of_res <= the_same_size_as_expected) \
        for(size_t i = 0; i < size_of_res; i++) \
            assert_that_charptr(marg_string_get(marg_vector_get(res, i)) equals to marg_string_get(marg_vector_get((expected_result), i))); \
} while(0)

#define error(code, error_message) do { \
    Lexer *l = lexer_new("file.marg", marg_string_new((code))); \
    Parser *p = parser_new(lexer_make_tokens(l)); \
    marg_vector *res = parser_analyze_syntax(p); \
    (void)res; \
} while(0)

#define evalcodes(code, expected_result) do { \
    Lexer *l = lexer_new("file.marg", marg_string_new((code))); \
    Parser *p = parser_new(lexer_make_tokens(l)); \
    Evaluator *e = evaluator_new(parser_analyze_syntax(p)); \
    marg_string *res = evaluator_evaluate(e); \
    \
    assert_that_charptr(marg_string_get(res) equals to (expected_result)); \
} while(0)

#endif
