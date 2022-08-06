require_relative "../ASTInterface";

class SExpression < ASTInterface
    def empty
        "";
    end

    def list(unit_list)
        res = "(";

        if unit_list.size > 0
            (0...unit_list.size-1).each do |i|
                res << unit_list[i] << " ";
            end
            res << unit_list[unit_list.size-1];
        end

        res << ")";
        res;
    end

    def translation_unit(optional_assignment_list, expr)
        res = "#{optional_assignment_list[0]}";
        (1...optional_assignment_list.size).each do |i|
            res << "(" << optional_assignment_list[i];
        end

        if expr[0] == "(" and expr[1] == "(" and expr[-1] == ")" and expr[-2] == ")"
            res << expr[1...-1];
        elsif res == "" and expr[0] == "(" and expr[-1] == ")"
            res << expr[1...-1];
        else
            res << expr;
        end

        (optional_assignment_list.size-1).times do
            res << ")";
        end
        res;
    end

    def assignment_message(id, eq)
        "#{eq} #{id} ";
    end

    def binary_operand(op, unchain)
        if op and op[0] == " " and op[-1] == " "
            op = "#{op[1...-1]}";
        end

        unchain.each do |un|
            op << un << " ";
        end
        op;
    end

    def keyword(id, optional_symbol, delim)
        "#{id}#{optional_symbol}#{delim}";
    end

    def keyword_argument(binop, binchain)
        binchain.each do |bin|
            binop << bin << " ";
        end
        binop;
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

    def array_literal(item_list, type="Array")
        res = "";
        item_list.each do
            res << "(with: "
        end
        res << "(new #{type})";
        item_list.each do |item|
            res << " #{item})";
        end
        res;
    end

    def tuple_literal(item_list)
        array_literal(item_list, "Tuple");
    end

    def hash_literal(association_list)
        array_literal(association_list, "Hash");
    end

    def association(key, value)
        "(key:value: Association #{key} #{value})";
    end

    def json_association(key, value)
        association(symbol_literal(key), value);
    end

    def quoted_list_literal(item_list)
        array_literal(item_list);
    end

    def block_literal(item_list)
        res = "(new Block ";
        res << array_literal(item_list);
        res << ")";
    end

    def symbol_literal(id)
        %Q{(new: Symbol "#{id}")};
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

    def terminal_COLON(symb)
        symb.value;
    end
end
