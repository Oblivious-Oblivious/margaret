#include "Bytecode.h"

#include <stdio.h> /* snprintf */
#include "alternate_to_dec.h"

// TODO Possibly work with tokens instead of MargValues

static int __all_keywords_equal(marg_vector *selectors) {
    size_t selectors_size = marg_vector_size(selectors);
    for(size_t i = 0; i < selectors_size; i++) {
        void *item = marg_vector_get(selectors, i);
        if(!marg_string_equals(marg_vector_get(item, 0), marg_vector_get(marg_vector_get(selectors, 0), 0)))
            return 0;
    }
    return 1;
}

marg_vector *ast_empty(void) {
    return marg_vector_new(NULL);
}

marg_vector *ast_first_unit(marg_vector *unit) {
    return unit;
}

marg_vector *ast_translation_unit(marg_vector *optional_assignment_list, marg_vector *expr) {
    marg_vector *res = expr;

    size_t optional_assignment_list_size = marg_vector_size(optional_assignment_list);
    for(size_t i = optional_assignment_list_size; i > 0; i--) {
        marg_vector *item = marg_vector_get(optional_assignment_list, i-1);
        size_t item_size = marg_vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            marg_vector_add(res, marg_vector_get(item, j));
    }

    return res;
}

marg_vector *ast_assignment(marg_vector *id) {
    if(marg_string_equals(marg_vector_get(id, 0), OP_PUSH_INSTANCE))
        return marg_vector_new(OP_STORE_INSTANCE, marg_vector_get(id, 1));
    else
        return marg_vector_new(OP_STORE, marg_vector_get(id, 1));
}

marg_vector *ast_message(marg_vector *msg) {
    return msg;
}

marg_vector *ast_unary_message(marg_vector *object, marg_vector *selectors) {
    marg_vector *res = marg_vector_new_empty();

    size_t object_size = marg_vector_size(object);
    for(size_t i = 0; i < object_size; i++)
        marg_vector_add(res, marg_vector_get(object, i));

    size_t selectors_size = marg_vector_size(selectors);
    for(size_t i = 0; i < selectors_size; i++) {
        marg_vector_add(res, OP_UNARY);
        marg_vector_add(res, marg_vector_get(marg_vector_get(selectors, i), 0));
    }
    return res;
}

marg_vector *ast_unary_object(marg_vector *object) {
    return object;
}

marg_vector *ast_unary_selector(marg_string *id, marg_string *optional_symbol) {
    marg_string *sel = id;
    marg_string_add(sel, optional_symbol);
    return marg_vector_new(sel);
}

marg_vector *ast_binary_message(marg_vector *object, marg_vector *selectors) {
    marg_vector *res = marg_vector_new_empty();

    size_t object_size = marg_vector_size(object);
    for(size_t i = 0; i < object_size; i++)
        marg_vector_add(res, marg_vector_get(object, i));
    
    size_t selectors_size = marg_vector_size(selectors);
    for(size_t i = 0; i < selectors_size; i++) {
        marg_vector *item = marg_vector_get(marg_vector_get(selectors, i), 1);
        size_t item_size = marg_vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            marg_vector_add(res, marg_vector_get(item, j));

        marg_vector_add(res, OP_BINARY);
        marg_vector_add(res, marg_vector_get(marg_vector_get(selectors, i), 0));
    }
    return res;
}

marg_vector *ast_binary_object(marg_vector *object) {
    return object;
}

marg_vector *ast_binary_selector(marg_string *sel, marg_vector *obj) {
    return marg_vector_new(sel, obj);
}

