#include "FormalAST.h"

#include <stdio.h> /* snprintf */
#include "alternate_to_dec.h"

static int __all_keywords_equal(vector *selectors) {
    size_t selectors_size = vector_size(selectors);
    for(size_t i = 0; i < selectors_size; i++) {
        void *item = vector_get(selectors, i);
        if(!string_equals(vector_get(item, 0), vector_get(vector_get(selectors, 0), 0)))
            return 0;
    }
    return 1;
}

vector *ast_empty(void) {
    return vector_new(NULL);
}

vector *ast_first_unit(vector *unit) {
    return unit;
}

vector *ast_translation_unit(vector *optional_assignment_list, vector *expr) {
    vector *res = expr;

    size_t optional_assignment_list_size = vector_size(optional_assignment_list);
    for(size_t i = optional_assignment_list_size; i > 0; i--) {
        vector *item = vector_get(optional_assignment_list, i-1);
        size_t item_size = vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            vector_add(res, vector_get(item, j));
    }

    return res;
}

vector *ast_assignment(vector *id) {
    if(string_equals(vector_get(id, 0), FM_INSTANCE))
        return vector_new(FM_STORE_INSTANCE, vector_get(id, 1));
    else if(string_equals(vector_get(id, 0), FM_GLOBAL))
        return vector_new(FM_STORE_GLOBAL, vector_get(id, 1));
    else
        return vector_new(FM_STORE_LOCAL, vector_get(id, 1));
}

vector *ast_message(vector *msg) {
    return msg;
}

vector *ast_unary_message(vector *object, vector *selectors) {
    vector *res = vector_new_empty();

    size_t object_size = vector_size(object);
    for(size_t i = 0; i < object_size; i++)
        vector_add(res, vector_get(object, i));

    size_t selectors_size = vector_size(selectors);
    for(size_t i = 0; i < selectors_size; i++) {
        vector_add(res, FM_UNARY);
        vector_add(res, vector_get(vector_get(selectors, i), 0));
    }
    return res;
}

vector *ast_unary_object(vector *object) {
    return object;
}

vector *ast_unary_selector(string *id, string *optional_symbol) {
    string *sel = id;
    string_add(sel, optional_symbol);
    return vector_new(sel);
}

vector *ast_binary_message(vector *object, vector *selectors) {
    vector *res = vector_new_empty();

    size_t object_size = vector_size(object);
    for(size_t i = 0; i < object_size; i++)
        vector_add(res, vector_get(object, i));
    
    size_t selectors_size = vector_size(selectors);
    for(size_t i = 0; i < selectors_size; i++) {
        vector *item = vector_get(vector_get(selectors, i), 1);
        size_t item_size = vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            vector_add(res, vector_get(item, j));

        vector_add(res, FM_BINARY);
        vector_add(res, vector_get(vector_get(selectors, i), 0));
    }
    return res;
}

vector *ast_binary_object(vector *object) {
    return object;
}

vector *ast_binary_selector(string *sel, vector *obj) {
    return vector_new(sel, obj);
}

vector *ast_keyword_message(vector *object, vector *selectors) {
    if(vector_size(selectors) > 1 && __all_keywords_equal(selectors)) {
        vector *res = vector_new_empty();

        size_t selectors_size = vector_size(selectors);
        for(size_t i = 0; i < selectors_size; i++) {
            string *sel0 = vector_get(vector_get(selectors, i), 0);
            vector *sel1 = vector_get(vector_get(selectors, i), 1);

            size_t object_size = vector_size(object);
            for(size_t j = 0; j < object_size; j++)
                vector_add(res, vector_get(object, j));
            
            size_t sel1_size = vector_size(sel1);
            for(size_t j = 0; j < sel1_size; j++)
                vector_add(res, vector_get(sel1, j));

            vector_add(res, FM_KEYWORD);
            vector_add(res, sel0);
            vector_add(res, string_new("1"));
        }
        return res;
    }
    else {
        string *joined_selector = string_new("");
        for(size_t i = 0; i < vector_size(selectors); i++)
            string_add(joined_selector, vector_get(vector_get(selectors, i), 0));

        vector *res = vector_new_empty();

        size_t object_size = vector_size(object);
        for(size_t i = 0; i < object_size; i++)
            vector_add(res, vector_get(object, i));
        
        size_t selectors_size = vector_size(selectors);
        for(size_t i = 0; i < selectors_size; i++) {
            vector *sel1 = vector_get(vector_get(selectors, i), 1);
            size_t sel1_size = vector_size(sel1);
            for(size_t i = 0; i < sel1_size; i++)
                vector_add(res, vector_get(sel1, i));
        }
 
        vector_add(res, FM_KEYWORD);
        vector_add(res, joined_selector);
        char size_ptr[32];
        snprintf(size_ptr, sizeof(size_ptr), "%zu", vector_size(selectors));
        string *size = string_new(size_ptr);
        vector_add(res, size);
        return res;
    }
}

