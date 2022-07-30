require_relative "_parser_helpers";

describe Parser do
    context "on booleans" do
        it "parses boolean methods" do
            parse("(b = (2 == 3))", "(= b (== 2 3))");
            parse("(b = 2 dosth!)", "(= b (dosth! 2))");
            parse("(b = (x != y))", "(= b (!= x y))");
            parse("(b = (x === y))", "(= b (=== x y))");
            parse("(b = (x !== y))", "(= b (!== x y))");
            parse("(b = (x > y))", "(= b (> x y))");
            parse("(b = (x < y))", "(= b (< x y))");
            parse("(b = (x >= y))", "(= b (>= x y))");
            parse("(b = (x <= y))", "(= b (<= x y))");
            parse("(b = b not)", "(= b (not b))");
            parse("(b = (x < 5) && (y > 1))", "(= b (&& ((< x 5)) (> y 1)))");
            parse("(b = (x < 5) || (y > 1))", "(= b (|| ((< x 5)) (> y 1)))");
            parse("(b = (x < 5) and: (y > 1))", "(= b (and: ((< x 5)) (> y 1)))");
            parse("(b = (x < 5) or: (y > 1))", "(= b (or: ((< x 5)) (> y 1)))");
            parse("(b = (x < 5) eqv: (y > 1))", "(= b (eqv: ((< x 5)) (> y 1)))");
            parse("(b = (x < 5) xor: (y > 1))", "(= b (xor: ((< x 5)) (> y 1)))");
            parse("(b = 5 between: 3 and: 12)", "(= b (between:and: 5 3 12))");
            parse("(b = 123 is_kind_of: Number)", "(= b (is_kind_of: 123 Number))");
            parse("(b = 123 is_member_of: SmallInteger)", "(= b (is_member_of: 123 SmallInteger))");
            parse(%Q{(b = 123 responds_to: "sqrt")}, %Q{(= b (responds_to: 123 "sqrt"))});
            parse("(b = x is_nil?)", "(= b (is_nil? x))");
            parse("(b = x is_zero?)", "(= b (is_zero? x))");
            parse("(b = x is_positive?)", "(= b (is_positive? x))");
            parse("(b = x is_negative?)", "(= b (is_negative? x))");
            parse("(b = x is_even?)", "(= b (is_even? x))");
            parse("(b = x is_odd?)", "(= b (is_odd? x))");
            parse("(b = x is_integer?)", "(= b (is_integer? x))");
            parse("(b = x is_float?)", "(= b (is_float? x))");
            parse("(b = x is_number?)", "(= b (is_number? x))");
            parse("(b = 'a' is_uppercase?)", "(= b (is_uppercase? 'a'))");
            parse("(b = 'a' is_lowercase?)", "(= b (is_lowercase? 'a'))");
        end
    end
end
