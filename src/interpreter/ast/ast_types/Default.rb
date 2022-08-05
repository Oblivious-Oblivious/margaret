require_relative "../ASTInterface";

class Default < ASTInterface
    def empty
    end

    def list(unit_list)
    end

    def translation_unit(optional_assignment_list, expr)
    end

    def assignment_message(id, eq)
    end

    def binary_operand(op, unchain)
    end

    def keyword(id, optional_symbol, delim)
    end

    def keyword_argument(binop, binchain)
    end

    def base_ten_literal(sign, number)
    end

    def alternate_base_literal(sign, number)
    end

    def big_integer_literal(sign, number)
    end

    def big_float_literal(sign, number)
    end

    def tuple_literal(item_list)
    end

    def hash_literal(association_list)
    end

    def association(key, value)
    end

    def json_association(key, value)
    end

    def symbol_literal(id)
    end

    def terminal_UNSIGNED_BASE_TEN_NUMBER(number)
    end

    def terminal_ALTERNATE_BASE_NUMBER(number)
    end

    def terminal_STRING(value)
    end

    def terminal_UNQUOTED_STRING(value)
    end

    def terminal_IDENTIFIER(id)
    end

    def terminal_MESSAGE_SYMBOL(symb)
    end

    def terminal_IDENTIFIER_SYMBOL(symb)
    end

    def terminal_SIGN(symb)
    end

    def terminal_EQUALS(symb)
    end

    def terminal_COLON(symb)
    end
end
