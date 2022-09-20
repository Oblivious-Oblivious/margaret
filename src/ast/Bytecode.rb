class Bytecode
    def empty
        [nil];
    end

    def first_unit(unit)
        unit = unit.flatten;
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
            # TODO Multiple assignments do not pop 
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
            selectors.map { |sel| [object, sel[1], "keyword", sel[0], "1"] };
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

    def expression(unit)
        unit;
    end

    def group(unit_list)
        unit_list;
    end

    def variable(optional_instance_symbol, name)
        if name == "nil"
            ["push_nil"];
        elsif name == "true"
            ["push_true"];
        elsif name == "false"
            ["push_false"];
        elsif name == "self"
            ["push_self"];
        elsif name == "super"
            ["push_super"];
        elsif optional_instance_symbol == "@"
            ["push_instance", name];
        else
            ["push_variable", name]
        end
    end

    # TODO New activation window on procs and methods
    def proc_literal(param_list, function)
        ["STARTpush_proc", tensor_literal(param_list.map { |item| ["push_variable", item] }), function, "ENDpush_proc"];
    end

    def c_function_declaration(return_type, name, params)
        params = tensor_literal(params.map { |param| ["push_variable", "CFunParam", "push_variable", "#{param[0]}", "push_variable", "#{param[1]}", "keyword", "c_type:c_name:", "2"] });
        ["STARTpush_c_function", "push_variable", return_type, "push_variable", name, params, "ENDpush_c_function"]
    end
    
    def unary_method_definition(selector, function)
        ["STARTpush_unary_method", %Q{"#{selector}"}, function, "ENDpush_unary_method"];
    end

    def binary_method_definition(selector, param, function)
        ["STARTpush_binary_method", %Q{"#{selector}"}, "push_variable", param, function, "ENDpush_binary_method"];
    end
    
    def keyword_method_definition(selector, function)
        joined_selector = "";
        selector.each { |sel| joined_selector << sel[0] };
        params = tensor_literal(selector.map { |item| ["push_variable", item[1]] });
        ["STARTpush_keyword_method", %Q{"#{joined_selector}"}, params, function, "ENDpush_keyword_method"];
    end

    def literal(unit)
        unit;
    end

    def integer_literal(sign, number)
        number = number.gsub(/_/, "");
        case "#{sign}#{number}"
        # TODO Refactor to work with multiple zeros
        when "0", "-0", "+0", "0b0", "-0b0", "+0b0", "0b00", "-0b00", "+0b00", "0o0", "-0o0", "+0o0", "0o000", "-0o000", "+0o000", "0x0", "-0x0", "+0x0", "0x00", "-0x00", "+0x00"
            ["push_0"];
        when "1", "+1", "0b1", "+0b1", "0b01", "+0b01", "0o1", "+0o1", "0o001", "+0o001", "0x1", "+0x1", "0x01", "+0x01"
            ["push_1"];
        when "-1", "-0b1", "-0b01", "-0o1", "-0o001", "-0x1", "-0x01"
            ["push_minus_1"];
        when "2", "+2", "0b2", "+0b2", "0b02", "+0b02", "0o2", "+0o2", "0o002", "+0o002", "0x2", "+0x2", "0x02", "+0x02"
            ["push_2"];
        else
            if number[0] == "0" and number[1].downcase == "b"
                number = number[2..].to_i(2).to_s;
            elsif number[0] == "0" and number[1].downcase == "o"
                number = number[2..].to_i(8).to_s;
            elsif number[0] == "0" and number[1].downcase == "x"
                number = number[2..].to_i(16).to_s;
            end

            if sign == "-"
                ["push_integer", "#{sign}#{number}"];
            else
                ["push_integer", "#{number}"];
            end
        end
    end

    def float_literal(sign, number)
        number = number.gsub(/_/, "");
        ["push_float", "#{sign}#{number}"];
    end

    def char_literal(sign, char)
        ["push_char", "#{sign}#{char}"];
    end

    def string_literal(string)
        ["push_string", string];
    end

    def tensor_literal(item_list)
        [item_list, "push_tensor", "#{item_list.size}"];
    end

    def hash_literal(association_list)
        [association_list, "push_hash", "#{association_list.size}"];
    end

    def association(key, value)
        ["push_variable", "Association", key, value, "keyword", "key:value:", "2"];
    end

    def json_association(key, value)
        ["push_variable", "Association", "push_string", %Q{"#{key}"}, value, "keyword", "key:value:", "2"];
    end
end
