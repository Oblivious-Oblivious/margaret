require_relative "_parser_helpers";

describe Parser do
    context "on assignments" do
        it "parses assignments" do
            parse("(x = 4)", "(= x 4)");
            parse("(x = y = z = 6)", "(= x (= y (= z 6)))");
            parse("(x = (y = 6) + 1)", "(= x (+ ((= y 6)) 1))");
            parse("(x = Object new)", "(= x (new Object))");
        end
    end
end
