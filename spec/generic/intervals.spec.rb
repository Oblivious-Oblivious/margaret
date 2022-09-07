describe Parser do
    context "on intervals" do
        it "parses intervals" do
            parse("(x = Interval from: 5 to: 10)", "(= x from:to: Interval 5 10)");
            parse("(x = Interval from: 5 to: 10 by: 2)", "(= x from:to:by: Interval 5 10 2)");
            parse("(x = 5 to: 10)", "(= x to: 5 10)");
            parse("(x = 5 to: 10 by: 2)", "(= x to:by: 5 10 2)");
        end
    end
end
