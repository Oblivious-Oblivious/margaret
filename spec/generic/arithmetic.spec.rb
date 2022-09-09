describe Parser do
    context "on arithmetic" do
        it "parses arithmetic expressions" do
            parse("(x = 6 + 3)", ["push_integer", "6", "push_integer", "3", "binary", "+", "store", "x"]);
            parse("(x = 6 - 3)", ["push_integer", "6", "push_integer", "3", "binary", "-", "store", "x"]);
            parse("(x = 6 * 3)", ["push_integer", "6", "push_integer", "3", "binary", "*", "store", "x"]);
            parse("(x = 1 + 2 * 3)", ["push_1", "push_2", "binary", "+", "push_integer", "3", "binary", "*", "store", "x"]);
            parse("(x = 5 / 3)", ["push_integer", "5", "push_integer", "3", "binary", "/", "store", "x"]);
            parse("(x = 5.0 / 3.0)", ["push_float", "5.0", "push_float", "3.0", "binary", "/", "store", "x"]);
            parse("(x = 5.0 // 3.0)", ["push_float", "5.0", "push_float", "3.0", "binary", "//", "store", "x"]);
            parse("(x = 5.0 rem: 3.0)", ["push_float", "5.0", "push_float", "3.0", "keyword", "rem:", "1", "store", "x"]);
            parse("(x = -5)", ["push_integer", "-5", "store", "x"]);
            parse("(x = 5 sign)", ["push_integer", "5", "unary", "sign", "store", "x"]);
            parse("(x = 5 negated)", ["push_integer", "5", "unary", "negated", "store", "x"]);
            parse("(x = 1.2 integer_part)", ["push_float", "1.2", "unary", "integer_part", "store", "x"]);  # 1.0
            parse("(x = 1.2 fraction_part)", ["push_float", "1.2", "unary", "fraction_part", "store", "x"]); # 0.2
            parse("(x = 5 reciprocal)", ["push_integer", "5", "unary", "reciprocal", "store", "x"]);
            parse("(x = 6 * 3.1)", ["push_integer", "6", "push_float", "3.1", "binary", "*", "store", "x"]); # Converts to Float
            parse("(x = 5 squared)", ["push_integer", "5", "unary", "squared", "store", "x"]);
            parse("(x = 25 sqrt)", ["push_integer", "25", "unary", "sqrt", "store", "x"]);
            parse("(x = 5 raised_to: 2)", ["push_integer", "5", "push_2", "keyword", "raised_to:", "1", "store", "x"]);
            parse("(x = 5 raised_to_integer: 2)", ["push_integer", "5", "push_2", "keyword", "raised_to_integer:", "1", "store", "x"]);
            parse("(x = 5 exp)", ["push_integer", "5", "unary", "exp", "store", "x"]);
            parse("(x = -5 abs)", ["push_integer", "-5", "unary", "abs", "store", "x"]);
            parse("(x = 3.99 rounded)", ["push_float", "3.99", "unary", "rounded", "store", "x"]);
            parse("(x = 3.99 truncated)", ["push_float", "3.99", "unary", "truncated", "store", "x"]);
            parse("(x = 3.99 round_to: 1)", ["push_float", "3.99", "push_1", "keyword", "round_to:", "1", "store", "x"]);
            parse("(x = 3.99 truncate_to: 1)", ["push_float", "3.99", "push_1", "keyword", "truncate_to:", "1", "store", "x"]);
            parse("(x = 3.99 floor)", ["push_float", "3.99", "unary", "floor", "store", "x"]);
            parse("(x = 3.99 ceiling)", ["push_float", "3.99", "unary", "ceiling", "store", "x"]);
            parse("(x = 5 factorial)", ["push_integer", "5", "unary", "factorial", "store", "x"]);
            parse("(x = -5 quotient: 3)", ["push_integer", "-5", "push_integer", "3", "keyword", "quotient:", "1", "store", "x"]);
            parse("(x = -5 rem: 3)", ["push_integer", "-5", "push_integer", "3", "keyword", "rem:", "1", "store", "x"]);
            parse("(x = 28 gcd: 12)", ["push_integer", "28", "push_integer", "12", "keyword", "gcd:", "1", "store", "x"]);
            parse("(x = 28 lcm: 12)", ["push_integer", "28", "push_integer", "12", "keyword", "lcm:", "1", "store", "x"]);
            parse("(x = 100 ln)", ["push_integer", "100", "unary", "ln", "store", "x"]);
            parse("(x = 100 log)", ["push_integer", "100", "unary", "log", "store", "x"]);
            parse("(x = 100 log: 10)", ["push_integer", "100", "push_integer", "10", "keyword", "log:", "1", "store", "x"]);
            parse("(x = 180 deg_to_rad)", ["push_integer", "180", "unary", "deg_to_rad", "store", "x"]);
            parse("(x = 3.14 rad_to_deg)", ["push_float", "3.14", "unary", "rad_to_deg", "store", "x"]);
            parse("(x = 0.7 sin)", ["push_float", "0.7", "unary", "sin", "store", "x"]);
            parse("(x = 0.7 cos)", ["push_float", "0.7", "unary", "cos", "store", "x"]);
            parse("(x = 0.7 tan)", ["push_float", "0.7", "unary", "tan", "store", "x"]);
            parse("(x = 0.7 arcsin)", ["push_float", "0.7", "unary", "arcsin", "store", "x"]);
            parse("(x = 0.7 arccos)", ["push_float", "0.7", "unary", "arccos", "store", "x"]);
            parse("(x = 0.7 arctan)", ["push_float", "0.7", "unary", "arctan", "store", "x"]);
            parse("(x = [10, 20] max)", ["push_integer", "10", "push_integer", "20", "push_tensor", "2", "unary", "max", "store", "x"]);
            parse("(x = [10, 20] min)", ["push_integer", "10", "push_integer", "20", "push_tensor", "2", "unary", "min", "store", "x"]);
            parse("(x = [0, 100] random)", ["push_0", "push_integer", "100", "push_tensor", "2", "unary", "random", "store", "x"]);

            parse("(x = Float PI)", ["push_variable", "Float", "unary", "PI", "store", "x"]);
            parse("(x = Float E)", ["push_variable", "Float", "unary", "E", "store", "x"]);
            parse("(x = Float INF)", ["push_variable", "Float", "unary", "INF", "store", "x"]);
            parse("(x = Float NAN)", ["push_variable", "Float", "unary", "NAN", "store", "x"]);
        end
    end
end
