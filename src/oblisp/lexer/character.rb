class Character
    attr_reader :c;

    def initialize(c)
        @c = c;
    end

    def <<(other)
        @c = "#{@c}#{other.c}";
    end

    def omit_last
        Character.new "#{@c[0...-1]}";
    end

    def is_integer
        return false if self.c.to_i > 2147483647 or self.c.to_i < -2147483647;
        !!(self.c =~ /^[-]?[1-9][0-9]*$/);
    end

    def is_big_integer
        # TODO Maybe implement big number stuff in optimization step
        return false if !(self.c.to_i > 2147483647 or self.c.to_i < -2147483647);
        !!(self.c =~ /^[-]?[1-9][0-9]*$/); # TODO underscore integers
    end

    def is_float
        !!(self.c =~ /^[0-9]+[.][0-9]+$/);
    end

    def is_big_float
        #TODO big float
    end

    def is_binary
        !!(self.c =~ /^[0][bB][01]+$/);
    end

    def is_hexadecimal
        !!(self.c =~ /^[0][xX][0-9a-fA-F]+$/);
    end

    def is_octal
        !!(self.c =~ /^[0][oO][0-7]+$/);
    end

    def is_string
        # TODO check out C lexer string regex
        !!(self.c =~ /^["'].*["']$/);
    end

    def is_whitespace
        !!(self.c =~ /^[ \n]/);
    end

    def is_identifier
        # TODO extend to use symbols
        !!(self.c =~ /^[_a-zA-Z][_a-zA-Z0-9]*$/);
    end

    def is_comment
        !!(self.c =~ /^\/\/.*$/);
    end

    def is_self_token
        !!(self.c =~ /^self$/);
    end

    def is_super_token
        !!(self.c =~ /^super$/);
    end

    def is_structure_symbol
        # TODO Structure symbols
    end

    def to_s
        "#{c}";
    end
end
