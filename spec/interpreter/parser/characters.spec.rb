require_relative "_parser_helpers";

describe Parser do
    context "on characters" do
        it "parses character messages" do
            parse("(x = 'a' is_lowercase?)", "(= x (is_lowercase? 'a'))");
            parse("(x = 'a' is_uppercase?)", "(= x (is_uppercase? 'a'))");
            parse("(x = 'a' is_letter?)", "(= x (is_letter? 'a'))");
            parse("(x = 'a' is_digit?)", "(= x (is_digit? 'a'))");
            parse("(x = 'a' is_alphanumeric?)", "(= x (is_alphanumeric? 'a'))");
            parse("(x = 'a' is_separator?)", "(= x (is_separator? 'a'))");
            parse("(x = 'a' is_vowel?)", "(= x (is_vowel? 'a'))");
            parse("(x = 'a' to_digit)", "(= x (to_digit 'a'))");
            parse("(x = 'a' to_lowercase)", "(= x (to_lowercase 'a'))");
            parse("(x = 'a' to_uppercase)", "(= x (to_uppercase 'a'))");
            parse("(x = 'a' to_ascii)", "(= x (to_ascii 'a'))");
            parse("(x = 'a' <= 'b')", "(= x (<= 'a' 'b'))");
        end
    end
end
