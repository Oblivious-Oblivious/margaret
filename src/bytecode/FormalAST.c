#include "FormalAST.h"

#include "../opcode/fmcodes.h"
#include "alternate_to_dec.h"

#include <stdio.h> /* snprintf */

static int __all_keywords_equal(EmeraldsVector *selectors) {
  size_t selectors_size = vector_size(selectors);
  for(size_t i = 0; i < selectors_size; i++) {
    void *item = vector_get(selectors, i);
    if(!string_equals(
         vector_get(item, 0), vector_get(vector_get(selectors, 0), 0)
       )) {
      return 0;
    }
  }
  return 1;
}

EmeraldsVector *ast_empty(void) { return vector_new(NULL); }

EmeraldsVector *ast_first_unit(EmeraldsVector *unit) { return unit; }

EmeraldsVector *ast_translation_unit(
  EmeraldsVector *optional_assignment_list, EmeraldsVector *expr
) {
  EmeraldsVector *res = expr;

  size_t optional_assignment_list_size = vector_size(optional_assignment_list);
  for(size_t i = optional_assignment_list_size; i > 0; i--) {
    EmeraldsVector *item = vector_get(optional_assignment_list, i - 1);
    size_t item_size     = vector_size(item);
    for(size_t j = 0; j < item_size; j++) {
      vector_add(res, vector_get(item, j));
    }
  }
  vector_add(res, FM_POP);

  return res;
}

EmeraldsVector *ast_assignment(EmeraldsVector *id) {
  if(string_equals(vector_get(id, 0), FM_INSTANCE)) {
    return vector_new(FM_STORE_INSTANCE, vector_get(id, 1));
  } else if(string_equals(vector_get(id, 0), FM_GLOBAL)) {
    return vector_new(FM_STORE_GLOBAL, vector_get(id, 1));
  } else {
    return vector_new(FM_STORE_LOCAL, vector_get(id, 1));
  }
}

EmeraldsVector *ast_message(EmeraldsVector *msg) { return msg; }

EmeraldsVector *
ast_unary_message(EmeraldsVector *object, EmeraldsVector *selectors) {
  EmeraldsVector *res = vector_new_empty();

  size_t object_size = vector_size(object);
  for(size_t i = 0; i < object_size; i++) {
    vector_add(res, vector_get(object, i));
  }

  size_t selectors_size = vector_size(selectors);
  for(size_t i = 0; i < selectors_size; i++) {
    vector_add(res, FM_UNARY);
    vector_add(res, vector_get(vector_get(selectors, i), 0));
  }
  return res;
}

EmeraldsVector *ast_unary_object(EmeraldsVector *object) { return object; }

EmeraldsVector *
ast_unary_selector(EmeraldsString *id, EmeraldsString *optional_symbol) {
  EmeraldsString *sel = id;
  string_add(sel, optional_symbol);
  return vector_new(sel);
}

EmeraldsVector *
ast_binary_message(EmeraldsVector *object, EmeraldsVector *selectors) {
  EmeraldsVector *res = vector_new_empty();

  size_t object_size = vector_size(object);
  for(size_t i = 0; i < object_size; i++) {
    vector_add(res, vector_get(object, i));
  }

  size_t selectors_size = vector_size(selectors);
  for(size_t i = 0; i < selectors_size; i++) {
    EmeraldsVector *item = vector_get(vector_get(selectors, i), 1);
    size_t item_size     = vector_size(item);
    for(size_t j = 0; j < item_size; j++) {
      vector_add(res, vector_get(item, j));
    }

    vector_add(res, FM_BINARY);
    vector_add(res, vector_get(vector_get(selectors, i), 0));
  }
  return res;
}

EmeraldsVector *ast_binary_object(EmeraldsVector *object) { return object; }

EmeraldsVector *ast_binary_selector(EmeraldsString *sel, EmeraldsVector *obj) {
  return vector_new(sel, obj);
}

