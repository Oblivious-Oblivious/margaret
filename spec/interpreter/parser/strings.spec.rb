require_relative "_parser_helpers";

describe Parser do
    context "on strings" do
        it "parses string literals" do
            parse(%Q{("hello" puts)}, %Q{(puts "hello")});
            parse(%Q{"multi
                line
                string"}, %Q{"multi
                line
                string"});
        end

        it "parses escape strings" do
            parse(%Q{"foo\tbar"}, %Q{"foo\tbar"});
            parse(%Q{"a string lit"}, %Q{"a string lit"});
            parse(%Q{"str"}, %Q{"str"});
    
            parse(%Q{"\a"}, %Q{"\a"});
            parse(%Q{"\b"}, %Q{"\b"});
            parse(%Q{"\t"}, %Q{"\t"});
            parse(%Q{"\n"}, %Q{"\n"});
            parse(%Q{"\v"}, %Q{"\v"});
            parse(%Q{"\f"}, %Q{"\f"});
            parse(%Q{"\r"}, %Q{"\r"});
            parse(%Q{"\e"}, %Q{"\e"});
            parse(%Q{"\s"}, %Q{"\s"});
            parse(%Q{"\\"}, %Q{"\\"});
        end
        
        it "parses string messages" do
            parse("(b = s is_empty?)", "(= b is_empty? s)");
            parse("(x = s size)", "(= x size s)");
            parse("(x = s at: 2)", "(= x at: s 2)");
            parse("(x = s copy_from: 2 to: 4)", "(= x copy_from:to: s 2 4)");
            parse("(x = s index_of: 'a' if_absent: 0)", "(= x index_of:if_absent: s 'a' 0)");
            parse("(s at: 1 put: 'a', s at: 2 put: 'b', s at: 3 put: 'c')", "(at:put: s 1 'a', at:put: s 2 'b', at:put: s 3 'c')");
            parse("s << 'a' << 'b' << 'c' << 'd'", "<< (<< (<< (<< s 'a') 'b') 'c') 'd'");
            parse("s add: 'a' add: 'b' add: 'c' add: 'd'", "(add: s 'a', add: s 'b', add: s 'c', add: s 'd')");
            parse("(s each_char: ->{a | a puts})", %Q{(each_char: s params:function: Proc (a) puts a)});
            parse("(b = s conform: ->{a | (a >= 'a') && (a <= 'z')})", %Q{(= b conform: s params:function: Proc (a) && (>= a 'a') (<= a 'z'))});
            parse("(x = s select: ->{ a | a > 'a'})", %Q{(= x select: s params:function: Proc (a) > a 'a')});
            parse("(x = s to_list)", "(= x to_list s)");
            parse("(x = s to_symbol)", "(= x to_symbol s)");
            parse(%Q{(x = "abcd" to_byte_array)}, %Q{(= x to_byte_array "abcd")});
            parse("(x = s shuffled)", "(= x shuffled s)");
        end
    end
end
