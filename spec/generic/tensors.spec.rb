describe Parser do
    context "on tensors" do
        it "parses tensor literals" do
            parse("[]", ["push_tensor", "0"]);
            parse("([])", ["push_tensor", "0"]);
            parse("[[], []]", ["push_tensor", "0", "push_tensor", "0", "push_tensor", "2"]);
            parse("[41, 42]", ["push_integer", "41", "push_integer", "42", "push_tensor", "2"]);
            parse("([41, 42])", ["push_integer", "41", "push_integer", "42", "push_tensor", "2"]);
            parse(%Q{[42, "str", var]}, ["push_integer", "42", "push_string", %Q{"str"}, "push_variable", "var", "push_tensor", "3"]);
            error("[", "missing closing bracket on tensor.");
            error("]", "missing opening bracket on tensor.");
            parse(%Q{[42, "Hello", 'x', v1, v2]}, ["push_integer", "42", "push_string", %Q{"Hello"}, "push_char", "'x'", "push_variable", "v1", "push_variable", "v2", "push_tensor", "5"]);
            parse(%Q{[42, "Hello", 'x', v1, v2, (), [], {}, x = 1]}, ["push_integer", "42", "push_string", %Q{"Hello"}, "push_char", "'x'", "push_variable", "v1", "push_variable", "v2", "push_tensor", "0", "push_hash", "0", "push_1", "store", "x", "push_tensor", "9"]);
        end
    end
end
