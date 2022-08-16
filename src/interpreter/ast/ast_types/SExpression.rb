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
            res = "#{optional_assignment_list[0]}";
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

    def assignment_message(id, eq)
        "#{eq} #{id} ";
    end

    def message(msg)
        msg;
    end

    def unary_message(object, selectors)
        if selectors.size == 0
            object;
        else
            "(" << selectors.pop << " " << unary_message(object, selectors) << ")";
        end
    end

    def binary_message(object, selectors)
        if selectors.size == 0
            object;
        else
            curr = selectors.pop;
            "(" << curr[0] << " " << binary_message(object, selectors) << " " << curr[1] << ")";
        end
    end

    def keyword_message(object, selectors)
        res = "";

        selectors.each do |sel|
            res << sel[0];
        end

        res << " " << object << " ";

        selectors.each do |sel|
            res << sel[1] << " ";
        end

        res[0...-1];
    end

    def cascaded_message
        "";
    end

    def literal(unit)
        unit;
    end

    def base_ten_literal(sign, number)
        "#{sign}#{number}";
    end

    def alternate_base_literal(sign, number)
        "#{sign}#{number}";
    end
    
    def big_integer_literal(sign, number)
        %Q{new: BigInteger "#{sign}#{number[3...]}"};
    end

    def big_float_literal(sign, number)
        %Q{new: BigFloat "#{sign}#{number[3...]}"};
    end

    def association(key, value)
        "#{key}: #{value}";
    end

    def json_association(key, value)
        association(symbol_literal(key), value);
    end

    def string_literal(string)
        string;
    end

    def symbol_literal(id)
        %Q{:"#{id}"};
    end

    def symbol_name(name)
        name;
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

    def quoted_list_literal(item_list)
        list(item_list);
    end

    def block_literal(param_list, function)
        res = "(params:function: Block ";
        res << list(param_list);
        res << " ";
        res << function;
        res << ")";
    end
end
