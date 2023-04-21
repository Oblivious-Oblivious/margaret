#ifndef __FORMAL_AST_H_
#define __FORMAL_AST_H_

#include "../base/string.h"
#include "../base/vector.h"
#include "../opcode/Opcodes.h"

vector *ast_empty(void);

vector *ast_first_unit(vector *unit);
vector *ast_translation_unit(vector *optional_assignment_list, vector *expr);
vector *ast_assignment(vector *id);

vector *ast_message(vector *msg);
vector *ast_unary_message(vector *object, vector *selectors);
vector *ast_unary_object(vector *object);
vector *ast_unary_selector(string *id, string *optional_symbol);
vector *ast_binary_message(vector *object, vector *selectors);
vector *ast_binary_object(vector *object);
vector *ast_binary_selector(string *sel, vector *obj);
vector *ast_keyword_message(vector *object, vector *selectors);
vector *ast_keyword_object(vector *object);
vector *ast_keyword_selector(string *id, string *optional_symbol, string *delim, vector *obj);

vector *ast_expression(vector *unit);
vector *ast_margaret_object(void);
vector *ast_group(vector *unit_list);
vector *ast_variable(string *optional_instance_symbol, string *name);
vector *ast_proc_literal(vector *param_list, vector *function);
vector *ast_c_function_declaration(string *return_type, string *name, vector *params);
vector *ast_unary_method_definition(vector *multimethod_object_default_value, string *selector, vector *function);
vector *ast_binary_method_definition(vector *multimethod_object_default_value, string *selector, vector *param, vector *function);
vector *ast_keyword_method_definition(vector *multimethod_object_default_value, string *selector, vector *params, vector *function);
vector *ast_any_object(void);
vector *ast_method_parameter(string *param_name);

vector *ast_literal(vector *unit);
vector *ast_integer_literal(string *sign, string *number);
vector *ast_float_literal(string *sign, string *number);
vector *ast_string_literal(string *string);
vector *ast_tuple_literal(vector *item_list);
vector *ast_tensor_literal(vector *item_list);
vector *ast_bitstring_literal(vector *item_list);
vector *ast_hash_literal(vector *association_list);
vector *ast_bit_literal(vector *bit);
vector *ast_bit_size_literal(vector *bit, vector *size);
vector *ast_association(vector *key, vector *value);
vector *ast_json_association(string *key, vector *value);

#endif