marg_vector *ast_keyword_message(marg_vector *object, marg_vector *selectors) {
    if(marg_vector_size(selectors) > 1 && __all_keywords_equal(selectors)) {
        marg_vector *res = marg_vector_new_empty();

        size_t selectors_size = marg_vector_size(selectors);
        for(size_t i = 0; i < selectors_size; i++) {
            marg_string *sel0 = marg_vector_get(marg_vector_get(selectors, i), 0);
            marg_vector *sel1 = marg_vector_get(marg_vector_get(selectors, i), 1);

            size_t object_size = marg_vector_size(object);
            for(size_t j = 0; j < object_size; j++)
                marg_vector_add(res, marg_vector_get(object, j));
            
            size_t sel1_size = marg_vector_size(sel1);
            for(size_t j = 0; j < sel1_size; j++)
                marg_vector_add(res, marg_vector_get(sel1, j));

            marg_vector_add(res, OP_KEYWORD);
            marg_vector_add(res, sel0);
            marg_vector_add(res, marg_string_new("1"));
        }
        return res;
    }
    else {
        marg_string *joined_selector = marg_string_new("");
        for(size_t i = 0; i < marg_vector_size(selectors); i++)
            marg_string_add(joined_selector, marg_vector_get(marg_vector_get(selectors, i), 0));

        marg_vector *res = marg_vector_new_empty();

        size_t object_size = marg_vector_size(object);
        for(size_t i = 0; i < object_size; i++)
            marg_vector_add(res, marg_vector_get(object, i));
        
        size_t selectors_size = marg_vector_size(selectors);
        for(size_t i = 0; i < selectors_size; i++) {
            marg_vector *sel1 = marg_vector_get(marg_vector_get(selectors, i), 1);
            size_t sel1_size = marg_vector_size(sel1);
            for(size_t i = 0; i < sel1_size; i++)
                marg_vector_add(res, marg_vector_get(sel1, i));
        }
 
        marg_vector_add(res, OP_KEYWORD);
        marg_vector_add(res, joined_selector);
        char size_ptr[32];
        snprintf(size_ptr, sizeof(size_ptr), "%zu", marg_vector_size(selectors));
        marg_string *size = marg_string_new(size_ptr);
        marg_vector_add(res, size);
        return res;
    }
}

marg_vector *ast_keyword_object(marg_vector *object) {
    return object;
}

marg_vector *ast_keyword_selector(marg_string *id, marg_string *optional_symbol, marg_string *delim, marg_vector *obj) {
    marg_string *sel = marg_string_new("");
    marg_string_add(sel, id);
    marg_string_add(sel, optional_symbol);
    marg_string_add(sel, delim);

    return marg_vector_new(sel, obj);
}

marg_vector *ast_expression(marg_vector *unit) {
    return unit;
}

marg_vector *ast_group(marg_vector *unit_list) {
    marg_vector *res = marg_vector_new_empty();

    size_t unit_list_size = marg_vector_size(unit_list);
    for(size_t i = 0; i < unit_list_size; i++) {
        marg_vector *item = marg_vector_get(unit_list, i);
        size_t item_size = marg_vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            marg_vector_add(res, marg_vector_get(item, j));
    }

    return res;
}

marg_vector *ast_variable(marg_string *optional_instance_symbol, marg_string *name) {
    if(marg_string_equals(name, marg_string_new("nil")))
        return marg_vector_new(OP_PUSH_NIL);
    else if(marg_string_equals(name, marg_string_new("true")))
        return marg_vector_new(OP_PUSH_TRUE);
    else if(marg_string_equals(name, marg_string_new("false")))
        return marg_vector_new(OP_PUSH_FALSE);
    else if(marg_string_equals(name, marg_string_new("self")))
        return marg_vector_new(OP_PUSH_SELF);
    else if(marg_string_equals(name, marg_string_new("super")))
        return marg_vector_new(OP_PUSH_SUPER);
    else if(marg_string_equals(optional_instance_symbol, marg_string_new("@")))
        return marg_vector_new(OP_PUSH_INSTANCE, name);
    else
        return marg_vector_new(OP_PUSH_VARIABLE, name);
}

marg_vector *ast_proc_literal(marg_vector *param_list, marg_vector *function) {
    marg_vector *res = marg_vector_new(OP_START_PUSH_PROC);

    size_t param_list_size = marg_vector_size(param_list);
    for(size_t i = 0; i < param_list_size; i++) {
        marg_vector_add(res, OP_PUSH_VARIABLE);
        marg_vector_add(res, marg_vector_get(param_list, i));
    }

    marg_vector_add(res, OP_PUSH_TENSOR);
    char size_ptr[32];
    snprintf(size_ptr, sizeof(size_ptr), "%zu", marg_vector_size(param_list));
    marg_string *size = marg_string_new(size_ptr);
    marg_vector_add(res, size);

    size_t function_size = marg_vector_size(function);
    for(size_t i = 0; i < function_size; i++)
        marg_vector_add(res, marg_vector_get(function, i));

    marg_vector_add(res, OP_END_PUSH_PROC);
    return res;
}

