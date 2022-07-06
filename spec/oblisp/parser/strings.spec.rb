require_relative "_parser_helpers";

describe Parser do
    context "on strings" do
        it "parses string literals" do
            parse(%Q{("hello" puts)});
        end
        
        it "parses string messages" do
            parse("(b = s is_empty?)");
            parse("(x = s size)");
            parse("(x = s at: 2)");
            parse("(x = s copy_from: 2 to: 4)");
            parse("(x = s index_of: 'a' if_absent: 0)");
            parse("(s at: 1 put: 'a'; at: 2 put: 'b'; at: 3 put: 'c')");
            parse("(s with: 'a'; with: 'b'; with: 'c'; with: 'd')");
            parse("(s each_char: [(a) (a puts)])");
            parse("(b = s conform: [(a) (a >= 'a') && (a <= 'z')])");
            parse("(x = s select: [(a) (a > 'a')])");
            parse("(x = s to_list)");
            parse("(x = s to_symbol)");
            parse(%Q{(x = "abcd" to_byte_array)});
            parse("(x = s shuffled)");
        end
    end
end
