require_relative "_parser_helpers";

describe Parser do
    context "on iterations" do
        it "parses iteration statements" do
            parse("((x > 0) while_true: ((x = x - 1) (y = y * 2)))");
            parse("((x >= 0) while_false: ((x = x + 1) (y = y * 2)))");
            parse("(x times: (y = y * 2))");
            parse("(1 to: 5 do: (y = y * 2))");
            parse("(1 to: 5 by: 2 do: (y = y / 2))");
            parse("((1 2 3 4) each: [(item), (x = x + item)])");
        end
    end
end