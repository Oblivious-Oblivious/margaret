require_relative "../ast/ASTFactory";

AST_TYPE = "s-expressions";

class Array
    def >>(item)
        self.unshift item;
    end
end

class Parser
    attr_accessor :table, :ast;

    def initialize(table)
        @table = table;
        @ast = ASTFactory.new.generate AST_TYPE;
        @is_comma_message = true;
    end

    def toggle_comma_as_message_while_in_association
        @is_comma_message = @is_comma_message.!;
    end

    def __list_of_grammar_rule(&rule)
        __list = [];
        loop do
            current_position = table.token_table_pos;
            item = rule.call;
            break if current_position == table.token_table_pos;
            __list << item;
        end
        __list;
    end

    def __consume_quoted_tokens
        paren_count = 0;
        __items = [];
        loop do
            break if table.lookahead(1) == ")" and paren_count == 0;
            tok = table.consume.value;
            paren_count += 1 if tok == "(";
            paren_count -= 1 if tok == ")";
            __items << ast.symbol_literal(tok);
        end
        __items >> ast.symbol_literal("(");
        __items << ast.symbol_literal(")");
        __items;
    end

    def analyse_syntax
        first_unit;
    end

    def first_unit
        result = operand;
        table.ensure_consumption "eof", "reached end of program";
        result;
    end

    def list
        is_quoted = table.consume if table.lookahead(1) == "`";
        table.ensure_consumption "(", "missing opening parenthesis on list";

        if is_quoted != nil
            __units = quotted_list;
        else
            __units = translation_unit_list;
        end
        
        table.ensure_consumption ")", "missing closing parenthesis on list";
        ast.list __units;
    end

    def translation_unit_list
        __list_of_grammar_rule { translation_unit };
    end

    def translation_unit
        current_position = table.token_table_pos;
        optional_assignment_list = assignment_message_list;
        expr = expression;

        if current_position != table.token_table_pos
            ast.translation_unit optional_assignment_list, expr;
        else
            ast.empty;
        end
    end

    def assignment_message_list
        __list_of_grammar_rule { assignment_message };
    end
    
    def assignment_message
        current_position = table.token_table_pos;
        id = terminal_IDENTIFIER;

        if current_position != table.token_table_pos
            eq = terminal_EQUALS;
            if eq != nil
                ast.assignment_message id, eq;
            else
                table.resume;
            end
        end
    end

    def expression
        # TODO ast
        left = operand;
        if left and left[0] == " " and left[-1] == " "
            left = "(#{left[1...-1]})";
        end

        chain = message_chain;
        __cascaded_list = cascaded_message_list;
        if chain and chain[0].is_a? String
            chain = [chain];
            __cascaded_list.each do |casc|
                chain << casc;
            end

            res = "";

            (0...chain.size-1).each do |i|
                key = chain[i][0];
                args = chain[i][1];

                res << "(" << key << " " << left << " ";
                (0...args.size-1).each do |i|
                    res << args[i] << " ";
                end
                res << args[args.size-1] << ") ";
            end
            key = chain[chain.size-1][0];
            args = chain[chain.size-1][1];

            if chain.size > 1
                res << "(";
            end
            res << key << " " << left << " ";
            (0...args.size-1).each do |i|
                res << args[i] << " ";
            end
            res << args[args.size-1];
            if chain.size > 1
                res << ")";
            end

            "(" + res + ")";
        elsif chain and chain.size > 0
            res = "";
            right_sides = [];
            number_of_nests = chain[-1];
            (0...number_of_nests).each do |i|
                msg = chain[i][0];
                right = chain[i][1];
                if right == ""
                    right_sides << right;
                else
                    right_sides << " " + right;
                end
                
                res << "#{msg} (";
            end
            right_sides.reverse!;
            msg = chain[number_of_nests][0];
            right = chain[number_of_nests][1];
            if right == ""
                res << "#{msg} #{left}";
            else
                res << "#{msg} #{left} #{right}";
            end

            number_of_nests.times do |i|
                res << ")" << right_sides[i];
            end

            "(" + res + ")";
        elsif left != nil
            left;
        end
    end

    def cascaded_message_list
        __casc = [];
        loop do
            break if table.lookahead(1) != ";"
            table.ensure_consumption ";", "missing semicolon after cascaded message";
            __casc << message_chain;
        end
        __casc;
    end

    def message_chain
        def __chain_helper(rest_un)
            res = [];
            number_of_nests = 0;

            if rest_un.size > 0
                (0...rest_un.size-1).each do |i|
                    msg = rest_un[i][0];
                    right = rest_un[i][1];
                    res << [msg, right];
                end
                msg = rest_un[rest_un.size-1][0];
                right = rest_un[rest_un.size-1][1];
                res << [msg, right];
                number_of_nests += rest_un.size-1;
            end

            [res, number_of_nests];
        end

        if table.lookahead(1).type == Type::IDENTIFIER
            _id = table.consume;
            optional_id_symbol = table.consume;
            possible_colon = table.consume;
            table.resume;
            table.resume;
            table.resume;
            if optional_id_symbol == ":" or (optional_id_symbol.type == Type::ID_SYMBOL and possible_colon == ":")
                rest_key = keyword_message;
                res = rest_key;
                number_of_nests = 0;

                if res.size > 0
                    [*res, number_of_nests];
                end
            else
                res = [];
                number_of_nests = 0;

                unchain = __chain_helper(unary_message_chain);
                res += unchain[0];
                number_of_nests += unchain[1];

                binchain = __chain_helper(binary_message_chain);
                res += binchain[0];
                number_of_nests += binchain[1];

                rest_key = keyword_message;
                if rest_key[1].size > 0
                    msg = rest_key[0];
                    args = rest_key[1];
                    res = [[msg, args.join(" ")]] + res;
                    number_of_nests += 1;
                end

                if res.size > 0
                    [*res, number_of_nests];
                end
            end
        elsif table.lookahead(1).type == Type::MESSAGE_SYMBOL
            res = [];
            number_of_nests = 0;
            
            binchain = __chain_helper(binary_message_chain);
            res += binchain[0];
            number_of_nests += binchain[1];

            rest_key = keyword_message;
            if rest_key[1].size > 0
                msg = rest_key[0];
                args = rest_key[1];
                res = [[msg, args.join(" ")]] + res;
                number_of_nests += 1;
            end

            if res.size > 0
                [*res, number_of_nests];
            end
        end
    end

    def unary_message
        unary_selector;
    end

    def unary_selector
        id = terminal_IDENTIFIER;
        optional_symbol = terminal_IDENTIFIER_SYMBOL;

        if table.lookahead(1) != ":"
            msg = "#{id}#{optional_symbol}";
            right = "";

            if msg != ""
                [msg, right];
            else
                [];
            end
        else
            table.resume;
            [];
        end
    end

    def unary_message_chain
        __unary_chain = [];
        loop do
            msg = unary_message;
            break if msg == []
            __unary_chain << msg;
        end
        __unary_chain.reverse!;
    end

    def binary_message_chain
        __list_of_grammar_rule { binary_message }.reverse!;
    end

    def binary_message
        [binary_selector, binary_operand];
    end

    def binary_selector
        if table.lookahead(1) == ","
            terminal_MESSAGE_SYMBOL if @is_comma_message;
        else
            terminal_MESSAGE_SYMBOL;
        end
    end

    def binary_operand
        ast.binary_operand operand, unary_message_chain;
    end

    def keyword_message
        __segment_list = keyword_segment_list;
        [__segment_list[0].join(""), __segment_list[1]];
    end

    def keyword_segment_list
        __keyword_list = [];
        __argument_list = [];
        loop do
            segment = keyword_segment;
            break if segment == nil;
            __keyword_list << segment[0];
            __argument_list << segment[1];
        end
        [__keyword_list, __argument_list];
    end

    def keyword_segment
        if (key = keyword) and (arg = keyword_argument)
            [key, arg];
        end
    end

    def keyword
        id = terminal_IDENTIFIER;
        optional_symbol = terminal_IDENTIFIER_SYMBOL;
        delim = terminal_COLON;

        if id != nil and delim != nil
            ast.keyword id, optional_symbol, delim;
        else
            ast.empty;
        end
    end

    def keyword_argument
        ast.keyword_argument binary_operand, binary_message_chain;
    end

    def operand
        # TODO Change nullity to empty strings
        res = nil;
        current_position = table.token_table_pos;
        if current_position == table.token_table_pos
            res = literal;
        end
        if current_position == table.token_table_pos
            res = variable;
        end
        # TODO Refactor
        if current_position == table.token_table_pos and table.lookahead(1) != ")" and table.lookahead(1) != "]" and table.lookahead(1) != "}" and table.lookahead(1) != "," and table.lookahead(1) != ";" and table.lookahead(1) != "eof"
            res = list;
        end
        res;
    end

    def literal
        sign = "";
        if ["+", "-"].include? table.lookahead(1).value
            sign = terminal_SIGN;
        end

        if [Type::INTEGER, Type::FLOAT].include?(table.lookahead(1).type)
            base_ten_literal(sign);
        elsif [Type::BINARY, Type::HEXADECIMAL, Type::OCTAL].include?(table.lookahead(1).type)
            alternate_base_literal(sign);
        elsif table.lookahead(1).type == Type::BIGINTEGER
            big_integer_literal(sign);
        elsif table.lookahead(1).type == Type::BIGFLOAT
            big_float_literal(sign);
        elsif table.lookahead(1).type == Type::STRING
            string_literal;
        elsif table.lookahead(1) == ":"
            symbol_literal;
        elsif table.lookahead(1) == "["
            array_literal;
        elsif table.lookahead(1) == "#"
            tuple_literal;
        elsif table.lookahead(1) == "{"
            hash_literal;
        elsif table.lookahead(1) == "`"
            quoted_list_literal;
        elsif table.lookahead(1) == "->"
            block_literal;
        end
    end

    def base_ten_literal(sign)
        ast.base_ten_literal sign, terminal_UNSIGNED_BASE_TEN_NUMBER;
    end

    def alternate_base_literal(sign)
        ast.alternate_base_literal sign, terminal_ALTERNATE_BASE_NUMBER;
    end

    def big_integer_literal(sign)
        ast.big_integer_literal sign, terminal_BIGINTEGER;
    end

    def big_float_literal(sign)
        ast.big_float_literal sign, terminal_BIGFLOAT;
    end
    
    def string_literal
        terminal_STRING;
    end

    def symbol_literal
        table.consume;
        ast.symbol_literal symbol_name;
    end

    def symbol_name
        if table.lookahead(1).type == Type::MESSAGE_SYMBOL
            terminal_MESSAGE_SYMBOL;
        elsif table.lookahead(1).type == Type::IDENTIFIER
            terminal_IDENTIFIER;
        elsif table.lookahead(1).type == Type::STRING
            terminal_UNQUOTED_STRING;
        end
    end

    def array_literal
        table.ensure_consumption "[", "missing opening bracket on array";
        __items = __list_of_grammar_rule { array_literal_item };
        table.ensure_consumption "]", "missing closing bracket on array";
        ast.array_literal __items;
    end

    def array_literal_item
        toggle_comma_as_message_while_in_association;
        value = operand;
        toggle_comma_as_message_while_in_association;
        table.ensure_consumption ",", "array items should be separated by commas" if table.lookahead(1) != "]";
        value;
    end

    def tuple_literal
        table.ensure_consumption "#", "missing '#' symbol on tuple literal";
        table.ensure_consumption "(", "missing opening parenthesis on tuple";
        __items = __list_of_grammar_rule { tuple_item };
        table.ensure_consumption ")", "missing closing parenthesis on tuple";
        ast.tuple_literal __items;
    end

    def tuple_item
        toggle_comma_as_message_while_in_association;
        value = operand;
        toggle_comma_as_message_while_in_association;
        table.ensure_consumption ",", "tuple items should be separated by commas" if table.lookahead(1) != ")";
        value;
    end

    def hash_literal
        table.ensure_consumption "{", "missing opening curly brace on hash";
        __items = __list_of_grammar_rule { association };
        table.ensure_consumption "}", "missing closing curly brace on hash";
        ast.hash_literal __items;
    end

    def association
        if table.lookahead(1).type == Type::IDENTIFIER
            key = terminal_IDENTIFIER;
            table.ensure_consumption ":", "hash keys should be denoted by colons";
            toggle_comma_as_message_while_in_association;
            value = operand;
            toggle_comma_as_message_while_in_association;
            table.ensure_consumption ",", "keys should be separated by commas" if table.lookahead(1) != "}";
            ast.json_association key, value;
        elsif table.lookahead(1) == ":"
            key = symbol_literal;
            table.ensure_consumption ":", "hash keys should be denoted by colons";
            toggle_comma_as_message_while_in_association;
            value = operand;
            toggle_comma_as_message_while_in_association;
            table.ensure_consumption ",", "keys should be separated by commas" if table.lookahead(1) != "}";
            ast.association key, value;
        elsif table.lookahead(1).type == Type::STRING
            key = string_literal;
            table.ensure_consumption ":", "hash keys should be denoted by colons";
            toggle_comma_as_message_while_in_association;
            value = operand;
            toggle_comma_as_message_while_in_association;
            table.ensure_consumption ",", "keys should be separated by commas" if table.lookahead(1) != "}";
            ast.association key, value;
        end
    end

    def quoted_list_literal
        table.ensure_consumption "`", "missing '`' symbol on quoted list literal";
        table.ensure_consumption "(", "missing opening parenthesis on quoted list literal";
        __items = __consume_quoted_tokens;
        table.ensure_consumption ")", "missing closing parenthesis on quoted list literal";
        ast.quoted_list_literal __items;
    end

    def block_literal
        table.ensure_consumption "->", "missing '->' symbol on block literal";
        table.ensure_consumption "(", "missing opening parenthesis on block literal";
        __items = __consume_quoted_tokens;
        table.ensure_consumption ")", "missing closing parenthesis on block literal";
        ast.block_literal __items;
    end

    def variable
        optional_instance_symbol = "";
        if table.lookahead(1) == "@"
            optional_instance_symbol = terminal_INSTANCE_SYMBOL;
        end

        ast.variable optional_instance_symbol, terminal_IDENTIFIER;
    end

    def list
        table.ensure_consumption "(", "missing opening parenthesis on list";
        __units = __list_of_grammar_rule { message };
        table.ensure_consumption ")", "missing closing parenthesis on list";
        ast.list __units;
    end

    def message
        optional_assignment_list = __list_of_grammar_rule { assignment_message };
        expr = expression;

        if optional_assignment_list.empty?
            ast.empty;
        else
            ast.translation_unit optional_assignment_list, expr;
        end
    end

    def assignment_message
        current_position = table.token_table_pos;
        id = variable;

        if table.lookahead(1) == "="
            ast.assignment_message id, terminal_EQUALS;
        # else
        #     table.resume;
        end
    end

    def expression
        operand;
    end

    def terminal_UNSIGNED_BASE_TEN_NUMBER
        ast.terminal_UNSIGNED_BASE_TEN_NUMBER table.consume;
    end

    def terminal_ALTERNATE_BASE_NUMBER
        ast.terminal_ALTERNATE_BASE_NUMBER table.consume;
    end

    def terminal_BIGINTEGER
        ast.terminal_BIGINTEGER table.consume;
    end

    def terminal_BIGFLOAT
        ast.terminal_BIGFLOAT table.consume;
    end

    def terminal_STRING
        ast.terminal_STRING table.consume;
    end

    def terminal_UNQUOTED_STRING
        ast.terminal_UNQUOTED_STRING table.consume;
    end

    def terminal_IDENTIFIER
        if table.lookahead(1).type == Type::IDENTIFIER
            ast.terminal_IDENTIFIER table.consume;
        end
    end

    def terminal_MESSAGE_SYMBOL
        if table.lookahead(1).type == Type::MESSAGE_SYMBOL
            ast.terminal_MESSAGE_SYMBOL table.consume;
        end
    end

    def terminal_IDENTIFIER_SYMBOL
        if table.lookahead(1).type == Type::ID_SYMBOL
            ast.terminal_IDENTIFIER_SYMBOL table.consume;
        end
    end

    def terminal_INSTANCE_SYMBOL
        ast.terminal_INSTANCE_SYMBOL table.consume;
    end

    # TODO Issue a module with symbol representations for typechecking (hashmap or tokens)
    def terminal_SIGN
        ast.terminal_SIGN table.consume;
    end

    def terminal_EQUALS
        ast.terminal_EQUALS table.consume;
    end

    def terminal_COLON
        if table.lookahead(1) == ":"
            ast.terminal_COLON table.consume;
        end
    end
end