EmeraldsVector *
ast_keyword_message(EmeraldsVector *object, EmeraldsVector *selectors) {
  if(vector_size(selectors) > 1 && __all_keywords_equal(selectors)) {
    EmeraldsVector *res = vector_new_empty();

    size_t selectors_size = vector_size(selectors);
    for(size_t i = 0; i < selectors_size; i++) {
      EmeraldsString *sel0 = vector_get(vector_get(selectors, i), 0);
      EmeraldsVector *sel1 = vector_get(vector_get(selectors, i), 1);

      size_t object_size = vector_size(object);
      for(size_t j = 0; j < object_size; j++) {
        vector_add(res, vector_get(object, j));
      }

      size_t sel1_size = vector_size(sel1);
      for(size_t j = 0; j < sel1_size; j++) {
        vector_add(res, vector_get(sel1, j));
      }

      vector_add(res, FM_KEYWORD);
      vector_add(res, sel0);
      vector_add(res, string_new("1"));
    }
    return res;
  } else {
    EmeraldsString *joined_selector = string_new("");
    for(size_t i = 0; i < vector_size(selectors); i++) {
      string_add(joined_selector, vector_get(vector_get(selectors, i), 0));
    }

    EmeraldsVector *res = vector_new_empty();

    size_t object_size = vector_size(object);
    for(size_t i = 0; i < object_size; i++) {
      vector_add(res, vector_get(object, i));
    }

    size_t selectors_size = vector_size(selectors);
    for(size_t i = 0; i < selectors_size; i++) {
      EmeraldsVector *sel1 = vector_get(vector_get(selectors, i), 1);
      size_t sel1_size     = vector_size(sel1);
      for(size_t i = 0; i < sel1_size; i++) {
        vector_add(res, vector_get(sel1, i));
      }
    }

    vector_add(res, FM_KEYWORD);
    vector_add(res, joined_selector);
    char size_ptr[32];
    snprintf(size_ptr, sizeof(size_ptr), "%zu", vector_size(selectors));
    EmeraldsString *size = string_new(size_ptr);
    vector_add(res, size);
    return res;
  }
}

EmeraldsVector *ast_keyword_object(EmeraldsVector *object) { return object; }

EmeraldsVector *ast_keyword_selector(
  EmeraldsString *id,
  EmeraldsString *optional_symbol,
  EmeraldsString *delim,
  EmeraldsVector *obj
) {
  EmeraldsString *sel = string_new("");
  string_add(sel, id);
  string_add(sel, optional_symbol);
  string_add(sel, delim);

  return vector_new(sel, obj);
}

EmeraldsVector *ast_expression(EmeraldsVector *unit) { return unit; }

EmeraldsVector *ast_margaret_object(void) {
  return vector_new(FM_GLOBAL, string_new("$Margaret"));
}

EmeraldsVector *ast_group(EmeraldsVector *unit_list) {
  EmeraldsVector *res = vector_new_empty();

  size_t unit_list_size = vector_size(unit_list);
  for(size_t i = 0; i < unit_list_size; i++) {
    EmeraldsVector *item = vector_get(unit_list, i);
    size_t item_size     = vector_size(item);
    for(size_t j = 0; j < item_size; j++) {
      vector_add(res, vector_get(item, j));
    }
  }

  if(vector_size(res) == 0) {
    return vector_new(FM_NIL);
  } else {
    vector_remove_last(res);
    return res;
  }
}

EmeraldsVector *
ast_variable(EmeraldsString *optional_instance_symbol, EmeraldsString *name) {
  if(string_equals(optional_instance_symbol, string_new("$")) &&
     string_equals(name, string_new("nil"))) {
    return vector_new(FM_NIL);
  } else if(string_equals(optional_instance_symbol, string_new("$")) &&
            string_equals(name, string_new("true"))) {
    return vector_new(FM_TRUE);
  } else if(string_equals(optional_instance_symbol, string_new("$")) &&
            string_equals(name, string_new("false"))) {
    return vector_new(FM_FALSE);
  } else if(string_equals(optional_instance_symbol, string_new("@")) &&
            string_equals(name, string_new("self"))) {
    return vector_new(FM_SELF);
  } else if(string_equals(optional_instance_symbol, string_new("@")) &&
            string_equals(name, string_new("super"))) {
    return vector_new(FM_SUPER);
  } else if(string_equals(optional_instance_symbol, string_new("@"))) {
    string_add(optional_instance_symbol, name);
    return vector_new(FM_INSTANCE, optional_instance_symbol);
  } else if(string_equals(optional_instance_symbol, string_new("$"))) {
    string_add(optional_instance_symbol, name);
    return vector_new(FM_GLOBAL, optional_instance_symbol);
  } else {
    return vector_new(FM_LOCAL, name);
  }
}

