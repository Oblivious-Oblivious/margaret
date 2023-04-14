#ifndef __BYTECODE_H_
#define __BYTECODE_H_

#include "../base/marg_string.h"
#include "../base/marg_vector.h"
#include "../opcode/Opcode.h"

marg_vector *ast_empty(void);

marg_vector *ast_first_unit(marg_vector *unit);
marg_vector *ast_translation_unit(marg_vector *optional_assignment_list, marg_vector *expr);
marg_vector *ast_assignment(marg_vector *id);

marg_vector *ast_message(marg_vector *msg);
marg_vector *ast_unary_message(marg_vector *object, marg_vector *selectors);
marg_vector *ast_unary_object(marg_vector *object);
marg_vector *ast_unary_selector(marg_string *id, marg_string *optional_symbol);
marg_vector *ast_binary_message(marg_vector *object, marg_vector *selectors);
marg_vector *ast_binary_object(marg_vector *object);
marg_vector *ast_binary_selector(marg_string *sel, marg_vector *obj);
marg_vector *ast_keyword_message(marg_vector *object, marg_vector *selectors);
marg_vector *ast_keyword_object(marg_vector *object);
marg_vector *ast_keyword_selector(marg_string *id, marg_string *optional_symbol, marg_string *delim, marg_vector *obj);

marg_vector *ast_expression(marg_vector *unit);
marg_vector *ast_margaret_object(void);
marg_vector *ast_group(marg_vector *unit_list);
marg_vector *ast_variable(marg_string *optional_instance_symbol, marg_string *name);
marg_vector *ast_proc_literal(marg_vector *param_list, marg_vector *function);
marg_vector *ast_c_function_declaration(marg_string *return_type, marg_string *name, marg_vector *params);
marg_vector *ast_unary_method_definition(marg_vector *multimethod_object_default_value, marg_string *selector, marg_vector *function);
marg_vector *ast_binary_method_definition(marg_vector *multimethod_object_default_value, marg_string *selector, marg_vector *param, marg_vector *function);
marg_vector *ast_keyword_method_definition(marg_vector *multimethod_object_default_value, marg_string *selector, marg_vector *params, marg_vector *function);
marg_vector *ast_any_object(void);
marg_vector *ast_method_parameter(marg_string *param_name);

marg_vector *ast_literal(marg_vector *unit);
marg_vector *ast_integer_literal(marg_string *sign, marg_string *number);
marg_vector *ast_float_literal(marg_string *sign, marg_string *number);
marg_vector *ast_char_literal(marg_string *sign, marg_string *c);
marg_vector *ast_string_literal(marg_string *string);
marg_vector *ast_tuple_literal(marg_vector *item_list);
marg_vector *ast_tensor_literal(marg_vector *item_list);
marg_vector *ast_bitstring_literal(marg_vector *item_list);
marg_vector *ast_hash_literal(marg_vector *association_list);
marg_vector *ast_bit_literal(marg_vector *bit);
marg_vector *ast_bit_size_literal(marg_vector *bit, marg_vector *size);
marg_vector *ast_association(marg_vector *key, marg_vector *value);
marg_vector *ast_json_association(marg_string *key, marg_vector *value);

#endif
