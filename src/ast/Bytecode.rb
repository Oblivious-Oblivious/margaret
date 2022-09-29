class Bytecode
    def empty
        [nil];
    end

    def first_unit(unit)
        unit;
    end

    def translation_unit(optional_assignment_list, expr)
        res = expr;
        (optional_assignment_list.size-1).downto 0 do |i|
            item = optional_assignment_list[i];
            item.each { |opcode| res << opcode };
        end
        res;
    end

    def assignment(id, _)
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
        res = [];
        object.each { |opcode| res << opcode };
        selectors.each do |sel|
            res << "unary";
            res << sel[0];
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
        res = [];
        object.each { |opcode| res << opcode };
        selectors.each do |sel|
            sel[1].each { |opcode| res << opcode };
            res << "binary" << sel[0];
        end
        res;
    end

    def binary_object(object)
        object;
    end

    def binary_selector(sel, obj)
        res = [];
        res << sel;
        res << obj;
        res;
    end

    def keyword_message(object, selectors)
        if selectors.size > 1 and selectors.all? { |sel| sel.first == selectors.first.first }
            res = [];
            selectors.each do |sel|
                object.each { |opcode| res << opcode };
                sel[1].each { |opcode| res << opcode };
                res << "keyword" << sel[0] << "1";
            end
            res;
        else
            joined_selector = "";
            selectors.each { |sel| joined_selector << sel[0] };

            res = [];
            object.each { |opcode| res << opcode };
            selectors.each do |sel|
                sel[1].each { |opcode| res << opcode };
            end
            res << "keyword" << joined_selector << "#{selectors.size}";
            res;
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
        res = [];
        unit_list.each do |unit|
            unit.each { |opcode| res << opcode };
        end
        res;
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
            ["push_variable", name];
        end
    end

    # TODO New activation window on procs and methods
    def proc_literal(param_list, function)
        res = ["STARTpush_proc"];
        param_list.each { |item| res << "push_variable" << item };
        res << "push_tensor" << "#{param_list.size}";
        function.each { |item| res << item };
        res << "ENDpush_proc";
        res;
    end

    def c_function_declaration(return_type, name, params)
        res = ["STARTpush_c_function", "push_variable", return_type, "push_variable", name];
        params.each { |item| res << "push_variable" << "CFunParam" << "push_variable" << "#{item[0]}" << "push_variable" << "#{item[1]}" << "keyword" << "c_type:c_name:" << "2" };
        res << "push_tensor" << "#{params.size}" << "ENDpush_c_function";
        res;
    end
    
    def unary_method_definition(selector, function)
        res = ["STARTpush_unary_method", %Q{"#{selector}"}];
        function.each { |item| res << item };
        res << "ENDpush_unary_method";
        res;
    end

    def binary_method_definition(selector, param, function)
        res = ["STARTpush_binary_method", %Q{"#{selector}"}, "push_variable", param];
        function.each { |item| res << item };
        res << "ENDpush_binary_method";
        res;
    end
    
    def keyword_method_definition(selector, function)
        joined_selector = "";
        selector.each { |sel| joined_selector << sel[0] };

        res = ["STARTpush_keyword_method", %Q{"#{joined_selector}"}];
        selector.each { |sel| res << "push_variable" << sel[1] };
        res << "push_tensor" << "#{selector.size}";
        function.each { |item| res << item };
        res << "ENDpush_keyword_method";
        res;
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
        when "2", "+2", "0b10", "+0b10", "0b010", "+0b010", "0o2", "+0o2", "0o002", "+0o002", "0x2", "+0x2", "0x02", "+0x02"
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
        res = [];
        item_list.each do |item|
            item.each { |opcode| res << opcode };
        end
        res << "push_tensor" << "#{item_list.size}";
        res;
    end

    def hash_literal(association_list)
        res = [];
        association_list.each do |item|
            item.each { |opcode| res << opcode };
        end
        res << "push_hash" << "#{association_list.size}";
        res;
    end

    def association(key, value)
        res = [];
        res << "push_variable" << "Association";
        key.each { |opcode| res << opcode };
        value.each { |opcode| res << opcode };
        res << "keyword" << "key:value:" << "2";
        res;
    end

    def json_association(key, value)
        res = [];
        res << "push_variable" << "Association" << "push_string" << %Q{"#{key}"};
        value.each { |opcode| res << opcode };
        res << "keyword" << "key:value:" << "2";
        res;
    end
end
