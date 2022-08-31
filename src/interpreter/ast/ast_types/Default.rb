require_relative "../ASTInterface";

class Default < ASTInterface
    def empty
    end

    def first_unit(unit)
    end

    def translation_unit(optional_assignment_list, expr)
    end

    def assignment(id, eq)
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

    def expression(unit)
    end

    def group(unit_list)
    end

    def variable(optional_instance_symbol, name)
    end

    def proc_literal(param_list, function)
    end

    def c_function_declaration(return_type, name, params)
    end

    def unary_method_definition(selector, function)
    end

    def binary_method_definition(selector, param, function)
    end

    def keyword_method_definition(selector, function)
    end

    def literal(unit)
    end

    def integer_literal(sign, number)
    end

    def float_literal(sign, number)
    end

    def char_literal(sign, char)
    end

    def string_literal(string)
    end

    def tensor_literal(item_list)
    end

    def hash_literal(association_list)
    end

    def association(key, value)
    end

    def json_association(key, value)
    end
end
