class Parser
    attr_accessor :lexer, :token;

    def initialize(lexer)
        @lexer = lexer;
        @token = nil;
    end

    def next_token
        @token = lexer.next_token;
        # print "consumed #{@token} at ";
        # p caller[0].scan(/\d+/).first;
        # @token;
    end

    def prev_token
        # print "undid #{@token} at ";
        @token = lexer.prev_token;
        # p caller[0].scan(/\d+/).first;
        # @token;
    end

    def peek_token
        peek = lexer.next_token;
        lexer.prev_token;
        # print "peeked #{peek} at ";
        # p caller[0].scan(/\d+/).first;
        peek;
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

        if next_token == "eof"
            # TODO
        else
            error "reached end of program";
        end
    end

    def list
        if next_token == "("
            translation_unit;
            if next_token == ")"
                # TODO
            else
                error "missing closing parenthesis on list";
            end
        else
            error "missing opening parenthesis on list";
        end
    end

    def translation_unit
        if peek_token == "("
            list;
            translation_unit;
        # TODO Fix grammar ambiguity
        elsif peek_token != ")" and peek_token != "]" and peek_token != "}" and peek_token != "eof"
            expression;
            translation_unit;
        else
            # TODO
        end
    end

    def expression
        current_token = peek_token;
        if current_token == peek_token
            object;
        end
        if current_token == peek_token
            message;
        end
        if current_token == peek_token
            literal;
        end
    end

    def object
        current_token = peek_token;
        if current_token == peek_token
            identifier;
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
        identifier;
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
    end

    def keyword_list
        identifier;
        if peek_token == ":"
            next_token;
            translation_unit;
            keyword_list;
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
            next_token;
        end
    end

    def positive_base_ten_literal
        if peek_token.type == Type::INTEGER
            next_token;
            # TODO integer
        elsif peek_token.type == Type::FLOAT
            next_token;
            # TODO float
        end
    end

    def alternate_base_literal
        if peek_token.type == Type::BINARY
            next_token;
            # TODO binary
        end
        if peek_token.type == Type::HEXADECIMAL
            next_token;
            # TODO hexadecimal
        end
        if peek_token.type == Type::OCTAL
             next_token;
            # TODO octal
        end
    end
    
    def string_literal
        if peek_token.type == Type::STRING
            next_token;
            # TODO string
        end
    end

    def tuple_literal
        if peek_token == "["
            next_token;
            tuple_items;
            if next_token == "]"
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
            next_token;
            hash_list;
            if next_token == "}"
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
            identifier;
            if next_token == ":"
                translation_unit;
            else
                error "json style keys should be denoted by colons";
            end
        elsif peek_token == ":"
            symbol_literal;
            if next_token == "="
                if next_token == ">"
                    translation_unit;
                else
                    error "hash keys should be denoted by arrow symbols";
                end
            else
                error "hash keys should be denoted by arrow symbols";
            end
        elsif peek_token.type == Type::STRING
            string_literal;
            if next_token == "="
                if next_token == ">"
                    translation_unit;
                else
                    error "hash keys should be denoted by arrow symbols";
                end
            else
                error "hash keys should be denoted by arrow symbols";
            end
        else
        end
    end

    def symbol_literal
        if peek_token == ":"
            next_token;
            identifier;
        end
    end

    def identifier
        current_token = peek_token;
        terminal_ID;

        if current_token != peek_token
            terminal_IDENTIFIER_SYMBOL;
        end
    end

    def terminal_SELF
        if peek_token.type == Type::SELF
            next_token;
        end
    end

    def terminal_SUPER
        if peek_token.type == Type::SUPER
            next_token;
        end
    end

    def terminal_ID
        if peek_token.type == Type::IDENTIFIER
            next_token;
        end
    end

    def terminal_MESSAGE_SYMBOL
        if peek_token.type == Type::MESSAGE_SYMBOL
            next_token;
        end
    end

    def terminal_IDENTIFIER_SYMBOL
        if peek_token == "?" or peek_token == "!"
            next_token;
        end
    end
end
