#include "Parser.h"

#include "../ast/Bytecode.h"
#include "../base/memory.h"
#include "../tokens/Type.h"

#include <stdio.h>

#define lookahead_1_value_equals(token) token_equals_values(token_table_lookahead(self->table, 1), marg_string_new((token)))
#define lookahead_1_value_not_equals(token) !token_equals_values(token_table_lookahead(self->table, 1), marg_string_new((token)))
#define lookahead_2_value_equals(token) token_equals_values(token_table_lookahead(self->table, 2), marg_string_new((token)))
#define lookahead_2_value_not_equals(token) !token_equals_values(token_table_lookahead(self->table, 2), marg_string_new((token)))
#define lookahead_3_value_equals(token) token_equals_values(token_table_lookahead(self->table, 3), marg_string_new((token)))
#define lookahead_3_value_not_equals(token) !token_equals_values(token_table_lookahead(self->table, 3), marg_string_new((token)))
#define lookahead_1_type_equals(expected_type) token_table_lookahead(self->table, 1)->type == (expected_type)
#define lookahead_1_type_not_equals(expected_type) token_table_lookahead(self->table, 1)->type != (expected_type)
#define lookahead_2_type_equals(expected_type) token_table_lookahead(self->table, 2)->type == (expected_type)
#define lookahead_2_type_not_equals(expected_type) token_table_lookahead(self->table, 2)->type != (expected_type)
#define lookahead_3_type_equals(expected_type) token_table_lookahead(self->table, 3)->type == (expected_type)
#define lookahead_3_type_not_equals(expected_type) token_table_lookahead(self->table, 3)->type != (expected_type)

#define ensure_value(value, msg) token_table_ensure_value(self->table, (value), (msg))
#define ensure_type(type, msg) token_table_ensure_type(self->table, (type), (msg))
#define __chain_of(selector) do { \
    while(1) { \
        marg_vector *chain = selector(self); \
        if(marg_vector_size(chain) == 1 && marg_vector_get(chain, 0) == NULL) \
            break; \
        marg_vector_add(sel, chain); \
    } \
} while(0)

Parser *parser_new(TokenTable *tokens) {
    Parser *self = (Parser*)collected_malloc(sizeof(Parser));

    self->table = tokens;

    return self;
}

marg_vector *parser_analyze_syntax(Parser *self) {
    return parser_first_unit(self);
}

marg_vector *parser_first_unit(Parser *self) {
    if(lookahead_1_value_equals(")"))      return parser_group(self);
    else if(lookahead_1_value_equals("]")) return parser_tensor_literal(self);
    else if(lookahead_1_value_equals("}")) return parser_hash_literal(self);
    else {
        marg_vector *result = parser_translation_unit(self);
        ensure_value("eof", "reached end of program.");
        return ast_first_unit(result);
    }
}

marg_vector *parser_translation_unit(Parser *self) {
    return ast_translation_unit(parser_assignment_chain(self), parser_message(self));
}

marg_vector *parser_assignment_chain(Parser *self) {
    marg_vector *optional_assignment_list = marg_vector_new_empty();
    while((lookahead_1_type_equals(TOKEN_IDENTIFIER) && lookahead_2_value_equals("=")) || (lookahead_1_value_equals("@") && lookahead_2_type_equals(TOKEN_IDENTIFIER) && lookahead_3_value_equals("=")))
        marg_vector_add(optional_assignment_list, parser_assignment(self));

    return optional_assignment_list;
}

marg_vector *parser_assignment(Parser *self) {
    marg_vector *var = parser_variable(self);
    ensure_value("=", "expected '=' on assignment message.");
    return ast_assignment(var);
}

marg_vector *parser_message(Parser *self) {
    return ast_message(parser_keyword_message(self));
}

marg_vector *parser_unary_message(Parser *self) {
    marg_vector *obj = parser_unary_object(self);
    marg_vector *sel = marg_vector_new_empty();
    __chain_of(parser_unary_selector);

    if(marg_vector_size(sel) == 0)
        return ast_expression(obj);
    else
        return ast_unary_message(obj, sel);
}

marg_vector *parser_unary_object(Parser *self) {
    return ast_unary_object(parser_expression(self));
}

