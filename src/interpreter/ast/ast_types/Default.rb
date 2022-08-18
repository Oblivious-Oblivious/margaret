require_relative "../ASTInterface";

class Default < ASTInterface
    def empty
    end

    def first_unit(unit)
    end

    def translation_unit(optional_assignment_list, expr)
    end

    def assignment_message(id, eq)
    end

    def message(msg)
    end

    def unary_message(object, selectors)
    end

    def unary_object(object)
    end

    def unary_selector(id, optional_symbol)
    end

    def binary_message(object, selectors)
    end

    def binary_object(object)
    end

    def binary_selector(sel, obj)
    end

    def keyword_message(object, selectors)
    end

    def keyword_object(object)
    end

    def keyword_selector(id, optional_symbol, delim, obj)
    end

    def literal(unit)
    end

    def integer_literal(sign, number)
    end

    def float_literal(sign, number)
    end

    def binary_literal(sign, number)
    end

    def hexadecimal_literal(sign, number)
    end

    def octal_literal(sign, number)
    end
    
    def big_integer_literal(sign, number)
    end

    def big_float_literal(sign, number)
    end

    def association(key, value)
    end

    def json_association(key, value)
    end

    def string_literal(string)
    end

    def symbol_literal(id)
    end

    def symbol_name(name)
    end

    def variable(optional_instance_symbol, name)
    end

    def list(unit_list)
    end

    def tuple_literal(item_list)
    end

    def hash_literal(association_list)
    end

    def quoted_list_literal(item_list)
    end

    def block_literal(param_list, function)
    end
end
