Dir[Dir.pwd + "/src/**/*.rb"].each { |f| require f };

require "readline";

module TRANSLATE_TO
    INTERPRETER = 1;
    STACK_VM = 2;
    REGISTER_VM = 3;
    MACHINE_CODE = 4;
end

class Margaret
    def self.SCAN(prompt)
        if line = Readline.readline(prompt, true)
            if line == ""
                Readline::HISTORY.pop;
                ['(', ')'];
            elsif line == "<<exit>>" or line == "<<quit>>"
                exit;
            else
                line.chars;
            end
        else
            nil;
        end
    end

    def self.READ(chars, filename="repl")
        Lexer.new(filename, chars).make_tokens;
    end

    # TODO def self.EVAL(ast) -> AST traversal
    def self.EVAL(tokens)
        Parser.new(tokens).analyse_syntax;
    end

    def self.PRINT(evaluated)
        puts "=> #{evaluated}";
    end

    def self.repl(type)
        case type
        when TRANSLATE_TO::INTERPRETER
            loop { PRINT(EVAL(READ(SCAN("$> ")))); };
        when TRANSLATE_TO::STACK_VM
            puts "Stack VM";
        when TRANSLATE_TO::REGISTER_VM
            puts "Register VM";
        when TRANSLATE_TO::MACHINE_CODE
            puts "Machine Code";
        else
            puts "error";
        end
    end

    def self.run_file(filename)
        chars = FileLoader.new(filename).load;
        tokens = READ(chars, filename);
        evaluated = EVAL(tokens);

        puts evaluated;
    end
end

Margaret.repl TRANSLATE_TO::INTERPRETER;
# Margaret.run_file ARGV[0];