marg_vector *parser_unary_selector(Parser *self) {
    if(lookahead_1_type_equals(TOKEN_IDENTIFIER) && (lookahead_2_value_equals(":") || (lookahead_2_type_equals(TOKEN_ID_SYMBOL) && lookahead_3_value_equals(":")))) {
        return ast_empty();
    }
    if(lookahead_1_type_equals(TOKEN_IDENTIFIER)) {
        marg_string *id = ensure_type(TOKEN_IDENTIFIER, "expected identifier on unary selector.");
        marg_string *optional_symbol = marg_string_new("");
        if(lookahead_1_type_equals(TOKEN_ID_SYMBOL))
            optional_symbol = ensure_type(TOKEN_ID_SYMBOL, "expected id symbol on unary identifier.");
        return ast_unary_selector(id, optional_symbol);
    }
    else {
        return ast_empty();
    }
}

marg_vector *parser_binary_message(Parser *self) {
    marg_vector *obj = parser_binary_object(self);
    marg_vector *sel = marg_vector_new_empty();
    __chain_of(parser_binary_selector);

    if(marg_vector_size(sel) == 0)
        return ast_expression(obj);
    else
        return ast_binary_message(obj, sel);
}

marg_vector *parser_binary_object(Parser *self) {
    return ast_binary_object(parser_unary_message(self));
}

marg_vector *parser_binary_selector(Parser *self) {
    if(lookahead_1_type_equals(TOKEN_MESSAGE_SYMBOL)) {
        marg_string *sel = ensure_type(TOKEN_MESSAGE_SYMBOL, "expected message symbol on binary selector.");
        marg_vector *obj = parser_unary_message(self);

        if(marg_vector_size(obj) == 1 && marg_vector_get(obj, 0) == NULL)
            return ast_empty();
        else
            return ast_binary_selector(sel, obj);
    }
    else {
        return ast_empty();
    }
}

marg_vector *parser_keyword_message(Parser *self) {
    marg_vector *obj = parser_keyword_object(self);
    marg_vector *sel = marg_vector_new_empty();
    __chain_of(parser_keyword_selector);

    if(marg_vector_size(sel) == 0)
        return ast_expression(obj);
    else
        return ast_keyword_message(obj, sel);
}

marg_vector *parser_keyword_object(Parser *self) {
    return ast_keyword_object(parser_binary_message(self));
}

marg_vector *parser_keyword_selector(Parser *self) {
    if(lookahead_1_type_equals(TOKEN_IDENTIFIER) && (lookahead_2_value_equals(":") || (lookahead_2_type_equals(TOKEN_ID_SYMBOL) && lookahead_3_value_equals(":")))) {
        marg_string *id = ensure_type(TOKEN_IDENTIFIER, "expected identifier on keyword selector.");
        marg_string *optional_symbol = marg_string_new("");
        if(lookahead_1_type_equals(TOKEN_ID_SYMBOL))
            optional_symbol = ensure_type(TOKEN_ID_SYMBOL, "expected id symbol on keyword identifier.");
        marg_string *delim = ensure_value(":", "expected ':' on keyword selector.");
        marg_vector *obj = parser_binary_message(self);

        if(marg_vector_size(obj) == 1 && marg_vector_get(obj, 0) == NULL)
            return ast_empty();
        else
            return ast_keyword_selector(id, optional_symbol, delim, obj);
    }
    else {
        return ast_empty();
    }
}

marg_vector *parser_expression(Parser *self) {
    if(lookahead_1_value_equals("("))
        return ast_expression(parser_group(self));
    else if(lookahead_1_type_equals(TOKEN_IDENTIFIER) || (lookahead_1_value_equals("@") && lookahead_2_type_equals(TOKEN_IDENTIFIER)))
        return ast_expression(parser_variable(self));
    else if(lookahead_1_value_equals("->"))
        return ast_expression(parser_proc_literal(self));
    else if(lookahead_1_value_equals("#") && lookahead_2_value_equals("#") && lookahead_3_value_equals("#"))
        return ast_expression(parser_c_function_declaration(self));
    else if(lookahead_1_value_equals("#"))
        return ast_expression(parser_method_definition_literal(self));
    else
        return parser_literal(self);
}

marg_vector *parser_group(Parser *self) {
    ensure_value("(", "missing opening parenthesis on group.");

    marg_vector *__items = marg_vector_new_empty();
    while(!lookahead_1_value_equals(")") && !lookahead_1_value_equals("eof")) {
        marg_vector_add(__items, parser_translation_unit(self));

        if(!lookahead_1_value_equals(")") && !lookahead_1_value_equals("eof"))
            ensure_value(",", "grouped items should be separated by commas.");
    }

    ensure_value(")", "missing closing parenthesis on group.");
    return ast_group(__items);
}

