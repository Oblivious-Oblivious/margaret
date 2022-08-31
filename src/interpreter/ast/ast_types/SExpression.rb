require_relative "../ASTInterface";

class SExpression < ASTInterface
    def empty
        "";
    end

    def first_unit(unit)
        unit;
    end

    def translation_unit(optional_assignment_list, expr)
        res = "";
        if optional_assignment_list.size > 0
            res << "#{optional_assignment_list[0]}";
            (1...optional_assignment_list.size).each do |i|
                res << "(" << optional_assignment_list[i];
            end
        end

        res << expr;

        if optional_assignment_list.size > 0
            (optional_assignment_list.size-1).times do
                res << ")";
            end
        end
        res;
    end

    def assignment(id, eq)
        "#{eq} #{id} ";
    end

    def message(msg)
        msg;
    end

    def unary_message(object, selectors)
        def __unary_message_helper(object, selectors)
            if selectors.empty?
                object;
            else
                "(" << selectors.pop << " " << __unary_message_helper(object, selectors) << ")";
            end
        end
        __unary_message_helper(object, selectors)[1...-1];
    end

    def unary_object(object)
        object;
    end

    def unary_selector(id, optional_symbol)
        "#{id}#{optional_symbol}";
    end

    def binary_message(object, selectors)
        def __binary_message_helper(object, selectors)
            if selectors.empty?
                object;
            else
                curr = selectors.pop;
                "(" << curr[0] << " " << __binary_message_helper(object, selectors) << " " << curr[1] << ")";
            end
        end
        __binary_message_helper(object, selectors)[1...-1];
    end

    def binary_object(object)
        object;
    end

    def binary_selector(sel, obj)
        [sel, obj];
    end

    def keyword_message(object, selectors)
        if selectors.size > 1 and selectors.all? { |sel| sel.first == selectors.first.first }
            res = "(";
            selectors.size.times do |i|
                res << selectors[0][0] << " " << object << " " << selectors[i][1] << ", ";
            end
            res.delete_suffix!(", ");
            res << ")";
        else
            res = "";
            selectors.each { |sel| res << sel[0] };
            res << " " << object << " ";
            selectors.each { |sel| res << sel[1] << " " };
            res[0...-1];
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
        "#{sign}#{number}";
    end

    def float_literal(sign, number)
        "#{sign}#{number}";
    end

    def char_literal(sign, char)
        "#{sign}#{char}";
    end

    def string_literal(string)
        string;
    end

    def variable(optional_instance_symbol, name)
        "#{optional_instance_symbol}#{name}";
    end

    def list(unit_list)
        res = "(";

        if unit_list.size > 0
            (0...unit_list.size-1).each do |i|
                res << unit_list[i] << ", ";
            end
            res << unit_list[unit_list.size-1];
        end

        res << ")";
        res;
    end

    def tuple_literal(item_list)
        "new Tuple #{list(item_list)}";
    end

    def hash_literal(association_list)
        "new Hash #{list(association_list)}";
    end

    def association(key, value)
        "#{key}: #{value}";
    end

    def json_association(key, value)
        association(%Q{"#{key}"}, value);
    end

    def proc_literal(param_list, function)
        res = "params:function: Proc ";
        res << list(param_list);
        res << " ";
        res << function;
    end

    def c_function_declaration(return_type, name, params)
        res = "name:params:return_type: CLib ";
        res << %Q{"#{name}"};
        res << " ";
        res << %Q{"#{return_type}"};
        res << " ";
        res << list(params.map { |param| %Q{c_type:c_name: CFunParam "#{param[0]}" "#{param[1]}"} });
    end

    def unary_method_definition(selector, function)
        res = "selector:proc: Method ";
        res << %Q{"#{selector}"};
        res << " ";

        res << proc_literal([], function);
    end

    def binary_method_definition(selector, param, function)
        res = "selector:proc: Method ";
        res << %Q{"#{selector}"};
        res << " ";

        res << proc_literal([param], function);
    end

    def keyword_method_definition(selector, function)
        res = "selector:proc: Method ";
        res << %Q{"};
        selector.each { |keyword| res << keyword[0] };
        res << %Q{"};
        res << " ";

        res << proc_literal(selector.map { |keyword| keyword[1] }, function);
    end
end
