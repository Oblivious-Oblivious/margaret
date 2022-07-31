require_relative "_parser_helpers";

describe Parser do
    context "on arithmetic" do
        it "parses arithmetic expressions" do
            parse("(x = 6 + 3)", "(= x (+ 6 3))");
            parse("(x = 6 - 3)", "(= x (- 6 3))");
            parse("(x = 6 * 3)", "(= x (* 6 3))");
            parse("(x = 1 + 2 * 3)", "(= x (* (+ 1 2) 3))");
            parse("(x = 5 / 3)", "(= x (/ 5 3))");
            parse("(x = 5.0 / 3.0)", "(= x (/ 5.0 3.0))");
            parse("(x = 5.0 // 3.0)", "(= x (// 5.0 3.0))");
            parse("(x = 5.0 rem: 3.0)", "(= x (rem: 5.0 3.0))");
            parse("(x = -5)", "(= x -5)");
            parse("(x = 5 sign)", "(= x (sign 5))");
            parse("(x = 5 negated)", "(= x (negated 5))");
            parse("(x = 1.2 integer_part)", "(= x (integer_part 1.2))");  # 1.0
            parse("(x = 1.2 fraction_part)", "(= x (fraction_part 1.2))"); # 0.2
            parse("(x = 5 reciprocal)", "(= x (reciprocal 5))");
            parse("(x = 6 * 3.1)", "(= x (* 6 3.1))"); # Converts to Float
            parse("(x = 5 squared)", "(= x (squared 5))");
            parse("(x = 25 sqrt)", "(= x (sqrt 25))");
            parse("(x = 5 raised_to: 2)", "(= x (raised_to: 5 2))");
            parse("(x = 5 raised_to_integer: 2)", "(= x (raised_to_integer: 5 2))");
            parse("(x = 5 exp)", "(= x (exp 5))");
            parse("(x = -5 abs)", "(= x (abs -5))");
            parse("(x = 3.99 rounded)", "(= x (rounded 3.99))");
            parse("(x = 3.99 truncated)", "(= x (truncated 3.99))");
            parse("(x = 3.99 round_to: 1)", "(= x (round_to: 3.99 1))");
            parse("(x = 3.99 truncate_to: 1)", "(= x (truncate_to: 3.99 1))");
            parse("(x = 3.99 floor)", "(= x (floor 3.99))");
            parse("(x = 3.99 ceiling)", "(= x (ceiling 3.99))");
            parse("(x = 5 factorial)", "(= x (factorial 5))");
            parse("(x = -5 quotient: 3)", "(= x (quotient: -5 3))");
            parse("(x = -5 rem: 3)", "(= x (rem: -5 3))");
            parse("(x = 28 gcd: 12)", "(= x (gcd: 28 12))");
            parse("(x = 28 lcm: 12)", "(= x (lcm: 28 12))");
            parse("(x = 100 ln)", "(= x (ln 100))");
            parse("(x = 100 log)", "(= x (log 100))");
            parse("(x = 100 log: 10)", "(= x (log: 100 10))");
            parse("(x = 180 deg_to_rad)", "(= x (deg_to_rad 180))");
            parse("(x = 3.14 rad_to_deg)", "(= x (rad_to_deg 3.14))");
            parse("(x = 0.7 sin)", "(= x (sin 0.7))");
            parse("(x = 0.7 cos)", "(= x (cos 0.7))");
            parse("(x = 0.7 tan)", "(= x (tan 0.7))");
            parse("(x = 0.7 arcsin)", "(= x (arcsin 0.7))");
            parse("(x = 0.7 arccos)", "(= x (arccos 0.7))");
            parse("(x = 0.7 arctan)", "(= x (arctan 0.7))");
            parse("(x = (10 20) max)", "(= x (max ((10 20))))");
            parse("(x = (10 20) min)", "(= x (min ((10 20))))");
            parse("(x = (0 100) random)", "(= x (random ((0 100))))");

            parse("(x = Float PI)", "(= x (PI Float))");
            parse("(x = Float E)", "(= x (E Float))");
            parse("(x = Float INF)", "(= x (INF Float))");
            parse("(x = Float NAN)", "(= x (NAN Float))");
        end
    end
end