marg_vector *ast_c_function_declaration(marg_string *return_type, marg_string *name, marg_vector *params) {
    marg_vector *res = marg_vector_new(OP_START_PUSH_C_FUNCTION, OP_PUSH_VARIABLE, return_type, OP_PUSH_VARIABLE, name);

    size_t params_size = marg_vector_size(params);
    for(size_t i = 0; i < params_size; i++) {
        marg_vector_add(res, OP_PUSH_VARIABLE);
        marg_vector_add(res, marg_string_new("CFunParam"));
        marg_vector_add(res, OP_PUSH_VARIABLE);
        marg_vector_add(res, marg_vector_get(marg_vector_get(params, i), 0));
        marg_vector_add(res, OP_PUSH_VARIABLE);
        marg_vector_add(res, marg_vector_get(marg_vector_get(params, i), 1));
        marg_vector_add(res, OP_KEYWORD);
        marg_vector_add(res, marg_string_new("c_type:c_name:"));
        marg_vector_add(res, marg_string_new("2"));
    }

    marg_vector_add(res, OP_PUSH_TENSOR);
    char size_ptr[32];
    snprintf(size_ptr, sizeof(size_ptr), "%zu", marg_vector_size(params));
    marg_string *size = marg_string_new(size_ptr);
    marg_vector_add(res, size);
    marg_vector_add(res, OP_END_PUSH_C_FUNCTION);
    return res;
}

marg_vector *ast_unary_method_definition(marg_vector *multimethod_object_default_value, marg_string *selector, marg_vector *function) {
    marg_vector *res = marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Method"), OP_UNARY, marg_string_new("unary"));

    size_t multimethod_object_default_value_size = marg_vector_size(multimethod_object_default_value);
    for(size_t i = 0; i < multimethod_object_default_value_size; i++)
        marg_vector_add(res, marg_vector_get(multimethod_object_default_value, i));

    marg_vector_add(res, OP_PUSH_STRING);
    marg_string *selector_name = marg_string_new("\"");
    marg_string_add(selector_name, selector);
    marg_string_add_str(selector_name, "\"");
    marg_vector_add(res, selector_name);

    marg_vector_add(res, OP_START_PUSH_PROC);
    marg_vector_add(res, OP_PUSH_SELF);
    marg_vector_add(res, OP_PUSH_TENSOR);
    marg_vector_add(res, marg_string_new("1"));
    size_t function_size = marg_vector_size(function);
    for(size_t i = 0; i < function_size; i++)
        marg_vector_add(res, marg_vector_get(function, i));
    marg_vector_add(res, OP_END_PUSH_PROC);
    marg_vector_add(res, OP_KEYWORD);
    marg_vector_add(res, marg_string_new("object:message:method:"));
    marg_vector_add(res, marg_string_new("3"));

    return res;
}

marg_vector *ast_binary_method_definition(marg_vector *multimethod_object_default_value, marg_string *selector, marg_vector *param, marg_vector *function) {
    marg_vector *res = marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Method"), OP_UNARY, marg_string_new("binary"));

    size_t multimethod_object_default_value_size = marg_vector_size(multimethod_object_default_value);
    for(size_t i = 0; i < multimethod_object_default_value_size; i++)
        marg_vector_add(res, marg_vector_get(multimethod_object_default_value, i));

    marg_vector_add(res, OP_PUSH_STRING);
    marg_string *selector_name = marg_string_new("\"");
    marg_string_add(selector_name, selector);
    marg_string_add_str(selector_name, "\"");
    marg_vector_add(res, selector_name);

    if(marg_string_equals(marg_vector_get(param, 0), OP_PUSH_METHOD_PARAMETER)) {
        marg_vector_add(res, OP_PUSH_METHOD_PARAMETER);
        marg_string *param_str = marg_string_new("\"");
        marg_string_add(param_str, marg_vector_get(param, 1));
        marg_string_add_str(param_str, "\"");
        marg_vector_add(res, param_str);
    }
    else {
        size_t param_size = marg_vector_size(param);
        for(size_t i = 0; i < param_size; i++)
            marg_vector_add(res, marg_vector_get(param, i));
    }

    marg_vector_add(res, OP_START_PUSH_PROC);
    marg_vector_add(res, OP_PUSH_SELF);
    if(marg_string_equals(marg_vector_get(param, 0), OP_PUSH_METHOD_PARAMETER)) {
        marg_vector_add(res, OP_PUSH_VARIABLE);
        marg_vector_add(res, marg_vector_get(param, 1));
        marg_vector_add(res, OP_PUSH_TENSOR);
        marg_vector_add(res, marg_string_new("2"));
    }
    else {
        marg_vector_add(res, OP_PUSH_TENSOR);
        marg_vector_add(res, marg_string_new("1"));
    }
    size_t function_size = marg_vector_size(function);
    for(size_t i = 0; i < function_size; i++)
        marg_vector_add(res, marg_vector_get(function, i));
    marg_vector_add(res, OP_END_PUSH_PROC);
    marg_vector_add(res, OP_KEYWORD);
    marg_vector_add(res, marg_string_new("object:message:param:method:"));
    marg_vector_add(res, marg_string_new("4"));

    return res;
}

