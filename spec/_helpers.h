#ifndef ___HELPERS_H_
#define ___HELPERS_H_

#include "cSpec.h"

#include "../src/base/string.h"
#include "../src/base/vector.h"
#include "../src/lexer/Lexer.h"
#include "../src/opcode/fmcodes.h"
#include "../src/parser/Parser.h"

void parse(const char *code, vector *expected_result) {
    Lexer *l = lexer_new("file.marg", string_new(code));
    Parser *p = parser_new(lexer_make_tokens(l));
    vector *res = parser_analyze_syntax(p);
    size_t size_of_res = vector_size(res);
    size_t the_same_size_as_expected = vector_size(expected_result);

    assert_that_int(size_of_res equals to the_same_size_as_expected);

    if(size_of_res <= the_same_size_as_expected)
        for(size_t i = 0; i < size_of_res; i++)
            assert_that_charptr(string_get((string*)vector_get(res, i)) equals to string_get((string*)vector_get(expected_result, i)));
}

void debug(const char *code, vector *expected_result) {
    Lexer *l = lexer_new("file.marg", string_new(code));
    Parser *p = parser_new(lexer_make_tokens(l));
    vector *res = parser_analyze_syntax(p);
    size_t size_of_res = vector_size(res);
    size_t the_same_size_as_expected = vector_size(expected_result);
    printf("[");
    for(size_t i = 0; i < size_of_res-1; i++) {
        if(res == NULL || vector_get(res, i) == NULL or string_get((string*)vector_get(res, i)) == NULL)
            printf("(NULL), ");
        else
            printf("%s, ", string_get((string*)vector_get(res, i)));
    }
    if(res == NULL || vector_get(res, size_of_res-1) == NULL or string_get((string*)vector_get(res, size_of_res-1)) == NULL)
        printf("(NULL), ");
    else
        printf("%s]\n", string_get((string*)vector_get(res, size_of_res-1)));
  
    assert_that_int(size_of_res equals to the_same_size_as_expected);
  
    if(size_of_res <= the_same_size_as_expected)
        for(size_t i = 0; i < size_of_res; i++)
            assert_that_charptr(string_get((string*)vector_get(res, i)) equals to string_get((string*)vector_get(expected_result, i)));
}

void error(const char *code, const char *error_message) {
    Lexer *l = lexer_new("file.marg", string_new(code));
    Parser *p = parser_new(lexer_make_tokens(l));
    vector *res = parser_analyze_syntax(p);
    (void)res;
}

#endif
