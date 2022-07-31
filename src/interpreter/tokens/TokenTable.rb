class TokenTable
    attr_accessor :token_list, :pos;

    def error(message)
        raise StandardError.new message;
        # TODO Abstract error somewhere closer to boundary
        # TODO Track line numbers to each error
        # TODO Gather a list of errors and output after parsing all code
        # puts "#{lexer.filename}:#{token.line_number}: #{'error'.red} #{message}";
        # puts "Compilation #{'failed'.red}";
    end

    def display
        print "(";

        token_list.each do |token|
            puts token;
        end

        print ")";
    end

    def initialize(token_list)
        @token_list = token_list;
        @pos = -1;
    end

    def size
        token_list.size;
    end

    def get(i)
        if i >= size
            token_list[size-1];
        else
            token_list[i];
        end
    end

    def lookahead(i)
        token_list[pos + i];
    end

    def consume
        @pos += 1;
        token_list[pos];
    end

    def resume
        @pos -= 1;
        token_list[pos];
    end

    def ensure_consumption(token, error_message)
        if consume != token
            error error_message;
        end
    end

    def token_table_pos
        @pos + 1;
    end
end