EmeraldsVector *
ast_proc_literal(EmeraldsVector *param_list, EmeraldsVector *function) {
  EmeraldsVector *res = vector_new(FM_START_PROC);

  (void)param_list;

  // size_t param_list_size = vector_size(param_list);
  // for(size_t i = 0; i < param_list_size; i++) {
  //     vector_add(res, FM_PROC_PARAMETER);
  //     vector_add(res, vector_get(param_list, i));
  // }

  size_t valid_function_elements = 0;
  size_t function_size           = vector_size(function);
  for(size_t i = 0; i < function_size; i++) {
    if(vector_get(function, i) != NULL) {
      valid_function_elements++;
      vector_add(res, vector_get(function, i));
    }
  }

  if(valid_function_elements == 1) {
    vector_remove_last(res);
    vector_add(res, FM_NIL);
    vector_add(res, FM_POP);
  }

  vector_remove_last(res);
  vector_add(res, FM_END_PROC);
  return res;
}

EmeraldsVector *ast_c_function_declaration(
  EmeraldsString *return_type, EmeraldsString *name, EmeraldsVector *params
) {
  EmeraldsVector *res =
    vector_new(FM_START_C_FUNCTION, FM_LOCAL, return_type, FM_LOCAL, name);

  size_t params_size = vector_size(params);
  for(size_t i = 0; i < params_size; i++) {
    vector_add(res, FM_LOCAL);
    vector_add(res, string_new("CFunParam"));
    vector_add(res, FM_LOCAL);
    vector_add(res, vector_get(vector_get(params, i), 0));
    vector_add(res, FM_LOCAL);
    vector_add(res, vector_get(vector_get(params, i), 1));
    vector_add(res, FM_KEYWORD);
    vector_add(res, string_new("c_type:c_name:"));
    vector_add(res, string_new("2"));
  }

  vector_add(res, FM_TENSOR);
  char size_ptr[32];
  snprintf(size_ptr, sizeof(size_ptr), "%zu", vector_size(params));
  EmeraldsString *size = string_new(size_ptr);
  vector_add(res, size);
  vector_add(res, FM_END_C_FUNCTION);
  return res;
}

EmeraldsVector *ast_unary_method_definition(
  EmeraldsVector *multimethod_object_default_value,
  EmeraldsString *selector,
  EmeraldsVector *function
) {
  EmeraldsVector *res = vector_new(FM_START_UNARY_METHOD, selector);

  // TODO Hash method definition as a particular message instead of pattern
  // matching from `# 0 + 1 => 1` we derive: HASHED("MARG_0 + MARG_1") from `# +
  // other => self + other` we derive default HASHED("+")
  (void)multimethod_object_default_value;

  // size_t multimethod_object_default_value_size =
  // vector_size(multimethod_object_default_value); for(size_t i = 0; i <
  // multimethod_object_default_value_size; i++)
  //     vector_add(res, vector_get(multimethod_object_default_value, i));
  // vector_add(res, FM_METHOD_RECEIVER);

  size_t function_size = vector_size(function);
  for(size_t i = 0; i < function_size; i++) {
    vector_add(res, vector_get(function, i));
  }

  vector_remove_last(res);
  vector_add(res, FM_END_UNARY_METHOD);

  return res;
}

EmeraldsVector *ast_binary_method_definition(
  EmeraldsVector *multimethod_object_default_value,
  EmeraldsString *selector,
  EmeraldsVector *param,
  EmeraldsVector *function
) {
  EmeraldsVector *res = vector_new(FM_START_BINARY_METHOD, selector);

  (void)multimethod_object_default_value;

  // size_t multimethod_object_default_value_size =
  // vector_size(multimethod_object_default_value); for(size_t i = 0; i <
  // multimethod_object_default_value_size; i++)
  //     vector_add(res, vector_get(multimethod_object_default_value, i));
  // vector_add(res, FM_METHOD_RECEIVER);

  // TODO Refactor assumption that we define methods with named parameters
  vector_add(res, FM_METHOD_PARAMETER);
  if(vector_size(param) == 1) {
    vector_add(res, vector_get(param, 0));
  } else {
    vector_add(res, vector_get(param, 1));
  }

  size_t function_size = vector_size(function);
  for(size_t i = 0; i < function_size; i++) {
    vector_add(res, vector_get(function, i));
  }

  vector_remove_last(res);
  vector_add(res, FM_END_BINARY_METHOD);

  return res;
}

