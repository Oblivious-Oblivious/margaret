describe Parser do
    context "on numeric" do
        it "parses numeric expressions" do
            parse("(0)", "(0)");
            parse("(0,0,0)", "(0, 0, 0)");
            parse("(42)", "(42)");
            parse("(41, 42, 43)", "(41, 42, 43)");
            parse("(41, (42), 43)", "(41, (42), 43)");
            parse("(-41 - (-42))", "(- -41 (-42))");
            parse("((-41), (-42))", "((-41), (-42))");
            parse("(42 - 41)", "(- 42 41)");
        end

        it "parses integers literals" do
            parse("42", "42");
            parse("-42", "-42");
            parse("+42", "+42");
    
            parse("4_200", "4200");
            parse("-4_200", "-4200");
        end

        it "parses float literals" do
            parse("42.0", "42.0");
            parse("-42.0", "-42.0");
            parse("986513.00056129", "986513.00056129");
            parse("-986513.00056129", "-986513.00056129");
            # TODO `E` floats
            # parse("1234e-2", "12.34");
            # parse("1234E-2", "12.34");
            # parse("1.234e1", "12.34");
            # parse("1.234E1", "12.34");
        end

        it "parses binary literals" do
            parse("0b0110", "0b0110");
            parse("0B10", "0b10");
            parse("-0b0110", "-0b0110");
            parse("-0B10", "-0b10");
            parse("(
                x = 0b0101 + 0b1011,
                x to_int puts,
            )", "(= x + 0b0101 0b1011, puts (to_int x))");
        end
        
        it "parses hexadecimal literals" do
            parse("0xbeef", "0xbeef");
            parse("-0xbeEf", "-0xbeef");
            parse("0X0427", "0x0427");
            parse("-0X0427", "-0x0427");
            parse("(x = 0xbeef to_bin to_int puts)", "(= x puts (to_int (to_bin 0xbeef)))");
            parse("(0xbeef - 0xabb2)", "(- 0xbeef 0xabb2)");
        end
        
        it "parses octal literals" do
            parse("0o741", "0o741");
            parse("-0o741", "-0o741");
            parse("0O0210", "0o0210");
            parse("-0O0210", "-0o0210");
            parse("(x = 0o751 to_hex to_bin to_int puts)", "(= x puts (to_int (to_bin (to_hex 0o751))))");
            parse("(0O541 + 0o777)", "(+ 0o541 0o777)");
        end

        it "parses negative characters" do
            parse("-'a'", "-'a'");
            parse("-'æ'", "-'æ'");
        end
    end
end
