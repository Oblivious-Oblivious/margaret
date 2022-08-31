require_relative "_parser_helpers";

describe Parser do
    context "on tensors" do
        it "parses tensor literals" do
            parse("[]", "new Tensor ()");
            parse("([])", "(new Tensor ())");
            parse("[[], []]", "new Tensor (new Tensor (), new Tensor ())");
            parse("[41, 42]", "new Tensor (41, 42)");
            parse("([41, 42])", "(new Tensor (41, 42))");
            parse(%Q{[42, "str", var]}, %Q{new Tensor (42, "str", var)});
            error("[", "missing closing bracket on tensor.");
            error("]", "missing opening bracket on tensor.");
            parse(%Q{[42, "Hello", 'x', v1, v2]}, %Q{new Tensor (42, "Hello", 'x', v1, v2)});
            parse(%Q{[42, "Hello", 'x', v1, v2, (), [], {}, x = 1]}, %Q{new Tensor (42, "Hello", 'x', v1, v2, (), new Tensor (), new Hash (), = x 1)});
        end
    end
end
