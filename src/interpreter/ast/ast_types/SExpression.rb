require_relative "../ASTInterface";

class SExpression < ASTInterface
    def empty
        "";
    end

    def first_unit(unit)
        unit;
    end

    def translation_unit(unit)
        unit;
    end

    def base_ten_literal(sign, number)
        "#{sign}#{number}";
    end

    def alternate_base_literal(sign, number)
        "#{sign}#{number}";
    end
    
    def big_integer_literal(sign, number)
        %Q{(new: BigInteger "#{sign}#{number[3...]}")};
    end

    def big_float_literal(sign, number)
        %Q{(new: BigFloat "#{sign}#{number[3...]}")};
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
        "(new Tuple #{list(item_list)})";
    end

    def tuple_item(item)
        item;
    end

    def hash_literal(association_list)
        "(new Hash #{list(association_list)})";
    end

    def association(key, value)
        "#{key}: #{value}";
    end

    def json_association(key, value)
        association(symbol_literal(key), value);
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

    def expression(optional_assignment_list, expr)
        res = "";
        if optional_assignment_list.size > 0
            res = "#{optional_assignment_list[0]}";
            (1...optional_assignment_list.size).each do |i|
                # res << " (" << optional_assignment_list[i];
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

    def message(optional_assignment_list, expr)
        res = "#{optional_assignment_list[0]}";
        (1...optional_assignment_list.size).each do |i|
            res << "(" << optional_assignment_list[i];
        end

        res << expr;

        (optional_assignment_list.size-1).times do
            res << ")";
        end
        res;
    end

    def assignment_message(id, eq)
        "#{eq} #{id} ";
    end

    def expression(expr)
        expr;
    end

    def terminal_UNSIGNED_BASE_TEN_NUMBER(number)
        number.value;
    end

    def terminal_ALTERNATE_BASE_NUMBER(number)
        number.value;
    end

    def terminal_BIGINTEGER(number)
        number.value;
    end

    def terminal_BIGFLOAT(number)
        number.value;
    end

    def terminal_STRING(value)
        value.value;
    end

    def terminal_UNQUOTED_STRING(value)
        value.value[1...-1];
    end

    def terminal_IDENTIFIER(id)
        id.value;
    end

    def terminal_INSTANCE_SYMBOL(symb)
        symb.value;
    end

    def terminal_MESSAGE_SYMBOL(symb)
        symb.value;
    end

    def terminal_IDENTIFIER_SYMBOL(symb)
        symb.value;
    end

    def terminal_SIGN(symb)
        symb.value;
    end

    def terminal_EQUALS(symb)
        symb.value;
    end
end
