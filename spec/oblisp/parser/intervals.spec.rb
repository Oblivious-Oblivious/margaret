require_relative "_parser_helpers";

describe Parser do
    context "on intervals" do
        it "parses intervals" do
            parse("(x = Interval from: 5 to: 10)");
            parse("(x = Interval from: 5 to: 10 by: 2)");
            parse("(x = 5 to: 10)");
            parse("(x = 5 to: 10 by: 2)");
            # TODO invervals have list messages
        end
    end
end
