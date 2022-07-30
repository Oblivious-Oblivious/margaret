require_relative "_parser_helpers";

describe Parser do
    context "on associations hashes" do
        it "parses hash literals" do
            parse("({})", "(new Hash ())");
            parse("({a: {}, b: {}})", %Q{(new Hash ((key:value: Association (new Symbol "a") new Hash ()) (key:value: Association (new Symbol "b") new Hash ())))});
            parse("({a: 1, b: 2, c: 3})", %Q{(new Hash ((key:value: Association (new Symbol "a") 1) (key:value: Association (new Symbol "b") 2) (key:value: Association (new Symbol "c") 3)))});
            parse("({:a => 1, :b => 2, :c => 3})", %Q{(new Hash ((key:value: Association (new Symbol "a") 1) (key:value: Association (new Symbol "b") 2) (key:value: Association (new Symbol "c") 3)))});
            parse("({:a => (self), :b => (super), :c => 3})", %Q{(new Hash ((key:value: Association (new Symbol "a") (self)) (key:value: Association (new Symbol "b") (super)) (key:value: Association (new Symbol "c") 3)))});
            parse(%Q{({"k1" => "v1", "k2" => "v2", "k3" => "v3"})}, %Q{(new Hash ((key:value: Association "k1" "v1") (key:value: Association "k2" "v2") (key:value: Association "k3" "v3")))});
            parse("({:a => x, :b => y, :c => z})", %Q{(new Hash ((key:value: Association (new Symbol "a") x) (key:value: Association (new Symbol "b") y) (key:value: Association (new Symbol "c") z)))});
        end
        
        it "parses associations" do
            parse("(x = Association key: :a value: 100)", %Q{(= x (key:value: Association (new Symbol "a") 100))});
            parse("(y = x key)", "(= y (key x))");
            parse("(y = x value)", "(= y (value x))");
        end

        it "parses hashes" do
            parse("(x = {:a => 100, :b => 200, :c => 300})", %Q{(= x (new Hash ((key:value: Association (new Symbol "a") 100) (key:value: Association (new Symbol "b") 200) (key:value: Association (new Symbol "c") 300))))});
            parse(%Q{(x at: "a" put: 3)}, %Q{(at:put: x "a" 3)});
            parse("(x is_empty?)", "(is_empty? x)");
            parse("(x size)", "(size x)");
            parse(%Q{(x at: :a if_absent: "")}, %Q{(at:if_absent: x (new Symbol "a") "")});
            parse(%Q{(x key_at_value: 3 if_absent: "")}, %Q{(key_at_value:if_absent: x 3 "")});
            parse(%Q{(x remove_key: :e if_absent: "")}, %Q{(remove_key:if_absent: x (new Symbol "e") "")});
            parse("(b = x includes_key: :a)", %Q{(= b (includes_key: x (new Symbol "a")))});
            parse("(x keys puts)", "(puts (keys x))");
            parse("(x values puts)", "(puts (values x))");
            parse("(x each_key: ((:a) (a puts)))", %Q{(each_key: x ((new Symbol "a") (puts a)))});
            parse("(x each_value: ((:a) (a puts)))", %Q{(each_value: x ((new Symbol "a") (puts a)))});
            parse("(x each: ((:a) (a puts)))", %Q{(each: x ((new Symbol "a") (puts a)))}); # Prints hash associations
        end
    end
end
