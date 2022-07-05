def parse(code)
    l = Lexer.new "file.obl", code.chars;
    l.make_tokens;
    p = Parser.new l;
    expect(p.analyse_syntax).to eq %Q{Compilation #{"successful".green()}};
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

    it "parses self and super" do
        parse("(self)");
        parse("(super)");
        parse("(self self self)");
        parse("(self super self)");
        parse("(self 42 super (10) ((self) (super 42)))");
    end

    it "parses identifiers" do
        parse("(s (42) self)");
        parse("(ident 42 another)");
        parse("(stuff? ident2)");
    end

    it "parses unary messages" do
        parse("(42 puts)");
        parse("(obj puts)");
        parse("(obj puts 42 incr)");
    end

    it "parses binary messages" do
        parse("(2 + 3)");
        parse("(2 * 5)");
        parse("(a + b)");
    end

    it "parses keyword messages" do
        parse("(list put: 42 at: 5)");
        parse("(
            (list = List new)
            (list put: 42 at: 5)
            (x = list get: 2)
            (x puts)
        )");
    end

    it "parses integer literals" do
        parse("(42)");
        parse("(41 42 43)");
        parse("(41 (42) 43)");
        parse("(41 (42) 43)");
        # TODO
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

    it "parses string literals" do
        parse(%Q{("hello" puts)});
    end

    it "parses tuple literals" do
        parse("([])");
        parse("([41 42])");
        parse(%Q{([42 "str" var])});
        error("([)", "missing closing bracket on tuple");
        error("(])", "missing closing parenthesis on list");
    end

    it "parses hash literals" do
        # TODO
        parse("({a: 1, b: 2, c: 3})");
        parse("({:a => 1 :b => 2 :c => 3})");
        parse("({:a => (self a) :b => (super b) :c => 3})");
        parse(%Q{({"k1 => "v1" "k2" => "v2" "k3" => "v3"})});
    end

    it "parses symbol literals" do
        parse("(:a :b :c)");
    end
end
