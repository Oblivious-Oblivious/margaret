require_relative "_parser_helpers";

describe Parser do
    context "on blocks" do
        # TODO blocks
        it "parses blocks" do
            parse("->(x = (x = 1, y = 2))", "params:function: Block () = x (= x 1, = y 2)"); # x = 2
            parse("x = ->(
                :v1, :v2, (
                    v1 += 1,
                    v1 += 2,
                    v1 * v2
                )
            )", %Q{= x params:function: Block (:"v1", :"v2") (+= v1 1, += v1 2, * v1 v2)}); # v1 * v2
        end

        it "parses parameterized blocks and blocks returning literals" do
            parse("->(42)", "params:function: Block () 42");
            parse("->(:a, a puts)", %Q{params:function: Block (:"a") puts a});
            parse("->(2 + 3)", "params:function: Block () + 2 3");
            parse("->((x = 1, y = 2, x + y))", "params:function: Block () (= x 1, = y 2, + x y)");
            parse("->(:a, :b, a + b)", %Q{params:function: Block (:"a", :"b") + a b});
            parse("->(:a, a)", %Q{params:function: Block (:"a") a});
            parse("->(x = 2) exec", "exec params:function: Block () = x 2");
            parse("->(:param, param puts) value: 42", %Q{value: params:function: Block (:"param") puts param 42});
        end
    end
end
