describe Parser do
    context "on numeric" do
        it "parses numeric expressions" do
            parse("(0)", ["push_0"]);
            parse("(0,0,0)", ["push_0", "push_0", "push_0"]);
            parse("(42)", ["push_integer", "42"]);
            parse("(41, 42, 43)", ["push_integer", "41", "push_integer", "42", "push_integer", "43"]);
            parse("(41, (42), 43)", ["push_integer", "41", "push_integer", "42", "push_integer", "43"]);
            parse("(-41 - (-42))", ["push_integer", "-41", "push_integer", "-42", "binary", "-"]);
            parse("((-41), (-42))", ["push_integer", "-41", "push_integer", "-42"]);
            parse("(42 - 41)", ["push_integer", "42", "push_integer", "41", "binary", "-"]);
        end

        it "parses integers literals" do
            parse("42", ["push_integer", "42"]);
            parse("-42", ["push_integer", "-42"]);
            parse("+42", ["push_integer", "42"]);
    
            parse("4_200", ["push_integer", "4200"]);
            parse("-4_200", ["push_integer", "-4200"]);
        end

        it "parses float literals" do
            parse("42.0", ["push_float", "42.0"]);
            parse("-42.0", ["push_float", "-42.0"]);
            parse("986513.00056129", ["push_float", "986513.00056129"]);
            parse("-986513.00056129", ["push_float", "-986513.00056129"]);
            # TODO `E` floats
            # parse("1234e-2", "12.34");
            # parse("1234E-2", "12.34");
            # parse("1.234e1", "12.34");
            # parse("1.234E1", "12.34");
        end

        it "parses binary literals" do
            parse("0b0110", ["push_integer", "6"]);
            parse("0B10", ["push_2"]);
            parse("-0b0110", ["push_integer", "-6"]);
            parse("-0B10", ["push_integer", "-2"]);
            parse("(
                x = 0b0101 + 0b1011,
                x to_int puts,
            )", ["push_integer", "5", "push_integer", "11", "binary", "+", "store", "x", "push_variable", "x", "unary", "to_int", "unary", "puts"]);
        end
        
        it "parses hexadecimal literals" do
            parse("0xbeef", ["push_integer", "48879"]);
            parse("-0xbeEf", ["push_integer", "-48879"]);
            parse("0X0427", ["push_integer", "1063"]);
            parse("-0X0427", ["push_integer", "-1063"]);
            parse("(x = 0xbeef to_bin to_int puts)", ["push_integer", "48879", "unary", "to_bin", "unary", "to_int", "unary", "puts", "store", "x"]);
            parse("(0xbeef - 0xabb2)", ["push_integer", "48879", "push_integer", "43954", "binary", "-"]);
        end
        
        it "parses octal literals" do
            parse("0o741", ["push_integer", "481"]);
            parse("-0o741", ["push_integer", "-481"]);
            parse("0O0210", ["push_integer", "136"]);
            parse("-0O0210", ["push_integer", "-136"]);
            parse("(x = 0o751 to_hex to_bin to_int puts)", ["push_integer", "489", "unary", "to_hex", "unary", "to_bin", "unary", "to_int", "unary", "puts", "store", "x"]);
            parse("(0O541 + 0o777)", ["push_integer", "353", "push_integer", "511", "binary", "+"]);
        end

        it "parses negative characters" do
            parse("-'a'", ["push_char", "-'a'"]);
            parse("-'æ'", ["push_char", "-'æ'"]);
        end
    end
end
