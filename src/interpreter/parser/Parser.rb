require_relative "../ast/ASTFactory";

class Parser
    attr_accessor :table, :ast;

    def initialize(table, type="default")
        @table = table;
        @ast = ASTFactory.new.generate type;
    end

    def __chain_of(&selector)
        selectors = [];
        loop do
            sel = selector.call;
            break if sel == ast.empty
            selectors << sel;
        end
        selectors;
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
            table.ensure_value "eof", "reached end of program.";
            ast.first_unit result;
        end
    end

    def translation_unit
        optional_assignment_list = [];
        while table.lookahead(2) == "=" or (table.lookahead(1) == "@" and table.lookahead(3) == "=")
            optional_assignment_list << assignment;
        end

        res = message;

        if res == ""
            ast.empty;
        else
            ast.translation_unit optional_assignment_list, res;
        end
    end

    def assignment
        if table.lookahead(2) == "=" or (table.lookahead(1) == "@" and table.lookahead(3) == "=")
            ast.assignment variable(""), table.ensure_value("=", "expected `=` on assignment message.");
        else
            ast.empty;
        end
    end

    def message
        ast.message keyword_message;
    end

    def unary_message
        obj = unary_object;
        sel = __chain_of { unary_selector };

        if sel == []
            ast.literal obj;
        else
            ast.unary_message(obj, sel);
        end
    end

    def unary_object
        ast.unary_object literal;
    end

    def unary_selector
        if table.lookahead(2) == ":" or ((table.lookahead(2) == "!" or table.lookahead(2) == "?") and table.lookahead(3) == ":")
            ast.empty;
        elsif table.lookahead(1).type == Type::IDENTIFIER
            id = table.ensure_type(Type::IDENTIFIER, "expected identifier on unary selector.");
            if table.lookahead(1).type == Type::ID_SYMBOL
                optional_symbol = table.ensure_type(Type::ID_SYMBOL, "expected id symbol on unary identifier.");
            else
                optional_symbol = "";
            end
            ast.unary_selector id, optional_symbol;
        else
            ast.empty;
        end
    end

    def binary_message
        obj = binary_object;
        sel = __chain_of { binary_selector };

        if sel == []
            ast.literal obj;
        else
            ast.binary_message(obj, sel);
        end
    end

    def binary_object
        ast.binary_object unary_message;
    end

    def binary_selector
        sel = "";
        if table.lookahead(1).type == Type::MESSAGE_SYMBOL
            sel = table.ensure_type(Type::MESSAGE_SYMBOL, "expected message symbol on binary selector.");
        end

        if sel == ""
            ast.empty;
        else
            ast.binary_selector sel, unary_message;
        end
    end

    def keyword_message
        obj = keyword_object;
        sel = __chain_of { keyword_selector };

        if sel == []
            ast.literal obj;
        else
            ast.keyword_message(obj, sel);
        end
    end

    def keyword_object
        ast.keyword_object binary_message;
    end

    def keyword_selector
        if table.lookahead(1).type == Type::IDENTIFIER and (table.lookahead(2) == ":" or ((table.lookahead(2) == "!" or table.lookahead(2) == "?") and table.lookahead(3) == ":"))
            id = table.ensure_type(Type::IDENTIFIER, "expected identifier on keyword selector.");
            if table.lookahead(1).type == Type::ID_SYMBOL
                optional_symbol = table.ensure_type(Type::ID_SYMBOL, "expected id symbol on keyword identifier.");
            else
                optional_symbol = "";
            end
            delim = table.ensure_value(":", "expected `:` on keyword selector.");
            obj = binary_message;

            ast.keyword_selector id, optional_symbol, delim, obj;
        else
            ast.empty;
        end
    end

    def literal
        # TODO Convert sign into a unary `negate` message
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
        elsif table.lookahead(1).type == Type::CHAR
            ast.literal char_literal(sign);
        elsif table.lookahead(1).type == Type::STRING
            ast.literal string_literal;
        elsif table.lookahead(1).type == Type::IDENTIFIER or (table.lookahead(1) == "@" and table.lookahead(2).type == Type::IDENTIFIER)
            ast.literal variable(sign);
        elsif table.lookahead(1) == "("
            ast.literal list;
        elsif table.lookahead(1) == "["
            ast.literal tuple_literal;
        elsif table.lookahead(1) == "{"
            ast.literal hash_literal;
        elsif table.lookahead(1) == "->"
            ast.literal proc_literal;
        elsif table.lookahead(1) == "#"
            ast.literal method_definition_literal;
        end
    end

    def integer_literal(sign)
        ast.integer_literal sign, table.ensure_type(Type::INTEGER, "expected integer literal.");
    end

    def float_literal(sign)
        ast.float_literal sign, table.ensure_type(Type::FLOAT, "expected float literal.");
    end

    def binary_literal(sign)
        ast.binary_literal sign, table.ensure_type(Type::BINARY, "expected binary literal.");
    end

    def hexadecimal_literal(sign)
        ast.hexadecimal_literal sign, table.ensure_type(Type::HEXADECIMAL, "expected hexadecimal literal.");
    end

    def octal_literal(sign)
        ast.octal_literal sign, table.ensure_type(Type::OCTAL, "expected octal literal.");
    end

    def big_integer_literal(sign)
        ast.big_integer_literal sign, table.ensure_type(Type::BIGINTEGER, "expected big integer literal.");
    end

    def big_float_literal(sign)
        ast.big_float_literal sign, table.ensure_type(Type::BIGFLOAT, "expected big float literal.");
    end

    def char_literal(sign)
        ast.char_literal sign, table.ensure_type(Type::CHAR, "expected character literal.");
    end
    
    def string_literal
        ast.string_literal table.ensure_type(Type::STRING, "expected string literal.");
    end

    def variable(sign)
        if table.lookahead(1) == "@"
            ast.variable sign, table.ensure_value("@", "expected `@` on instance variable declaration."), table.ensure_type(Type::IDENTIFIER, "expected identifier on variable declaration.");
        else
            ast.variable sign, "", table.ensure_type(Type::IDENTIFIER, "expected identifier on variable declaration.");
        end
    end

    def list
        table.ensure_value "(", "missing opening parenthesis on list.";
        
        __items = [];
        while table.lookahead(1) != ")" and table.lookahead(1) != "eof"
            __items << translation_unit;
            table.ensure_value ",", "list items should be separated by commas." if table.lookahead(1) != ")" and table.lookahead(1) != "eof";
        end
        
        table.ensure_value ")", "missing closing parenthesis on list.";
        ast.list __items;
    end

    def tuple_literal
        table.ensure_value "[", "missing opening bracket on tuple.";
        
        __items = [];
        while table.lookahead(1) != "]" and table.lookahead(1) != "eof"
            __items << translation_unit;
            table.ensure_value ",", "tuple items should be separated by commas." if table.lookahead(1) != "]" and table.lookahead(1) != "eof";
        end

        table.ensure_value "]", "missing closing bracket on tuple.";
        ast.tuple_literal __items;
    end

    def hash_literal
        table.ensure_value "{", "missing opening curly brace on hash.";
        
        __items = [];
        while table.lookahead(1) != "}" and table.lookahead(1) != "eof"
            __items << association_literal;
            table.ensure_value ",", "keys should be separated by commas." if table.lookahead(1) != "}" and table.lookahead(1) != "eof";
        end
        
        table.ensure_value "}", "missing closing curly brace on hash.";
        ast.hash_literal __items;
    end

    def association_literal
        if table.lookahead(1).type == Type::IDENTIFIER
            key = table.ensure_type(Type::IDENTIFIER, "expected identifier on association literal.");
            table.ensure_value ":", "hash keys should be denoted by colons.";
            value = translation_unit;
            ast.json_association key, value;
        elsif table.lookahead(1).type == Type::STRING
            key = string_literal;
            table.ensure_value ":", "hash keys should be denoted by colons.";
            value = translation_unit;
            ast.association key, value;
        else
            ast.empty;
        end
    end

    def proc_literal
        table.ensure_value "->", "missing '->' symbol on proc literal.";
        table.ensure_value "{", "missing opening curly on proc literal.";

        __params = [];
        while table.lookahead(1).type == Type::IDENTIFIER and (table.lookahead(2) == "," or table.lookahead(2) == "|")
            __params << table.ensure_type(Type::IDENTIFIER, "expected identifier parameter on proc.");
            if table.lookahead(1) != "}" and table.lookahead(1) != "|" and table.lookahead(1) != "eof"
                table.ensure_value ",", "proc parameters are separated by commas.";
            end
        end

        if table.lookahead(1) == "|"
            table.ensure_value "|", "missing '|' symbol on proc literal.";
        end
        function = translation_unit;

        table.ensure_value "}", "missing closing curly on proc literal.";
        ast.proc_literal __params, function;
    end

    def method_definition_literal
        table.ensure_value "#", "missing '#' on method definition.";

        if table.lookahead(1).type == Type::IDENTIFIER and (table.lookahead(2) == ":" or ((table.lookahead(2) == "!" or table.lookahead(2) == "?") and table.lookahead(3) == ":"))
            keyword_method_definition;
        elsif table.lookahead(1).type == Type::IDENTIFIER
            unary_method_definition;
        elsif table.lookahead(1).type == Type::MESSAGE_SYMBOL
            binary_method_definition;
        end
    end

    def unary_method_definition
        selector = table.ensure_type(Type::IDENTIFIER, "expected identifier on unary method definition.");
        if table.lookahead(1).type == Type::ID_SYMBOL
            selector << table.ensure_type(Type::ID_SYMBOL, "expected id symbol on unary identifier.");
        end
        table.ensure_value "=>", "missing '=>' on unary method definition.";
        function = translation_unit;
        ast.unary_method_definition selector, function;
    end

    def binary_method_definition
        selector = table.ensure_type(Type::MESSAGE_SYMBOL, "expected message symbol on binary method definition.");
        param = table.ensure_type(Type::IDENTIFIER, "expected one parameter on binary method definition.");
        table.ensure_value "=>", "missing '=>' on binary method definition.";
        function = translation_unit;
        ast.binary_method_definition selector, param, function;
    end

    def keyword_method_definition
        selector = [];
        while table.lookahead(1).type == Type::IDENTIFIER
            key = table.ensure_type(Type::IDENTIFIER, "expected identifier on keyword method selector.");
            if table.lookahead(1).type == Type::ID_SYMBOL
                key << table.ensure_type(Type::ID_SYMBOL, "expected id symbol on keyword method identifier.");
            end
            key << table.ensure_value(":", "expected `:` on keyword method definition.");
            param = table.ensure_type(Type::IDENTIFIER, "keyword parameter");
            selector << [key, param];
        end
        table.ensure_value "=>", "missing '=>' on keyword method definition.";
        function = translation_unit;
        ast.keyword_method_definition selector, function;
    end
end
