class Lexer
    attr_accessor :text, :pos, :current_char;
    private attr_writer :pos, :current_char;

    def initialize(text)
        @text = text;
        @pos = -1;
    end

    def advance
        self.pos += 1;

        if pos < text.size
            Character.new text[pos];
        else
            Character.new nil;
        end
    end

    def make_tokens
        tokens = [];

        # TODO Try refactor condition
        while ((c = advance) && c.c)
            case c

            when c.is_integer
            when c.is_big_integer
            when c.is_float
            when c.is_big_float

            when c.is_binary
            when c.is_hexadecimal
            when c.is_octal

            when c.is_string
            # when c.is_symbol

            end
        end

        tokens;
    end
end
