describe Parser do
    context "on associations hashes" do
        it "parses hash literals" do
            parse("({})", ["push_hash", "0"]);
            parse("({a: {}, b: {}})", ["push_variable", "Association", "push_string", %Q{"a"}, "push_hash", "0", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_hash", "0", "keyword", "key:value:", "2", "push_hash", "2"]);
            parse("({a: 1, b: 2, c: 3})", ["push_variable", "Association", "push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3"]);
            parse(%Q{{"a": 1, "b": 2, "c": 3}}, ["push_variable", "Association", "push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3"]);
            parse(%Q{({"k1": "v1", "k2": "v2", "k3": "v3"})}, ["push_variable", "Association", "push_string", %Q{"k1"}, "push_string", %Q{"v1"}, "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"k2"}, "push_string", %Q{"v2"}, "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"k3"}, "push_string", %Q{"v3"}, "keyword", "key:value:", "2", "push_hash", "3"]);
            parse("{x: {a: 1, b: 2}, y: {c: 3, d: 4}}", ["push_variable", "Association", "push_string", %Q{"x"}, "push_variable", "Association", "push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_hash", "2", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"y"}, "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"d"}, "push_integer", "4", "keyword", "key:value:", "2", "push_hash", "2", "keyword", "key:value:", "2", "push_hash", "2"]);
            parse("{a: 42 factorial, b: 2 + 3, c: 41 plus: 1, d: (42 incr decr, 41 incr)}", ["push_variable", "Association", "push_string", %Q{"a"}, "push_integer", "42", "unary", "factorial", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "push_integer", "3", "binary", "+", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "41", "push_1", "keyword", "plus:", "1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"d"}, "push_integer", "42", "unary", "incr", "unary", "decr", "push_integer", "41", "unary", "incr", "keyword", "key:value:", "2", "push_hash", "4"]);
        end

        it "parses hashes" do
            parse(%Q{(x at: 'a' put: 3)}, ["push_variable", "x", "push_char", "'a'", "push_integer", "3", "keyword", "at:put:", "2"]);
            parse("(x is_empty?)", ["push_variable", "x", "unary", "is_empty?"]);
            parse("(x size)", ["push_variable", "x", "unary", "size"]);
            parse(%Q{(x at: "a" if_absent: "")}, ["push_variable", "x", "push_string", %Q{"a"}, "push_string", %Q{""}, "keyword", "at:if_absent:", "2"]);
            parse(%Q{(x key_at_value: 3 if_absent: "")}, ["push_variable", "x", "push_integer", "3", "push_string", %Q{""}, "keyword", "key_at_value:if_absent:", "2"]);
            parse(%Q{(x remove_key: "e" if_absent: "")}, ["push_variable", "x", "push_string", %Q{"e"}, "push_string", %Q{""}, "keyword", "remove_key:if_absent:", "2"]);
            parse(%Q{(b = x includes_key: "a")}, ["push_variable", "x", "push_string", %Q{"a"}, "keyword", "includes_key:", "1", "store", "b"]);
            parse("(x keys puts)", ["push_variable", "x", "unary", "keys", "unary", "puts"]);
            parse("(x values puts)", ["push_variable", "x", "unary", "values", "unary", "puts"]);
            parse("(x each_key: ->{a | a puts})", ["push_variable", "x", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "unary", "puts", "ENDpush_proc", "keyword", "each_key:", "1"]);
            parse("(x each_value: ->{a | a puts})", ["push_variable", "x", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "unary", "puts", "ENDpush_proc", "keyword", "each_value:", "1"]);
            parse("(x each: ->{a | a puts})", ["push_variable", "x", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "unary", "puts", "ENDpush_proc", "keyword", "each:", "1"]); # Prints hash associations
        end
    end
end