vector *ast_keyword_object(vector *object) {
    return object;
}

vector *ast_keyword_selector(string *id, string *optional_symbol, string *delim, vector *obj) {
    string *sel = string_new("");
    string_add(sel, id);
    string_add(sel, optional_symbol);
    string_add(sel, delim);

    return vector_new(sel, obj);
}

vector *ast_expression(vector *unit) {
    return unit;
}

vector *ast_margaret_object(void) {
    return vector_new(FM_GLOBAL, string_new("Margaret"));
}

vector *ast_group(vector *unit_list) {
    vector *res = vector_new_empty();

    size_t unit_list_size = vector_size(unit_list);
    for(size_t i = 0; i < unit_list_size; i++) {
        vector *item = vector_get(unit_list, i);
        size_t item_size = vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            vector_add(res, vector_get(item, j));
    }

    if(vector_size(res) == 0)
        return vector_new(FM_NIL);
    else
        return res;
}

vector *ast_variable(string *optional_instance_symbol, string *name) {
    if(string_equals(optional_instance_symbol, string_new("$")) && string_equals(name, string_new("nil")))
        return vector_new(FM_NIL);
    else if(string_equals(optional_instance_symbol, string_new("$")) && string_equals(name, string_new("true")))
        return vector_new(FM_TRUE);
    else if(string_equals(optional_instance_symbol, string_new("$")) && string_equals(name, string_new("false")))
        return vector_new(FM_FALSE);
    else if(string_equals(optional_instance_symbol, string_new("@")) && string_equals(name, string_new("self")))
        return vector_new(FM_SELF);
    else if(string_equals(optional_instance_symbol, string_new("@")) && string_equals(name, string_new("super")))
        return vector_new(FM_SUPER);
    else if(string_equals(optional_instance_symbol, string_new("@")))
        return vector_new(FM_INSTANCE, name);
    else if(string_equals(optional_instance_symbol, string_new("$")))
        return vector_new(FM_GLOBAL, name);
    else
        return vector_new(FM_LOCAL, name);
}

vector *ast_proc_literal(vector *param_list, vector *function) {
    vector *res = vector_new(FM_START_PROC);

    size_t param_list_size = vector_size(param_list);
    for(size_t i = 0; i < param_list_size; i++) {
        vector_add(res, FM_PROC_PARAMETER);
        vector_add(res, vector_get(param_list, i));
    }

    size_t function_size = vector_size(function);
    for(size_t i = 0; i < function_size; i++)
        if(vector_get(function, i) != NULL)
            vector_add(res, vector_get(function, i));

    vector_add(res, FM_END_PROC);
    return res;
}

vector *ast_c_function_declaration(string *return_type, string *name, vector *params) {
    vector *res = vector_new(FM_START_C_FUNCTION, FM_LOCAL, return_type, FM_LOCAL, name);

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
    string *size = string_new(size_ptr);
    vector_add(res, size);
    vector_add(res, FM_END_C_FUNCTION);
    return res;
}

vector *ast_unary_method_definition(vector *multimethod_object_default_value, string *selector, vector *function) {
    vector *res = vector_new(FM_START_UNARY_METHOD, selector);

    size_t multimethod_object_default_value_size = vector_size(multimethod_object_default_value);
    for(size_t i = 0; i < multimethod_object_default_value_size; i++)
        vector_add(res, vector_get(multimethod_object_default_value, i));
    vector_add(res, FM_METHOD_RECEIVER);

    size_t function_size = vector_size(function);
    for(size_t i = 0; i < function_size; i++)
        vector_add(res, vector_get(function, i));
    vector_add(res, FM_END_UNARY_METHOD);

    return res;
}

