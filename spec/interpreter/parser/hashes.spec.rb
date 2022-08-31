require_relative "_parser_helpers";

describe Parser do
    context "on associations hashes" do
        it "parses hash literals" do
            parse("({})", "({})");
            parse("({a: {}, b: {}})", %Q{({"a": {}, "b": {}})});
            parse("({a: 1, b: 2, c: 3})", %Q{({"a": 1, "b": 2, "c": 3})});
            parse(%Q{{"a": 1, "b": 2, "c": 3}}, %Q{{"a": 1, "b": 2, "c": 3}});
            parse(%Q{({"k1": "v1", "k2": "v2", "k3": "v3"})}, %Q{({"k1": "v1", "k2": "v2", "k3": "v3"})});
            parse("{x: {a: 1, b: 2}, y: {c: 3, d: 4}}", %Q{{"x": {"a": 1, "b": 2}, "y": {"c": 3, "d": 4}}});
            parse("{a: 42 factorial, b: 2 + 3, c: 41 plus: 1, d: (42 incr decr, 41 incr)}", %Q{{"a": factorial 42, "b": + 2 3, "c": plus: 41 1, "d": (decr (incr 42), incr 41)}});
        end

        it "parses hashes" do
            parse(%Q{(x at: 'a' put: 3)}, %Q{(at:put: x 'a' 3)});
            parse("(x is_empty?)", "(is_empty? x)");
            parse("(x size)", "(size x)");
            parse(%Q{(x at: "a" if_absent: "")}, %Q{(at:if_absent: x "a" "")});
            parse(%Q{(x key_at_value: 3 if_absent: "")}, %Q{(key_at_value:if_absent: x 3 "")});
            parse(%Q{(x remove_key: "e" if_absent: "")}, %Q{(remove_key:if_absent: x "e" "")});
            parse(%Q{(b = x includes_key: "a")}, %Q{(= b includes_key: x "a")});
            parse("(x keys puts)", "(puts (keys x))");
            parse("(x values puts)", "(puts (values x))");
            parse("(x each_key: ->{a | a puts})", %Q{(each_key: x params:function: Proc [a] puts a)});
            parse("(x each_value: ->{a | a puts})", %Q{(each_value: x params:function: Proc [a] puts a)});
            parse("(x each: ->{a | a puts})", %Q{(each: x params:function: Proc [a] puts a)}); # Prints hash associations
        end
    end
end
