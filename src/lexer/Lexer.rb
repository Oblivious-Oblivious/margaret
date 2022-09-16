require_relative "../tokens/Type";

module RegexMatchers
    WHITESPACE = [" ","\t","\f","\r"];
    NEWLINE = ["\n"];

    NUMBER = ["0","1","2","3","4","5","6","7","8","9"];
    LETTER = [
        "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z",
        "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
    ];
    BINARY = ["0","1"];
    HEXADECIMAL = NUMBER + ["A","a","B","b","C","c","D","d","E","e","F","f"];
    OCTAL = ["0","1","2","3","4","5","6","7"];

    ID_SYMBOL = ["!","?"];
    MESSAGE_SYMBOL = ID_SYMBOL + ["+","-","*","/","\\","~","<",">","=","%","|","&","^",";",".","`","$"];
    SYNTAX_SYMBOL = ["_", "(",")","[","]","{","}",",",":","@","#"];
    SINGLE_QUOTE = ["'"];
    DOUBLE_QUOTE = ["\""];
end

class String
    def matches(regex)
        regex.include? self;
    end

    def red
        "\033[1;31m#{self}\033[0m";
    end

    def green
        "\033[1;32m#{self}\033[0m";
    end
end

class Lexer
    attr_accessor :filename, :text, :pos, :lineno;

    def initialize(filename, text)
        @filename = filename;
        @text = text;
        @pos = -1;
        @lineno = 1;
    end

    def error(message)
        # TODO Extract closer to boundary
        puts "#{filename}:#{lineno}: #{'error:'.red} #{message}";
        nil;
    end

    def next_character
        @pos += 1;
        text[pos];
    end

    def peek_character(i)
        text[pos + i];
    end

    def tokenize_integer(c)
        final_number = "";
        loop do
            final_number << c;
            c = peek_character(1);
            if c == "_"
                c = next_character;
                next;
            end

            break if c == nil or not c.matches(RegexMatchers::NUMBER);
            c = next_character;
        end
        Token.new final_number, Type::INTEGER, lineno;
    end

    def tokenize_integer_or_float(c)
        int_token = tokenize_integer(c);

        c = peek_character(1);
        if c == '.'
            tokenize_number_special(int_token.value, RegexMatchers::NUMBER, Type::FLOAT);
        else
            int_token;
        end
    end

    def tokenize_number_special(final_number, matcher, type)
        # Fraction part
        c = next_character;
        final_number << c.downcase;

        # Rest of number
        c = next_character;
        loop do
            final_number << c.downcase;
            c = peek_character(1);
            if c == "_"
                c = next_character;
                next;
            end

            break if c == nil or not c.matches(matcher)
            c = next_character;
        end
        Token.new final_number, type, lineno;
    end

    def tokenize_number(c)
        final_number = c;
        if c == '0'
            c = peek_character(1);
            if c == '.'
                tokenize_number_special(final_number, RegexMatchers::NUMBER, Type::FLOAT);
            elsif c == 'b' or c == 'B'
                tokenize_number_special(final_number, RegexMatchers::BINARY, Type::INTEGER);
            elsif c == 'x' or c == 'X'
                tokenize_number_special(final_number, RegexMatchers::HEXADECIMAL, Type::INTEGER);
            elsif c == 'o' or c == 'O'
                tokenize_number_special(final_number, RegexMatchers::OCTAL, Type::INTEGER);
            else
                Token.new "0", Type::INTEGER, lineno;
            end
        else
            tokenize_integer_or_float(c);
        end
    end

    def tokenize_identifier(c)
        final_identifier = "";

        # TODO Add unicode support for identifier names (APL or Julia style)
        loop do
            final_identifier << c;
            c = peek_character(1);
            break if c == nil or not (c.matches(RegexMatchers::NUMBER) or c == '_' or c.matches(RegexMatchers::LETTER))
            c = next_character;
        end

        Token.new final_identifier, Type::IDENTIFIER, lineno;
    end

    def tokenize_message_symbol(c)
        final_symbol = "";

        loop do
            final_symbol << c;
            c = peek_character(1);
            break if c == nil or not (c.matches(RegexMatchers::MESSAGE_SYMBOL))
            c = next_character;
        end

        if final_symbol.matches(RegexMatchers::ID_SYMBOL)
            Token.new final_symbol, Type::ID_SYMBOL, lineno;
        else
            Token.new final_symbol, Type::MESSAGE_SYMBOL, lineno;
        end
    end

    def tokenize_character(c)
        final_char = c;
        char = next_character;
        if not char.matches(RegexMatchers::SINGLE_QUOTE)
            final_char << char;
            quote = next_character;
            if quote == nil
                return error "unterminated character literal: `#{final_char}`";
            end
        end
        final_char << quote;
        Token.new final_char, Type::CHAR, lineno;
    end

    def tokenize_string(c)
        final_string = c;
        c = next_character;
        while not c.matches(RegexMatchers::DOUBLE_QUOTE)
            final_string << c;
            c = next_character;
            if c == nil
                return error "unterminated string literal: `#{final_string}`";
            elsif c.matches(RegexMatchers::NEWLINE)
                @lineno += 1;
            end
        end
        final_string << c;
        Token.new final_string, Type::STRING, lineno;
    end

    def make_tokens
        token_table = [];

        loop do
            c = next_character;
            if c == nil
                break;
            elsif c.matches(RegexMatchers::NEWLINE)
                @lineno += 1;
            elsif c.matches(RegexMatchers::WHITESPACE)
                # Skip
            elsif c.matches(RegexMatchers::NUMBER)
                token_table << tokenize_number(c);
            elsif c.matches(RegexMatchers::LETTER) or c == '_'
                token_table << tokenize_identifier(c);
            elsif c.matches(RegexMatchers::MESSAGE_SYMBOL)
                token_table << tokenize_message_symbol(c);
            elsif c.matches(RegexMatchers::SYNTAX_SYMBOL)
                token_table << (Token.new c, Type::SYNTAX_SYMBOL, lineno);
            elsif c.matches(RegexMatchers::SINGLE_QUOTE)
                tok = tokenize_character(c);
                break if tok == nil;
                token_table << tok;
            elsif c.matches(RegexMatchers::DOUBLE_QUOTE)
                tok = tokenize_string(c);
                break if tok == nil;
                token_table << tok;
            else
                error "Unrecognized character: `#{c}`";
                break;
            end
        end

        token_table << (Token.new "eof", Type::EOF, lineno);
        
        TokenTable.new token_table;
    end
end
