#ifndef __FORMAL_AST_H_
#define __FORMAL_AST_H_

#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../libs/EmeraldsVector/export/EmeraldsVector.h"

EmeraldsVector *ast_empty(void);

EmeraldsVector *ast_first_unit(EmeraldsVector *unit);
EmeraldsVector *ast_translation_unit(
  EmeraldsVector *optional_assignment_list, EmeraldsVector *expr
);
EmeraldsVector *ast_assignment(EmeraldsVector *id);

EmeraldsVector *ast_message(EmeraldsVector *msg);
EmeraldsVector *
ast_unary_message(EmeraldsVector *object, EmeraldsVector *selectors);
EmeraldsVector *ast_unary_object(EmeraldsVector *object);
EmeraldsVector *
ast_unary_selector(EmeraldsString *id, EmeraldsString *optional_symbol);
EmeraldsVector *
ast_binary_message(EmeraldsVector *object, EmeraldsVector *selectors);
EmeraldsVector *ast_binary_object(EmeraldsVector *object);
EmeraldsVector *ast_binary_selector(EmeraldsString *sel, EmeraldsVector *obj);
EmeraldsVector *
ast_keyword_message(EmeraldsVector *object, EmeraldsVector *selectors);
EmeraldsVector *ast_keyword_object(EmeraldsVector *object);
EmeraldsVector *ast_keyword_selector(
  EmeraldsString *id,
  EmeraldsString *optional_symbol,
  EmeraldsString *delim,
  EmeraldsVector *obj
);

EmeraldsVector *ast_expression(EmeraldsVector *unit);
EmeraldsVector *ast_margaret_object(void);
EmeraldsVector *ast_group(EmeraldsVector *unit_list);
EmeraldsVector *
ast_variable(EmeraldsString *optional_instance_symbol, EmeraldsString *name);
EmeraldsVector *
ast_proc_literal(EmeraldsVector *param_list, EmeraldsVector *function);
EmeraldsVector *ast_c_function_declaration(
  EmeraldsString *return_type, EmeraldsString *name, EmeraldsVector *params
);
EmeraldsVector *ast_unary_method_definition(
  EmeraldsVector *multimethod_object_default_value,
  EmeraldsString *selector,
  EmeraldsVector *function
);
EmeraldsVector *ast_binary_method_definition(
  EmeraldsVector *multimethod_object_default_value,
  EmeraldsString *selector,
  EmeraldsVector *param,
  EmeraldsVector *function
);
EmeraldsVector *ast_keyword_method_definition(
  EmeraldsVector *multimethod_object_default_value,
  EmeraldsString *selector,
  EmeraldsVector *params,
  EmeraldsVector *function
);
EmeraldsVector *ast_any_object(void);

EmeraldsVector *ast_literal(EmeraldsVector *unit);
EmeraldsVector *ast_nil_literal(void);
EmeraldsVector *ast_false_literal(void);
EmeraldsVector *ast_true_literal(void);
EmeraldsVector *
ast_integer_literal(EmeraldsString *sign, EmeraldsString *number);
EmeraldsVector *ast_float_literal(EmeraldsString *sign, EmeraldsString *number);
EmeraldsVector *ast_string_literal(EmeraldsString *string);
EmeraldsVector *ast_tuple_literal(EmeraldsVector *item_list);
EmeraldsVector *ast_tensor_literal(EmeraldsVector *item_list);
EmeraldsVector *ast_bitstring_literal(EmeraldsVector *item_list);
EmeraldsVector *ast_hash_literal(EmeraldsVector *association_list);
EmeraldsVector *ast_bit_literal(EmeraldsVector *bit);
EmeraldsVector *ast_bit_size_literal(EmeraldsVector *bit, EmeraldsVector *size);
EmeraldsVector *ast_association(EmeraldsVector *key, EmeraldsVector *value);
EmeraldsVector *
ast_json_association(EmeraldsString *key, EmeraldsVector *value);

#endif