marg_vector *ast_keyword_method_definition(marg_vector *multimethod_object_default_value, marg_string *selector, marg_vector *params, marg_vector *function) {
    marg_vector *res = marg_vector_new(OP_PUSH_VARIABLE, marg_string_new("Method"), OP_UNARY, marg_string_new("keyword"));

    size_t multimethod_object_default_value_size = marg_vector_size(multimethod_object_default_value);
    for(size_t i = 0; i < multimethod_object_default_value_size; i++)
        marg_vector_add(res, marg_vector_get(multimethod_object_default_value, i));

    marg_vector_add(res, OP_PUSH_STRING);
    marg_string *selector_name = marg_string_new("\"");
    marg_string_add(selector_name, selector);
    marg_string_add_str(selector_name, "\"");
    marg_vector_add(res, selector_name);

    size_t params_size = marg_vector_size(params);
    size_t number_of_formal_params = 1;
    for(size_t i = 0; i < params_size; i++) {
        marg_vector *param = marg_vector_get(params, i);
        if(marg_string_equals(marg_vector_get(param, 0), OP_PUSH_METHOD_PARAMETER)) {
            number_of_formal_params++;
            marg_vector_add(res, OP_PUSH_METHOD_PARAMETER);
            marg_string *param_name = marg_string_new("\"");
            marg_string_add(param_name, marg_vector_get(param, 1));
            marg_string_add_str(param_name, "\"");
            marg_vector_add(res, param_name);
        }
        else {
            size_t param_size = marg_vector_size(param);
            for(size_t i = 0; i < param_size; i++)
                marg_vector_add(res, marg_vector_get(param, i));
        }
    }
    marg_vector_add(res, OP_PUSH_TENSOR);
    char params_size_str[32];
    snprintf(params_size_str, sizeof(params_size_str), "%zu", params_size);
    marg_vector_add(res, marg_string_new(params_size_str));

    marg_vector_add(res, OP_START_PUSH_PROC);
    marg_vector_add(res, OP_PUSH_SELF);
    for(size_t i = 0; i < params_size; i++) {
        marg_vector *param = marg_vector_get(params, i);
        if(marg_string_equals(marg_vector_get(param, 0), OP_PUSH_METHOD_PARAMETER)) {
            marg_vector_add(res, OP_PUSH_VARIABLE);
            marg_vector_add(res, marg_vector_get(param, 1));
        }
    }
    marg_vector_add(res, OP_PUSH_TENSOR);
    char number_of_formal_params_str[32];
    snprintf(number_of_formal_params_str, sizeof(number_of_formal_params_str), "%zu", number_of_formal_params);
    marg_vector_add(res, marg_string_new(number_of_formal_params_str));
    size_t function_size = marg_vector_size(function);
    for(size_t i = 0; i < function_size; i++)
        marg_vector_add(res, marg_vector_get(function, i));
    marg_vector_add(res, OP_END_PUSH_PROC);
    marg_vector_add(res, OP_KEYWORD);
    marg_vector_add(res, marg_string_new("object:message:params:method:"));
    marg_vector_add(res, marg_string_new("4"));

    return res;
}

marg_vector *ast_literal(marg_vector *unit) {
    return unit;
}

