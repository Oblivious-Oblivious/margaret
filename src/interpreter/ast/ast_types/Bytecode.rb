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
        optional_assignment_list.each do |opt|
            res << opt;
        end
        res << expr;
        res;
    end

    def assignment(id, eq)
        # TODO Fix needs to be called after elements are pushed onto the stack
        ["store", "#{id[1]}"];
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
            res = [];
            selectors.size.times { |i| res << object << selectors[i][1] << "keyword" << selectors[0][0] << "1" };
            res << "push_variable" << "List" << "push_integer" << "#{selectors.size}" << "keyword" << "new:" << "1";
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
        ["push_variable", "BigInteger", "push_string", %Q{"#{sign}#{number[3...]}"}, "keyword", "new:", "1"];
    end

    def big_float_literal(sign, number)
        ["push_variable", "BigFloat", "push_string", %Q{"#{sign}#{number[3...]}"}, "keyword", "new:", "1"];
    end

    def association(key, value)
        [key, value, "keyword", "key:value:", "2"];
    end

    def json_association(key, value)
        ["push_symbol", %Q{"#{key}"}, value, "keyword", "key:value:", "2"];
    end

    def string_literal(string)
        ["push_string", string];
    end

    def symbol_literal(id)
        ["push_symbol", %Q{"#{id}"}];
    end

    def symbol_name(name)
        name;
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
        res << ["push_variable", "List", integer_literal("", unit_list.size), "keyword", "new:", "1"];
        res;
    end

    def tuple_literal(item_list)
        ["push_variable", "Tuple", list(item_list), "keyword", "new:", "1"];
    end

    def hash_literal(association_list)
        ["push_variable", "Hash", list(association_list), "keyword", "new:", "1"];
    end

    def quoted_list_literal(item_list)
        list(item_list);
    end

    def block_literal(param_list, function)
        [list(param_list), function, "keyword", "params:function:", "2"];
    end
end
