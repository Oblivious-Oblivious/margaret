require_relative "_parser_helpers";

describe Parser do
    context "on constants" do
        it "parses constants" do
            parse("(b = true)");
            parse("(b = false)");
            parse("(x = nil)");

            parse("(x = 1)");
            parse("(x = -1)");
            # TODO
            parse("(x = --1)");
            parse("(x = 3.14159)");
            parse("(x = 0.42)");
            parse("(x = 0xbeef)");
            parse("(x = 0b0101)");
            parse("(x = 0o741)");

            parse(%Q{(x = "Hello")});
            parse(%Q{(x = :a_symbol)});
        end
    end
end
