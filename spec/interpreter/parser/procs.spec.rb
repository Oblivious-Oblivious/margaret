require_relative "_parser_helpers";

describe Parser do
    context "on procs" do
        it "parses procs" do
            parse("-> { x = (x = 1, y = 2) }", "params:function: Proc [] = x (= x 1, = y 2)"); # x = 2
            parse("x = -> {
                v1, v2 | (
                    v1 += 1,
                    v1 += 2,
                    v1 * v2
                )
            }", %Q{= x params:function: Proc [v1, v2] (+= v1 1, += v1 2, * v1 v2)}); # v1 * v2
        end

        it "parses parameterized procs and procs returning literals" do
            parse("->{ 42 }", "params:function: Proc [] 42");
            parse("->{ a | a puts }", %Q{params:function: Proc [a] puts a});
            parse("->{ 2 + 3 }", "params:function: Proc [] + 2 3");
            parse("->{ (x = 1, y = 2, x + y) }", "params:function: Proc [] (= x 1, = y 2, + x y)");
            parse("->{ param | param puts }", %Q{params:function: Proc [param] puts param});
            parse("->{ a | a }", %Q{params:function: Proc [a] a});
            parse("->{ x = 2 } eval", "eval params:function: Proc [] = x 2");
            parse("->{ param | param puts } value: 42", %Q{value: params:function: Proc [param] puts param 42});
        end
    end
end