marg_vector *parser_variable(Parser *self) {
    if(lookahead_1_value_equals("@"))
        return ast_variable(ensure_value("@", "expected '@' on instance variable declaration."), ensure_type(TOKEN_IDENTIFIER, "expected identifier on variable declaration."));
    else
        return ast_variable(marg_string_new(""), ensure_type(TOKEN_IDENTIFIER, "expected identifier on variable declaration."));
}

marg_vector *parser_proc_literal(Parser *self) {
    ensure_value("->", "missing '->' symbol on proc literal.");
    ensure_value("{", "missing opening curly on proc literal.");

    marg_vector *__params = marg_vector_new_empty();
    while(lookahead_1_type_equals(TOKEN_IDENTIFIER) && (lookahead_2_value_equals(",") || lookahead_2_value_equals("|"))) {
        marg_vector_add(__params, ensure_type(TOKEN_IDENTIFIER, "expected identifier parameter on proc."));
        if(!lookahead_1_value_equals("}") && !lookahead_1_value_equals("|") && !lookahead_1_value_equals("eof"))
            ensure_value(",", "proc parameters are separated by commas.");
    }

    if(lookahead_1_value_equals("|"))
        ensure_value("|", "missing '|' symbol on proc literal.");
    marg_vector *function = parser_translation_unit(self);

    ensure_value("}", "missing closing curly on proc literal.");
    return ast_proc_literal(__params, function);
}

marg_vector *parser_c_function_declaration(Parser *self) {
    ensure_value("#", "missing '###' on C function declaration.");
    ensure_value("#", "missing '###' on C function declaration.");
    ensure_value("#", "missing '###' on C function declaration.");
    marg_string *return_type = ensure_type(TOKEN_IDENTIFIER, "expected identifier on C function return type.");
    while(lookahead_1_type_equals(TOKEN_MESSAGE_SYMBOL))
        marg_string_add(return_type, ensure_type(TOKEN_MESSAGE_SYMBOL, "expected '*' symbols when C functions returns a pointer."));
    marg_string *name = ensure_type(TOKEN_IDENTIFIER, "expected identifier on C function name.");

    marg_vector *__params = marg_vector_new_empty();
    ensure_value("(", "missing opening parenthesis on C function declaration");
    while(lookahead_1_type_equals(TOKEN_IDENTIFIER)) {
        if(lookahead_1_value_equals("void") && lookahead_2_value_equals(")")) {
            ensure_value("void", "expected 'void'");
            break;
        }

        marg_string *param_type = ensure_type(TOKEN_IDENTIFIER, "expected identifier on C function param type.");
        while(lookahead_1_type_equals(TOKEN_MESSAGE_SYMBOL))
            marg_string_add(param_type, ensure_type(TOKEN_MESSAGE_SYMBOL, "expected '*' symbol for C parameter pointer."));
        marg_string *param_name = ensure_type(TOKEN_IDENTIFIER, "expected identifier on C function param name.");
        marg_vector *param = marg_vector_new(param_type, param_name);
        marg_vector_add(__params, param);
        if(!lookahead_1_value_equals(")") && !lookahead_1_value_equals("eof"))
            ensure_value(",", "C function parameters should be separated by commas.");
    }
    ensure_value(")", "missing closing parenthesis on C function declaration");

    return ast_c_function_declaration(return_type, name, __params);
}

marg_vector *parser_method_definition_literal(Parser *self) {
    ensure_value("#", "missing '#' on method definition.");

    marg_vector *multimethod_object_default_value = NULL;
    if(lookahead_1_type_not_equals(TOKEN_IDENTIFIER)
    && lookahead_1_type_not_equals(TOKEN_MESSAGE_SYMBOL)) {
        multimethod_object_default_value = parser_literal(self);
    }
    else {
        if(lookahead_1_value_equals("_"))
            ensure_value("_", "missing '_' on multimethod default value");
        // TODO Turn into an AST node
        multimethod_object_default_value = marg_vector_new(OP_PUSH_ANY_OBJECT);
    }

    if(lookahead_1_type_equals(TOKEN_IDENTIFIER) && (lookahead_2_value_equals(":") || (lookahead_2_type_equals(TOKEN_ID_SYMBOL) && lookahead_3_value_equals(":"))))
        return parser_keyword_method_definition(self, multimethod_object_default_value);
    else if(lookahead_1_type_equals(TOKEN_IDENTIFIER))
        return parser_unary_method_definition(self, multimethod_object_default_value);
    else if(lookahead_1_type_equals(TOKEN_MESSAGE_SYMBOL))
        return parser_binary_method_definition(self, multimethod_object_default_value);
    else
        return ast_empty();
}

