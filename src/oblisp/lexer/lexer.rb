require_relative "./type"

module RegexMatchers
    WHITESPACE = [" ","\t","\f"];
    NEWLINE = ["\r", "\n"];

    NUMBER = ["0","1","2","3","4","5","6","7","8","9"];
    LETTER = [
        "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z",
        "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
    ];
    BINARY = ["0","1"];
    HEXADECIMAL = NUMBER + ["A","a","B","b","C","c","D","d","E","e","F","f"];
    OCTAL = ["0","1","2","3","4","5","6","7"];

    MESSAGE_SYMBOL = ["+","-","*","/","\\","~","<",">","=","@","%","|","&","?","!","^",",","`",";","$","`"];
    SYNTAX_SYMBOL = ["(",")","[","]","{","}",":",".", "_"];
    QUOTE = ["\"","'"];

    KEYWORDS = ["self","super"];
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

    def make_tokens
        token_table = [];

        loop do
            c = next_character;
            if c == nil
                break;
            elsif c.matches(RegexMatchers::NEWLINE)
                self.lineno += 1;
            elsif c.matches(RegexMatchers::WHITESPACE)
            elsif c.matches(RegexMatchers::NUMBER)
                final_number = c;
                if c == '0'
                    c = next_character;
                    if c == '.'
                        final_number << c;
                        c = next_character;
                        while c != nil and c.matches(RegexMatchers::NUMBER)
                            final_number << c;
                            c = next_character;
                        end
                        token_table << (Token.new final_number, Type::FLOAT, lineno);
                    elsif c == 'b' or c == 'B'
                        final_number << c.downcase;
                        c = next_character;
                        while c != nil and c.matches(RegexMatchers::BINARY)
                            final_number << c;
                            c = next_character;
                        end
                        c = prev_character;
                        token_table << (Token.new final_number, Type::BINARY, lineno);
                    elsif c == 'x' or c == 'X'
                        final_number << c.downcase;
                        c = next_character;
                        while c != nil and c.matches(RegexMatchers::HEXADECIMAL)
                            final_number << c;
                            c = next_character;
                        end
                        c = prev_character;
                        token_table << (Token.new final_number, Type::HEXADECIMAL, lineno);
                    elsif c == 'o' or c == 'O'
                        final_number << c.downcase;
                        c = next_character;
                        while c != nil and c.matches(RegexMatchers::OCTAL)
                            final_number << c;
                            c = next_character;
                        end
                        c = prev_character;
                        token_table << (Token.new final_number, Type::OCTAL, lineno);
                    else
                        return self.error "expected fraction part after numeric literal";
                    end
                else
                    actual_type = Type::INTEGER;
                    final_number = c;
                    c = next_character;
                    while c != nil and c.matches(RegexMatchers::NUMBER)
                        final_number << c;
                        c = next_character;
                    end

                    if c == '.'
                        final_number << c;
                        c = next_character;
                        while c != nil and c.matches(RegexMatchers::NUMBER)
                            final_number << c;
                            c = next_character;
                        end
                        actual_type = Type::FLOAT;
                    end
                    c = prev_character;
                    token_table << (Token.new final_number, actual_type, lineno);
                end
            elsif c.matches(RegexMatchers::LETTER) or c == '_'
                final_identifier = c;
                c = next_character;
                while c != nil and (c.matches(RegexMatchers::NUMBER) or c == '_' or c.matches(RegexMatchers::LETTER))
                    final_identifier << c;
                    c = next_character;
                end
                c = prev_character;

                if final_identifier.matches(RegexMatchers::KEYWORDS)
                    if final_identifier == "self"
                        token_table << (Token.new final_identifier, Type::SELF, lineno);
                    else
                        token_table << (Token.new final_identifier, Type::SUPER, lineno);
                    end
                else
                    token_table << (Token.new final_identifier, Type::IDENTIFIER, lineno);
                end
            elsif c.matches(RegexMatchers::MESSAGE_SYMBOL)
                token_table << (Token.new c, Type::MESSAGE_SYMBOL, lineno);
            elsif c.matches(RegexMatchers::SYNTAX_SYMBOL)
                token_table << (Token.new c, Type::SYNTAX_SYMBOL, lineno);
            elsif c.matches(RegexMatchers::QUOTE)
                final_string = c;
                c = next_character;
                while not c.matches(RegexMatchers::QUOTE)
                    final_string << c;
                    c = next_character;
                    if c.matches(RegexMatchers::NEWLINE)
                        self.lineno += 1;
                    elsif c == nil
                        return self.error "unterminated string literal";
                    end
                end
                final_string << c;
                token_table << (Token.new final_string, Type::STRING, lineno);
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

    def peek_token
        if token_pos+1 >= token_table.size
            Token.new "eof", Type::EOF, lineno;
        else
            token_table[token_pos+1];
        end
    end
end
