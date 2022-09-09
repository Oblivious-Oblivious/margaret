describe Parser do
    context "on complex numbers" do
        it "parses complex literals" do
            parse("1i", ["push_1", "unary", "i"]);
            parse("1i * 1i", ["push_1", "unary", "i", "push_1", "unary", "i", "binary", "*"]);
            parse("12.3r i", ["push_float", "12.3", "unary", "r", "unary", "i"]);
        end

        it "parses complex literal messages" do
            # TODO complex messages
        end
    end
end
