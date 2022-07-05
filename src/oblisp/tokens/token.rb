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

    def ==(other)
        if other.is_a? String
            value == other;
        elsif other.is_a? Token
            value == other.value && type == other.type && line_number == other.line_number;
        end
    end
end
