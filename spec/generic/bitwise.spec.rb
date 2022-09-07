describe Parser do
    context "on bitwise" do
        it "parses bitwise operations" do
            parse("(x = 0xff bitand: 0x0f)", "(= x bitand: 0xff 0x0f)");
            parse("(x = 0xf0 bitor: 0x0f)", "(= x bitor: 0xf0 0x0f)");
            parse("(x = 0xff bitxor: 0x0f)", "(= x bitxor: 0xff 0x0f)");
            parse("(x = 0xff bitinvert)", "(= x bitinvert 0xff)");
            parse("(x = 0x0f bitshift: 4)", "(= x bitshift: 0x0f 4)"); # Left shift
            parse("(x = 0xf0 bitshift: -4)", "(= x bitshift: 0xf0 -4)"); # Right shift
            parse("(x = 0x80 highbit)", "(= x highbit 0x80)");
            parse("(x = 0xff all_mask: 0x0f)", "(= x all_mask: 0xff 0x0f)");
            parse("(x = 0xff any_mask: 0x0f)", "(= x any_mask: 0xff 0x0f)");
            parse("(x = 0xff no_mask: 0x0f)", "(= x no_mask: 0xff 0x0f)");
        end
    end
end
