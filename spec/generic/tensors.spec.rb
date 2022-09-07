describe Parser do
    context "on tensors" do
        it "parses tensor literals" do
            parse("[]", "[]");
            parse("([])", "([])");
            parse("[[], []]", "[[], []]");
            parse("[41, 42]", "[41, 42]");
            parse("([41, 42])", "([41, 42])");
            parse(%Q{[42, "str", var]}, %Q{[42, "str", var]});
            error("[", "missing closing bracket on tensor.");
            error("]", "missing opening bracket on tensor.");
            parse(%Q{[42, "Hello", 'x', v1, v2]}, %Q{[42, "Hello", 'x', v1, v2]});
            parse(%Q{[42, "Hello", 'x', v1, v2, (), [], {}, x = 1]}, %Q{[42, "Hello", 'x', v1, v2, (), [], {}, = x 1]});
        end
    end
end
