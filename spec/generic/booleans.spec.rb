describe Parser do
    context "on booleans" do
        it "parses boolean methods" do
            parse("(b = 2 == 3)", ["push_2", "push_integer", "3", "binary", "==", "store", "b"]);
            parse("(b = 2 dosth!)", ["push_2", "unary", "dosth!", "store", "b"]);
            parse("(b = x != y)", ["push_variable", "x", "push_variable", "y", "binary", "!=", "store", "b"]);
            parse("(b = x === y)", ["push_variable", "x", "push_variable", "y", "binary", "===", "store", "b"]);
            parse("(b = x !== y)", ["push_variable", "x", "push_variable", "y", "binary", "!==", "store", "b"]);
            parse("(b = x > y)", ["push_variable", "x", "push_variable", "y", "binary", ">", "store", "b"]);
            parse("(b = x < y)", ["push_variable", "x", "push_variable", "y", "binary", "<", "store", "b"]);
            parse("(b = x >= y)", ["push_variable", "x", "push_variable", "y", "binary", ">=", "store", "b"]);
            parse("(b = x <= y)", ["push_variable", "x", "push_variable", "y", "binary", "<=", "store", "b"]);
            parse("(b = b not)", ["push_variable", "b", "unary", "not", "store", "b"]);
            parse("(b = (x < 5) && (y > 1))", ["push_variable", "x", "push_integer", "5", "binary", "<", "push_variable", "y", "push_1", "binary", ">", "binary", "&&", "store", "b"]);
            parse("(b = (x < 5) || (y > 1))", ["push_variable", "x", "push_integer", "5", "binary", "<", "push_variable", "y", "push_1", "binary", ">", "binary", "||", "store", "b"]);
            parse("(b = (x < 5) and: (y > 1))", ["push_variable", "x", "push_integer", "5", "binary", "<", "push_variable", "y", "push_1", "binary", ">", "keyword", "and:", "1", "store", "b"]);
            parse("(b = (x < 5) or: (y > 1))", ["push_variable", "x", "push_integer", "5", "binary", "<", "push_variable", "y", "push_1", "binary", ">", "keyword", "or:", "1", "store", "b"]);
            parse("(b = (x < 5) eqv: (y > 1))", ["push_variable", "x", "push_integer", "5", "binary", "<", "push_variable", "y", "push_1", "binary", ">", "keyword", "eqv:", "1", "store", "b"]);
            parse("(b = (x < 5) xor: (y > 1))", ["push_variable", "x", "push_integer", "5", "binary", "<", "push_variable", "y", "push_1", "binary", ">", "keyword", "xor:", "1", "store", "b"]);
            parse("(b = 5 between: 3 and: 12)", ["push_integer", "5", "push_integer", "3", "push_integer", "12", "keyword", "between:and:", "2", "store", "b"]);
            parse("(b = 123 is_kind_of: Number)", ["push_integer", "123", "push_variable", "Number", "keyword", "is_kind_of:", "1", "store", "b"]);
            parse("(b = 123 is_member_of: SmallInteger)", ["push_integer", "123", "push_variable", "SmallInteger", "keyword", "is_member_of:", "1", "store", "b"]);
            parse(%Q{(b = 123 responds_to: "sqrt")}, ["push_integer", "123", "push_string", %Q{"sqrt"}, "keyword", "responds_to:", "1", "store", "b"]);
            parse("(b = x is_nil?)", ["push_variable", "x", "unary", "is_nil?", "store", "b"]);
            parse("(b = x is_zero?)", ["push_variable", "x", "unary", "is_zero?", "store", "b"]);
            parse("(b = x is_positive?)", ["push_variable", "x", "unary", "is_positive?", "store", "b"]);
            parse("(b = x is_negative?)", ["push_variable", "x", "unary", "is_negative?", "store", "b"]);
            parse("(b = x is_even?)", ["push_variable", "x", "unary", "is_even?", "store", "b"]);
            parse("(b = x is_odd?)", ["push_variable", "x", "unary", "is_odd?", "store", "b"]);
            parse("(b = x is_integer?)", ["push_variable", "x", "unary", "is_integer?", "store", "b"]);
            parse("(b = x is_float?)", ["push_variable", "x", "unary", "is_float?", "store", "b"]);
            parse("(b = x is_number?)", ["push_variable", "x", "unary", "is_number?", "store", "b"]);
            parse("(b = 'a' is_uppercase?)", ["push_char", "'a'", "unary", "is_uppercase?", "store", "b"]);
            parse("(b = 'a' is_lowercase?)", ["push_char", "'a'", "unary", "is_lowercase?", "store", "b"]);
        end
    end
end
