require_relative "../ASTInterface";

class Default < ASTInterface
    def empty
    end

    def first_unit(unit)
    end

    def translation_unit(unit)
    end

    def literal(lit)
    end

    def base_ten_literal(sign, number)
    end

    def alternate_base_literal(sign, number)
    end
    
    def big_integer_literal(sign, number)
    end

    def big_float_literal(sign, number)
    end

    def string_literal(string)
    end

    def symbol_literal(id)
    end

    def symbol_name(name)
    end

    def array_literal(item_list, type)
    end

    def array_item(item)
    end

    def tuple_literal(item_list)
    end

    def tuple_item(item)
    end

    def hash_literal(association_list)
    end

    def association(key, value)
    end

    def json_association(key, value)
    end

    def quoted_list_literal(item_list)
    end

    def block_literal(param_list, item_list)
    end

    def variable(optional_instance_symbol, name)
    end

    def list(unit_list)
    end

    def message(optional_assignment_list, expr)
    end

    def assignment_message(id, eq)
    end

    def expression(expr)
        expr;
    end

    def terminal_UNSIGNED_BASE_TEN_NUMBER(number)
    end

    def terminal_ALTERNATE_BASE_NUMBER(number)
    end

    def terminal_BIGINTEGER(number)
    end

    def terminal_BIGFLOAT(number)
    end

    def terminal_STRING(value)
    end

    def terminal_UNQUOTED_STRING(value)
    end

    def terminal_IDENTIFIER(id)
    end

    def terminal_INSTANCE_SYMBOL(symb)
    end

    def terminal_MESSAGE_SYMBOL(symb)
    end

    # def terminal_IDENTIFIER_SYMBOL(symb)
    # end

    def terminal_SIGN(symb)
    end

    def terminal_EQUALS(symb)
    end

    # def terminal_COLON(symb)
    # end
end
