require_relative "_parser_helpers";

describe Parser do
    context "on tuples" do
        it "parses tuple literals" do
            parse("([])");
            parse("([[], []])");
            parse("([41 42])");
            parse(%Q{([42 "str" var])});
            error("([)", "missing closing bracket on tuple");
            error("(])", "missing closing parenthesis on list");
        end
    end
end
