describe Lexer do
    it "contains the input text, lexer position and current character" do
        l = Lexer.new "file.obl", "(42 factorial.)".chars;
        expect(l.text).to eq "(42 factorial.)".chars;
        expect(l.pos).to eq -1;
    end

    context "#next_character" do
        it "properly advances characters in the array" do
            l = Lexer.new "file.obl", "(42 factorial.)".chars;

            current_char = l.next_character;
            expect(current_char).to eq "(";
            expect(l.pos).to eq 0;

            current_char = l.next_character;
            expect(current_char).to eq "4";
            expect(l.pos).to eq 1;

            current_char = l.next_character;
            current_char = l.next_character;
            current_char = l.next_character;
            expect(current_char).to eq "f";
            expect(l.pos).to eq 4;
        end

        it "reads all characters until the list ends" do
            l = Lexer.new "file.obl", ["1","2","3","4","5"];
    
            c1 = l.next_character;
            c2 = l.next_character;
            c3 = l.next_character;
            c4 = l.next_character;
            c5 = l.next_character;
            expect(c1).to eq "1";
            expect(c2).to eq "2";
            expect(c3).to eq "3";
            expect(c4).to eq "4";
            expect(c5).to eq "5";

            # String reaches EOF
            c6 = l.next_character;
            expect(c6).to eq nil;
        end
    end

    context "#prev_character" do
        it "goes back to a previous character in the list" do
            l = Lexer.new "file.obl", "(42 factorial.)".chars;

            c = l.next_character;
            c = l.next_character;
            c = l.next_character;
            c = l.prev_character;

            expect(c).to eq "4";
        end
    end

    context "string extensions" do
        it "matches regular expressions" do
            expect(" ".matches(RegexMatchers::WHITESPACE)).to be true;
            expect("\n".matches(RegexMatchers::NEWLINE)).to be true;
            expect("#".matches(RegexMatchers::COMMENT)).to be true;
            expect("9".matches(RegexMatchers::NUMBER)).to be true;
            expect("k".matches(RegexMatchers::LETTER)).to be true;
            expect("?".matches(RegexMatchers::MESSAGE_SYMBOL)).to be true;
            expect("'".matches(RegexMatchers::QUOTE)).to be true;
            expect("self".matches(RegexMatchers::KEYWORDS)).to be true;
            expect("super".matches(RegexMatchers::KEYWORDS)).to be true;
        end
    end

    it "prints error messages" do
        l = Lexer.new "file.obl", "(42 factorial.)".chars;
        response = l.error("random exception");
        expect(response).to eq [];
    end

    context "#make_tokens" do
        it "correctly counts the number of lines" do
            l = Lexer.new "file.obl", "(42 factorial.\nx = 2 + 3\ny = 5)".chars;
            l.make_tokens;

            expect(l.lineno).to eq 3;
        end

        it "ignores comment lines" do
            l = Lexer.new "file.obl", "(1 2 3\n#Comment Stuff#\n5)".chars;
            tokens = l.make_tokens;
            expect(tokens.size).to eq 6;
        end

        it "tokenizes symbols" do
            l = Lexer.new "file.obl", "(!@$%^&*)".chars;
            tokens = l.make_tokens;
            expect(tokens.size).to eq 9;
            expect(tokens[3].value).to eq "$";
        end

        it "tokenizes integers" do
            l = Lexer.new "file.obl", "(42 msg.)".chars;
            tokens = l.make_tokens;

            expect(tokens[1].value).to eq "42";
            expect(tokens[1].type).to eq Type::INTEGER;
            expect(tokens[1].line_number).to eq 1;
        end

        it "draws an error when trying to tokenize an integer starting with 0" do
            l = Lexer.new "file.obl", "(042 msg.)".chars;
            tokens = l.make_tokens;
        end

        it "tokenizes floats" do
            l = Lexer.new "file.obl", "(42.7 msg.)".chars;
            tokens = l.make_tokens;
            expect(tokens[1].value).to eq "42.7";
            expect(tokens[1].type).to eq Type::FLOAT;
            expect(tokens[1].line_number).to eq 1;

            l = Lexer.new "file.obl", "(0.7 msg.)".chars;
            tokens = l.make_tokens;
            expect(tokens[1].value).to eq "0.7";
            expect(tokens[1].type).to eq Type::FLOAT;
            expect(tokens[1].line_number).to eq 1;

            l = Lexer.new "file.obl", "(.7 msg.)".chars;
            tokens = l.make_tokens;
            expect(tokens[1].value).to eq ".";
            expect(tokens[2].value).to eq "7";
            expect(tokens[3].value).to eq "msg";
            expect(tokens[4].value).to eq ".";

            l = Lexer.new "file.obl", "(124.0 msg.)".chars;
            tokens = l.make_tokens;
            expect(tokens[1].value).to eq "124.0";
            expect(tokens[2].value).to eq "msg";
            expect(tokens[3].value).to eq ".";
        end

        it "tokenizes binary literals" do
            l = Lexer.new "file.obl", "(0b1010 + 0B0100)".chars;
            tokens = l.make_tokens;
            expect(tokens[1].value).to eq "0b1010";
            expect(tokens[3].value).to eq "0b0100";
        end

        it "tokenizes hexadecimal literals" do
            l = Lexer.new "file.obl", "(0xfeed42 + 0Xbeef41)".chars;
            tokens = l.make_tokens;
            expect(tokens[1].value).to eq "0xfeed42";
            expect(tokens[3].value).to eq "0xbeef41";
        end

        it "tokenizes octal literals" do
            l = Lexer.new "file.obl", "(0o752 + 0O52)".chars;
            tokens = l.make_tokens;
            expect(tokens[1].value).to eq "0o752";
            expect(tokens[3].value).to eq "0o52";
        end

        it "tokenizes string literals" do
            l = Lexer.new "file.obl", "(\"hello\" puts.)";
            token = l.make_tokens;
            expect(token[1].value).to eq "\"hello\"";

            l = Lexer.new "file.obl", "(\"multi\nline\nstring\" puts.)";
            token = l.make_tokens;
            expect(token[1].value).to eq "\"multi\nline\nstring\"";
        end

        it "tokenizes identifiers" do
            l = Lexer.new "file.obl", "(42 factorial.\nx = (2 times: 3)\n3 plus: 4)".chars;
            tokens = l.make_tokens;
            expect(tokens.size).to eq 17;
            expect(tokens[2].value).to eq "factorial";
            expect(tokens[4].value).to eq "x";
            expect(tokens[8].value).to eq "times";
            expect(tokens[13].value).to eq "plus";
        end

        it "tokenizes identifiers starting with an underscore" do
            l = Lexer.new "file.obl", "((1 2 3) __msg.)".chars;
            tokens = l.make_tokens;
            expect(tokens[6].value).to eq "__msg";
        end

        it "tokenizes the `self` keyword" do
            l = Lexer.new "file.obl", "(self puts.)";
            tokens = l.make_tokens;
            expect(tokens.size).to eq 5;
            expect(tokens[1].value).to eq "self";
        end

        it "tokenizes the `super` keyword" do
            l = Lexer.new "file.obl", "(super puts.)";
            tokens = l.make_tokens;
            expect(tokens.size).to eq 5;
            expect(tokens[1].value).to eq "super";
        end

        it "prints the token table" do
            l = Lexer.new "file.obl", "(super puts.)";
            tokens = l.make_tokens;
            expect(tokens.size).to eq 5;

            l.print_token_table;
        end

        it "traverses through the token table" do
            l = Lexer.new "file.obl", "(self puts.)";
            tokens = l.make_tokens;
            expect(tokens.size).to eq 5;
            expect(l.next_token.value).to eq "(";
            expect(l.next_token.value).to eq "self"
            expect(l.next_token.value).to eq "puts";
            expect(l.next_token.value).to eq ".";
            expect(l.next_token.value).to eq ")";
            expect(l.next_token.value).to eq "eof";
            expect(l.prev_token.value).to eq ")";
            expect(l.prev_token.value).to eq ".";
            expect(l.prev_token.value).to eq "puts";
        end
    end
end
