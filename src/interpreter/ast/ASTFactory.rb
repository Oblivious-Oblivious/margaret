require_relative "ast_types/Default";
require_relative "ast_types/SExpression";

class ASTFactory
    def generate(ast_type)
        case ast_type
        when "interpreter"
            Interpreter.new;
        when "s-expressions"
            SExpression.new;
        else
            Default.new;
        end
    end
end
