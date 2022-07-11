require_relative "../ast/ASTFactory";

AST_TYPE = "s-expressions";

class Parser
    attr_accessor :lexer, :ast, :is_comma_message;

    def initialize(lexer)
        @lexer = lexer;
        @ast = ASTFactory.new.generate AST_TYPE;
        @is_comma_message = true;
    end

    def consume_next
        lexer.next_token;
        # print "consumed #{@token} at ";
        # p caller[0].scan(/\d+/).first;
        # @token;
    end

    def resume_prev
        lexer.prev_token;
    end

    def peek_token
        lexer.peek_token;
        # print "peeked #{peek} at ";
        # p caller[0].scan(/\d+/).first;
        # @token;
    end

    def token_table_pos
        lexer.token_pos;
    end

    def ensure_consumption(token, error_message)
        if consume_next != token
            error error_message;
        end
    end

    def toggle_comma_as_message_while_in_association
        @is_comma_message = is_comma_message.!;
    end

    def error(message)
        raise StandardError.new message;
        # TODO Track line numbers to each error
        # TODO Gather a list of errors and output after parsing all code
        # puts "#{lexer.filename}:#{token.line_number}: #{'error'.red} #{message}";
        # puts "Compilation #{'failed'.red}";
    end

    def analyse_syntax
        first_unit;
    end

    def first_unit
        result = list;
        ensure_consumption "eof", "reached end of program";
        result;
    end

    def list
        is_quoted = terminal_LITERAL_BACKQUOTE;
        ensure_consumption "(", "missing opening parenthesis on list";        
        __units = translation_unit_list;
        ensure_consumption ")", "missing closing parenthesis on list";

        if is_quoted
            ast.quoted_list __units;
        else
            ast.list __units;
        end
    end

    def translation_unit_list
        __units = [];
        loop do
            current_position = token_table_pos;
            unit = translation_unit;
            break if current_position == token_table_pos;
            __units << unit;
        end
        __units;
    end

    def translation_unit
        if peek_token == "`" or peek_token == "("
            list;
        else
            statement;
        end
    end

    def statement
        current_position = token_table_pos;
        optional_assignment_list = assignment_message_list;
        expr = expression;

        # print "OPTIONAL ASS: "; pp optional_assignment_list;
        # print "EXPRESS: "; pp expression;

        res = "";
        if current_position != token_table_pos
            res << "#{optional_assignment_list[0]}";
            (1...optional_assignment_list.size).each do |i|
                res << "(" << optional_assignment_list[i];
            end

            if res == "" and expr[0] == "(" and expr[-1] == ")"
                # TODO Removes parentheses when it is a lone expression
                res << expr[1...-1];
            else
                res << expr;
            end

            (optional_assignment_list.size-1).times do
                res << ")";
            end
        end

        res;
    end

    def assignment_message_list
        __assign_list = [];
        loop do
            current_position = token_table_pos;
            assign = assignment_message;
            break if current_position == token_table_pos;
            __assign_list << assign;
        end
        # print "ASSIGN LIST: "; pp __assign_list;
        __assign_list;
    end
    
    def assignment_message
        current_position = token_table_pos;
        id = terminal_IDENTIFIER;

        if current_position != token_table_pos
            current_position = token_table_pos;
            terminal_EQUALS;
            if current_position != token_table_pos
                # TODO ast
                # ast.assignment_message id;
                "= #{id} ";
            else
                resume_prev;
            end
        end
    end

    def expression
        left = operand;
        # print "LEFT: "; pp left;
        chain = message_chain;
        # print "COMPLETE: "; pp chain;
        if chain and chain[0].is_a? String
            res = "";

            key = chain[0];
            args = chain[1];

            res << key << " " << left << " ";
            (0...args.size-1).each do |i|
                res << args[i] << " ";
            end
            res << args[args.size-1];
            "(" + res + ")";
        elsif chain and chain.size > 0
            res = "";
            right_sides = [];
            number_of_nestings = chain[-1];
            # print "NUMBER OF NESTINGS: "; pp number_of_nestings
            (0...number_of_nestings).each do |i|
                msg = chain[i][0];
                # print "MSG: "; pp msg;
                right = chain[i][1];
                # print "RIGHT: "; pp right;
                if right == ""
                    right_sides << right;
                else
                    right_sides << " " + right;
                end

                # TODO Cascaded
                # __cascaded_list = cascaded_message_list;

                res << "#{msg} (";
            end
            right_sides.reverse!;
            msg = chain[number_of_nestings][0];
            right = chain[number_of_nestings][1];
            if right == ""
                res << "#{msg} #{left}";
            else
                res << "#{msg} #{left} #{right}";
            end

            number_of_nestings.times do |i|
                res << ")" << right_sides[i];
            end

            "(" + res + ")";
        elsif left != nil
            left;
        end
    end

    #   IDENTIFIER     -> 1
    # | MESSAGE_SYMBOL -> 2
    # | IDENTIFIER ':' -> 3
    def message_chain
        if peek_token.type == Type::IDENTIFIER
            _id = consume_next;
            lookahead = consume_next;
            resume_prev;
            resume_prev;
            if lookahead == ":"
                puts "KEYWORD MESSAGE";
                rest_key = keyword_message;
                res = rest_key;
                number_of_nestings = 0;
                pp [*res, number_of_nestings];
            else
                puts "UNARY MESSAGE";
                rest_un = unary_message_chain;
                rest_bin = binary_message_chain;
                rest_key = keyword_message;

                res = [];
                number_of_nestings = 0;
                if rest_un.size > 0
                    (0...rest_un.size-1).each do |i|
                        msg = rest_un[i][0];
                        right = rest_un[i][1];
                        res << [msg, right];
                    end
                    msg = rest_un[rest_un.size-1][0];
                    right = rest_un[rest_un.size-1][1];
                    res << [msg, right];
                    number_of_nestings += rest_un.size-1;
                end

                if rest_bin.size > 0
                    (0...rest_bin.size-1).each do |i|
                        msg = rest_bin[i][0];
                        right = rest_bin[i][1];
                        res << [msg, right];
                    end
                    msg = rest_bin[rest_bin.size-1][0];
                    right = rest_bin[rest_bin.size-1][1];
                    res << [msg, right];
                    number_of_nestings += rest_bin.size-1;
                end

                if rest_key[1].size > 0
                    msg = rest_key[0];
                    args = rest_key[1];
                    res = [[msg, args.join(" ")]] + res;
                    number_of_nestings += 1;
                end

                pp [*res, number_of_nestings];
            end
        elsif peek_token.type == Type::MESSAGE_SYMBOL
            puts "BINARY MESSAGE";
            rest_bin = binary_message_chain;
            rest_key = keyword_message;

            res = [];
            number_of_nestings = 0;
            if rest_bin.size > 0
                (0...rest_bin.size-1).each do |i|
                    msg = rest_bin[i][0];
                    right = rest_bin[i][1];
                    res << [msg, right];
                end
                msg = rest_bin[rest_bin.size-1][0];
                right = rest_bin[rest_bin.size-1][1];
                res << [msg, right];
                number_of_nestings += rest_bin.size-1;
            end

            if rest_key[1].size > 0
                msg = rest_key[0];
                args = rest_key[1];
                res = [[msg, args.join(" ")]] + res;
                number_of_nestings += 1;
            end

            pp [*res, number_of_nestings];
        end
    end

    def unary_message
        unary_selector;
    end

    def unary_selector
        id = terminal_IDENTIFIER;
        optional_symbol = terminal_IDENTIFIER_SYMBOL;

        if peek_token != ":"
            msg = "#{id}#{optional_symbol}";
            right = "";

            if msg != ""
                [msg, right];
            else
                [];
            end
        else
            # TODO Resumes from binary operator
            resume_prev;
            [];
        end
    end

    def unary_message_chain
        __unary_chain = [];
        loop do
            msg = unary_message;
            # TODO null object pattern
            if msg == []
                break;
            elsif msg[-1] == ":"
                resume_prev;
                break;
            end
            __unary_chain << msg;
        end
        __unary_chain.reverse!;
    end

    def binary_message_chain
        __binary_chain = [];
        loop do
            msg = binary_message;
            # TODO null object pattern
            break if msg == [];
            __binary_chain << msg;
        end
        __binary_chain.reverse!;
    end

    def binary_message
        msg = binary_selector;
        right = binary_operand;
        if msg != nil and right != nil
            [msg, right];
        else
            [];
        end
    end

    def binary_selector
        if peek_token == ","
            if is_comma_message
                terminal_MESSAGE_SYMBOL;
            else
                nil;
            end
        else
            terminal_MESSAGE_SYMBOL;
        end
    end

    def binary_operand
        res = operand;
        if res != nil
            rest_un = unary_message_chain;
            rest_un.each do |un|
                res << un << " ";
            end
            res;
        end
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
        key = keyword;
        arg = keyword_argument;

        if key != nil and arg != nil
            [key, arg];
        end
    end

    def keyword
        id = terminal_IDENTIFIER;
        if id != nil
            optional_symbol = terminal_IDENTIFIER_SYMBOL;
            consume_next;
            "#{id}#{optional_symbol}:";
        end
    end

    def keyword_argument
        res = binary_operand;
        
        if res != nil
            rest_bin = binary_message_chain;
            rest_bin.each do |bin|
                res << bin << " ";
            end
            res;
        end
    end

    def operand
        current_position = token_table_pos;
        res = nil;
        if current_position == token_table_pos
            res = literal;
        end
        if current_position == token_table_pos
            res = terminal_IDENTIFIER;
        end
        if current_position == token_table_pos
            res = terminal_SELF;
        end
        if current_position == token_table_pos
            res = terminal_SUPER
        end
        # TODO Refactor
        if current_position == token_table_pos and peek_token != ")" and peek_token != "]" and peek_token != "}" and peek_token != ","
            res = list;
        end
        res;
    end

    def literal
        res = nil;
        current_position = token_table_pos;
        if current_position == token_table_pos
            res = base_ten_literal;
        end
        if current_position == token_table_pos
            res = alternate_base_literal;
        end
        if current_position == token_table_pos
            res = string_literal;
        end
        if current_position == token_table_pos
            res = tuple_literal;
        end
        if current_position == token_table_pos
            res = hash_literal;
        end
        if current_position == token_table_pos
            res = symbol_literal;
        end
        res;
    end

    def base_ten_literal
        ast.base_ten_literal terminal_SIGN, positive_base_ten_literal;
    end

    def positive_base_ten_literal
        terminal_POSITIVE_BASE_TEN_NUMBER;
    end

    def alternate_base_literal
        terminal_ALTERNATE_BASE_NUMBER;
    end
    
    def string_literal
        terminal_STRING;
    end

    def tuple_literal
        if peek_token == "["
            consume_next;
            __items = translation_unit_list;
            ensure_consumption "]", "missing closing bracket on tuple";
            ast.tuple_literal __items;
        end
    end

    def hash_literal
        if peek_token == "{"
            consume_next;
            __list = association_list;
            ensure_consumption "}", "missing closing curly brace on hash";
            ast.hash_literal __list;
        end
    end

    def association_list
        __list = [];
        loop do
            current_position = token_table_pos;
            assoc = association;
            break if current_position == token_table_pos;
            __list << assoc;
        end
        __list;
    end

    def association
        if peek_token.type == Type::IDENTIFIER
            key = terminal_IDENTIFIER;
            ensure_consumption ":", "json style keys should be denoted by colons";
            toggle_comma_as_message_while_in_association;
            value = translation_unit_list;
            toggle_comma_as_message_while_in_association;
            ensure_consumption ",", "json style keys should be separated by commas" if peek_token != "}";
            ast.json_association key, value;
        elsif peek_token == ":"
            key = symbol_literal;
            ensure_consumption "=>", "hash keys should be denoted by arrow symbols";
            toggle_comma_as_message_while_in_association;
            value = translation_unit_list;
            toggle_comma_as_message_while_in_association;
            ensure_consumption ",", "json style keys should be separated by commas" if peek_token != "}";
            ast.association key, value;
        elsif peek_token.type == Type::STRING
            key = string_literal;
            ensure_consumption "=>", "hash keys should be denoted by arrow symbols";
            toggle_comma_as_message_while_in_association;
            value = translation_unit_list;
            toggle_comma_as_message_while_in_association;
            ensure_consumption ",", "json style keys should be separated by commas" if peek_token != "}";
            ast.association key, value;
        end
    end

    def symbol_literal
        if peek_token == ":"
            consume_next;
            ast.symbol_literal terminal_IDENTIFIER;
        end
    end

    def terminal_SELF
        if peek_token.type == Type::SELF
            ast.terminal_SELF consume_next;
        end
    end

    def terminal_SUPER
        if peek_token.type == Type::SUPER
            ast.terminal_SUPER consume_next;
        end
    end

    def terminal_POSITIVE_BASE_TEN_NUMBER
        if [Type::INTEGER, Type::FLOAT].include? peek_token.type
            ast.terminal_POSITIVE_BASE_TEN_NUMBER consume_next;
        end
    end

    def terminal_ALTERNATE_BASE_NUMBER
        if [Type::BINARY, Type::HEXADECIMAL, Type::OCTAL].include? peek_token.type
            ast.terminal_ALTERNATE_BASE_NUMBER consume_next;
        end
    end

    def terminal_STRING
        if peek_token.type == Type::STRING
            ast.terminal_STRING consume_next;
        end
    end

    def terminal_IDENTIFIER
        if peek_token.type == Type::IDENTIFIER
            ast.terminal_IDENTIFIER consume_next;
        end
    end

    def terminal_MESSAGE_SYMBOL
        if peek_token.type == Type::MESSAGE_SYMBOL
            ast.terminal_MESSAGE_SYMBOL consume_next;
        end
    end

    def terminal_IDENTIFIER_SYMBOL
        if peek_token.type == Type::ID_SYMBOL
            ast.terminal_IDENTIFIER_SYMBOL consume_next;
        end
    end

    def terminal_SIGN
        if peek_token == '+' or peek_token == '-'
            ast.terminal_SIGN consume_next;
        end
    end

    def terminal_LITERAL_BACKQUOTE
        if peek_token == "`"
            consume_next;
        end
    end

    def terminal_SEMICOLON
        if peek_token == ";"
            consume_next;
        end
    end

    def terminal_EQUALS
        if peek_token == "="
            consume_next;
        end
    end
end
