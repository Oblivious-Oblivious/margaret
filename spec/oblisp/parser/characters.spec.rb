require_relative "_parser_helpers";

describe Parser do
    context "on characters" do
        it "parses character messages" do
            parse("(x = 'a' is_lowercase?)");
            parse("(x = 'a' is_uppercase?)");
            parse("(x = 'a' is_letter?)");
            parse("(x = 'a' is_digit?)");
            parse("(x = 'a' is_alphanumeric?)");
            parse("(x = 'a' is_separator?)");
            parse("(x = 'a' is_vowel?)");
            parse("(x = 'a' to_digit)");
            parse("(x = 'a' to_lowercase)");
            parse("(x = 'a' to_uppercase)");
            parse("(x = 'a' to_ascii)");
            parse("(x = 'a' to_ascii)");
            parse("(x = 'a' <= 'b')");
        end
    end
end
