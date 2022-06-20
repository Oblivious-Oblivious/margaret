class Parser
    attr_accessor :lexer, :token;

    def initialize(lexer)
        @lexer = lexer;
        @token = nil;
    end

    def next_token
        @token = lexer.next_token;
        # print "consumed #{@token} at ";
        # p caller[0].scan(/\d+/).first;
        # @token;
    end

    def prev_token
        # print "undid #{@token} at ";
        @token = lexer.prev_token;
        # p caller[0].scan(/\d+/).first;
        # @token;
    end

    def peek_token
        peek = lexer.next_token;
        lexer.prev_token;
        # print "peeked #{peek} at ";
        # p caller[0].scan(/\d+/).first;
        peek;
    end

    def error(message)
        raise StandardError.new message;
        # TODO Gather a list of errors and output after parsing all code
        # puts "#{lexer.filename}:#{token.line_number}: #{'error'.red} #{message}";
        # puts "Compilation #{'failed'.red}";
    end

    def analyse_syntax
        first_unit;
        "Compilation #{'successful'.green()}";
    end

    def first_unit
    end
end
