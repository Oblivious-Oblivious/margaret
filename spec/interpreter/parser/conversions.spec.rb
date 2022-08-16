require_relative "_parser_helpers";

describe Parser do
    context "on conversions" do
        it "parses object conversion" do
            parse("(x = 3.99 to_int)", "(= x to_int 3.99)");
            parse("(x = 3.99 to_fraction)", "(= x to_fraction 3.99)");
            parse("(x = 3 to_float)", "(= x to_float 3)");
            parse("(x = 65 to_char)", "(= x to_char 65)");
            parse(%Q{(x = "A" to_ascii)}, %Q{(= x to_ascii "A")});
            parse(%Q{(x = 'b' to_ascii)}, %Q{(= x to_ascii 'b')});
        end
    end
end
