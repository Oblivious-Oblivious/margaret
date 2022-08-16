require_relative "_parser_helpers";

describe Parser do
    context "on quoted lists" do
        it "quoted list literals" do
            parse("`()", %Q{(:"(", :")")});
            parse("`(a b c)", %Q{(:"(", :"a", :"b", :"c", :")")});
            parse("`(:a msg: :b)", %Q{(:"(", :":", :"a", :"msg", :":", :":", :"b", :")")});
            parse("`(2 * (3 + 5) / 4)", %Q{(:"(", :"2", :"*", :"(", :"3", :"+", :"5", :")", :"/", :"4", :")")});
        end

        it "evaluates quoted lists" do
            parse("`(x = 2) eval", %Q{eval (:"(", :"x", :"=", :"2", :")")});
        end
    end
end
