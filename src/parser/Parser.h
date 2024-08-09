#ifndef __PARSER_H_
#define __PARSER_H_

#include "../tokens/TokenTable.h"

/**
 * @brief Starts the parsing process
 * @param table -> The parser token table
 * @return -> A vector of opcodes
 */
char **parser_analyze_syntax(Token **table);

void parser_first_unit(Token **table, char ***fmcodes);
char *parser_unit_list(Token **table, char ***fmcodes);
void parser_unit(Token **table, char ***fmcodes);
void parser_assignment_message(Token **table, char ***fmcodes);
void parser_assignment_selector_chain(Token **table, char ***fmcodes);
void parser_keyword_message(Token **table, char ***fmcodes);
void parser_keyword_selector_chain(Token **table, char ***fmcodes);
void parser_binary_message(Token **table, char ***fmcodes);
void parser_binary_selector_chain(Token **table, char ***fmcodes);
void parser_unary_message(Token **table, char ***fmcodes);
void parser_unary_selector_chain(Token **table, char ***fmcodes);
void parser_lhs_message(Token **table, char ***fmcodes);
void parser_literal(Token **table, char ***fmcodes);
void parser_param_list(Token **table, char ***fmcodes);
char *parser_bit_list(Token **table, char ***fmcodes);
void parser_bit(Token **table, char ***fmcodes);
char *parser_association_list(Token **table, char ***fmcodes);
void parser_key(Token **table, char ***fmcodes);
void parser_method_definition(Token **table, char ***fmcodes);
char *parser_keyword_list(Token **table, char ***fmcodes);
void parser_scalar(Token **table, char ***fmcodes);
void parser_variable(Token **table, char ***fmcodes);

#endif