EmeraldsVector *ast_keyword_method_definition(
  EmeraldsVector *multimethod_object_default_value,
  EmeraldsString *selector,
  EmeraldsVector *params,
  EmeraldsVector *function
) {
  EmeraldsVector *res = vector_new(FM_START_KEYWORD_METHOD, selector);

  (void)multimethod_object_default_value;

  // size_t multimethod_object_default_value_size =
  // vector_size(multimethod_object_default_value); for(size_t i = 0; i <
  // multimethod_object_default_value_size; i++)
  //     vector_add(res, vector_get(multimethod_object_default_value, i));
  // vector_add(res, FM_METHOD_RECEIVER);

  size_t params_size = vector_size(params);
  for(size_t i = 0; i < params_size; i++) {
    EmeraldsVector *param = vector_get(params, i);
    // TODO Refactor assumption that we define methods with named parameters
    vector_add(res, FM_METHOD_PARAMETER);
    if(vector_size(param) == 1) {
      vector_add(res, vector_get(param, 0));
    } else {
      vector_add(res, vector_get(param, 1));
    }
  }

  size_t function_size = vector_size(function);
  for(size_t i = 0; i < function_size; i++) {
    vector_add(res, vector_get(function, i));
  }

  vector_remove_last(res);
  vector_add(res, FM_END_KEYWORD_METHOD);

  return res;
}

EmeraldsVector *ast_any_object(void) { return vector_new(FM_ANY_OBJECT); }

EmeraldsVector *ast_literal(EmeraldsVector *unit) { return unit; }

EmeraldsVector *ast_nil_literal(void) { return vector_new(FM_NIL); }

EmeraldsVector *ast_false_literal(void) { return vector_new(FM_FALSE); }

EmeraldsVector *ast_true_literal(void) { return vector_new(FM_TRUE); }

EmeraldsVector *
ast_integer_literal(EmeraldsString *sign, EmeraldsString *number) {
  number = string_remove_underscores(number);

  if(string_get_char_at_index(number, 0) == '0' &&
     (string_get_char_at_index(number, 1) == 'b' ||
      string_get_char_at_index(number, 1) == 'B')) {
    string_skip(number, 2);
    number = string_new(bin_to_dec(string_get(number)));
  } else if(string_get_char_at_index(number, 0) == '0' &&
            (string_get_char_at_index(number, 1) == 'o' ||
             string_get_char_at_index(number, 1) == 'O')) {
    string_skip(number, 2);
    number = string_new(oct_to_dec(string_get(number)));
  } else if(string_get_char_at_index(number, 0) == '0' &&
            (string_get_char_at_index(number, 1) == 'x' ||
             string_get_char_at_index(number, 1) == 'X')) {
    string_skip(number, 2);
    number = string_new(hex_to_dec(string_get(number)));
  }

  if(string_equals(sign, string_new("-"))) {
    EmeraldsString *inum = string_new("");
    string_add(inum, sign);
    string_add(inum, number);

    return vector_new(FM_INTEGER, inum);
  } else {
    return vector_new(FM_INTEGER, number);
  }
}

EmeraldsVector *
ast_float_literal(EmeraldsString *sign, EmeraldsString *number) {
  EmeraldsString *f = string_new("");
  string_add(f, sign);
  string_add(f, string_remove_underscores(number));

  return vector_new(FM_FLOAT, f);
}

EmeraldsVector *ast_string_literal(EmeraldsString *string) {
  string_skip(string, 1);
  string_shorten(string, string_size(string) - 1);
  return vector_new(FM_STRING, string);
}

EmeraldsVector *ast_tensor_literal(EmeraldsVector *item_list) {
  EmeraldsVector *res = vector_new_empty();

  size_t item_list_size = vector_size(item_list);
  for(size_t i = 0; i < item_list_size; i++) {
    EmeraldsVector *item = vector_get(item_list, i);
    size_t item_size     = vector_size(item);
    for(size_t j = 0; j < item_size; j++) {
      vector_add(res, vector_get(item, j));
    }
    vector_remove_last(res);
  }

  vector_add(res, FM_TENSOR);
  char size_ptr[32];
  snprintf(size_ptr, sizeof(size_ptr), "%zu", vector_size(item_list));
  EmeraldsString *size = string_new(size_ptr);
  vector_add(res, size);
  return res;
}

