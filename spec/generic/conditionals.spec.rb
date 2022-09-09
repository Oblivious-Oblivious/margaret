describe Parser do
    context "on conditionals" do
        it "parses conditional statements" do
            parse("(x > 10 + 42)", ["push_variable", "x", "push_integer", "10", "binary", ">", "push_integer", "42", "binary", "+"]);
            parse("(x > 10 if_true: 42)", ["push_variable", "x", "push_integer", "10", "binary", ">", "push_integer", "42", "keyword", "if_true:", "1"]);
            parse("(x > 10 if_false: 41)", ["push_variable", "x", "push_integer", "10", "binary", ">", "push_integer", "41", "keyword", "if_false:", "1"]);
            parse("(x > 10
                    if_true: 42
                    if_false: 41)", ["push_variable", "x", "push_integer", "10", "binary", ">", "push_integer", "42", "push_integer", "41", "keyword", "if_true:if_false:", "2"]);
            parse("(x > 10
                    if_true: (
                        x > 5
                            if_true: 1
                            if_false: 2
                    )
                    if_false: 3
            )", ["push_variable", "x", "push_integer", "10", "binary", ">", "push_variable", "x", "push_integer", "5", "binary", ">", "push_1", "push_2", "keyword", "if_true:if_false:", "2", "push_integer", "3", "keyword", "if_true:if_false:", "2"]);
            parse("(obj match: [
                        [1, 100],
                        [2, 200],
                        [3, 300],
                    ]
            )", ["push_variable", "obj", "push_1", "push_integer", "100", "push_tensor", "2", "push_2", "push_integer", "200", "push_tensor", "2", "push_integer", "3", "push_integer", "300", "push_tensor", "2", "push_tensor", "3", "keyword", "match:", "1"]);
            parse(%Q{obj match: {"1": 100, "2": 200, "3": 300}}, ["push_variable", "obj", "push_variable", "Association", "push_string", %Q{"1"}, "push_integer", "100", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"2"}, "push_integer", "200", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"3"}, "push_integer", "300", "keyword", "key:value:", "2", "push_hash", "3", "keyword", "match:", "1"]);
        end
    end
end
