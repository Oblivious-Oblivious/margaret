require_relative "_parser_helpers";

describe Parser do
    context "on message types" do
        it "parses unary messages" do
            parse("(42 puts)");
            parse("(obj puts)");
            parse("(obj puts 42 incr)");
        end

        it "parses binary messages" do
            parse("(2 + 3)");
            parse("(2 * 5)");
            parse("(a + b)");
        end

        it "parses keyword messages" do
            parse("(list put: 42 at: 5)");
            parse("(
                (list = List new)
                (list put: 42 at: 5)
                (x = list get: 2)
                (x puts)
            )");
        end
    end
end
