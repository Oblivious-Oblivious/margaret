require_relative "_parser_helpers";

describe Parser do
    context "on tuples" do
        it "parses tuple literals" do
            parse("[]", "new Tuple ()");
            parse("([])", "(new Tuple ())");
            parse("[[], []]", "new Tuple (new Tuple (), new Tuple ())");
            parse("[41, 42]", "new Tuple (41, 42)");
            parse("([41, 42])", "(new Tuple (41, 42))");
            parse(%Q{[42, "str", var]}, %Q{new Tuple (42, "str", var)});
            error("[", "missing closing bracket on tuple.");
            error("]", "missing opening bracket on tuple.");
            parse(%Q{[42, "Hello", 'x', :ok, v1, v2]}, %Q{new Tuple (42, "Hello", 'x', :"ok", v1, v2)});
            parse(%Q{[42, "Hello", 'x', :ok, v1, v2, (), [], {}, x = 1]}, %Q{new Tuple (42, "Hello", 'x', :"ok", v1, v2, (), new Tuple (), new Hash (), = x 1)});
        end
    end
end
