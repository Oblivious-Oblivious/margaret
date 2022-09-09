describe Parser do
    context "on conversions" do
        it "parses object conversion" do
            parse("(x = 3.99 to_int)", ["push_float", "3.99", "unary", "to_int", "store", "x"]);
            parse("(x = 3.99 to_fraction)", ["push_float", "3.99", "unary", "to_fraction", "store", "x"]);
            parse("(x = 3 to_float)", ["push_integer", "3", "unary", "to_float", "store", "x"]);
            parse("(x = 65 to_char)", ["push_integer", "65", "unary", "to_char", "store", "x"]);
            parse(%Q{(x = "A" to_ascii)}, ["push_string", %Q{"A"}, "unary", "to_ascii", "store", "x"]);
            parse(%Q{(x = 'b' to_ascii)}, ["push_char", "'b'", "unary", "to_ascii", "store", "x"]);
        end
    end
end
