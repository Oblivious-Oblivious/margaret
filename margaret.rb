Dir[Dir.pwd + "/src/**/*.rb"].each { |f| require f };

require "readline";

class Margaret
    def self.SCAN(prompt)
        line = Readline.readline(prompt, true)
        if line == ""
            Readline::HISTORY.pop;
            ['(', ')'];
        elsif line == "<<exit>>" or line == "<<quit>>"
            exit;
        else
            line.chars;
        end
    end

    def self.READ(chars)
        Lexer.new("repl", chars).make_tokens;
    end

    def self.EVAL(tokens)
        Parser.new(tokens).analyse_syntax;
    end

    def self.PRINT(evaluated)
        puts "=> #{evaluated}";
    end

    def self.repl
        loop { PRINT(EVAL(READ(SCAN("$> ")))); };
    end

    def self.run_file(filename)
        chars = FileLoader.new.load(filename);
        tokens = Lexer.new(filename, chars).make_tokens;
        bytecode = Parser.new(tokens).analyse_syntax;
        evaluated = Evaluator.new(bytecode).run;

        puts bytecode;
        evaluated;
    end
end

Margaret.repl;
# Margaret.run_file ARGV[0];
