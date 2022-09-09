describe Parser do
    context "on characters" do
        it "parses character literals" do
            parse("'a'", ["push_char", "'a'"]);
            parse("'\n'", ["push_char", "'\n'"]);
            parse("'œ'", ["push_char", "'œ'"]);
        end

        it "parses character messages" do
            parse("(x = 'a' is_lowercase?)", ["push_char", "'a'", "unary", "is_lowercase?", "store", "x"]);
            parse("(x = 'a' is_uppercase?)", ["push_char", "'a'", "unary", "is_uppercase?", "store", "x"]);
            parse("(x = 'a' is_letter?)", ["push_char", "'a'", "unary", "is_letter?", "store", "x"]);
            parse("(x = 'a' is_digit?)", ["push_char", "'a'", "unary", "is_digit?", "store", "x"]);
            parse("(x = 'a' is_alphanumeric?)", ["push_char", "'a'", "unary", "is_alphanumeric?", "store", "x"]);
            parse("(x = 'a' is_separator?)", ["push_char", "'a'", "unary", "is_separator?", "store", "x"]);
            parse("(x = 'a' is_vowel?)", ["push_char", "'a'", "unary", "is_vowel?", "store", "x"]);
            parse("(x = 'a' to_digit)", ["push_char", "'a'", "unary", "to_digit", "store", "x"]);
            parse("(x = 'a' to_lowercase)", ["push_char", "'a'", "unary", "to_lowercase", "store", "x"]);
            parse("(x = 'a' to_uppercase)", ["push_char", "'a'", "unary", "to_uppercase", "store", "x"]);
            parse("(x = 'a' to_ascii)", ["push_char", "'a'", "unary", "to_ascii", "store", "x"]);
            parse("(x = 'a' <= 'b')", ["push_char", "'a'", "push_char", "'b'", "binary", "<=", "store", "x"]);
        end
    end
end
