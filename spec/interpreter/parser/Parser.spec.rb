require_relative "_parser_helpers";

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

    it "TEST0" do
        # TODO message precedence
        # parse("(3 factorial + 4 factorial between: 10 and: 100)", "(between:and: (+ (factorial 3) (factorial 4)) 10 100)");
    end

    it "TEST1" do
        parse("nil", "nil");
        parse("true", "true");
        parse("false", "false");
        parse("self", "self");
        parse("super", "super");
    end

    it "TEST2" do
        parse("42", "42");
        parse("-42", "-42");
        parse("+42", "+42");

        parse("4_200", "4200");
        parse("-4_200", "-4200");
    end

    it "TEST3" do
        parse("0b0110", "0b0110");
        parse("0B10", "0b10");
        parse("-0b0110", "-0b0110");
        parse("-0B10", "-0b10");
    end

    it "TEST4" do
        parse("0xbeef", "0xbeef");
        parse("-0xbeEf", "-0xbeef");
        parse("0X0427", "0x0427");
        parse("-0X0427", "-0x0427");
    end

    it "TEST5" do
        parse("0o741", "0o741");
        parse("-0o741", "-0o741");
        parse("0O0210", "0o0210");
        parse("-0O0210", "-0o0210");
    end

    it "TEST6" do
        parse("0bi42_000", %Q{(new: BigInteger "42000")});
        parse("-0bi42_000", %Q{(new: BigInteger "-42000")});
        parse("0bi42000", %Q{(new: BigInteger "42000")});
        parse("-0bi42000", %Q{(new: BigInteger "-42000")});
    end

    it "TEST7" do
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

    it "TEST8" do
        parse("0bf0.042", %Q{(new: BigFloat "0.042")});
        parse("-0bf0.042", %Q{(new: BigFloat "-0.042")});
    end

    it "TEST9" do
        # TODO Rational
        # parse("(1 r)", "(r 1)");
        # parse("(2/3r)", "");
        # parse("(-1r)", "");
        # parse("(-2/3r)", "");
        # parse("(2/-3r)", "");
        # parse("(-2/-3r)", "");
        # parse("(+1/+3r)", "");
        # parse("(1.2r)", "");
        # parse("(1_1/2_2r)", "");
        # parse("(2/4r)", "");
    end

    it "TEST10" do
        # TODO Complex
        # parse("(1i)", "(i 1)");
        # parse("((1i) * (1i))");
        # parse("(12.3ri)");
        # parse("(1i)");
        # parse("(1i)");
        # parse("(1i)");
        # parse("(1i)");
    end

    it "TEST11" do
        parse("'a'", "'a'");
        parse("'\n'", "'\n'");
        parse("'œ'", "'œ'");
    end

    it "TEST12" do
        parse(%Q{"foo\tbar"}, %Q{"foo\tbar"});
        parse(%Q{"a string lit"}, %Q{"a string lit"});
        parse(%Q{"multi
            line
            string"}, %Q{"multi
            line
            string"});
        parse(%Q{"str"}, %Q{"str"});

        parse(%Q{"\a"}, %Q{"\a"});
        parse(%Q{"\b"}, %Q{"\b"});
        parse(%Q{"\t"}, %Q{"\t"});
        parse(%Q{"\n"}, %Q{"\n"});
        parse(%Q{"\v"}, %Q{"\v"});
        parse(%Q{"\f"}, %Q{"\f"});
        parse(%Q{"\r"}, %Q{"\r"});
        parse(%Q{"\e"}, %Q{"\e"});
        parse(%Q{"\s"}, %Q{"\s"});
        parse(%Q{"\\"}, %Q{"\\"});
    end

    it "TEST13" do
        parse(":symb", %Q{:"symb"});
        parse(":+", %Q{:"+"});
        parse(%Q{:"a symbol lit"}, %Q{:"a symbol lit"});
    end

    it "TEST14" do
        parse("()", "()");
        parse("(())", "(())");
        parse("(42)", "(42)");
        parse("(1, 2, 3)", "(1, 2, 3)");
        parse("(1, 2, (10, 20, 30), 3)", "(1, 2, (10, 20, 30), 3)");
    end

    it "TEST15" do
        parse("`()", %Q{(:"(", :")")});
        parse("`(a b c)", %Q{(:"(", :"a", :"b", :"c", :")")});
        parse("`(:a msg: :b)", %Q{(:"(", :":", :"a", :"msg", :":", :":", :"b", :")")});
        parse("`(2 * (3 + 5) / 4)", %Q{(:"(", :"2", :"*", :"(", :"3", :"+", :"5", :")", :"/", :"4", :")")});
    end

    it "TEST16" do
        parse("->(42)", "(params:function: Block () 42)");
        parse("->(:a, (a puts))", %Q{(params:function: Block (:"a") (puts a))});
        parse("->((2 + 3))", "(params:function: Block () (+ 2 3))");
        parse("->((x = 1, y = 2, x + y))", "(params:function: Block () (= x 1, = y 2, + x y))");
        parse("->(:a, :b, (a + b))", %Q{(params:function: Block (:"a", :"b") (+ a b))});
        parse("->(:a, a)", %Q{(params:function: Block (:"a") a)});
    end

    it "TEST17" do
        parse("[]", "(new Tuple ())");
        parse("[1]", "(new Tuple (1))");
        parse("[1, 2]", "(new Tuple (1, 2))");
        parse(%Q{[42, "Hello", 'x', :ok, v1, v2, (), [], {}, (x = 1)]}, %Q{(new Tuple (42, "Hello", 'x', :"ok", v1, v2, (), (new Tuple ()), (new Hash ()), (= x 1)))});
    end

    it "TEST18" do
        parse("{}", "(new Hash ())");
        parse("{a: 1}", %Q{(new Hash (:"a": 1))});
        parse(%Q{{"a": 1, "b": 2, "c": 3}}, %Q{(new Hash ("a": 1, "b": 2, "c": 3))});
        parse(%Q{{:a: 1, :b: 2, :c: 3}}, %Q{(new Hash (:"a": 1, :"b": 2, :"c": 3))});
        parse(%Q{{a: 1, b: 2, c: 3}}, %Q{(new Hash (:"a": 1, :"b": 2, :"c": 3))});
        parse("{x: {a: 1, b: 2}, y: {c: 3, d: 4}}", %Q{(new Hash (:"x": (new Hash (:"a": 1, :"b": 2)), :"y": (new Hash (:"c": 3, :"d": 4))))});
    end

    it "TEST19" do
        parse("variable", "variable");
        parse("@instvar", "@instvar");
        parse("@x", "@x");
    end

    it "TEST20" do
        error("(", "missing closing parenthesis on list");
        error(")", "reached end of program");
        error("()stuff", "reached end of program");
        error("(()", "missing closing parenthesis on list");
        error("())", "reached end of program");
        # TODO
        # error("(42 43 44)", "list items should be separated by commas");
        error("[", "missing closing bracket on tuple");
        error("]", "reached end of program");
        error("{", "missing closing curly brace on hash");
        error("}", "reached end of program");
        error("->", "missing opening parenthesis on block literal");
        error("`", "missing opening parenthesis on quoted list literal");
    end

    it "TEST21" do
        parse("(var = 12)", "(= var 12)");
        parse("(a = b = c = d = 42)", "(= a (= b (= c (= d 42))))")
        # TODO with messages
        # parse("(a = b = (c = 42) + 12)", "(= a (= b (+ (= c 42) 12)))");
        # parse("(a = 12 + 3 * 4)", "(= a (* (+ 12 3) 4))");
    end
end