marg_vector *ast_integer_literal(marg_string *sign, marg_string *number) {
    // TODO Refactor to work with multiple zeros
    // "0", "-0", "+0", "0b0", "-0b0", "+0b0", "0b00", "-0b00", "+0b00", "0o0", "-0o0", "+0o0", "0o000", "-0o000", "+0o000", "0x0", "-0x0", "+0x0", "0x00", "-0x00", "+0x00"
    // "1", "+1", "0b1", "+0b1", "0b01", "+0b01", "0o1", "+0o1", "0o001", "+0o001", "0x1", "+0x1", "0x01", "+0x01"
    // "-1", "-0b1", "-0b01", "-0o1", "-0o001", "-0x1", "-0x01"
    // "2", "+2", "0b10", "+0b10", "0b010", "+0b010", "0o2", "+0o2", "0o002", "+0o002", "0x2", "+0x2", "0x02", "+0x02"
    number = marg_string_remove_underscores(number);
    if(marg_string_equals(number, marg_string_new("0")))
        return marg_vector_new(OP_PUSH_0);
    else if(marg_string_equals(number, marg_string_new("1"))) {
        if(marg_string_equals(sign, marg_string_new("-")))
            return marg_vector_new(OP_PUSH_MINUS_1);
        else
            return marg_vector_new(OP_PUSH_1);
    }
    else if(
        marg_string_equals(number, marg_string_new("2"))
    ||  marg_string_equals(number, marg_string_new("0b10"))
    ) {
        if(marg_string_equals(sign, marg_string_new("-")))
            return marg_vector_new(OP_PUSH_INTEGER, marg_string_new("-2"));
        else
            return marg_vector_new(OP_PUSH_2);
    }
    else {
        if(marg_string_get_char_at_index(number, 0) == '0' && (marg_string_get_char_at_index(number, 1) == 'b' || marg_string_get_char_at_index(number, 1) == 'B')) {
            marg_string_skip(number, 2);
            number = marg_string_new(bin_to_dec(marg_string_get(number)));
        }
        else if(marg_string_get_char_at_index(number, 0) == '0' && (marg_string_get_char_at_index(number, 1) == 'o' || marg_string_get_char_at_index(number, 1) == 'O')) {
            marg_string_skip(number, 2);
            number = marg_string_new(oct_to_dec(marg_string_get(number)));
        }
        else if(marg_string_get_char_at_index(number, 0) == '0' && (marg_string_get_char_at_index(number, 1) == 'x' || marg_string_get_char_at_index(number, 1) == 'X')) {
            marg_string_skip(number, 2);
            number = marg_string_new(hex_to_dec(marg_string_get(number)));
        }

        if(marg_string_equals(sign, marg_string_new("-"))) {
            marg_string *inum = marg_string_new("");
            marg_string_add(inum, sign);
            marg_string_add(inum, number);

            return marg_vector_new(OP_PUSH_INTEGER, inum);
        }
        else {
            return marg_vector_new(OP_PUSH_INTEGER, number);
        }
    }
}

marg_vector *ast_float_literal(marg_string *sign, marg_string *number) {
    marg_string *f = marg_string_new("");
    marg_string_add(f, sign);
    marg_string_add(f, marg_string_remove_underscores(number));

    return marg_vector_new(OP_PUSH_FLOAT, f);
}

marg_vector *ast_char_literal(marg_string *sign, marg_string *c) {
    marg_string *character = marg_string_new("");
    marg_string_add(character, sign);
    marg_string_add(character, c);

    return marg_vector_new(OP_PUSH_CHAR, character);
}

marg_vector *ast_string_literal(marg_string *string) {
    return marg_vector_new(OP_PUSH_STRING, string);
}

marg_vector *ast_tuple_literal(marg_vector *item_list) {
    marg_vector *res = marg_vector_new_empty();

    size_t item_list_size = marg_vector_size(item_list);
    for(size_t i = 0; i < item_list_size; i++) {
        marg_vector *item = marg_vector_get(item_list, i);
        size_t item_size = marg_vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            marg_vector_add(res, marg_vector_get(item, j));
    }

    marg_vector_add(res, OP_PUSH_TUPLE);
    char size_ptr[32];
    snprintf(size_ptr, sizeof(size_ptr), "%zu", marg_vector_size(item_list));
    marg_string *size = marg_string_new(size_ptr);
    marg_vector_add(res, size);
    return res;
}

marg_vector *ast_tensor_literal(marg_vector *item_list) {
    marg_vector *res = marg_vector_new_empty();

    size_t item_list_size = marg_vector_size(item_list);
    for(size_t i = 0; i < item_list_size; i++) {
        marg_vector *item = marg_vector_get(item_list, i);
        size_t item_size = marg_vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            marg_vector_add(res, marg_vector_get(item, j));
    }

    marg_vector_add(res, OP_PUSH_TENSOR);
    char size_ptr[32];
    snprintf(size_ptr, sizeof(size_ptr), "%zu", marg_vector_size(item_list));
    marg_string *size = marg_string_new(size_ptr);
    marg_vector_add(res, size);
    return res;
}

