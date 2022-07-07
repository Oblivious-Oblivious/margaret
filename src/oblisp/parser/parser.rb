class Parser
    attr_accessor :lexer, :token;

    def initialize(lexer)
        @lexer = lexer;
        @token = nil;
    end

    def consume_next
        @token = lexer.next_token;
        # print "consumed #{@token} at ";
        # p caller[0].scan(/\d+/).first;
        # @token;
    end

    def peek_token
        @token = lexer.peek_token;
        # print "peeked #{peek} at ";
        # p caller[0].scan(/\d+/).first;
        # @token;
    end

    def error(message)
        raise StandardError.new message;
        # TODO Gather a list of errors and output after parsing all code
        # puts "#{lexer.filename}:#{token.line_number}: #{'error'.red} #{message}";
        # puts "Compilation #{'failed'.red}";
    end

    def analyse_syntax
        first_unit;
        "Compilation #{'successful'.green()}";
    end

    def first_unit
        list;

        # TODO first_unit
        if consume_next == "eof"
        else
            error "reached end of program";
        end
    end

    def list
        terminal_LITERAL_BACKQUOTE;
        if consume_next == "("
            translation_unit;
            if consume_next == ")"
                # TODO list
            else
                error "missing closing parenthesis on list";
            end
        else
            error "missing opening parenthesis on list";
        end
    end

    def translation_unit
        terminal_LITERAL_BACKQUOTE;
        if peek_token == "("
            list;
            translation_unit;
        # TODO Fix grammar ambiguity
        elsif peek_token != ")" and peek_token != "]" and peek_token != "}" and peek_token != "eof"
            expression;
            translation_unit;
        else
            # TODO translation_unit
        end
    end

    def expression
        current_token = peek_token;
        if current_token == peek_token
            message;
        end
        if current_token == peek_token
            object;
        end
        if current_token == peek_token
            literal;
        end
    end

    def object
        current_token = peek_token;
        if current_token == peek_token
            terminal_IDENTIFIER;
        end
        if current_token == peek_token
            terminal_SELF;
        end
        if current_token == peek_token
            terminal_SUPER
        end
    end

    def message
        current_token = peek_token;
        if current_token == peek_token
            unary_message;
        end
        if current_token == peek_token
            binary_message;
        end
        if current_token == peek_token
            keyword_message;
        end
    end

    def unary_message
        unary_selector;
    end

    def unary_selector
        current_token = peek_token;
        terminal_IDENTIFIER;

        if current_token != peek_token
            terminal_IDENTIFIER_SYMBOL;
        end
    end

    def binary_message
        current_token = peek_token;
        binary_selector;
        if current_token != peek_token
            translation_unit;
        end
    end

    def binary_selector
        terminal_MESSAGE_SYMBOL;
    end

    def keyword_message
        keyword_list;
        terminal_SEMICOLON;
    end

    def keyword_list
        terminal_IDENTIFIER;
        while peek_token == ":"
            consume_next;
            translation_unit;
            terminal_IDENTIFIER;
        end
    end

    def literal
        current_token = peek_token;
        if current_token == peek_token
            base_ten_literal;
        end
        if current_token == peek_token
            alternate_base_literal;
        end
        if current_token == peek_token
            string_literal;
        end
        if current_token == peek_token
            tuple_literal;
        end
        if current_token == peek_token
            hash_literal;
        end
        if current_token == peek_token
            symbol_literal;
        end
    end

    def base_ten_literal
        sign;
        positive_base_ten_literal;
    end

    def sign
        if peek_token == '+' or peek_token == '-'
            consume_next;
        end
    end

    def positive_base_ten_literal
        if peek_token.type == Type::INTEGER
            consume_next;
            # TODO integer
        elsif peek_token.type == Type::FLOAT
            consume_next;
            # TODO float
        end
    end

    def alternate_base_literal
        if peek_token.type == Type::BINARY
            consume_next;
            # TODO binary
        end
        if peek_token.type == Type::HEXADECIMAL
            consume_next;
            # TODO hexadecimal
        end
        if peek_token.type == Type::OCTAL
             consume_next;
            # TODO octal
        end
    end
    
    def string_literal
        if peek_token.type == Type::STRING
            consume_next;
            # TODO string
        end
    end

    def tuple_literal
        if peek_token == "["
            consume_next;
            tuple_items;
            if consume_next == "]"
                # TODO tuple
            else
                error "missing closing bracket on tuple";
            end
        end
    end
    
    def tuple_items
        current_token = peek_token;
        translation_unit;
        if current_token != peek_token
            tuple_items;
        end
    end

    def hash_literal
        if peek_token == "{"
            consume_next;
            hash_list;
            if consume_next == "}"
                # TODO hash
            else
                error "missing closing curly brace on hash";
            end
        end
    end

    def hash_list
        current_token = peek_token;
        hash;
        if current_token != peek_token
            hash_list;
        end
    end

    def hash
        if peek_token.type == Type::IDENTIFIER
            terminal_IDENTIFIER;
            if consume_next == ":"
                translation_unit;
            else
                error "json style keys should be denoted by colons";
            end
        elsif peek_token == ":"
            symbol_literal;
            # TODO Turn this into a regular binary message for symbols and strings
            if consume_next == "=>"
                translation_unit;
            else
                error "hash keys should be denoted by arrow symbols";
            end
        elsif peek_token.type == Type::STRING
            string_literal;
            if consume_next == "=>"
                translation_unit;
            else
                error "hash keys should be denoted by arrow symbols";
            end
        else
        end
    end

    def symbol_literal
        if peek_token == ":"
            consume_next;
            terminal_IDENTIFIER;
        end
    end

    def terminal_LITERAL_BACKQUOTE
        if peek_token == "`"
            consume_next;
        end
    end

    def terminal_SELF
        if peek_token.type == Type::SELF
            consume_next;
        end
    end

    def terminal_SUPER
        if peek_token.type == Type::SUPER
            consume_next;
        end
    end

    def terminal_IDENTIFIER
        if peek_token.type == Type::IDENTIFIER
            consume_next;
        end
    end

    def terminal_MESSAGE_SYMBOL
        if peek_token.type == Type::MESSAGE_SYMBOL
            consume_next;
        end
    end

    def terminal_IDENTIFIER_SYMBOL
        if peek_token.type == Type::ID_SYMBOL
            consume_next;
        end
    end

    def terminal_SEMICOLON
        if peek_token == ";"
            consume_next;
        end
    end
end
