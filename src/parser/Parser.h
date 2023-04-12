#ifndef __PARSER_H_
#define __PARSER_H_

#include "../base/marg_string.h"
#include "../base/marg_vector.h"
#include "../tokens/TokenTable.h"

typedef struct Parser {
    TokenTable *table;
} Parser;

/**
 * @brief Constructs a new Parser object
 * @param tokens -> The list of tokens analyzed in the lexer
 * @return Parser* 
 */
Parser *parser_new(TokenTable *tokens);

/**
 * @brief Starts the parsing process
 * @param self -> The parser object
 * @return marg_vector* -> A vector of opcodes
 */
marg_vector *parser_analyze_syntax(Parser *self);

marg_vector *parser_first_unit(Parser *self);
marg_vector *parser_translation_unit(Parser *self);
marg_vector *parser_assignment_chain(Parser *self);
marg_vector *parser_assignment(Parser *self);

marg_vector *parser_message(Parser *self);
marg_vector *parser_unary_message(Parser *self);
marg_vector *parser_unary_object(Parser *self);
marg_vector *parser_unary_selector(Parser *self);
marg_vector *parser_binary_message(Parser *self);
marg_vector *parser_binary_object(Parser *self);
marg_vector *parser_binary_selector(Parser *self);
marg_vector *parser_keyword_message(Parser *self);
marg_vector *parser_keyword_object(Parser *self);
marg_vector *parser_keyword_selector(Parser *self);

marg_vector *parser_expression(Parser *self);
marg_vector *parser_group(Parser *self);
marg_vector *parser_variable(Parser *self);
marg_vector *parser_proc_literal(Parser *self);
marg_vector *parser_c_function_declaration(Parser *self);
marg_vector *parser_method_definition_literal(Parser *self);
marg_vector *parser_unary_method_definition(Parser *self);
marg_vector *parser_binary_method_definition(Parser *self);
marg_vector *parser_keyword_method_definition(Parser *self);

marg_vector *parser_literal(Parser *self);
marg_vector *parser_integer_literal(Parser *self, marg_string *sign);
marg_vector *parser_float_literal(Parser *self, marg_string *sign);
marg_vector *parser_char_literal(Parser *self, marg_string *sign);
marg_vector *parser_string_literal(Parser *self);
marg_vector *parser_tuple_literal(Parser *self);
marg_vector *parser_tensor_literal(Parser *self);
marg_vector *parser_bitstring_literal(Parser *self);
marg_vector *parser_hash_literal(Parser *self);
marg_vector *parser_bit_literal(Parser *self);
marg_vector *parser_association_literal(Parser *self);

#endif
