require_relative "_parser_helpers";

describe Parser do
    context "on numeric" do
        it "parses integer literals" do
            parse("(0)");
            parse("(0 0 0)");
            parse("(.7)");
            parse("(42)");
            parse("(41 42 43)");
            parse("(41 (42) 43)");
            parse("(41 (42) 43)");
            # TODO negative numeric ambiguity
            parse("(-41 -42)");
            parse("(42 - 41)");
        end
        
        it "parses binary literals" do
            parse("(
                (x = 0b0101 + 0b1011)
                (x to_int puts)
            )");
        end
        
        it "parses hexadecimal literals" do
            parse("(x = 0xbeef to_bin to_int puts)");
            parse("(0xbeef - 0xabb2)");
        end
        
        it "parses octal literals" do
            parse("(x = 0o751 to_hex to_bin to_int puts)");
            parse("(0O541 + 0o777)");
        end
    end
end
