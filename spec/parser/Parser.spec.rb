describe Parser do
    it "creates a Parser object with Lexer as a parameter" do
        l = Lexer.new "file.obl", "(42 factorial)".chars;
        p = Parser.new l.make_tokens;
        expect(p).to be_kind_of Parser;
    end

    it "traverses through the token table" do
        l = Lexer.new "file.obl", "(42 factorial)".chars;
        p = Parser.new l.make_tokens;
        expect(p.table.consume).to eq "(";
        expect(p.table.consume).to eq "42";
        expect(p.table.consume).to eq "factorial";
        expect(p.table.consume).to eq ")";
        expect(p.table.consume).to eq "eof";
    end

    it "peeks on top of the token table" do
        l = Lexer.new "file.obl", "(42 factorial)".chars;
        p = Parser.new l.make_tokens;
        expect(p.table.lookahead(5)).to eq "eof";
        expect(p.table.lookahead(2)).to eq "42";
        expect(p.table.lookahead(3)).to eq "factorial";
        expect(p.table.lookahead(1)).to eq "(";
        expect(p.table.lookahead(4)).to eq ")";
    end

    it "has an error message for syntax errors" do
        l = Lexer.new "file.obl", "(42 factorial)".chars;
        p = Parser.new l.make_tokens;
        p.table.consume;

        begin
            p.table.error "This is a random syntax error";
        rescue Exception => e
            expect(e.message).to eq "This is a random syntax error";
        end
    end
end