EmeraldsVector *ast_tuple_literal(EmeraldsVector *item_list) {
  EmeraldsVector *res = vector_new_empty();

  size_t item_list_size = vector_size(item_list);
  for(size_t i = 0; i < item_list_size; i++) {
    EmeraldsVector *item = vector_get(item_list, i);
    size_t item_size     = vector_size(item);
    for(size_t j = 0; j < item_size; j++) {
      vector_add(res, vector_get(item, j));
    }
    vector_remove_last(res);
  }

  vector_add(res, FM_TUPLE);
  char size_ptr[32];
  snprintf(size_ptr, sizeof(size_ptr), "%zu", vector_size(item_list));
  EmeraldsString *size = string_new(size_ptr);
  vector_add(res, size);
  return res;
}

EmeraldsVector *ast_hash_literal(EmeraldsVector *association_list) {
  EmeraldsVector *res = vector_new_empty();

  size_t association_list_size = vector_size(association_list);
  for(size_t i = 0; i < association_list_size; i++) {
    EmeraldsVector *item = vector_get(association_list, i);
    size_t item_size     = vector_size(item);
    for(size_t j = 0; j < item_size; j++) {
      vector_add(res, vector_get(item, j));
    }
    vector_remove_last(res);
  }

  vector_add(res, FM_HASH);
  char size_ptr[32];
  snprintf(
    size_ptr, sizeof(size_ptr), "%zu", vector_size(association_list) * 2
  );
  EmeraldsString *size = string_new(size_ptr);
  vector_add(res, size);
  return res;
}

EmeraldsVector *ast_association(EmeraldsVector *key, EmeraldsVector *value) {
  EmeraldsVector *res = vector_new_empty();

  size_t key_size = vector_size(key);
  for(size_t i = 0; i < key_size; i++) {
    vector_add(res, vector_get(key, i));
  }

  size_t value_size = vector_size(value);
  for(size_t i = 0; i < value_size; i++) {
    vector_add(res, vector_get(value, i));
  }

  return res;
}

EmeraldsVector *
ast_json_association(EmeraldsString *key, EmeraldsVector *value) {
  EmeraldsVector *res = vector_new_empty();
  vector_add(res, FM_STRING);
  vector_add(res, key);

  size_t value_size = vector_size(value);
  for(size_t i = 0; i < value_size; i++) {
    vector_add(res, vector_get(value, i));
  }

  return res;
}

EmeraldsVector *ast_bitstring_literal(EmeraldsVector *item_list) {
  EmeraldsVector *res   = vector_new_empty();
  size_t item_list_size = vector_size(item_list);

  for(size_t i = 0; i < item_list_size; i++) {
    EmeraldsVector *item = vector_get(item_list, i);
    size_t item_size     = vector_size(item);
    for(size_t j = 0; j < item_size; j++) {
      vector_add(res, vector_get(item, j));
    }
  }

  vector_add(res, FM_BITSTRING);
  char size_ptr[32];
  snprintf(size_ptr, sizeof(size_ptr), "%zu", vector_size(item_list) * 2);
  EmeraldsString *size = string_new(size_ptr);
  vector_add(res, size);
  return res;
}

EmeraldsVector *ast_bit_literal(EmeraldsVector *bit) {
  EmeraldsVector *res = vector_new_empty();

  size_t bit_length = vector_size(bit);
  for(size_t i = 0; i < bit_length; i++) {
    vector_add(res, vector_get(bit, i));
  }

  vector_add(res, FM_INTEGER);
  vector_add(res, string_new("8"));

  return res;
}

EmeraldsVector *
ast_bit_size_literal(EmeraldsVector *bit, EmeraldsVector *size) {
  EmeraldsVector *res = vector_new_empty();

  size_t bit_length = vector_size(bit);
  for(size_t i = 0; i < bit_length; i++) {
    vector_add(res, vector_get(bit, i));
  }

  size_t size_length = vector_size(size);
  for(size_t i = 0; i < size_length; i++) {
    vector_add(res, vector_get(size, i));
  }

  return res;
}
