#ifndef __PARSER_H_
#define __PARSER_H_

#include "../base/string.h"
#include "../base/vector.h"
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
 * @return vector* -> A vector of opcodes
 */
vector *parser_analyze_syntax(Parser *self);

vector *parser_first_unit(Parser *self);
vector *parser_translation_unit(Parser *self);
vector *parser_assignment_chain(Parser *self);
vector *parser_assignment(Parser *self);

vector *parser_message(Parser *self);
vector *parser_unary_message(Parser *self);
vector *parser_unary_object(Parser *self);
vector *parser_unary_selector(Parser *self);
vector *parser_binary_message(Parser *self);
vector *parser_binary_object(Parser *self);
vector *parser_binary_selector(Parser *self);
vector *parser_keyword_message(Parser *self);
vector *parser_keyword_object(Parser *self);
vector *parser_keyword_selector(Parser *self);

vector *parser_expression(Parser *self);
vector *parser_group(Parser *self);
vector *parser_variable(Parser *self);
vector *parser_proc_literal(Parser *self);
vector *parser_c_function_declaration(Parser *self);
vector *parser_method_definition_literal(Parser *self);
vector *parser_unary_method_definition(Parser *self, vector *multimethod_object_default_value);
vector *parser_binary_method_definition(Parser *self, vector *multimethod_object_default_value);
vector *parser_keyword_method_definition(Parser *self, vector *multimethod_object_default_value);
vector *parser_any_object(void);
vector *parser_method_parameter(string *param_name);
vector *parser_global_primitive_method_parameter(string *param_name);

vector *parser_literal(Parser *self);
vector *parser_integer_literal(Parser *self, string *sign);
vector *parser_float_literal(Parser *self, string *sign);
vector *parser_string_literal(Parser *self);
vector *parser_tuple_literal(Parser *self);
vector *parser_tensor_literal(Parser *self);
vector *parser_bitstring_literal(Parser *self);
vector *parser_hash_literal(Parser *self);
vector *parser_bit_literal(Parser *self);
vector *parser_association_literal(Parser *self);

#endif
