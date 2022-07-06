require_relative "_parser_helpers";

describe Parser do
    context "on arithmetic" do
        it "parses arithmetic expressions" do
            parse("(x = 6 + 3)");
            parse("(x = 6 - 3)");
            parse("(x = 6 * 3)");
            parse("(x = 1 + 2 * 3)");
            parse("(x = 5 / 3)");
            parse("(x = 5.0 / 3.0)");
            parse("(x = 5.0 // 3.0)");
            parse("(x = 5.0 rem: 3.0)");
            parse("(x = -5)");
            parse("(x = 5 sign)");
            parse("(x = 5 negated)");
            parse("(x = 1.2 integer_part)");  # 1.0
            parse("(x = 1.2 fraction_part)"); # 0.2
            parse("(x = 5 reciprocal)");
            parse("(x = 6 * 3.1)"); # Converts to Float
            parse("(x = 5 squared)");
            parse("(x = 25 sqrt)");
            parse("(x = 5 raised_to: 2)");
            parse("(x = 5 raised_to_integer: 2)");
            parse("(x = 5 exp)");
            parse("(x = -5 abs)");
            parse("(x = 3.99 rounded)");
            parse("(x = 3.99 truncated)");
            parse("(x = 3.99 rount_to: 1)");
            parse("(x = 3.99 truncate_to: 1)");
            parse("(x = 3.99 floor)");
            parse("(x = 3.99 ceiling)");
            parse("(x = 5 factorial)");
            parse("(x = -5 quotient: 3)");
            parse("(x = -5 rem: 3)");
            parse("(x = 28 gcd: 12)");
            parse("(x = 28 lcm: 12)");
            parse("(x = 100 ln)");
            parse("(x = 100 log)");
            parse("(x = 100 log: 10)");
            parse("(x = 180 deg_to_rad)");
            parse("(x = 3.14 rad_to_deg)");
            parse("(x = 0.7 sin)");
            parse("(x = 0.7 cos)");
            parse("(x = 0.7 tan)");
            parse("(x = 0.7 arcsin)");
            parse("(x = 0.7 arccos)");
            parse("(x = 0.7 arctan)");
            parse("(x = (10 20) max)");
            parse("(x = (10 20) min)");
            parse("(x = (0 100) random)");

            parse("(x = Float PI)");
            parse("(x = Float E)");
            parse("(x = Float INF)");
            parse("(x = Float NAN)");
        end
    end
end
