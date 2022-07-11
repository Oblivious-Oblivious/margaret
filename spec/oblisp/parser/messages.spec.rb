require_relative "_parser_helpers";

describe Parser do
    context "on message types" do
        it "parses unary messages" do
            parse("(42 puts)", "(puts 42)");
            parse("(obj puts)", "(puts obj)");
            parse("(x = obj puts)", "(= x (puts obj))");
            parse("((obj puts) (42 incr))", "((puts obj) (incr 42))");
            parse("(42 incr incr decr decr)", "(decr (decr (incr (incr 42))))");
            parse("(x = 42 incr incr decr decr)", "(= x (decr (decr (incr (incr 42)))))");
        end

        it "parses binary messages" do
            parse("(2 + 3)", "(+ 2 3)");
            parse("(2 * 5)", "(* 2 5)");
            parse("(a + b)", "(+ a b)");
            parse("(x = a + b * 2 - 5)", "(= x (- (* (+ a b) 2) 5))");
        end

        it "parses keyword messages" do
            parse("(list put: 42 at: 5)", "(put:at: list 42 5)");
            parse("(list put: (42 incr) at: 5)", "(put:at: list (incr 42) 5)");
            parse("(
                (list = List new)
                (list put: 42 at: 5)
                (x = list get: 2)
                (x puts)
            )", "((= list (new List)) (put:at: list 42 5) (= x (get: list 2)) (puts x))");
        end
    end
end
