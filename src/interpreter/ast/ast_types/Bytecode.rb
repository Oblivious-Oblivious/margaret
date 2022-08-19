require_relative "../ASTInterface";

class Bytecode < ASTInterface
    def empty
        [];
    end

    def first_unit(unit)
        ["halt"];
    end

    def translation_unit(optional_assignment_list, expr)
        empty;
    end

    def assignment(id, eq)
        empty;
    end

    def message(msg)
        empty;
    end

    def unary_message(object, selectors)
        empty;
    end

    def unary_object(object)
        empty;
    end

    def unary_selector(id, optional_symbol)
        empty;
    end

    def binary_message(object, selectors)
        empty;
    end

    def binary_object(object)
        empty;
    end

    def binary_selector(sel, obj)
        empty;
    end

    def keyword_message(object, selectors)
        empty;
    end

    def keyword_object(object)
        empty;
    end

    def keyword_selector(id, optional_symbol, delim, obj)
        empty;
    end

    def literal(unit)
        empty;
    end

    def integer_literal(sign, number)
        empty;
    end

    def float_literal(sign, number)
        empty;
    end

    def binary_literal(sign, number)
        empty;
    end

    def hexadecimal_literal(sign, number)
        empty;
    end

    def octal_literal(sign, number)
        empty;
    end
    
    def big_integer_literal(sign, number)
        empty;
    end

    def big_float_literal(sign, number)
        empty;
    end

    def association(key, value)
        empty;
    end

    def json_association(key, value)
        empty;
    end

    def string_literal(string)
        empty;
    end

    def symbol_literal(id)
        empty;
    end

    def symbol_name(name)
        empty;
    end

    def variable(optional_instance_symbol, name)
        empty;
    end

    def list(unit_list)
        empty;
    end

    def tuple_literal(item_list)
        empty;
    end

    def hash_literal(association_list)
        empty;
    end

    def quoted_list_literal(item_list)
        empty;
    end

    def block_literal(param_list, function)
        empty;
    end
end