vector *ast_binary_method_definition(vector *multimethod_object_default_value, string *selector, vector *param, vector *function) {
    vector *res = vector_new(FM_START_BINARY_METHOD, selector);

    size_t multimethod_object_default_value_size = vector_size(multimethod_object_default_value);
    for(size_t i = 0; i < multimethod_object_default_value_size; i++)
        vector_add(res, vector_get(multimethod_object_default_value, i));
    vector_add(res, FM_METHOD_RECEIVER);

    size_t param_size = vector_size(param);
    for(size_t i = 0; i < param_size; i++)
        vector_add(res, vector_get(param, i));
    vector_add(res, FM_METHOD_PARAMETER);

    size_t function_size = vector_size(function);
    for(size_t i = 0; i < function_size; i++)
        vector_add(res, vector_get(function, i));
    vector_add(res, FM_END_BINARY_METHOD);

    return res;
}

vector *ast_keyword_method_definition(vector *multimethod_object_default_value, string *selector, vector *params, vector *function) {
    vector *res = vector_new(FM_START_KEYWORD_METHOD, selector);

    size_t multimethod_object_default_value_size = vector_size(multimethod_object_default_value);
    for(size_t i = 0; i < multimethod_object_default_value_size; i++)
        vector_add(res, vector_get(multimethod_object_default_value, i));
    vector_add(res, FM_METHOD_RECEIVER);

    size_t params_size = vector_size(params);
    for(size_t i = 0; i < params_size; i++) {
        vector *param = vector_get(params, i);
        size_t param_size = vector_size(param);
        for(size_t i = 0; i < param_size; i++)
            vector_add(res, vector_get(param, i));
        vector_add(res, FM_METHOD_PARAMETER);
    }

    size_t function_size = vector_size(function);
    for(size_t i = 0; i < function_size; i++)
        vector_add(res, vector_get(function, i));
    vector_add(res, FM_END_KEYWORD_METHOD);

    return res;
}

vector *ast_any_object(void) {
    return vector_new(FM_ANY_OBJECT);
}

vector *ast_literal(vector *unit) {
    return unit;
}

vector *ast_nil_literal(void) {
    return vector_new(FM_NIL);
}

vector *ast_false_literal(void) {
    return vector_new(FM_FALSE);
}

vector *ast_true_literal(void) {
    return vector_new(FM_TRUE);
}

vector *ast_integer_literal(string *sign, string *number) {
    number = string_remove_underscores(number);

    if(string_get_char_at_index(number, 0) == '0' && (string_get_char_at_index(number, 1) == 'b' || string_get_char_at_index(number, 1) == 'B')) {
        string_skip(number, 2);
        number = string_new(bin_to_dec(string_get(number)));
    }
    else if(string_get_char_at_index(number, 0) == '0' && (string_get_char_at_index(number, 1) == 'o' || string_get_char_at_index(number, 1) == 'O')) {
        string_skip(number, 2);
        number = string_new(oct_to_dec(string_get(number)));
    }
    else if(string_get_char_at_index(number, 0) == '0' && (string_get_char_at_index(number, 1) == 'x' || string_get_char_at_index(number, 1) == 'X')) {
        string_skip(number, 2);
        number = string_new(hex_to_dec(string_get(number)));
    }

    if(string_equals(sign, string_new("-"))) {
        string *inum = string_new("");
        string_add(inum, sign);
        string_add(inum, number);

        return vector_new(FM_INTEGER, inum);
    }
    else {
        return vector_new(FM_INTEGER, number);
    }
}

vector *ast_float_literal(string *sign, string *number) {
    string *f = string_new("");
    string_add(f, sign);
    string_add(f, string_remove_underscores(number));

    return vector_new(FM_FLOAT, f);
}

vector *ast_string_literal(string *string) {
    string_skip(string, 1);
    string_shorten(string, string_size(string)-1);
    return vector_new(FM_STRING, string);
}

vector *ast_tuple_literal(vector *item_list) {
    vector *res = vector_new_empty();

    size_t item_list_size = vector_size(item_list);
    for(size_t i = 0; i < item_list_size; i++) {
        vector *item = vector_get(item_list, i);
        size_t item_size = vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            vector_add(res, vector_get(item, j));
    }

    vector_add(res, FM_TUPLE);
    char size_ptr[32];
    snprintf(size_ptr, sizeof(size_ptr), "%zu", vector_size(item_list));
    string *size = string_new(size_ptr);
    vector_add(res, size);
    return res;
}

