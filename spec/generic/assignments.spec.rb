describe Parser do
    context "on assignments" do
        it "parses assignments" do
            parse("(x = 4)", ["push_integer", "4", "store", "x"]);
            parse("(x = y = z = 6)", ["push_integer", "6", "store", "z", "store", "y", "store", "x"]);
            parse("(x = (y = 6) + 1)", ["push_integer", "6", "store", "y", "push_1", "binary", "+", "store", "x"]);
            parse("(x = Object new)", ["push_variable", "Object", "unary", "new", "store", "x"]);
            parse("var = 12", ["push_integer", "12", "store", "var"]);
            parse("arr = []", ["push_tensor", "0", "store", "arr"]);
            parse("@x = x + 2", ["push_variable", "x", "push_2", "binary", "+", "store_instance", "x"]);
            parse("a = b", ["push_variable", "b", "store", "a"]);
            parse("a = b = c", ["push_variable", "c", "store", "b", "store", "a"]);
            parse("a = b = c = d = 42", ["push_integer", "42", "store", "d", "store", "c", "store", "b", "store", "a"]);
            parse("(a = 2, b = 3, c = a = b)", ["push_2", "store", "a", "push_integer", "3", "store", "b", "push_variable", "b", "store", "a", "store", "c"]);
            parse("((a = 2), (b = 3), (c = a = b))", ["push_2", "store", "a", "push_integer", "3", "store", "b", "push_variable", "b", "store", "a", "store", "c"]);
            parse("a = b = (c = 42) + 12", ["push_integer", "42", "store", "c", "push_integer", "12", "binary", "+", "store", "b", "store", "a"]);
            parse("a = 12 + 3 * 4", ["push_integer", "12", "push_integer", "3", "binary", "+", "push_integer", "4", "binary", "*", "store", "a"]);
        end

        it "parses assignments as a plain message on non assignable values" do
            parse("[a, b, c] = [1, 2, 3]", ["push_variable", "a", "push_variable", "b", "push_variable", "c", "push_tensor", "3", "push_1", "push_2", "push_integer", "3", "push_tensor", "3", "binary", "="]);
            parse("a = 3 + 4", ["push_integer", "3", "push_integer", "4", "binary", "+", "store", "a"]);
            parse("2 = 3 + 4", ["push_2", "push_integer", "3", "binary", "=", "push_integer", "4", "binary", "+"]);
        end
    end
end