marg_vector *parser_unary_method_definition(Parser *self, marg_vector *multimethod_object_default_value) {
    marg_string *selector = ensure_type(TOKEN_IDENTIFIER, "expected identifier on unary method definition.");
    if(lookahead_1_type_equals(TOKEN_ID_SYMBOL))
        marg_string_add(selector, ensure_type(TOKEN_ID_SYMBOL, "expected id symbol on unary identifier."));
    ensure_value("=>", "missing '=>' on unary method definition.");
    marg_vector *function = parser_translation_unit(self);
    return ast_unary_method_definition(multimethod_object_default_value, selector, function);
}

marg_vector *parser_binary_method_definition(Parser *self, marg_vector *multimethod_object_default_value) {
    marg_string *selector = ensure_type(TOKEN_MESSAGE_SYMBOL, "expected message symbol on binary method definition.");

    marg_vector *param = NULL;
    if(lookahead_1_type_equals(TOKEN_IDENTIFIER)) {
        if(lookahead_1_value_equals("_")) {
            ensure_value("_", "missing '_' on multimethod default parameter");
            // TODO Turn into an AST node
            param = marg_vector_new(OP_PUSH_ANY_OBJECT);
        }
        else {
            // TODO Turn into an AST node
            param = marg_vector_new(OP_PUSH_METHOD_PARAMETER, ensure_type(TOKEN_IDENTIFIER, "expected one parameter on binary method definition."));
        }
    }
    else {
        param = parser_literal(self);
    }

    ensure_value("=>", "missing '=>' on binary method definition.");
    marg_vector *function = parser_translation_unit(self);
    return ast_binary_method_definition(multimethod_object_default_value, selector, param, function);
}

    marg_vector *selector = marg_vector_new_empty();
marg_vector *parser_keyword_method_definition(Parser *self, marg_vector *multimethod_object_default_value) {
    while(lookahead_1_type_equals(TOKEN_IDENTIFIER)) {
        marg_string *key = ensure_type(TOKEN_IDENTIFIER, "expected identifier on keyword method selector.");
        if(lookahead_1_type_equals(TOKEN_ID_SYMBOL))
            marg_string_add(key, ensure_type(TOKEN_ID_SYMBOL, "expected id symbol on keyword method identifier."));
        marg_string_add(key, ensure_value(":", "expected `:` on keyword method definition."));
        marg_string *param = ensure_type(TOKEN_IDENTIFIER, "expected keyword parameter");
        marg_vector *keyparam = marg_vector_new(key, param);
        marg_vector_add(selector, keyparam);
    }
    ensure_value("=>", "missing '=>' on keyword method definition.");
    marg_vector *function = parser_translation_unit(self);
    return ast_keyword_method_definition(multimethod_object_default_value, selector, params, function);
}

marg_vector *parser_literal(Parser *self) {
    marg_string *sign = marg_string_new("");
    if(lookahead_1_value_equals("+"))
        sign = ensure_value("+", "expected '+' on literal.");
    else if(lookahead_1_value_equals("-"))
        sign = ensure_value("-", "expected '-' on literal.");

    // TODO Add different integer sizes
    if(lookahead_1_type_equals(TOKEN_INTEGER))
        return ast_literal(parser_integer_literal(self, sign));
    else if(lookahead_1_type_equals(TOKEN_FLOAT))
        return ast_literal(parser_float_literal(self, sign));
    else if(lookahead_1_type_equals(TOKEN_CHAR))
        return ast_literal(parser_char_literal(self, sign));
    else if(lookahead_1_type_equals(TOKEN_STRING))
        return ast_literal(parser_string_literal(self));
    else if(lookahead_1_value_equals("[")) {
        if(lookahead_2_value_equals("<"))
            return ast_literal(parser_tuple_literal(self));
        else
            return ast_literal(parser_tensor_literal(self));
    }
    else if(lookahead_1_value_equals("{")) {
        if(lookahead_2_value_equals("<"))
            return ast_literal(parser_bitstring_literal(self));
        else
            return ast_literal(parser_hash_literal(self));
    }
    else
        return ast_empty();
}

marg_vector *parser_integer_literal(Parser *self, marg_string *sign) {
    return ast_integer_literal(sign, ensure_type(TOKEN_INTEGER, "expected integer literal."));
}

marg_vector *parser_float_literal(Parser *self, marg_string *sign) {
    return ast_float_literal(sign, ensure_type(TOKEN_FLOAT, "expected float literal."));
}

