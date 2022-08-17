require_relative "../ast/ASTFactory";

AST_TYPE = "s-expressions";

class Parser
    attr_accessor :table, :ast;

    def initialize(table)
        @table = table;
        @ast = ASTFactory.new.generate AST_TYPE;
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

    def analyse_syntax
        first_unit;
    end

    def first_unit
        if table.lookahead(1) == ")";    list;          # Error opening
        elsif table.lookahead(1) == "]"; tuple_literal; # Error opening
        elsif table.lookahead(1) == "}"; hash_literal;  # Error opening
        else
            result = translation_unit;
            table.ensure_value "eof", "reached end of program";
            ast.first_unit result;
        end
    end

    def translation_unit
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
            ast.translation_unit optional_assignment_list, res;
        end
    end

    def assignment_message
        # TODO possible error in logic
        if table.lookahead(2) == "=" #or (table.lookahead(1) == "@" and table.lookahead(3) == "=")
            ast.assignment_message variable, table.ensure_value("=", "expected `=` on assignment message");
        else
            ast.empty;
        end
    end

    def message
        res = keyword_message;

        if res == ""
            ast.empty;
        else
            ast.message res;
        end
    end

    def unary_message
        obj = unary_object;
        sel = unary_selector;

        if sel == []
            ast.literal obj;
        else
            ast.unary_message(obj, sel)[1...-1];
        end
    end

    def unary_object
        literal;
    end

    def unary_selector
        def unary_selector_pattern
            if table.lookahead(2) == ":" or ((table.lookahead(2) == "!" or table.lookahead(2) == "?") and table.lookahead(3) == ":")
                "";
            elsif table.lookahead(1).type == Type::IDENTIFIER
                id = table.ensure_type(Type::IDENTIFIER, "expected identifier on unary selector");
                optional = "";
                if table.lookahead(1).type == Type::ID_SYMBOL
                    optional = table.ensure_type(Type::ID_SYMBOL, "expected id symbol on unary identifier");
                end
                "#{id}#{optional}";
            end
        end

        __list_of_grammar_rule { unary_selector_pattern };
    end

    def binary_message
        obj = binary_object;
        sel = binary_selector;

        if sel == []
            ast.literal obj;
        else
            ast.binary_message(obj, sel)[1...-1];
        end
    end

    def binary_object
        unary_message;
    end

    def binary_selector
        def binary_selector_pattern
            sel = __list_of_grammar_rule {
                if table.lookahead(1).type == Type::MESSAGE_SYMBOL
                    table.ensure_type(Type::MESSAGE_SYMBOL, "expected message symbol on binary selector");
                else
                    # TODO Simplify by returning [] on first empty
                    ast.empty;
                end
            }.join;

            if sel == ""
                [];
            else
                [sel, unary_message];
            end
        end

        __list_of_grammar_rule { binary_selector_pattern }.filter { |item| !item.empty? };
    end

    def keyword_message
        obj = keyword_object;
        sel = keyword_selector;

        if sel == []
            ast.literal obj;
        else
            ast.keyword_message(obj, sel);
        end
    end

    def keyword_object
        binary_message;
    end

    def keyword_selector
        # TODO Simplify keyword selector
        def keyword_selector_pattern
            if table.lookahead(1).type == Type::IDENTIFIER
                id = table.ensure_type(Type::IDENTIFIER, "expected identifier on keyword selector");
            else
                return [];
            end

            optional_symbol = "";
            if table.lookahead(1).type == Type::ID_SYMBOL
                optional_symbol = table.ensure_type(Type::ID_SYMBOL, "expected id symbol on keyword identifier");
            end

            if table.lookahead(1) == ":"
                delim = table.ensure_value(":", "expected `:` on keyword selector.");
            else
                return [];
            end

            obj = binary_object;

            if id == "" or delim == ""
                [];
            else
                ["#{id}#{optional_symbol}#{delim}", obj];
            end
        end

        __list_of_grammar_rule { keyword_selector_pattern }.filter { |item| !item.empty? };
    end

    def cascaded_message
        ast.empty; # TODO
    end

    def literal
        # TODO Refactor into its own message
        sign = ["+", "-"].include?(table.lookahead(1).value) ? table.consume.value : ast.empty;
        
        if table.lookahead(1).type == Type::INTEGER
            ast.literal integer_literal(sign);
        elsif table.lookahead(1).type == Type::FLOAT
            ast.literal float_literal(sign);
        elsif table.lookahead(1).type == Type::BINARY
            ast.literal binary_literal(sign);
        elsif table.lookahead(1).type == Type::HEXADECIMAL
            ast.literal hexadecimal_literal(sign);
        elsif table.lookahead(1).type == Type::OCTAL
            ast.literal octal_literal(sign);
        elsif table.lookahead(1).type == Type::BIGINTEGER
            ast.literal big_integer_literal(sign);
        elsif table.lookahead(1).type == Type::BIGFLOAT
            ast.literal big_float_literal(sign);
        elsif (table.lookahead(1).type == Type::IDENTIFIER and table.lookahead(2) == ":") or (table.lookahead(1).type == Type::STRING and table.lookahead(2) == ":") or (table.lookahead(1) == ":" and table.lookahead(2).type == Type::IDENTIFIER and table.lookahead(3) == ":")
            ast.literal association_literal;
        elsif table.lookahead(1).type == Type::STRING
            ast.literal string_literal;
        elsif table.lookahead(1) == ":"
            ast.literal symbol_literal;
        elsif table.lookahead(1).type == Type::IDENTIFIER or (table.lookahead(1) == "@" and table.lookahead(2).type == Type::IDENTIFIER)
            ast.literal variable;        
        elsif table.lookahead(1) == "("
            ast.literal list;
        elsif table.lookahead(1) == "["
            ast.literal tuple_literal;
        elsif table.lookahead(1) == "{"
            ast.literal hash_literal;
        elsif table.lookahead(1) == "`"
            ast.literal quoted_list_literal;
        elsif table.lookahead(1) == "->"
            ast.literal block_literal;
        end
    end

    def integer_literal(sign)
        ast.integer_literal sign, table.ensure_type(Type::INTEGER, "expected integer literal");
    end

    def float_literal(sign)
        ast.float_literal sign, table.ensure_type(Type::FLOAT, "expected float literal");
    end

    def binary_literal(sign)
        ast.binary_literal sign, table.ensure_type(Type::BINARY, "expected binary literal");
    end

    def hexadecimal_literal(sign)
        ast.hexadecimal_literal sign, table.ensure_type(Type::HEXADECIMAL, "expected hexadecimal literal");
    end

    def octal_literal(sign)
        ast.octal_literal sign, table.ensure_type(Type::OCTAL, "expected octal literal");
    end

    def big_integer_literal(sign)
        ast.big_integer_literal sign, table.ensure_type(Type::BIGINTEGER, "expected big integer literal");
    end

    def big_float_literal(sign)
        ast.big_float_literal sign, table.ensure_type(Type::BIGFLOAT, "expected big float literal");
    end

    def association_literal
        if table.lookahead(1).type == Type::IDENTIFIER
            key = table.ensure_type(Type::IDENTIFIER, "expected identifier on association literal");
            table.ensure_value ":", "hash keys should be denoted by colons";
            value = translation_unit;
            ast.json_association key, value;
        elsif table.lookahead(1) == ":"
            key = symbol_literal;
            table.ensure_value ":", "hash keys should be denoted by colons";
            value = translation_unit;
            ast.association key, value;
        elsif table.lookahead(1).type == Type::STRING
            key = string_literal;
            table.ensure_value ":", "hash keys should be denoted by colons";
            value = translation_unit;
            ast.association key, value;
        else
            ast.empty;
        end
    end
    
    def string_literal
        ast.string_literal table.ensure_type(Type::STRING, "expected string literal");
    end

    def symbol_literal
        table.ensure_value ":", "expected ':' on symbol literal";
        ast.symbol_literal symbol_name;
    end

    def symbol_name
        if table.lookahead(1).type == Type::MESSAGE_SYMBOL
            ast.symbol_name table.ensure_type(Type::MESSAGE_SYMBOL, "expected message symbol as a symbol name");
        elsif table.lookahead(1).type == Type::IDENTIFIER
            ast.symbol_name table.ensure_type(Type::IDENTIFIER, "expected identifier as a symbol name");
        elsif table.lookahead(1).type == Type::STRING
            ast.symbol_name table.ensure_type(Type::STRING, "expected string as a symbol name")[1...-1];
        else
            ast.empty;
        end
    end

    def variable
        if table.lookahead(1) == "@"
            ast.variable table.ensure_value("@", "expected `@` on instance variable declaration"), table.ensure_type(Type::IDENTIFIER, "expected identifier on variable declaration");
        else
            ast.variable "", table.ensure_type(Type::IDENTIFIER, "expected identifier on variable declaration");
        end
    end

    def list
        table.ensure_value "(", "missing opening parenthesis on list";
        
        __items = [];
        while table.lookahead(1) != ")" and table.lookahead(1) != "eof"
            __items << translation_unit;
            table.ensure_value ",", "list items should be separated by commas" if table.lookahead(1) != ")" and table.lookahead(1) != "eof";
        end
        
        table.ensure_value ")", "missing closing parenthesis on list";
        ast.list __items;
    end

    def tuple_literal
        table.ensure_value "[", "missing opening bracket on tuple";
        
        __items = [];
        while table.lookahead(1) != "]" and table.lookahead(1) != "eof"
            __items << translation_unit;
            table.ensure_value ",", "tuple items should be separated by commas" if table.lookahead(1) != "]" and table.lookahead(1) != "eof";
        end

        table.ensure_value "]", "missing closing bracket on tuple";
        ast.tuple_literal __items;
    end

    def hash_literal
        table.ensure_value "{", "missing opening curly brace on hash";
        
        __items = [];
        while table.lookahead(1) != "}" and table.lookahead(1) != "eof"
            __items << association_literal;
            table.ensure_value ",", "keys should be separated by commas" if table.lookahead(1) != "}" and table.lookahead(1) != "eof";
        end
        
        table.ensure_value "}", "missing closing curly brace on hash";
        ast.hash_literal __items;
    end

    def quoted_list_literal
        table.ensure_value "`", "missing '`' symbol on quoted list literal";
        table.ensure_value "(", "missing opening parenthesis on quoted list literal";

        paren_count = 0;
        __items = [];
        while table.lookahead(1) != ")" or paren_count != 0
            tok = table.consume.value;
            paren_count += 1 if tok == "(";
            paren_count -= 1 if tok == ")";
            __items << ast.symbol_literal(tok);
        end
        __items.unshift ast.symbol_literal("(");
        __items.push ast.symbol_literal(")");

        table.ensure_value ")", "missing closing parenthesis on quoted list literal";
        ast.quoted_list_literal __items;
    end

    def block_literal
        table.ensure_value "->", "missing '->' symbol on block literal";
        table.ensure_value "(", "missing opening parenthesis on block literal";

        __params = [];
        while table.lookahead(1) == ":"
            __params << symbol_literal;
            table.ensure_value ",", "block parameters are separated by commas" if table.lookahead(1) != ")" and table.lookahead(1) != "eof";
        end

        function = translation_unit;

        table.ensure_value ")", "missing closing parenthesis on block literal";
        ast.block_literal __params, function;
    end
end
