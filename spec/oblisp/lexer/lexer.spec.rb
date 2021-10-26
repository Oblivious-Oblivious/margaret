describe Lexer do
    it "contains the input text, lexer position and current character" do
        l = Lexer.new("(42 factorial)");
        expect(l.text).to eq "(42 factorial)";
        expect(l.pos).to eq -1;
    end

    it "#advance" do
        l = Lexer.new("(42 factorial)");

        current_char = l.advance;
        expect(current_char.c).to eq "(";
        expect(l.pos).to eq 0;

        current_char = l.advance
        expect(current_char.c).to eq "4";
        expect(l.pos).to eq 1;
    end

    it "reads all tokens until the string ends" do
        l = Lexer.new("12345");

        curr = l.advance;
        expect(curr.c).to eq "1";
        curr = l.advance;
        expect(curr.c).to eq "2";
        curr = l.advance;
        expect(curr.c).to eq "3";
        curr = l.advance;
        expect(curr.c).to eq "4";
        curr = l.advance;
        expect(curr.c).to eq "5";

        # String reaches EOF
        curr = l.advance;
        expect(curr.c).to eq nil;
    end

    it "creates a list of tokens" do
        l = Lexer.new("(42 factorial)");
        expect(l.make_tokens).to eq [];
    end
end
