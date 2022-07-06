require_relative "_parser_helpers";

describe Parser do
    context "on conversions" do
        it "parses object conversion" do
            parse("(x = 3.99 to_int)");
            parse("(x = 3.99 to_fraction)");
            parse("(x = 3 to_float)");
            parse("(x = 65 to_char)");
            parse(%Q{(x = "A" to_ascii)});
        end
    end
end
