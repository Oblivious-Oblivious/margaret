require_relative "../tokens/type";

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
    MESSAGE_SYMBOL = ID_SYMBOL + ["+","-","*","/","\\","~","<",">","=","@","%","|","&","^",",",".","$"];
    SYNTAX_SYMBOL = ["(",")","[","]","{","}",":",";","`","_"];
    QUOTE = ["\"","'"];
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
    attr_accessor :filename, :text, :pos, :token_pos, :lineno, :token_table;

    def initialize(filename, text)
        @filename = filename;
        @text = text;
        @pos = -1;
        @token_pos = -1;
        @lineno = 1;
    end

    def error(message)
        puts "#{filename}:#{lineno}: #{'error:'.red} #{message}";
        [];
    end

    def next_character
        @pos += 1;

        if pos < text.size
            text[pos];
        else
            nil;
        end
    end

    def peek_character
        if pos+1 < text.size
            text[pos+1];
        else
            nil;
        end
    end

    def print_token_table
        print "(";

        token_table.each do |token|
            puts token;
        end

        print ")";
    end

    def tokenize_integer(c)
        final_number = "";
        loop do
            final_number << c;
            c = peek_character;
            break if c == nil or not c.matches(RegexMatchers::NUMBER);
            c = next_character;
        end
        Token.new final_number, Type::INTEGER, lineno;
    end

    def tokenize_integer_or_float(c)
        int_token = tokenize_integer(c);

        c = peek_character;
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
            final_number << c;
            c = peek_character;
            break if c == nil or not c.matches(matcher)
            c = next_character;
        end
        Token.new final_number, type, lineno;
    end

    def tokenize_number(c)
        final_number = c;
        if c == '0'
            c = peek_character;
            if c == '.'
                tokenize_number_special(final_number, RegexMatchers::NUMBER, Type::FLOAT);
            elsif c == 'b' or c == 'B'
                tokenize_number_special(final_number, RegexMatchers::BINARY, Type::BINARY);
            elsif c == 'x' or c == 'X'
                tokenize_number_special(final_number, RegexMatchers::HEXADECIMAL, Type::HEXADECIMAL);
            elsif c == 'o' or c == 'O'
                tokenize_number_special(final_number, RegexMatchers::OCTAL, Type::OCTAL);
            else
                Token.new "0", Type::INTEGER, lineno;
            end
        else
            tokenize_integer_or_float(c);
        end
    end

    def tokenize_identifier(c)
        final_identifier = "";

        loop do
            final_identifier << c;
            c = peek_character;
            break if c == nil or not (c.matches(RegexMatchers::NUMBER) or c == '_' or c.matches(RegexMatchers::LETTER))
            c = next_character;
        end

        Token.new final_identifier, Type::IDENTIFIER, lineno;
    end

    def tokenize_message_symbol(c)
        final_symbol = "";

        loop do
            final_symbol << c;
            c = peek_character;
            break if c == nil or not (c.matches(RegexMatchers::MESSAGE_SYMBOL))
            c = next_character;
        end

        if final_symbol.matches(RegexMatchers::ID_SYMBOL)
            Token.new final_symbol, Type::ID_SYMBOL, lineno;
        else
            Token.new final_symbol, Type::MESSAGE_SYMBOL, lineno;
        end
    end

    def tokenize_string(c)
        final_string = c;
        c = next_character;
        while not c.matches(RegexMatchers::QUOTE)
            final_string << c;
            c = next_character;
            if c.matches(RegexMatchers::NEWLINE)
                @lineno += 1;
            elsif c == nil
                return error "unterminated string literal";
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
            elsif c.matches(RegexMatchers::NUMBER)
                token_table << tokenize_number(c);
            elsif c.matches(RegexMatchers::LETTER) or c == '_'
                token_table << tokenize_identifier(c);
            elsif c.matches(RegexMatchers::MESSAGE_SYMBOL)
                token_table << tokenize_message_symbol(c);
            elsif c.matches(RegexMatchers::SYNTAX_SYMBOL)
                token_table << (Token.new c, Type::SYNTAX_SYMBOL, lineno);
            elsif c.matches(RegexMatchers::QUOTE)
                token_table << tokenize_string(c);
            end
        end

        @token_table = token_table;
        token_table;
    end

    def next_token
        @token_pos += 1;

        if token_pos >= token_table.size
            Token.new "eof", Type::EOF, lineno;
        else
            token_table[token_pos];
        end
    end

    def prev_token
        @token_pos -= 1;

        if token_pos == -1
            Token.new "eof", Type::EOF, lineno;
        else
            token_table[token_pos];
        end
    end

    def peek_token
        if token_pos+1 >= token_table.size
            Token.new "eof", Type::EOF, lineno;
        else
            token_table[token_pos+1];
        end
    end
end
