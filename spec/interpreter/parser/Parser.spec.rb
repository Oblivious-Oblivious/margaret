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
        parse("3 factorial + 4 factorial between: 10 and: 100", "between:and: + factorial 3 factorial 4 10 100");
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
        parse("0bi42_000", %Q{new: BigInteger "42000"});
        parse("-0bi42_000", %Q{new: BigInteger "-42000"});
        parse("0bi42000", %Q{new: BigInteger "42000"});
        parse("-0bi42000", %Q{new: BigInteger "-42000"});
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
        parse("0bf0.042", %Q{new: BigFloat "0.042"});
        parse("-0bf0.042", %Q{new: BigFloat "-0.042"});
    end

    it "TEST9" do
        parse("1r", "r 1");
        parse("2/3r", "/ 2 r 3");
        parse("-1r", "r -1");
        parse("-2/3r", "/ -2 r 3");
        # TODO Separate `-` message on its own token (avoids `-/` or `/-`)
        parse("2/(-3r)", "/ 2 (r -3)");
        parse("-2/(-3r)", "/ -2 (r -3)");
        parse("+1 / (+3r)", "/ +1 (r +3)");
        parse("1.2r", "r 1.2");
        parse("1_1/2_2r", "/ 11 r 22");
        parse("2/4r", "/ 2 r 4");
    end

    it "TEST10" do
        parse("1i", "i 1");
        parse("1i * 1i", "* i 1 i 1");
        parse("12.3r i", "i (r 12.3)");
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
        parse("a: 3", %Q{:"a": 3});
        parse(%Q{"a": 5}, %Q{"a": 5});
        parse(":a: 7", %Q{:"a": 7});
    end

    it "TEST15" do
        parse("()", "()");
        parse("(())", "(())");
        parse("(42)", "(42)");
        parse("(1, 2, 3)", "(1, 2, 3)");
        parse("(1, 2, (10, 20, 30), 3)", "(1, 2, (10, 20, 30), 3)");
    end

    it "TEST16" do
        parse("`()", %Q{(:"(", :")")});
        parse("`(a b c)", %Q{(:"(", :"a", :"b", :"c", :")")});
        parse("`(:a msg: :b)", %Q{(:"(", :":", :"a", :"msg", :":", :":", :"b", :")")});
        parse("`(2 * (3 + 5) / 4)", %Q{(:"(", :"2", :"*", :"(", :"3", :"+", :"5", :")", :"/", :"4", :")")});
        parse("`(x = 2) eval", %Q{eval (:"(", :"x", :"=", :"2", :")")});
    end

    it "TEST17" do
        parse("->(42)", "(params:function: Block () 42)");
        parse("->(:a, a puts)", %Q{(params:function: Block (:"a") puts a)});
        parse("->(2 + 3)", "(params:function: Block () + 2 3)");
        parse("->((x = 1, y = 2, x + y))", "(params:function: Block () (= x 1, = y 2, + x y))");
        parse("->(:a, :b, a + b)", %Q{(params:function: Block (:"a", :"b") + a b)});
        parse("->(:a, a)", %Q{(params:function: Block (:"a") a)});
        parse("->(x = 2) exec", "exec (params:function: Block () = x 2)");
        parse("->(:param, param puts) value: 42", %Q{value: (params:function: Block (:"param") puts param) 42});
    end

    it "TEST18" do
        parse("[]", "new Tuple ()");
        parse("[1]", "new Tuple (1)");
        parse("[1, 2]", "new Tuple (1, 2)");
        parse(%Q{[42, "Hello", 'x', :ok, v1, v2, (), [], {}, x = 1]}, %Q{new Tuple (42, "Hello", 'x', :"ok", v1, v2, (), new Tuple (), new Hash (), = x 1)});
    end

    it "TEST19" do
        parse("{}", "new Hash ()");
        parse("{a: 1}", %Q{new Hash (:"a": 1)});
        parse(%Q{{"a": 1, "b": 2, "c": 3}}, %Q{new Hash ("a": 1, "b": 2, "c": 3)});
        parse(%Q{{:a: 1, :b: 2, :c: 3}}, %Q{new Hash (:"a": 1, :"b": 2, :"c": 3)});
        parse(%Q{{a: 1, b: 2, c: 3}}, %Q{new Hash (:"a": 1, :"b": 2, :"c": 3)});
        parse("{x: {a: 1, b: 2}, y: {c: 3, d: 4}}", %Q{new Hash (:"x": new Hash (:"a": 1, :"b": 2), :"y": new Hash (:"c": 3, :"d": 4))});
        parse("{a: 42 factorial, b: 2 + 3, c: 41 plus: 1, d: (42 incr decr, 41 incr)}", %Q{new Hash (:"a": factorial 42, :"b": + 2 3, :"c": plus: 41 1, :"d": (decr (incr 42), incr 41))});
    end

    it "TEST20" do
        parse("variable", "variable");
        parse("@instvar", "@instvar");
        parse("@x", "@x");
    end

    it "TEST21" do
        error("(", "missing closing parenthesis on list");
        error(")", "missing opening parenthesis on list");
        error("(()", "missing closing parenthesis on list");
        error("())", "reached end of program");
        error("[", "missing closing bracket on tuple");
        error("]", "missing opening bracket on tuple");
        error("{", "missing closing curly brace on hash");
        error("}", "missing opening curly brace on hash");
        error("->", "missing opening parenthesis on block literal");
        error("`", "missing opening parenthesis on quoted list literal");
    end

    it "TEST22" do
        parse("var = 12", "= var 12");
        parse("arr = ()", "= arr ()");
        parse("@x = x", "= @x x");
        parse("a = b", "= a b");
        parse("a = b = c", "= a (= b c)");
        parse("a = b = c = d = 42", "= a (= b (= c (= d 42)))");
        parse("(a = 2, b = 3, c = a = b)", "(= a 2, = b 3, = c (= a b))");
        parse("((a = 2), (b = 3), (c = a = b))", "((= a 2), (= b 3), (= c (= a b)))");
        parse("a = b = (c = 42) + 12", "= a (= b + (= c 42) 12)");
        parse("a = 12 + 3 * 4", "= a * (+ 12 3) 4");
    end

    it "TEST23" do
        parse("42 factorial", "factorial 42");
        parse("17 incr puts", "puts (incr 17)");
        parse("23 one two three", "three (two (one 23))");
        parse("@inst one two three", "three (two (one @inst))");
        parse("42 puts", "puts 42");
        parse("obj puts", "puts obj");
        parse("x = (obj puts)", "= x (puts obj)");
        parse("(obj puts, 42 incr)", "(puts obj, incr 42)");
        parse("((obj puts), (42 incr))", "((puts obj), (incr 42))");
        parse("42 incr incr decr decr", "decr (decr (incr (incr 42)))");
        parse("x = 42 incr incr decr decr", "= x decr (decr (incr (incr 42)))");
        parse("x incr!", "incr! x");
        parse("x is_empty?", "is_empty? x");
        parse("(42 one, 43 two, 44 three, 45, 46 four)", "(one 42, two 43, three 44, 45, four 46)");
        parse("p1 + p2 calc puts", "+ p1 puts (calc p2)");
        parse("(p1 + p2 calc) puts", "puts (+ p1 calc p2)");
    end

    it "TEST24" do
        parse("2 + 3", "+ 2 3");
        parse("2 + 3 + 4 + 5", "+ (+ (+ 2 3) 4) 5");
        parse("2 * 5", "* 2 5");
        parse("a + b", "+ a b");
        parse("42 factorial + 17", "+ factorial 42 17");
        parse("41 factorial + 42 factorial + 43 factorial", "+ (+ factorial 41 factorial 42) factorial 43");
        parse("(41 + 1, 42 + 0, 43 - 1)", "(+ 41 1, + 42 0, - 43 1)");
        parse("((41 + 1), (42 + 0), (43 - 1))", "((+ 41 1), (+ 42 0), (- 43 1))");
        parse("x = a + b * 2 - 5", "= x - (* (+ a b) 2) 5");
        parse("x << item", "<< x item");
        parse("[1, 2, 3] ++ [4, 5]", "++ new Tuple (1, 2, 3) new Tuple (4, 5)");
        parse("(4 + 3) * (5 + 6)", "* (+ 4 3) (+ 5 6)");
    end

    it "TEST25" do
        parse("list put: 42 at: 5", "put:at: list 42 5");
        parse("list put: (42 incr) at: 5", "put:at: list (incr 42) 5");
        parse("(
            list = List new,
            list put: 42 at: 5,
            x = list get: 2,
            x puts
        )", "(= list new List, put:at: list 42 5, = x get: list 2, puts x)");
        parse("2 + 3 incr add: 11", "add: + 2 incr 3 11");
        parse("(1, 2, 3) reverse!: true", "reverse!: (1, 2, 3) true");
        parse("true then: 1 else: 2", "then:else: true 1 2");
        parse("x ok?: true otherwise!: false", "ok?:otherwise!: x true false");
        parse("(5 + 13) greater_than?: (11 + 2)", "greater_than?: (+ 5 13) (+ 11 2)");
        parse("42 factorial and: (2 + 3)", "and: factorial 42 (+ 2 3)");
        parse("(list at: 3) + (list at: 5)", "+ (at: list 3) (at: list 5)");
    end

    it "TEST26" do
        parse("Object message: (:calc, `(@x + @y))", %Q{message: Object (:"calc", (:"(", :"@", :"x", :"+", :"@", :"y", :")"))});
        parse("Object unary: (:calc, `(@x + @y))", %Q{unary: Object (:"calc", (:"(", :"@", :"x", :"+", :"@", :"y", :")"))});
        parse("Object message: (:+, :other, `(@x += other x, @y += other y, self))", %Q{message: Object (:"+", :"other", (:"(", :"@", :"x", :"+=", :"other", :"x", :",", :"@", :"y", :"+=", :"other", :"y", :",", :"self", :")"))});
        parse("Object binary: (:+, :other, `(@x += other x, @y += other y, self))", %Q{binary: Object (:"+", :"other", (:"(", :"@", :"x", :"+=", :"other", :"x", :",", :"@", :"y", :"+=", :"other", :"y", :",", :"self", :")"))});
        parse("Object message: (x::x, y::y, `(@x = x, @y = y, self))", %Q{message: Object (:"x": :"x", :"y": :"y", (:"(", :"@", :"x", :"=", :"x", :",", :"@", :"y", :"=", :"y", :",", :"self", :")"))});
        parse("Object keyword: (x::x, y::y, `(@x = x, @y = y, self))", %Q{keyword: Object (:"x": :"x", :"y": :"y", (:"(", :"@", :"x", :"=", :"x", :",", :"@", :"y", :"=", :"y", :",", :"self", :")"))});
    end
end
