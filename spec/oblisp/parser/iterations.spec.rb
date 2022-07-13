require_relative "_parser_helpers";

describe Parser do
    context "on iterations" do
        it "parses iteration statements" do
            parse("((x > 0) while_true: ((x = x - 1) (y = y * 2)))", "(while_true: ((> x 0)) ((= x (- x 1)) (= y (* y 2))))");
            parse("((x >= 0) while_false: ((x = x + 1) (y = y * 2)))", "(while_false: ((>= x 0)) ((= x (+ x 1)) (= y (* y 2))))");
            parse("(x > 0 while_true: ((x = x - 1) (y = y * 2)))", "(while_true: (> x 0) ((= x (- x 1)) (= y (* y 2))))");
            parse("(x >= 0 while_false: ((x = x + 1) (y = y * 2)))", "(while_false: (>= x 0) ((= x (+ x 1)) (= y (* y 2))))");
            parse("(x times: (y = y * 2))", "(times: x (= y (* y 2)))");
            parse("(1 to: 5 do: (y = y * 2))", "(to:do: 1 5 (= y (* y 2)))");
            parse("(1 to: 5 by: 2 do: (y = y / 2))", "(to:by:do: 1 5 2 (= y (/ y 2)))");
            parse("((1 2 3 4) each: [(item) (x = x + item)])", "(each: ((1 2 3 4)) (new Tuple ((item) (= x (+ x item)))))");
        end
    end
end
