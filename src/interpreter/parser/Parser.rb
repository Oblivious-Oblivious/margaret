require_relative "../ast/ASTFactory";

AST_TYPE = "s-expressions";

class Array; def >>(item) = self.unshift item; end

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
        result = translation_unit;
        table.ensure_consumption "eof", "reached end of program";
        ast.first_unit result;
    end

    # def cascaded_message_list
    #     __casc = [];
    #     loop do
    #         break if table.lookahead(1) != ";"
    #         table.ensure_consumption ";", "missing semicolon after cascaded message";
    #         __casc << message_chain;
    #     end
    #     __casc;
    # end

    def translation_unit
        # TODO Refactor into its own message
        sign = ["+", "-"].include?(table.lookahead(1).value) ? terminal_SIGN : ast.empty;
        
        if [Type::INTEGER, Type::FLOAT].include?(table.lookahead(1).type)
            res = base_ten_literal(sign);
        elsif [Type::BINARY, Type::HEXADECIMAL, Type::OCTAL].include?(table.lookahead(1).type)
            res = alternate_base_literal(sign);
        elsif table.lookahead(1).type == Type::BIGINTEGER
            res = big_integer_literal(sign);
        elsif table.lookahead(1).type == Type::BIGFLOAT
            res = big_float_literal(sign);

        elsif table.lookahead(1).type == Type::STRING
            res = string_literal;
        elsif table.lookahead(1) == ":"
            res = symbol_literal;
        elsif table.lookahead(1) == "@" or table.lookahead(1).type == Type::IDENTIFIER
            res = variable;
        
        elsif table.lookahead(1) == "("
            res = list;
        elsif table.lookahead(1) == "["
            res = tuple_literal;
        elsif table.lookahead(1) == "{"
            res = hash_literal;
        elsif table.lookahead(1) == "`"
            res = quoted_list_literal;
        elsif table.lookahead(1) == "->"
            res = block_literal;
        end

        if res == "+" or res == "-"
            ast.empty;
        else
            ast.translation_unit res;
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
        ast.string_literal terminal_STRING;
    end

    def symbol_literal
        table.ensure_consumption ":", "expected ':' on symbol literal";
        ast.symbol_literal symbol_name;
    end

    def symbol_name
        if table.lookahead(1).type == Type::MESSAGE_SYMBOL
            ast.symbol_name terminal_MESSAGE_SYMBOL;
        elsif table.lookahead(1).type == Type::IDENTIFIER
            ast.symbol_name terminal_IDENTIFIER;
        elsif table.lookahead(1).type == Type::STRING
            ast.symbol_name terminal_UNQUOTED_STRING;
        else
            ast.empty;
        end
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
        
        __units = [];
        loop do
            break if table.lookahead(1) == ")" or table.lookahead(1) == "eof";
            __units << expression;
            table.ensure_consumption ",", "list items should be separated by commas" if table.lookahead(1) != ")" and table.lookahead(1) != "eof";
        end
        
        table.ensure_consumption ")", "missing closing parenthesis on list";
        ast.list __units;
    end

    def tuple_literal
        table.ensure_consumption "[", "missing opening bracket on tuple";
        __items = __list_of_grammar_rule { tuple_item };
        table.ensure_consumption "]", "missing closing bracket on tuple";
        ast.tuple_literal __items;
    end

    def tuple_item
        toggle_comma_as_message_while_in_association;
        value = translation_unit;
        toggle_comma_as_message_while_in_association;
        table.ensure_consumption ",", "tuple items should be separated by commas" if table.lookahead(1) != "]" and table.lookahead(1) != "eof";
        ast.tuple_item value;
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
            value = translation_unit;
            toggle_comma_as_message_while_in_association;
            table.ensure_consumption ",", "keys should be separated by commas" if table.lookahead(1) != "}";
            ast.json_association key, value;
        elsif table.lookahead(1) == ":"
            key = symbol_literal;
            table.ensure_consumption ":", "hash keys should be denoted by colons";
            toggle_comma_as_message_while_in_association;
            value = translation_unit;
            toggle_comma_as_message_while_in_association;
            table.ensure_consumption ",", "keys should be separated by commas" if table.lookahead(1) != "}";
            ast.association key, value;
        elsif table.lookahead(1).type == Type::STRING
            key = string_literal;
            table.ensure_consumption ":", "hash keys should be denoted by colons";
            toggle_comma_as_message_while_in_association;
            value = translation_unit;
            toggle_comma_as_message_while_in_association;
            table.ensure_consumption ",", "keys should be separated by commas" if table.lookahead(1) != "}";
            ast.association key, value;
        else
            ast.empty;
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

        __params = [];
        while table.lookahead(1) == ":"
            __params << symbol_literal;
            table.ensure_consumption ",", "block parameters are separated by commas";
        end

        function = translation_unit;

        table.ensure_consumption ")", "missing closing parenthesis on block literal";
        ast.block_literal __params, function;
    end

    def expression
        optional_assignment_list = __list_of_grammar_rule { assignment_message };

        res = "";
        current_position = table.token_table_pos;
        if current_position == table.token_table_pos
            res = message;
        end
        # if current_position == table.token_table_pos
        #     res = cascaded_message;
        # end

        if res == ""
            ast.empty;
        else
            ast.expression optional_assignment_list, res;
        end
    end

    end

    def message
        optional_assignment_list = __list_of_grammar_rule { assignment_message };
        expr = expression;

        if optional_assignment_list.empty?
            ast.empty;
        else
            ast.message optional_assignment_list, expr;
        end
    end

    def assignment_message
        current_position = table.token_table_pos;
        id = variable;

        if table.lookahead(1) == "="
            ast.assignment_message id, terminal_EQUALS;
        else
            ast.empty;
        end
    end

    def expression
        ast.expression translation_unit;
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

    def terminal_INSTANCE_SYMBOL
        ast.terminal_INSTANCE_SYMBOL table.consume;
    end

    def terminal_SIGN
        ast.terminal_SIGN table.consume;
    end

    def terminal_EQUALS
        ast.terminal_EQUALS table.consume;
    end

    def terminal_IDENTIFIER
        if table.lookahead(1).type == Type::IDENTIFIER
            ast.terminal_IDENTIFIER table.consume;
        else
            ast.empty;
        end
    end

    def terminal_IDENTIFIER_SYMBOL
        if table.lookahead(1).type == Type::ID_SYMBOL
            ast.terminal_IDENTIFIER_SYMBOL table.consume;
        else
            ast.empty;
        end
    end

    def terminal_MESSAGE_SYMBOL
        if table.lookahead(1).type == Type::MESSAGE_SYMBOL
            ast.terminal_MESSAGE_SYMBOL table.consume;
        else
            ast.empty;
        end
    end
end
