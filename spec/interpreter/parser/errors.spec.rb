require_relative "_parser_helpers";

describe Parser do
    context "on syntax errors" do
        it "enumerable literal errors" do
            error("(", "missing closing parenthesis on group.");
            error(")", "missing opening parenthesis on group.");
            error("(()", "missing closing parenthesis on group.");
            error("())", "reached end of program.");
            error("[", "missing closing bracket on tensor.");
            error("]", "missing opening bracket on tensor.");
            error("{", "missing closing curly brace on hash.");
            error("}", "missing opening curly brace on hash.");
            error("->", "missing opening curly on proc literal.");
        end

        it "other syntax errors" do
            # TODO
        end
    end
end
