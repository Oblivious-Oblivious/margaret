class Character
    attr_reader :c;

    def initialize(c)
        @c = c;
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
        !!(self.c =~ /^[_@'#'$a-zA-Z][_@'#'$a-zA-Z0-9]*$/);
    end

    def to_s
        "#{c}";
    end
end