marg_vector *ast_bitstring_literal(marg_vector *item_list) {
    marg_vector *res =marg_vector_new_empty();
    size_t item_list_size = marg_vector_size(item_list);

    for(size_t i = 0; i < item_list_size; i++) {
        marg_vector *item = marg_vector_get(item_list, i);
        size_t item_size = marg_vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            marg_vector_add(res, marg_vector_get(item, j));
    }

    marg_vector_add(res, OP_PUSH_BITSTRING);
    char size_ptr[32];
    snprintf(size_ptr, sizeof(size_ptr), "%zu", marg_vector_size(item_list));
    marg_string *size = marg_string_new(size_ptr);
    marg_vector_add(res, size);
    return res;
}

marg_vector *ast_hash_literal(marg_vector *association_list) {
    marg_vector *res =marg_vector_new_empty();

    size_t association_list_size = marg_vector_size(association_list);
    for(size_t i = 0; i < association_list_size; i++) {
        marg_vector *item = marg_vector_get(association_list, i);
        size_t item_size = marg_vector_size(item);
        for(size_t j = 0; j < item_size; j++)
            marg_vector_add(res, marg_vector_get(item, j));
    }
    
    marg_vector_add(res, OP_PUSH_HASH);
    char size_ptr[32];
    snprintf(size_ptr, sizeof(size_ptr), "%zu", marg_vector_size(association_list));
    marg_string *size = marg_string_new(size_ptr);
    marg_vector_add(res, size);
    return res;
}

marg_vector *ast_bit_literal(marg_vector *bit) {
    marg_vector *res = marg_vector_new_empty();
    marg_vector_add(res, OP_PUSH_VARIABLE);
    marg_vector_add(res, marg_string_new("Bit"));

    size_t bit_length = marg_vector_size(bit);
    for(size_t i = 0; i < bit_length; i++)
        marg_vector_add(res, marg_vector_get(bit, i));

    marg_vector_add(res, OP_KEYWORD);
    marg_vector_add(res, marg_string_new("value:"));
    marg_vector_add(res, marg_string_new("1"));
    return res;
}

marg_vector *ast_bit_size_literal(marg_vector *bit, marg_vector *size) {
    marg_vector *res = marg_vector_new_empty();
    marg_vector_add(res, OP_PUSH_VARIABLE);
    marg_vector_add(res, marg_string_new("Bit"));

    size_t bit_length = marg_vector_size(bit);
    for(size_t i = 0; i < bit_length; i++)
        marg_vector_add(res, marg_vector_get(bit, i));

    size_t size_length = marg_vector_size(size);
    for(size_t i = 0; i < size_length; i++)
        marg_vector_add(res, marg_vector_get(size, i));
    
    marg_vector_add(res, OP_KEYWORD);
    marg_vector_add(res, marg_string_new("value:size:"));
    marg_vector_add(res, marg_string_new("2"));
    return res;
}

marg_vector *ast_association(marg_vector *key, marg_vector *value) {
    marg_vector *res = marg_vector_new_empty();
    marg_vector_add(res, OP_PUSH_VARIABLE);
    marg_vector_add(res, marg_string_new("Association"));

    size_t key_size = marg_vector_size(key);
    for(size_t i = 0; i < key_size; i++)
        marg_vector_add(res, marg_vector_get(key, i));
    
    size_t value_size = marg_vector_size(value);
    for(size_t i = 0; i < value_size; i++)
        marg_vector_add(res, marg_vector_get(value, i));
    
    marg_vector_add(res, OP_KEYWORD);
    marg_vector_add(res, marg_string_new("key:value:"));
    marg_vector_add(res, marg_string_new("2"));
    return res;
}

marg_vector *ast_json_association(marg_string *key, marg_vector *value) {
    marg_vector *res = marg_vector_new_empty();
    marg_vector_add(res, OP_PUSH_VARIABLE);
    marg_vector_add(res, marg_string_new("Association"));
    marg_vector_add(res, OP_PUSH_STRING);
    marg_string *key_name = marg_string_new("\"");
    marg_string_add(key_name, key);
    marg_string_add_str(key_name, "\"");
    marg_vector_add(res, key_name);

    size_t value_size = marg_vector_size(value);
    for(size_t i = 0; i < value_size; i++)
        marg_vector_add(res, marg_vector_get(value, i));

    marg_vector_add(res, OP_KEYWORD);
    marg_vector_add(res, marg_string_new("key:value:"));
    marg_vector_add(res, marg_string_new("2"));
    return res;
}
