describe Parser do
    context "on strings" do
        it "parses string literals" do
            parse(%Q{("hello" puts)}, ["push_string", %Q{"hello"}, "unary", "puts"]);
            parse(%Q{"multi
                line
                string"}, ["push_string", %Q{"multi\n                line\n                string"}]);
        end

        it "parses escape strings" do
            parse(%Q{"foo\tbar"}, ["push_string", %Q{"foo\tbar"}]);
            parse(%Q{"a string lit"}, ["push_string", %Q{"a string lit"}]);
            parse(%Q{"str"}, ["push_string", %Q{"str"}]);
    
            parse(%Q{"\a"}, ["push_string", %Q{"\a"}]);
            parse(%Q{"\b"}, ["push_string", %Q{"\b"}]);
            parse(%Q{"\t"}, ["push_string", %Q{"\t"}]);
            parse(%Q{"\n"}, ["push_string", %Q{"\n"}]);
            parse(%Q{"\v"}, ["push_string", %Q{"\v"}]);
            parse(%Q{"\f"}, ["push_string", %Q{"\f"}]);
            parse(%Q{"\r"}, ["push_string", %Q{"\r"}]);
            parse(%Q{"\e"}, ["push_string", %Q{"\e"}]);
            parse(%Q{"\s"}, ["push_string", %Q{"\s"}]);
            parse(%Q{"\\"}, ["push_string", %Q{"\\"}]);
        end
        
        it "parses string messages" do
            parse("(b = s is_empty?)", ["push_variable", "s", "unary", "is_empty?", "store", "b"]);
            parse("(x = s size)", ["push_variable", "s", "unary", "size", "store", "x"]);
            parse("(x = s at: 2)", ["push_variable", "s", "push_2", "keyword", "at:", "1", "store", "x"]);
            parse("(x = s copy_from: 2 to: 4)", ["push_variable", "s", "push_2", "push_integer", "4", "keyword", "copy_from:to:", "2", "store", "x"]);
            parse("(x = s index_of: 'a' if_absent: 0)", ["push_variable", "s", "push_char", "'a'", "push_0", "keyword", "index_of:if_absent:", "2", "store", "x"]);
            parse("(s at: 1 put: 'a', s at: 2 put: 'b', s at: 3 put: 'c')", ["push_variable", "s", "push_1", "push_char", "'a'", "keyword", "at:put:", "2", "push_variable", "s", "push_2", "push_char", "'b'", "keyword", "at:put:", "2", "push_variable", "s", "push_integer", "3", "push_char", "'c'", "keyword", "at:put:", "2"]);
            parse("s << 'a' << 'b' << 'c' << 'd'", ["push_variable", "s", "push_char", "'a'", "binary", "<<", "push_char", "'b'", "binary", "<<", "push_char", "'c'", "binary", "<<", "push_char", "'d'", "binary", "<<"]);
            parse("s add: 'a' add: 'b' add: 'c' add: 'd'", ["push_variable", "s", "push_char", "'a'", "keyword", "add:", "1", "push_variable", "s", "push_char", "'b'", "keyword", "add:", "1", "push_variable", "s", "push_char", "'c'", "keyword", "add:", "1", "push_variable", "s", "push_char", "'d'", "keyword", "add:", "1"]);
            parse("(s each_char: ->{a | a puts})", ["push_variable", "s", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "unary", "puts", "ENDpush_proc", "keyword", "each_char:", "1"]);
            parse("(b = s conform: ->{a | (a >= 'a') && (a <= 'z')})", ["push_variable", "s", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "push_char", "'a'", "binary", ">=", "push_variable", "a", "push_char", "'z'", "binary", "<=", "binary", "&&", "ENDpush_proc", "keyword", "conform:", "1", "store", "b"]);
            parse("(x = s select: ->{ a | a > 'a'})", ["push_variable", "s", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "push_char", "'a'", "binary", ">", "ENDpush_proc", "keyword", "select:", "1", "store", "x"]);
            parse("(x = s to_list)", ["push_variable", "s", "unary", "to_list", "store", "x"]);
            parse("(x = s to_symbol)", ["push_variable", "s", "unary", "to_symbol", "store", "x"]);
            parse(%Q{(x = "abcd" to_byte_array)}, ["push_string", %Q{"abcd"}, "unary", "to_byte_array", "store", "x"]);
            parse("(x = s shuffled)", ["push_variable", "s", "unary", "shuffled", "store", "x"]);
        end
    end
end
