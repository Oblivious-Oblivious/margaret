require_relative "_parser_helpers";

describe Parser do
    context "on code as data" do
        it "parses quoted lists" do
            # NOTE Add more
            parse("(x = `(1 + 2))", %Q{(= x ((new Symbol "1") (new Symbol "+") (new Symbol "2")))});
        end
    end
end
