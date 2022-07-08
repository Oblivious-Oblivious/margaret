require_relative "../ast/ASTFactory";

AST_TYPE = "s-expressions";

class Parser
    attr_accessor :lexer, :ast;

    def initialize(lexer)
        @lexer = lexer;
        @ast = ASTFactory.new.generate AST_TYPE;
    end

    def consume_next
        lexer.next_token;
        # print "consumed #{@token} at ";
        # p caller[0].scan(/\d+/).first;
        # @token;
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

    def error(message)
        raise StandardError.new message;
        # TODO Track line numbers to each error
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
        ensure_consumption "eof", "reached end of program";
    end

    def list
        terminal_LITERAL_BACKQUOTE;
        ensure_consumption "(", "missing opening parenthesis on list";        
        translation_unit_list;
        ensure_consumption ")", "missing closing parenthesis on list";
    end

    def translation_unit_list
        loop do
            current_position = token_table_pos;
            translation_unit;
            break if current_position == token_table_pos;
        end
    end

    def translation_unit
        if peek_token == "`" or peek_token == "("
            list;
        else
            statement;
        end
    end

    def statement
        assignment_message;
        expression_list;
    end

    def assignment_message
        terminal_IDENTIFIER;
        terminal_EQUALS;
    end

    def expression_list
        loop do
            current_position = token_table_pos;
            expression;
            break if current_position == token_table_pos;
        end
    end

    def expression
        operand;
        message_list;
    end

    def operand
        # TODO Make sure operand rule emits one production only
        current_position = token_table_pos;
        if current_position == token_table_pos
            literal;
        end
        if current_position == token_table_pos
            terminal_IDENTIFIER;
        end
        if current_position == token_table_pos
            terminal_SELF;
        end
        if current_position == token_table_pos
            terminal_SUPER
        end
    end

    def message_list
        loop do
            current_position = token_table_pos;
            message;
            break if current_position == token_table_pos;
        end
    end

    def message
        # TODO Make sure operand rule emits one production only
        current_position = token_table_pos;
        if current_position == token_table_pos
            unary_message;
        end
        if current_position == token_table_pos
            binary_message;
        end
        if current_position == token_table_pos
            keyword_message;
        end
    end

    def unary_message
        unary_selector;
    end

    def unary_selector
        terminal_IDENTIFIER;
        terminal_IDENTIFIER_SYMBOL;
    end

    def binary_message
        current_position = token_table_pos;
        binary_selector;
        if current_position != token_table_pos;
            translation_unit_list;
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
            translation_unit_list;
            terminal_IDENTIFIER;
        end
    end

    def literal
        # TODO Make sure operand rule emits one production only
        current_position = token_table_pos;
        if current_position == token_table_pos
            base_ten_literal;
        end
        if current_position == token_table_pos
            alternate_base_literal;
        end
        if current_position == token_table_pos
            string_literal;
        end
        if current_position == token_table_pos
            tuple_literal;
        end
        if current_position == token_table_pos
            hash_literal;
        end
        if current_position == token_table_pos
            symbol_literal;
        end
    end

    def base_ten_literal
        terminal_SIGN;
        positive_base_ten_literal;
    end

    def positive_base_ten_literal
        if peek_token.type == Type::INTEGER
            consume_next;
        elsif peek_token.type == Type::FLOAT
            consume_next;
        end
    end

    def alternate_base_literal
        if peek_token.type == Type::BINARY
            consume_next;
        end
        if peek_token.type == Type::HEXADECIMAL
            consume_next;
        end
        if peek_token.type == Type::OCTAL
            consume_next;
        end
    end
    
    def string_literal
        terminal_STRING;
    end

    def tuple_literal
        if peek_token == "["
            consume_next;
            tuple_items;
            ensure_consumption "]", "missing closing bracket on tuple";
        end
    end
    
    def tuple_items
        loop do
            current_position = token_table_pos;
            translation_unit_list;
            break if current_position == token_table_pos;
        end
    end

    def hash_literal
        if peek_token == "{"
            consume_next;
            hash_list;
            ensure_consumption "}", "missing closing curly brace on hash";
        end
    end

    def hash_list
        loop do
            current_position = token_table_pos;
            hash;
            break if current_position == token_table_pos;
        end
    end

    def hash
        # TODO Turn this into a regular binary message for symbols and strings
        if peek_token.type == Type::IDENTIFIER
            terminal_IDENTIFIER;
            ensure_consumption ":", "json style keys should be denoted by colons";
            translation_unit_list;
        elsif peek_token == ":"
            symbol_literal;
            ensure_consumption "=>", "hash keys should be denoted by arrow symbols";
            translation_unit_list;
        elsif peek_token.type == Type::STRING
            string_literal;
            ensure_consumption "=>", "hash keys should be denoted by arrow symbols";
            translation_unit_list;
        else
            # TODO empty hash
        end
    end

    def symbol_literal
        if peek_token == ":"
            consume_next;
            terminal_IDENTIFIER;
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
