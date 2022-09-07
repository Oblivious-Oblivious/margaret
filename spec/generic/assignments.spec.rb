describe Parser do
    context "on assignments" do
        it "parses assignments" do
            parse("(x = 4)", "(= x 4)");
            parse("(x = y = z = 6)", "(= x (= y (= z 6)))");
            parse("(x = (y = 6) + 1)", "(= x + (= y 6) 1)");
            parse("(x = Object new)", "(= x new Object)");
            parse("var = 12", "= var 12");
            parse("arr = []", "= arr []");
            parse("@x = x + 2", "= @x + x 2");
            parse("a = b", "= a b");
            parse("a = b = c", "= a (= b c)");
            parse("a = b = c = d = 42", "= a (= b (= c (= d 42)))");
            parse("(a = 2, b = 3, c = a = b)", "(= a 2, = b 3, = c (= a b))");
            parse("((a = 2), (b = 3), (c = a = b))", "((= a 2), (= b 3), (= c (= a b)))");
            parse("a = b = (c = 42) + 12", "= a (= b + (= c 42) 12)");
            parse("a = 12 + 3 * 4", "= a * (+ 12 3) 4");
        end

        it "parses assignments as a plain message on non assignable values" do
            parse("[a, b, c] = [1, 2, 3]", "= [a, b, c] [1, 2, 3]");
            parse("a = 3 + 4", "= a + 3 4");
            parse("2 = 3 + 4", "+ (= 2 3) 4");
        end
    end
end
