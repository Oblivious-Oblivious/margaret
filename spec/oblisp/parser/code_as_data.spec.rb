require_relative "_parser_helpers";

describe Parser do
    context "on code as data" do
        it "parses quoted lists" do
            parse("(x = `(1 + 2))", %Q{(= x ((new Symbol "1") (new Symbol "+") (new Symbol "2")))});
            parse("(`(@ FWQ %^&G*))", %Q{(((new Symbol "@") (new Symbol "FWQ") (new Symbol "%^&") (new Symbol "G") (new Symbol "*")))});
        end
    end
end
