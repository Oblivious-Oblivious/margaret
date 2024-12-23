#ifndef __PARSER_H_
#define __PARSER_H_

#include "../vm/vm.h"

/**
 * @brief Consumes token
 * @param vm -> The vm containing the token table
 * @param type -> The type expecting to consume
 * @param error_msg -> Prints in case of consumption of wrong type
 * @return string*
 */
char *parser_consume(VM *vm, Type type, const char *error_msg);

/**
 * @brief Starts the parsing process and constructs the token table
 * @param vm -> The VM object
 * @return VM* -> The VM object
 */
VM *parser_analyze_syntax(VM *vm);

void parser_first_unit(VM *vm);
char *parser_unit_list(VM *vm, bool in_group);
void parser_unit(VM *vm);
void parser_assignment_message(VM *vm);
void parser_keyword_message(VM *vm);
void parser_keyword_selector_chain(VM *vm);
void parser_binary_message(VM *vm);
void parser_binary_selector_chain(VM *vm);
void parser_unary_message(VM *vm);
void parser_unary_selector_chain(VM *vm);
void parser_lhs_message(VM *vm);
void parser_subscript_message(VM *vm);
void parser_subscript_selector_chain(VM *vm);
void parser_literal(VM *vm);
void parser_param_list(VM *vm);
char *parser_bit_list(VM *vm);
void parser_bit(VM *vm);
char *parser_association_list(VM *vm);
void parser_key(VM *vm);
void parser_method_definition(VM *vm);
void parser_method_body(VM *vm);
char *parser_keyword_list(VM *vm);
void parser_scalar(VM *vm);
void parser_variable(VM *vm);

#endif