vector *ast_tensor_literal(vector *item_list) {
    vector *res = vector_new_empty();

    size_t item_list_size = vector_size(item_list);
    for(size_t i = 0; i < item_list_size; i++) {
        vector *item = vector_get(item_list, i);
        size_t item_size = vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            vector_add(res, vector_get(item, j));
    }

    vector_add(res, FM_TENSOR);
    char size_ptr[32];
    snprintf(size_ptr, sizeof(size_ptr), "%zu", vector_size(item_list));
    string *size = string_new(size_ptr);
    vector_add(res, size);
    return res;
}

vector *ast_bitstring_literal(vector *item_list) {
    vector *res = vector_new_empty();
    size_t item_list_size = vector_size(item_list);

    for(size_t i = 0; i < item_list_size; i++) {
        vector *item = vector_get(item_list, i);
        size_t item_size = vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            vector_add(res, vector_get(item, j));
    }

    vector_add(res, FM_BITSTRING);
    char size_ptr[32];
    snprintf(size_ptr, sizeof(size_ptr), "%zu", vector_size(item_list));
    string *size = string_new(size_ptr);
    vector_add(res, size);
    return res;
}

vector *ast_hash_literal(vector *association_list) {
    vector *res =vector_new_empty();

    size_t association_list_size = vector_size(association_list);
    for(size_t i = 0; i < association_list_size; i++) {
        vector *item = vector_get(association_list, i);
        size_t item_size = vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            vector_add(res, vector_get(item, j));
    }
    
    vector_add(res, FM_HASH);
    char size_ptr[32];
    snprintf(size_ptr, sizeof(size_ptr), "%zu", vector_size(association_list));
    string *size = string_new(size_ptr);
    vector_add(res, size);
    return res;
}

vector *ast_bit_literal(vector *bit) {
    vector *res = vector_new_empty();
    vector_add(res, FM_LOCAL);
    vector_add(res, string_new("Bit"));

    size_t bit_length = vector_size(bit);
    for(size_t i = 0; i < bit_length; i++)
        vector_add(res, vector_get(bit, i));

    vector_add(res, FM_KEYWORD);
    vector_add(res, string_new("value:"));
    vector_add(res, string_new("1"));
    return res;
}

vector *ast_bit_size_literal(vector *bit, vector *size) {
    vector *res = vector_new_empty();
    vector_add(res, FM_LOCAL);
    vector_add(res, string_new("Bit"));

    size_t bit_length = vector_size(bit);
    for(size_t i = 0; i < bit_length; i++)
        vector_add(res, vector_get(bit, i));

    size_t size_length = vector_size(size);
    for(size_t i = 0; i < size_length; i++)
        vector_add(res, vector_get(size, i));
    
    vector_add(res, FM_KEYWORD);
    vector_add(res, string_new("value:size:"));
    vector_add(res, string_new("2"));
    return res;
}

vector *ast_association(vector *key, vector *value) {
    vector *res = vector_new_empty();
    vector_add(res, FM_LOCAL);
    vector_add(res, string_new("Association"));

    size_t key_size = vector_size(key);
    for(size_t i = 0; i < key_size; i++)
        vector_add(res, vector_get(key, i));
    
    size_t value_size = vector_size(value);
    for(size_t i = 0; i < value_size; i++)
        vector_add(res, vector_get(value, i));
    
    vector_add(res, FM_KEYWORD);
    vector_add(res, string_new("key:value:"));
    vector_add(res, string_new("2"));
    return res;
}

vector *ast_json_association(string *key, vector *value) {
    vector *res = vector_new_empty();
    vector_add(res, FM_LOCAL);
    vector_add(res, string_new("Association"));
    vector_add(res, FM_STRING);
    vector_add(res, key);

    size_t value_size = vector_size(value);
    for(size_t i = 0; i < value_size; i++)
        vector_add(res, vector_get(value, i));

    vector_add(res, FM_KEYWORD);
    vector_add(res, string_new("key:value:"));
    vector_add(res, string_new("2"));
    return res;
}
