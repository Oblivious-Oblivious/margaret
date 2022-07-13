module Abstract
    def abstract_methods(*args)
        args.each do |name|
            class_eval(<<-END, __FILE__, __LINE__)
                def #{name}(*args)
                    raise NotImplementedError.new("Unimplemented #{name}(#{args}).");
                end
            END
        end
    end

    def error(message)
        raise StandardError.new message;
    end
end

class ASTInterface; extend Abstract;
    abstract_methods :empty,
                     :list,
                     :translation_unit,
                     :assignment_message,
                     :binary_operand,
                     :keyword,
                     :keyword_argument,
                     :base_ten_literal,
                     :tuple_literal,
                     :hash_literal,
                     :association,
                     :json_association,
                     :symbol_literal,
                     :terminal_POSITIVE_BASE_TEN_NUMBER,
                     :terminal_ALTERNATE_BASE_NUMBER,
                     :terminal_STRING,
                     :terminal_IDENTIFIER,
                     :terminal_MESSAGE_SYMBOL,
                     :terminal_IDENTIFIER_SYMBOL,
                     :terminal_SIGN;
end

class Default < ASTInterface
    def empty
    end

    def list(unit_list)
    end

    def translation_unit(optional_assignment_list, expr)
    end

    def assignment_message(id)
    end

    def binary_operand(op, unchain)
    end

    def keyword(id, optional_symbol, delim)
    end

    def keyword_argument(binop, binchain)
    end

    def base_ten_literal(sign, number)
    end

    def tuple_literal(item_list)
    end

    def hash_literal(association_list)
    end

    def association(key, value)
    end

    def json_association(key, value)
    end

    def symbol_literal(id)
    end

    def terminal_POSITIVE_BASE_TEN_NUMBER(number)
    end

    def terminal_ALTERNATE_BASE_NUMBER(number)
    end

    def terminal_STRING(value)
    end

    def terminal_IDENTIFIER(id)
    end

    def terminal_MESSAGE_SYMBOL(symb)
    end

    def terminal_IDENTIFIER_SYMBOL(symb)
    end

    def terminal_SIGN(symb)
    end
end

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

    def assignment_message(id)
        "= #{id} ";
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
        "#{id}#{optional_symbol}#{delim.value}";
    end

    def keyword_argument(binop, binchain)
        binchain.each do |bin|
            binop << bin << " ";
        end
        binop;
    end

    def base_ten_literal(sign, number)
        if sign == "-"
            "(negated #{number})";
        else
            number;
        end
    end

    def tuple_literal(item_list)
        res = "(new Tuple (";

        if item_list.size > 0
            (0...item_list.size-1).each do |i|
                res << item_list[i] << " ";
            end
            res << item_list[item_list.size-1];
        end

        res << "))";
        res;
    end

    def hash_literal(association_list)
        res = "(new Hash (";

        if association_list.size > 0
            (0...association_list.size-1).each do |i|
                res << association_list[i] << " ";
            end
            res << association_list[association_list.size-1];
        end

        res << "))";
        res;
    end

    def association(key, value)
        res = "(key:value: Association #{key} ";
        
        (0...value.size-1).each do |i|
            res << value[i] << " ";
        end
        res << value[value.size-1];

        res << ")";
        res;
    end

    def json_association(key, value)
        association(symbol_literal(key), value);
    end

    def symbol_literal(id)
        %Q{(new Symbol "#{id}")};
    end

    def terminal_POSITIVE_BASE_TEN_NUMBER(number)
        number.value;
    end

    def terminal_ALTERNATE_BASE_NUMBER(number)
        number.value;
    end

    def terminal_STRING(value)
        value.value;
    end

    def terminal_IDENTIFIER(id)
        id.value;
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
end

class ASTFactory
    def generate(ast_type)
        case ast_type
        when "s-expressions"
            SExpression.new;
        else
            Default.new;
        end
    end
end
