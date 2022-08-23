require_relative "_parser_helpers";

describe Parser do
    context "on symbols" do
        it "parses symbol literals" do
            parse(":ok", %Q{:"ok"});
            parse("(:a,:b,:c)", %Q{(:"a", :"b", :"c")});
            parse(":++", %Q{:"++"});
            parse(":*/-+%^&*", %Q{:"*/-+%^&*"});
        end

        it "parses different types of symbol literals" do
            parse("a: 3", %Q{:"a": 3});
            parse(%Q{"a": 5}, %Q{"a": 5});
            parse(":a: 7", %Q{:"a": 7});
        end

        it "parses symbol messages" do
            parse("(x = :Hello)", %Q{(= x :"Hello")});
            parse("(y = :symb)", %Q{(= y :"symb")});
            parse("((1,2,3) reduce: :+)", %Q{(reduce: (1, 2, 3) :"+")});
            parse(%Q{(x = :"a symbol")}, %Q{(= x :"a symbol")});
            # NOTE Look at ruby
        end
    end
end
