class Token
    attr_reader :value, :type, :line_number;

    def initialize(value, type, line_number)
        @value = value;
        @type = type;
        @line_number = line_number;
    end

    def to_s
        "(\"#{value}\" #{type} #{line_number})";
    end

    def ==(other_value)
        value == other_value;
    end
end
