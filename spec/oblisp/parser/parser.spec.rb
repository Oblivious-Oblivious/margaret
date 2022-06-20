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

    it "parses an empty list as a first unit" do
        parse("()");
        error("(", "missing closing parenthesis on list");
        error(")", "missing opening parenthesis on list");
        error("()stuff", "reached end of program");
    end

    it "parses multiple lists as translation units" do
        parse("(())");
        error("(()", "missing closing parenthesis on list");
        error("())", "reached end of program");
    end

    it "parses infinite lists of lists" do
        parse("(42)");
        parse("(42 43 44)");
        parse("(42 () 43 ())");
        parse("(42 (43) 44 ())");
        parse("(() () () ())");
        parse("((((()))))");
    end
end
