require_relative "_parser_helpers";

describe Parser do
    context "on bitwise" do
        it "parses bitwise operations" do
            parse("(x = 0xff bitand: 0x0f)");
            parse("(x = 0xf0 bitor: 0x0f)");
            parse("(x = 0xff bitxor: 0x0f)");
            parse("(x = 0xff bitinvert)");
            parse("(x = 0x0f bitshift: 4)"); # Left shift
            parse("(x = 0xf0 bitshift: -4)"); # Right shift
            parse("(x = 0x80 highbit)");
            parse("(x = 0xff all_mask: 0x0f)");
            parse("(x = 0xff any_mask: 0x0f)");
            parse("(x = 0xff no_mask: 0x0f)");
        end
    end
end
