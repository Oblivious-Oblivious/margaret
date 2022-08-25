require_relative "_parser_helpers";

describe Parser do
    context "on message types" do
        it "parses unary messages" do
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
    
        it "parses binary messages" do
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
            parse("x <<>>+-++-- 15", "<<>>+-++-- x 15");
            parse("[1, 2, 3] ++ [4, 5]", "++ new Tuple (1, 2, 3) new Tuple (4, 5)");
            parse("(4 + 3) * (5 + 6)", "* (+ 4 3) (+ 5 6)");
        end
    
        it "parses keyword messages" do
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
    
        it "parses message definitions" do
            parse("Object message: (:calc, `(@x + @y))", %Q{message: Object (:"calc", (:"(", :"@", :"x", :"+", :"@", :"y", :")"))});
            parse("Object unary: (:calc, `(@x + @y))", %Q{unary: Object (:"calc", (:"(", :"@", :"x", :"+", :"@", :"y", :")"))});
            parse("Object message: (:+, :other, `(@x += other x, @y += other y, self))", %Q{message: Object (:"+", :"other", (:"(", :"@", :"x", :"+=", :"other", :"x", :",", :"@", :"y", :"+=", :"other", :"y", :",", :"self", :")"))});
            parse("Object binary: (:+, :other, `(@x += other x, @y += other y, self))", %Q{binary: Object (:"+", :"other", (:"(", :"@", :"x", :"+=", :"other", :"x", :",", :"@", :"y", :"+=", :"other", :"y", :",", :"self", :")"))});
            parse("Object message: (x::x, y::y, `(@x = x, @y = y, self))", %Q{message: Object (:"x": :"x", :"y": :"y", (:"(", :"@", :"x", :"=", :"x", :",", :"@", :"y", :"=", :"y", :",", :"self", :")"))});
            parse("Object keyword: (x::x, y::y, `(@x = x, @y = y, self))", %Q{keyword: Object (:"x": :"x", :"y": :"y", (:"(", :"@", :"x", :"=", :"x", :",", :"@", :"y", :"=", :"y", :",", :"self", :")"))});
        end

        it "chains keyword messages of exactly the same selector" do
            parse("arr add: 1 add: 2 add: 3", "(add: arr 1, add: arr 2, add: arr 3)");
            parse("arr add: 'a' add: 'b' at: 3", "add:add:at: arr 'a' 'b' 3");
            parse("arr add: 'a' at: 1 add: 'b' at: 2", "add:at:add:at: arr 'a' 1 'b' 2");
        end

        it "parses composit messages" do
            parse("3 factorial + 4 factorial between: 10 and: 100", "between:and: + factorial 3 factorial 4 10 100");
            parse("
                (
                    Object message: (includesPoint::point, `(
                                            origin <= point
                                                if_true: ->(out goto)
                                                if_false: ->(false return),
                                            out = Label new
                                        )
                                    )
                )", %Q{(message: Object (:"includesPoint": :"point", (:"(", :"origin", :"<=", :"point", :"if_true", :":", :"->", :"(", :"out", :"goto", :")", :"if_false", :":", :"->", :"(", :"false", :"return", :")", :",", :"out", :"=", :"Label", :"new", :")")))});
            
            parse("(
                origin <= point
                    if_true: ->(out goto)
                    if_false: ->(false return),
                out = Label new
            )", "(if_true:if_false: <= origin point params:function: Block () goto out params:function: Block () return false, = out new Label)");
        end
    end
end
