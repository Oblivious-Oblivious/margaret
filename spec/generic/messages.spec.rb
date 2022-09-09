describe Parser do
    context "on message types" do
        it "parses unary messages" do
            parse("42 factorial", ["push_integer", "42", "unary", "factorial"]);
            parse("17 incr puts", ["push_integer", "17", "unary", "incr", "unary", "puts"]);
            parse("23 one two three", ["push_integer", "23", "unary", "one", "unary", "two", "unary", "three"]);
            parse("@inst one two three", ["push_instance", "inst", "unary", "one", "unary", "two", "unary", "three"]);
            parse("42 puts", ["push_integer", "42", "unary", "puts"]);
            parse("obj puts", ["push_variable", "obj", "unary", "puts"]);
            parse("x = (obj puts)", ["push_variable", "obj", "unary", "puts", "store", "x"]);
            parse("(obj puts, 42 incr)", ["push_variable", "obj", "unary", "puts", "push_integer", "42", "unary", "incr"]);
            parse("((obj puts), (42 incr))", ["push_variable", "obj", "unary", "puts", "push_integer", "42", "unary", "incr"]);
            parse("42 incr incr decr decr", ["push_integer", "42", "unary", "incr", "unary", "incr", "unary", "decr", "unary", "decr"]);
            parse("x = 42 incr incr decr decr", ["push_integer", "42", "unary", "incr", "unary", "incr", "unary", "decr", "unary", "decr", "store", "x"]);
            parse("x incr!", ["push_variable", "x", "unary", "incr!"]);
            parse("x is_empty?", ["push_variable", "x", "unary", "is_empty?"]);
            parse("(42 one, 43 two, 44 three, 45, 46 four)", ["push_integer", "42", "unary", "one", "push_integer", "43", "unary", "two", "push_integer", "44", "unary", "three", "push_integer", "45", "push_integer", "46", "unary", "four"]);
            parse("p1 + p2 calc puts", ["push_variable", "p1", "push_variable", "p2", "unary", "calc", "unary", "puts", "binary", "+"]);
            parse("(p1 + p2 calc) puts", ["push_variable", "p1", "push_variable", "p2", "unary", "calc", "binary", "+", "unary", "puts"]);
        end
    
        it "parses binary messages" do
            parse("2 + 3", ["push_2", "push_integer", "3", "binary", "+"]);
            parse("2 + 3 + 4 + 5", ["push_2", "push_integer", "3", "binary", "+", "push_integer", "4", "binary", "+", "push_integer", "5", "binary", "+"]);
            parse("2 * 5", ["push_2", "push_integer", "5", "binary", "*"]);
            parse("a + b", ["push_variable", "a", "push_variable", "b", "binary", "+"]);
            parse("42 factorial + 17", ["push_integer", "42", "unary", "factorial", "push_integer", "17", "binary", "+"]);
            parse("41 factorial + 42 factorial + 43 factorial", ["push_integer", "41", "unary", "factorial", "push_integer", "42", "unary", "factorial", "binary", "+", "push_integer", "43", "unary", "factorial", "binary", "+"]);
            parse("(41 + 1, 42 + 0, 43 - 1)", ["push_integer", "41", "push_1", "binary", "+", "push_integer", "42", "push_0", "binary", "+", "push_integer", "43", "push_1", "binary", "-"]);
            parse("((41 + 1), (42 + 0), (43 - 1))", ["push_integer", "41", "push_1", "binary", "+", "push_integer", "42", "push_0", "binary", "+", "push_integer", "43", "push_1", "binary", "-"]);
            parse("x = a + b * 2 - 5", ["push_variable", "a", "push_variable", "b", "binary", "+", "push_2", "binary", "*", "push_integer", "5", "binary", "-", "store", "x"]);
            parse("x << item", ["push_variable", "x", "push_variable", "item", "binary", "<<"]);
            parse("x <<>>+-++-- 15", ["push_variable", "x", "push_integer", "15", "binary", "<<>>+-++--"]);
            parse("[1, 2, 3] ++ [4, 5]", ["push_1", "push_2", "push_integer", "3", "push_tensor", "3", "push_integer", "4", "push_integer", "5", "push_tensor", "2", "binary", "++"]);
            parse("(4 + 3) * (5 + 6)", ["push_integer", "4", "push_integer", "3", "binary", "+", "push_integer", "5", "push_integer", "6", "binary", "+", "binary", "*"]);
        end
    
        it "parses keyword messages" do
            parse("list put: 42 at: 5", ["push_variable", "list", "push_integer", "42", "push_integer", "5", "keyword", "put:at:", "2"]);
            parse("list put: (42 incr) at: 5", ["push_variable", "list", "push_integer", "42", "unary", "incr", "push_integer", "5", "keyword", "put:at:", "2"]);
            parse("(
                list = List new,
                list put: 42 at: 5,
                x = list get: 2,
                x puts
            )", ["push_variable", "List", "unary", "new", "store", "list", "push_variable", "list", "push_integer", "42", "push_integer", "5", "keyword", "put:at:", "2", "push_variable", "list", "push_2", "keyword", "get:", "1", "store", "x", "push_variable", "x", "unary", "puts"]);
            parse("2 + 3 incr add: 11", ["push_2", "push_integer", "3", "unary", "incr", "binary", "+", "push_integer", "11", "keyword", "add:", "1"]);
            parse("(1, 2, 3) reverse!: true", ["push_1", "push_2", "push_integer", "3", "push_true", "keyword", "reverse!:", "1"]);
            parse("true then: 1 else: 2", ["push_true", "push_1", "push_2", "keyword", "then:else:", "2"]);
            parse("x ok?: true otherwise!: false", ["push_variable", "x", "push_true", "push_false", "keyword", "ok?:otherwise!:", "2"]);
            parse("(5 + 13) greater_than?: (11 + 2)", ["push_integer", "5", "push_integer", "13", "binary", "+", "push_integer", "11", "push_2", "binary", "+", "keyword", "greater_than?:", "1"]);
            parse("42 factorial and: (2 + 3)", ["push_integer", "42", "unary", "factorial", "push_2", "push_integer", "3", "binary", "+", "keyword", "and:", "1"]);
            parse("(list at: 3) + (list at: 5)", ["push_variable", "list", "push_integer", "3", "keyword", "at:", "1", "push_variable", "list", "push_integer", "5", "keyword", "at:", "1", "binary", "+"]);
        end

        it "chains keyword messages of exactly the same selector" do
            parse("arr add: 1 add: 2 add: 3", ["push_variable", "arr", "push_1", "keyword", "add:", "1", "push_variable", "arr", "push_2", "keyword", "add:", "1", "push_variable", "arr", "push_integer", "3", "keyword", "add:", "1"]);
            parse("arr add: 'a' add: 'b' at: 3", ["push_variable", "arr", "push_char", "'a'", "push_char", "'b'", "push_integer", "3", "keyword", "add:add:at:", "3"]);
            parse("arr add: 'a' at: 1 add: 'b' at: 2", ["push_variable", "arr", "push_char", "'a'", "push_1", "push_char", "'b'", "push_2", "keyword", "add:at:add:at:", "4"]);
        end

        it "parses composit messages" do
            parse("3 factorial + 4 factorial between: 10 and: 100", ["push_integer", "3", "unary", "factorial", "push_integer", "4", "unary", "factorial", "binary", "+", "push_integer", "10", "push_integer", "100", "keyword", "between:and:", "2"]);
            parse("(
                origin <= point
                    if_true: ->{ out goto }
                    if_false: ->{ false return },
                out = Label new
            )", ["push_variable", "origin", "push_variable", "point", "binary", "<=", "STARTpush_proc", "push_tensor", "0", "push_variable", "out", "unary", "goto", "ENDpush_proc", "STARTpush_proc", "push_tensor", "0", "push_false", "unary", "return", "ENDpush_proc", "keyword", "if_true:if_false:", "2", "push_variable", "Label", "unary", "new", "store", "out"]);
        end
    end
end
