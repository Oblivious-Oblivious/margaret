describe Parser do
    context "on constants" do
        it "parses constants" do
            parse("(b = true)", "(= b true)");
            parse("(b = false)", "(= b false)");
            parse("(x = nil)", "(= x nil)");

            parse("(x = 1)", "(= x 1)");
            parse("(x = -1)", "(= x -1)");
            parse("(x = 3.14159)", "(= x 3.14159)");
            parse("(x = 0.42)", "(= x 0.42)");
            parse("(x = 0xbeef)", "(= x 0xbeef)");
            parse("(x = 0b0101)", "(= x 0b0101)");
            parse("(x = 0o741)", "(= x 0o741)");

            parse(%Q{(x = "Hello")}, %Q{(= x "Hello")});
        end
    end
end
