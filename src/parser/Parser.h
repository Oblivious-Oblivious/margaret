#ifndef __PARSER_H_
#define __PARSER_H_

#include "../tokens/TokenTable.h"

/**
 * @brief Simple wrapper struct over a token table
    Does not store any additional information so we
    namespace with `Parser` for code clarity
 */
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
 * @return EmeraldsVector* -> A vector of opcodes
 */
EmeraldsVector *parser_analyze_syntax(Parser *self);

EmeraldsVector *parser_first_unit(Parser *self);
EmeraldsVector *parser_translation_unit(Parser *self);
EmeraldsVector *parser_assignment_chain(Parser *self);
EmeraldsVector *parser_assignment(Parser *self);

EmeraldsVector *parser_message(Parser *self);
EmeraldsVector *parser_unary_message(Parser *self);
EmeraldsVector *parser_unary_object(Parser *self);
EmeraldsVector *parser_unary_selector(Parser *self);
EmeraldsVector *parser_binary_message(Parser *self);
EmeraldsVector *parser_binary_object(Parser *self);
EmeraldsVector *parser_binary_selector(Parser *self);
EmeraldsVector *parser_keyword_message(Parser *self);
EmeraldsVector *parser_keyword_object(Parser *self);
EmeraldsVector *parser_keyword_selector(Parser *self);

EmeraldsVector *parser_expression(Parser *self);
EmeraldsVector *parser_group(Parser *self);
EmeraldsVector *parser_variable(Parser *self);
EmeraldsVector *parser_proc_literal(Parser *self);
EmeraldsVector *parser_c_function_declaration(Parser *self);
EmeraldsVector *parser_method_definition_literal(Parser *self);
EmeraldsVector *parser_unary_method_definition(
  Parser *self, EmeraldsVector *multimethod_object_default_value
);
EmeraldsVector *parser_binary_method_definition(
  Parser *self, EmeraldsVector *multimethod_object_default_value
);
EmeraldsVector *parser_keyword_method_definition(
  Parser *self, EmeraldsVector *multimethod_object_default_value
);
EmeraldsVector *parser_any_object(void);

EmeraldsVector *parser_literal(Parser *self);
EmeraldsVector *parser_nil_literal(Parser *self);
EmeraldsVector *parser_false_literal(Parser *self);
EmeraldsVector *parser_true_literal(Parser *self);
EmeraldsVector *parser_integer_literal(Parser *self, EmeraldsString *sign);
EmeraldsVector *parser_float_literal(Parser *self, EmeraldsString *sign);
EmeraldsVector *parser_string_literal(Parser *self);
EmeraldsVector *parser_tuple_literal(Parser *self);
EmeraldsVector *parser_tensor_literal(Parser *self);
EmeraldsVector *parser_bitstring_literal(Parser *self);
EmeraldsVector *parser_hash_literal(Parser *self);
EmeraldsVector *parser_bit_literal(Parser *self);
EmeraldsVector *parser_association_literal(Parser *self);

#endif
