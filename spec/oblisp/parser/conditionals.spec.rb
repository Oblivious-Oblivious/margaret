require_relative "_parser_helpers";

describe Parser do
    context "on conditionals" do
        it "parses conditional statements" do
            parse("(x > 10 + 42)", "(+ (> x 10) 42)");
            parse("(x > 10 if_true: 42)", "(if_true: (> x 10) 42)");
            parse("(x > 10 if_false: 41)", "(if_false: (> x 10) 41)");
            parse("(x > 10
                    if_true: 42
                    if_false: 41)", "(if_true:if_false: (> x 10) 42 41)");
            parse("(x > 10
                    if_true: (
                        x > 5
                            if_true: 1
                            if_false: 2
                    )
                    if_false: 3
            )", "(if_true:if_false: (> x 10) (if_true:if_false: (> x 5) 1 2) 3)");
            # TODO
            # parse("(obj match: (
            #             [1, 100]
            #             [2, 200]
            #             [3, 300]
            #         )
            # )");
        end
    end
end
