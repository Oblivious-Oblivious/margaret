def parse(code)
    l = Lexer.new "file.obl", code.chars;
    l.make_tokens;
    p = Parser.new l;
    expect(p.analyse_syntax).to eq "Compilation #{'successful'.green()}";
end

def error(code, error_message)
    begin
        l = Lexer.new "file.obl", code.chars;
        l.make_tokens;
        p = Parser.new l;
        expect(p.analyse_syntax).to eq nil;
    rescue Exception => e
        expect(e.message).to eq error_message;
    end
end

describe Parser do
    it "creates a Parser object with Lexer as a parameter" do
        l = Lexer.new "file.obl", "(42 factorial.)".chars;
        p = Parser.new l;
        expect(p).to be_kind_of Parser;
    end

    it "has a nil token when initially creating the parser" do
        l = Lexer.new "file.obl", "(42 factorial.)".chars;
        p = Parser.new l;
        expect(p.token).to be nil;
    end

    it "traverses through the token table" do
        l = Lexer.new "file.obl", "(42 factorial.)".chars;
        l.make_tokens;
        p = Parser.new l;
        expect(p.next_token.value).to eq "(";
        expect(p.next_token.value).to eq "42";
        expect(p.next_token.value).to eq "factorial";
        expect(p.next_token.value).to eq ".";
        expect(p.next_token.value).to eq ")";
        expect(p.next_token.value).to eq "eof";
        expect(p.prev_token.value).to eq ")";
        expect(p.prev_token.value).to eq ".";
        expect(p.prev_token.value).to eq "factorial";
        expect(p.prev_token.value).to eq "42";
        expect(p.prev_token.value).to eq "(";
    end

    it "peeks on top of the token table" do
        l = Lexer.new "file.obl", "(42 factorial.)".chars;
        l.make_tokens;
        p = Parser.new l;
        expect(p.peek_token.value).to eq "(";
        expect(p.peek_token.value).to eq "(";
        expect(p.peek_token.value).to eq "(";
        expect(p.peek_token.value).to eq "(";
        expect(p.peek_token.value).to eq "(";
    end

    it "analyses the syntax returning a successful compilation message" do
        l = Lexer.new "file.obl", "()".chars;
        l.make_tokens;
        p = Parser.new l;
        p.analyse_syntax;
    end

    it "has an error message for syntax errors" do
        l = Lexer.new "file.obl", "(42 factorial.)".chars;
        l.make_tokens;
        p = Parser.new l;
        p.next_token;

        begin
            p.error "This is a random syntax error";
        rescue Exception => e
        end
    end
end
