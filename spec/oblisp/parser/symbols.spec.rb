require_relative "_parser_helpers";

describe Parser do
    context "on symbols" do
        it "parses symbol literals" do
            parse("(:a :b :c)");
        end

        it "parses symbol messages" do
            parse("(x = :Hello)");
            parse("(y = :symb)");
            # TODO Look at ruby
        end
    end
end
