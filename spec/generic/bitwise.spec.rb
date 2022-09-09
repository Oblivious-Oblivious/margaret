describe Parser do
    context "on bitwise" do
        it "parses bitwise operations" do
            parse("(x = 0xff bitand: 0x0f)", ["push_integer", "255", "push_integer", "15", "keyword", "bitand:", "1", "store", "x"]);
            parse("(x = 0xf0 bitor: 0x0f)", ["push_integer", "240", "push_integer", "15", "keyword", "bitor:", "1", "store", "x"]);
            parse("(x = 0xff bitxor: 0x0f)", ["push_integer", "255", "push_integer", "15", "keyword", "bitxor:", "1", "store", "x"]);
            parse("(x = 0xff bitinvert)", ["push_integer", "255", "unary", "bitinvert", "store", "x"]);
            parse("(x = 0x0f bitshift: 4)", ["push_integer", "15", "push_integer", "4", "keyword", "bitshift:", "1", "store", "x"]); # Left shift
            parse("(x = 0xf0 bitshift: -4)", ["push_integer", "240", "push_integer", "-4", "keyword", "bitshift:", "1", "store", "x"]); # Right shift
            parse("(x = 0x80 highbit)", ["push_integer", "128", "unary", "highbit", "store", "x"]);
            parse("(x = 0xff all_mask: 0x0f)", ["push_integer", "255", "push_integer", "15", "keyword", "all_mask:", "1", "store", "x"]);
            parse("(x = 0xff any_mask: 0x0f)", ["push_integer", "255", "push_integer", "15", "keyword", "any_mask:", "1", "store", "x"]);
            parse("(x = 0xff no_mask: 0x0f)", ["push_integer", "255", "push_integer", "15", "keyword", "no_mask:", "1", "store", "x"]);
        end
    end
end
