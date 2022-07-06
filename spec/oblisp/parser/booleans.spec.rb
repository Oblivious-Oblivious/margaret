require_relative "_parser_helpers";

describe Parser do
    context "on booleans" do
        it "parses boolean methods" do
            parse("(b = (x == y))");
            parse("(b = (x != y))");
            parse("(b = (x === y))");
            parse("(b = (x !== y))");
            parse("(b = (x > y))");
            parse("(b = (x < y))");
            parse("(b = (x >= y))");
            parse("(b = (x <= y))");
            parse("(b = b not)");
            parse("(b = (x < 5) && (y > 1))");
            parse("(b = (x < 5) || (y > 1))");
            parse("(b = (x < 5) and: (y > 1))");
            parse("(b = (x < 5) or: (y > 1))");
            parse("(b = (x < 5) eqv: (y > 1))");
            parse("(b = (x < 5) xor: (y > 1))");
            parse("(b = 5 between: 3 and: 12)");
            parse("(b = 123 is_kind_of: Number)");
            parse("(b = 123 is_member_of: SmallInteger)");
            parse(%Q{(b = 123 responds_to: "sqrt")});
            parse("(b = x is_nil?)");
            parse("(b = x is_zero?)");
            parse("(b = x is_positive?)");
            parse("(b = x is_negative?)");
            parse("(b = x is_even?)");
            parse("(b = x is_odd?)");
            parse("(b = x is_integer?)");
            parse("(b = x is_float?)");
            parse("(b = x is_number?)");
            parse(%Q{(b = x "is_uppercase?")});
            parse(%Q{(b = x "is_lowercase?")});
        end
    end
end