marg_vector *parser_char_literal(Parser *self, marg_string *sign) {
    return ast_char_literal(sign, ensure_type(TOKEN_CHAR, "expected character literal."));
}

marg_vector *parser_string_literal(Parser *self) {
    return ast_string_literal(ensure_type(TOKEN_STRING, "expected string literal."));
}

marg_vector *parser_tuple_literal(Parser *self) {
    ensure_value("[", "missing opening bracket on tuple.");
    ensure_value("<", "missing opening tag on tuple.");

    marg_vector *__items = marg_vector_new_empty();
    while(!lookahead_1_value_equals("]") && !lookahead_1_value_equals("eof")) {
        marg_vector_add(__items, parser_translation_unit(self));
        if(!lookahead_1_value_equals("]") && !lookahead_1_value_equals("eof"))
            ensure_value(",", "tuple items should be separated by commas.");
    }

    ensure_value("]", "missing closing bracket on tuple.");
    return ast_tuple_literal(__items);
}

marg_vector *parser_tensor_literal(Parser *self) {
    ensure_value("[", "missing opening bracket on tensor.");

    marg_vector *__items = marg_vector_new_empty();
    while(!lookahead_1_value_equals("]") && !lookahead_1_value_equals("eof")) {
        marg_vector_add(__items, parser_translation_unit(self));
        if(!lookahead_1_value_equals("]") && !lookahead_1_value_equals("eof"))
            ensure_value(",", "tensor items should be separated by commas.");
    }

    ensure_value("]", "missing closing bracket on tensor.");
    return ast_tensor_literal(__items);
}

marg_vector *parser_bitstring_literal(Parser *self) {
    ensure_value("{", "missing opening curly brace on bitstring");
    ensure_value("<", "missing opening tag on bitstring");

    marg_vector *__items = marg_vector_new_empty();
    while(!lookahead_1_value_equals("}") && !lookahead_1_value_equals("eof")) {
        marg_vector_add(__items, parser_bit_literal(self));
        if(!lookahead_1_value_equals("}") && !lookahead_1_value_equals("eof"))
            ensure_value(",", "keys should be separated by commas.");
    }

    ensure_value("}", "missing closing curly brace on bitstring.");
    return ast_bitstring_literal(__items);
}

marg_vector *parser_hash_literal(Parser *self) {
    ensure_value("{", "missing opening curly brace on hash.");

    marg_vector *__items = marg_vector_new_empty();
    while(!lookahead_1_value_equals("}") && !lookahead_1_value_equals("eof")) {
        marg_vector_add(__items, parser_association_literal(self));
        if(!lookahead_1_value_equals("}") && !lookahead_1_value_equals("eof"))
            ensure_value(",", "keys should be separated by commas.");
    }

    ensure_value("}", "missing closing curly brace on hash.");
    return ast_hash_literal(__items);
}

marg_vector *parser_bit_literal(Parser *self) {
    marg_vector *bit = NULL;
    if(lookahead_1_type_equals(TOKEN_IDENTIFIER))
        bit = parser_variable(self);
    else
        bit = parser_literal(self);

    if(lookahead_1_value_equals(":") && lookahead_2_type_equals(TOKEN_INTEGER)) {
        ensure_value(":", "bit size should be denoted by colons on bitstrings.");
        marg_vector *size = parser_integer_literal(self, marg_string_new("+"));
        return ast_bit_size_literal(bit, size);
    }
    else {
        return ast_bit_literal(bit);
    }
}

marg_vector *parser_association_literal(Parser *self) {
    if(lookahead_1_type_equals(TOKEN_IDENTIFIER)) {
        marg_string *key = ensure_type(TOKEN_IDENTIFIER, "expected identifier on association literal.");
        ensure_value(":", "hash keys should be denoted by colons.");
        marg_vector *value = parser_translation_unit(self);
        return ast_json_association(key, value);
    }
    else if(lookahead_1_type_equals(TOKEN_STRING)) {
        marg_vector *key = parser_string_literal(self);
        ensure_value(":", "hash keys should be denoted by colons.");
        marg_vector *value = parser_translation_unit(self);
        return ast_association(key, value);
    }
    else {
        return ast_empty();
    }
}

#undef lookahead_1_value_equals
#undef lookahead_2_value_equals
#undef lookahead_3_value_equals
#undef lookahead_1_type_equals
#undef lookahead_2_type_equals
#undef lookahead_3_type_equals
#undef ensure_value
