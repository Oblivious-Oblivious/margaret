require_relative "_parser_helpers";

describe Parser do
    context "on associations hashes" do
        it "parses hash literals" do
            # TODO hash literals
            parse("({a: 1, b: 2, c: 3})");
            parse("({:a => 1 :b => 2 :c => 3})");
            parse("({:a => (self a) :b => (super b) :c => 3})");
            parse(%Q{({"k1" => "v1" "k2" => "v2" "k3" => "v3"})});
        end
        
        it "parses associations" do
            parse("(x = :a => 100)");
            parse("(y = x key)");
            parse("(y = x value)");
        end

        it "parses hashes" do
            parse("(x = {:a => 100, :b => 200, :c => 300})");
            parse("(x add: :a => 100; add: b => 200)");
            parse(%Q{(x at: "a" put: 3)});
            parse("(x is_empty?)");
            parse("(x size)");
            parse(%Q{(x at: :a if_absent: "")});
            parse(%Q{(x key_at_value: 3 if_absent: "")});
            parse(%Q{(x remove_key: :e if_absent: "")});
            parse("(b = x includes_key? :a)");
            parse("(x keys puts)");
            parse("(x values puts)");
            parse("(x each_key: [(a) (a puts)])");
            parse("(x each_value: [(a) (a puts)])");
            parse("(x each: [(a) (a puts)])"); # Prints hash associations
            # TODO hashes have list messages
        end
    end
end
