require_relative "_parser_helpers";

describe Parser do
    context "on complex numbers" do
        it "parses complex literals" do
            parse("1i", "i 1");
            parse("1i * 1i", "* i 1 i 1");
            parse("12.3r i", "i (r 12.3)");
        end

        it "parses complex literal messages" do
            # TODO complex messages
        end
    end
end
