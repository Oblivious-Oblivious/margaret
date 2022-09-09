describe Parser do
    context "on intervals" do
        it "parses intervals" do
            parse("(x = Interval from: 5 to: 10)", ["push_variable", "Interval", "push_integer", "5", "push_integer", "10", "keyword", "from:to:", "2", "store", "x"]);
            parse("(x = Interval from: 5 to: 10 by: 2)", ["push_variable", "Interval", "push_integer", "5", "push_integer", "10", "push_2", "keyword", "from:to:by:", "3", "store", "x"]);
            parse("(x = 5 to: 10)", ["push_integer", "5", "push_integer", "10", "keyword", "to:", "1", "store", "x"]);
            parse("(x = 5 to: 10 by: 2)", ["push_integer", "5", "push_integer", "10", "push_2", "keyword", "to:by:", "2", "store", "x"]);
        end
    end
end
