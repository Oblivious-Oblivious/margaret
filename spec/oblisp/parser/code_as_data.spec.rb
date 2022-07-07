require_relative "_parser_helpers";

describe Parser do
    context "on code as data" do
        it "parses quoted lists" do
            parse("(x = `(1 + 2))");
        end
    end
end
