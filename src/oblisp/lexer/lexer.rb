require_relative "./type"

module RegexMatchers
    WHITESPACE = [" ","\t","\r","\f"];
    NEWLINE = ["\n"];
    COMMENT = ["#"];

    NUMBER = ["0","1","2","3","4","5","6","7","8","9"];
    LETTER = [
        "a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z",
        "A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
    ];
    SYMBOL = ["+","-","*","/","\\","~","<",">","=","@","%","|","&","?","!","^","_",",","`",";","$","`"];
    SYNTAX_SYMBOL = ["(",")","[","]","{","}",":","."];
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
    attr_accessor :filename, :text, :pos, :lineno, :token_table;

    def initialize(filename, text)
        @filename = filename;
        @text = text;
        @pos = -1;
        @lineno = 1;
    end

    def error(message)
        puts "#{filename}:#{lineno}: #{'error:'.red} #{message}";
        [];
    end

    def next_character
        self.pos += 1;

        if pos < text.size
            text[pos];
        else
            nil;
        end
    end

    def prev_character
        self.pos -= 1;
        text[pos];
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
                next;
            elsif c.matches(RegexMatchers::COMMENT)
                c = next_character;
                while not c.matches(RegexMatchers::COMMENT)
                    c = next_character;
                    if c.matches(RegexMatchers::NEWLINE)
                        self.lineno += 1;
                    elsif c == nil
                        return self.error("unterminated # comment");
                    end
                end
            elsif c.matches(RegexMatchers::NUMBER) and c != '0'
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
            elsif c == '0'
                final_float = c;
                c = next_character;
                if c != '.'
                    return self.error("unexpected fraction part after numeric literal");
                else
                    final_float << c;
                    c = next_character;
                    while c != nil and c.matches(RegexMatchers::NUMBER)
                        final_float << c;
                        c = next_character;
                    end
                end
                c = prev_character;
                token_table << (Token.new final_float, Type::FLOAT, lineno);

            elsif c.matches(RegexMatchers::SYMBOL)
                token_table << (Token.new c, Type::SYMBOL, lineno);
            elsif c.matches(RegexMatchers::SYNTAX_SYMBOL)
                token_table << (Token.new c, Type::SYNTAX_SYMBOL, lineno);
            elsif c.matches(RegexMatchers::LETTER)
                final_identifier = c;
                c = next_character;
                while c != nil and (c.matches(RegexMatchers::NUMBER) or c.matches(RegexMatchers::SYMBOL) or c.matches(RegexMatchers::LETTER))
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
            end
        end

        @token_table = token_table;
        token_table;
    end
end
