Dir[Dir.pwd + "/src/interpreter/**/*.rb"].each { |f| require f };

require "readline";

module TRANSLATE_TO
    INTERPRETER = 1;
    STACK_VM = 2;
    REGISTER_VM = 3;
    MACHINE_CODE = 4;
end

class Oblisp
    def self.SCAN(prompt)
        if line = Readline.readline(prompt, true)
            line;
        else
            nil;
        end
    end

    def self.READ(str)
        str;
    end

    def self.EVAL(ast)
        ast;
    end

    def self.PRINT(result)
        puts result;
    end

    def self.LOOP(&list)
        loop { list.call; };
    end

    def self.main(type)
        case type
        when TRANSLATE_TO::INTERPRETER
            LOOP { PRINT(EVAL(READ(SCAN("$> ")))); };
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
end

Oblisp.main TRANSLATE_TO::INTERPRETER;
