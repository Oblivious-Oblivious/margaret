require_relative "_parser_helpers";

describe Parser do
    context "on strings" do
        it "parses string literals" do
            parse(%Q{("hello" puts)}, %Q{(puts "hello")});
        end
        
        it "parses string messages" do
            parse("(b = s is_empty?)", "(= b (is_empty? s))");
            parse("(x = s size)", "(= x (size s))");
            parse("(x = s at: 2)", "(= x (at: s 2))");
            parse("(x = s copy_from: 2 to: 4)", "(= x (copy_from:to: s 2 4))");
            parse("(x = s index_of: 'a' if_absent: 0)", "(= x (index_of:if_absent: s 'a' 0))");
            # TODO cascading messages
            # parse("(s at: 1 put: 'a'; at: 2 put: 'b'; at: 3 put: 'c')");
            # parse("(s with: 'a'; with: 'b'; with: 'c'; with: 'd')");

            parse("(s each_char: [(a) (a puts)])", "(each_char: s (new Tuple ((a) (puts a))))");
            # TODO
            # parse("(b = s conform: [(a) (a >= 'a') && (a <= 'z')])");
            parse("(x = s select: [(a) (a > 'a')])", "(= x (select: s (new Tuple ((a) (> a 'a')))))");
            parse("(x = s to_list)", "(= x (to_list s))");
            parse("(x = s to_symbol)", "(= x (to_symbol s))");
            parse(%Q{(x = "abcd" to_byte_array)}, %Q{(= x (to_byte_array "abcd"))});
            parse("(x = s shuffled)", "(= x (shuffled s))");
        end
    end
end
