require_relative "_parser_helpers";

describe Parser do
    context "on syntax errors" do
        it "enumerable literal errors" do
            error("(", "missing closing parenthesis on list.");
            error(")", "missing opening parenthesis on list.");
            error("(()", "missing closing parenthesis on list.");
            error("())", "reached end of program.");
            error("[", "missing closing bracket on tuple.");
            error("]", "missing opening bracket on tuple.");
            error("{", "missing closing curly brace on hash.");
            error("}", "missing opening curly brace on hash.");
            error("->", "missing opening parenthesis on block literal.");
            error("`", "missing opening parenthesis on quoted list literal.");
        end

        it "other syntax errors" do
            # TODO
        end
    end
end
