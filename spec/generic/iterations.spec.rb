describe Parser do
    context "on iterations" do
        it "parses iteration statements" do
            parse("(x > 0 while_true: (x = x - 1, y = y * 2))", ["push_variable", "x", "push_0", "binary", ">", "push_variable", "x", "push_1", "binary", "-", "store", "x", "push_variable", "y", "push_2", "binary", "*", "store", "y", "keyword", "while_true:", "1"]);
            parse("(x >= 0 while_false: (x = x + 1, y = y * 2))", ["push_variable", "x", "push_0", "binary", ">=", "push_variable", "x", "push_1", "binary", "+", "store", "x", "push_variable", "y", "push_2", "binary", "*", "store", "y", "keyword", "while_false:", "1"]);
            parse("(x times: (y = y * 2))", ["push_variable", "x", "push_variable", "y", "push_2", "binary", "*", "store", "y", "keyword", "times:", "1"]);
            parse("(1 to: 5 do: (y = y * 2))", ["push_1", "push_integer", "5", "push_variable", "y", "push_2", "binary", "*", "store", "y", "keyword", "to:do:", "2"]);
            parse("(1 to: 5 by: 2 do: (y = y / 2))", ["push_1", "push_integer", "5", "push_2", "push_variable", "y", "push_2", "binary", "/", "store", "y", "keyword", "to:by:do:", "3"]);
            parse("[1,2,3,4] each: ->{ item | x = x + item }", ["push_1", "push_2", "push_integer", "3", "push_integer", "4", "push_tensor", "4", "STARTpush_proc", "push_variable", "item", "push_tensor", "1", "push_variable", "x", "push_variable", "item", "binary", "+", "store", "x", "ENDpush_proc", "keyword", "each:", "1"]);
        end
    end
end
