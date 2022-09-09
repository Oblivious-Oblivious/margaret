describe Parser do
    context "on constants" do
        it "parses constants" do
            parse("(b = true)", ["push_true", "store", "b"]);
            parse("(b = false)", ["push_false", "store", "b"]);
            parse("(x = nil)", ["push_nil", "store", "x"]);

            parse("(x = 1)", ["push_1", "store", "x"]);
            parse("(x = -1)", ["push_minus_1", "store", "x"]);
            parse("(x = 3.14159)", ["push_float", "3.14159", "store", "x"]);
            parse("(x = 0.42)", ["push_float", "0.42", "store", "x"]);
            parse("(x = 0xbeef)", ["push_integer", "48879", "store", "x"]);
            parse("(x = 0b0101)", ["push_integer", "5", "store", "x"]);
            parse("(x = 0o741)", ["push_integer", "481", "store", "x"]);

            parse(%Q{(x = "Hello")}, ["push_string", %Q{"Hello"}, "store", "x"]);
        end
    end
end
