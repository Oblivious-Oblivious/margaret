require_relative "../ASTInterface";

class Bytecode < ASTInterface
    def empty
        "";
    end

    def first_unit(unit)
        [unit, "pop"].flatten;
    end

    def translation_unit(optional_assignment_list, expr)
        res = [];
        res << expr;
        while optional_assignment_list.size > 0
            res << optional_assignment_list.pop;
        end
        res;
    end

    def assignment(id, eq)
        if id[0] == "push_instance"
            ["store_instance", "#{id[1]}"];
        else
            ["store", "#{id[1]}"];
        end
    end

    def message(msg)
        msg;
    end

    def unary_message(object, selectors)
        res = object;
        selectors.each do |sel|
            res << "unary" << sel;
        end
        res;
    end

    def unary_object(object)
        object;
    end

    def unary_selector(id, optional_symbol)
        ["#{id}#{optional_symbol}"];
    end

    def binary_message(object, selectors)
        res = object;
        selectors.each do |sel|
            res << sel[1] << "binary" << sel[0];
        end
        res;
    end

    def binary_object(object)
        object;
    end

    def binary_selector(sel, obj)
        [sel, obj];
    end

    def keyword_message(object, selectors)
        if selectors.size > 1 and selectors.all? { |sel| sel.first == selectors.first.first }
            list(selectors.map { |sel| [object, sel[1], "keyword", sel[0], "1"] });
        else
            joined_selector = "";
            selectors.each { |sel| joined_selector << sel[0] };
            res = object;
            selectors.each { |sel| res << sel[1] };
            res << "keyword" << joined_selector << "#{selectors.size}";
        end
    end

    def keyword_object(object)
        object;
    end

    def keyword_selector(id, optional_symbol, delim, obj)
        ["#{id}#{optional_symbol}#{delim}", obj];
    end

    def literal(unit)
        unit;
    end

    def integer_literal(sign, number)
        case "#{sign}#{number}"
        when "0", "-0", "+0"
            ["push_0"];
        when "1", "+1"
            ["push_1"];
        when "-1"
            ["push_minus_1"];
        when "2", "+2"
            ["push_2"];
        else
            ["push_integer", "#{sign}#{number}"];
        end
    end
    
    def float_literal(sign, number)
        ["push_float", "#{sign}#{number}"];
    end
    
    def binary_literal(sign, number)
        ["push_binary", "#{sign}#{number}"];
    end

    def hexadecimal_literal(sign, number)
        ["push_hexadecimal", "#{sign}#{number}"];
    end

    def octal_literal(sign, number)
        ["push_octal", "#{sign}#{number}"];
    end
    
    def big_integer_literal(sign, number)
        ["push_big_integer", %Q{"#{sign}#{number[3...]}"}];
    end

    def big_float_literal(sign, number)
        ["push_big_float", %Q{"#{sign}#{number[3...]}"}];
    end

    def string_literal(string)
        ["push_string", string];
    end

    def variable(optional_instance_symbol, name)
        if optional_instance_symbol == "@"
            ["push_instance", name];
        elsif name == "nil"
            ["push_nil"];
        elsif name == "true"
            ["push_true"];
        elsif name == "false"
            ["push_false"];
        else
            ["push_variable", name];
        end
    end

    def list(unit_list)
        res = [];
        unit_list.each do |unit|
            res << unit;
        end
        res << ["push_list", "#{unit_list.size}"];
        res;
    end

    def tuple_literal(item_list)
        res = [];
        item_list.each do |item|
            res << item;
        end
        res << "push_tuple" << "#{item_list.size}";
    end

    def hash_literal(association_list)
        res = [];
        association_list.each do |association|
            res << association;
        end
        res << "push_hash" << "#{association_list.size}";
    end

    def association(key, value)
        [key, value, "keyword", "key:value:", "2"];
    end

    def json_association(key, value)
        ["push_string", %Q{"#{key}"}, value, "keyword", "key:value:", "2"];
    end

    def block_literal(param_list, function)
        [list(param_list.map { |item| ["push_variable", item] }), function, "keyword", "params:function:", "2"];
    end
end
