describe Parser do
    context "on procs" do
        it "parses procs" do
            parse("-> { x = (x = 1, y = 2) }", ["STARTpush_proc", "push_tensor", "0", "push_1", "store", "x", "push_2", "store", "y", "store", "x", "ENDpush_proc"]); # x = 2
            parse("x = -> {
                v1, v2 | (
                    v1 += 1,
                    v1 += 2,
                    v1 * v2
                )
            }", ["STARTpush_proc", "push_variable", "v1", "push_variable", "v2", "push_tensor", "2", "push_variable", "v1", "push_1", "binary", "+=", "push_variable", "v1", "push_2", "binary", "+=", "push_variable", "v1", "push_variable", "v2", "binary", "*", "ENDpush_proc", "store", "x"]); # v1 * v2
        end

        it "parses parameterized procs and procs returning literals" do
            parse("->{ 42 }", ["STARTpush_proc", "push_tensor", "0", "push_integer", "42", "ENDpush_proc"]);
            parse("->{ a | a puts }", ["STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "unary", "puts", "ENDpush_proc"]);
            parse("->{ 2 + 3 }", ["STARTpush_proc", "push_tensor", "0", "push_2", "push_integer", "3", "binary", "+", "ENDpush_proc"]);
            parse("->{ (x = 1, y = 2, x + y) }", ["STARTpush_proc", "push_tensor", "0", "push_1", "store", "x", "push_2", "store", "y", "push_variable", "x", "push_variable", "y", "binary", "+", "ENDpush_proc"]);
            parse("->{ param | param puts }", ["STARTpush_proc", "push_variable", "param", "push_tensor", "1", "push_variable", "param", "unary", "puts", "ENDpush_proc"]);
            parse("->{ a | a }", ["STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "ENDpush_proc"]);
            parse("->{ x = 2 } eval", ["STARTpush_proc", "push_tensor", "0", "push_2", "store", "x", "ENDpush_proc", "unary", "eval"]);
            parse("->{ param | param puts } value: 42", ["STARTpush_proc", "push_variable", "param", "push_tensor", "1", "push_variable", "param", "unary", "puts", "ENDpush_proc", "push_integer", "42", "keyword", "value:", "1"]);
        end
    end
end
