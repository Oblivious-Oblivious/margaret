describe Lexer do
    it "contains the input text, lexer position and current character" do
        l = Lexer.new "file.marg", "(42 factorial)".chars;
        expect(l.text).to eq "(42 factorial)".chars;
        expect(l.pos).to eq -1;
    end

    context "#next_character" do
        it "properly advances characters in the array" do
            l = Lexer.new "file.marg", "(42 factorial)".chars;

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
            l = Lexer.new "file.marg", ["1","2","3","4","5"];
    
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

    context "#peek_character" do
        it "peeks the next character from the list" do
            l = Lexer.new "file.marg", "(42 factorial)".chars;

            c1 = l.peek_character(1);
            c2 = l.peek_character(2);
            c3 = l.peek_character(3);
            c4 = l.peek_character(4);
            c5 = l.peek_character(5);

            expect(c1).to eq "(";
            expect(c2).to eq "4";
            expect(c3).to eq "2";
            expect(c4).to eq " ";
            expect(c5).to eq "f";
        end
    end

    context "string extensions" do
        it "matches regular expressions" do
            expect(" ".matches(RegexMatchers::WHITESPACE)).to be true;
            expect("\n".matches(RegexMatchers::NEWLINE)).to be true;
            expect("9".matches(RegexMatchers::NUMBER)).to be true;
            expect("k".matches(RegexMatchers::LETTER)).to be true;
            expect("+".matches(RegexMatchers::MESSAGE_SYMBOL)).to be true;
            expect("?".matches(RegexMatchers::ID_SYMBOL)).to be true;
            expect("!".matches(RegexMatchers::ID_SYMBOL)).to be true;
            expect("{".matches(RegexMatchers::SYNTAX_SYMBOL)).to be true;
            expect("'".matches(RegexMatchers::SINGLE_QUOTE)).to be true;
            expect("\"".matches(RegexMatchers::DOUBLE_QUOTE)).to be true;
        end
    end

    it "prints error messages" do
        l = Lexer.new "file.marg", "(42 factorial)".chars;
        response = l.error("random exception");
        expect(response).to eq [];
    end

    context "#make_tokens" do
        it "correctly counts the number of lines" do
            l = Lexer.new "file.marg", "(42 factorial\nx = 2 + 3\ny = 5)".chars;
            l.make_tokens;

            expect(l.lineno).to eq 3;
        end

        it "tokenizes symbols" do
            l = Lexer.new "file.marg", "(@ $ % ^ & *)".chars;
            tokens = l.make_tokens;
            expect(tokens.size).to eq 9;
            expect(tokens.get(3).value).to eq "%";
        end

        it "tokenizes integers" do
            tokens = Lexer.new("file.marg", "(42 msg)".chars).make_tokens;
            expect(tokens.get(1).value).to eq "42";
            expect(tokens.get(1).type).to eq Type::INTEGER;
            expect(tokens.get(1).line_number).to eq 1;

            tokens = Lexer.new("file.marg", "4_200".chars).make_tokens;
            expect(tokens.get(0).value).to eq "4200";
            tokens = Lexer.new("file.marg", "4_2_0_0".chars).make_tokens;
            expect(tokens.get(0).value).to eq "4200";
        end

        it "tokenizes zero" do
            l = Lexer.new "file.marg", "(0 is_zero?)".chars;
            tokens = l.make_tokens;

            expect(tokens.get(1).value).to eq "0";
            expect(tokens.get(1).type).to eq Type::INTEGER;
            expect(tokens.get(1).line_number).to eq 1;
        end

        it "draws an error when trying to tokenize an integer starting with 0" do
            l = Lexer.new "file.marg", "(042 msg)".chars;
            tokens = l.make_tokens;
        end

        it "tokenizes floats" do
            l = Lexer.new "file.marg", "0.0".chars;
            tokens = l.make_tokens;
            expect(tokens.get(0).value).to eq "0.0";
            expect(tokens.get(0).type).to eq Type::FLOAT;
            expect(tokens.get(1).line_number).to eq 1;

            l = Lexer.new "file.marg", "(42.7 msg)".chars;
            tokens = l.make_tokens;
            expect(tokens.get(1).value).to eq "42.7";
            expect(tokens.get(1).type).to eq Type::FLOAT;
            expect(tokens.get(1).line_number).to eq 1;

            l = Lexer.new "file.marg", "(0.7 msg)".chars;
            tokens = l.make_tokens;
            expect(tokens.get(1).value).to eq "0.7";
            expect(tokens.get(1).type).to eq Type::FLOAT;
            expect(tokens.get(1).line_number).to eq 1;

            l = Lexer.new "file.marg", "(0.7+0.5+0.23)".chars;
            tokens = l.make_tokens;
            expect(tokens.get(1).value).to eq "0.7";
            expect(tokens.get(2).value).to eq "+";
            expect(tokens.get(3).value).to eq "0.5";

            l = Lexer.new "file.marg", "(.7 msg)".chars;
            tokens = l.make_tokens;
            expect(tokens.get(1).value).to eq ".";
            expect(tokens.get(2).value).to eq "7";
            expect(tokens.get(3).value).to eq "msg";
            expect(tokens.get(4).value).to eq ")";

            l = Lexer.new "file.marg", "(124.0 msg)".chars;
            tokens = l.make_tokens;
            expect(tokens.get(1).value).to eq "124.0";
            expect(tokens.get(2).value).to eq "msg";
        end

        it "tokenizes binary literals" do
            l = Lexer.new "file.marg", "(0b1010 + 0B0100)".chars;
            tokens = l.make_tokens;
            expect(tokens.get(0).value).to eq "(";
            expect(tokens.get(1).value).to eq "0b1010";
            expect(tokens.get(2).value).to eq "+";
            expect(tokens.get(3).value).to eq "0b0100";
            expect(tokens.get(4).value).to eq ")";

            expect(tokens.get(1).type).to eq Type::INTEGER;
            expect(tokens.get(3).type).to eq Type::INTEGER;
        end

        it "tokenizes hexadecimal literals" do
            l = Lexer.new "file.marg", "(0xfeed42 + 0Xbeef41)".chars;
            tokens = l.make_tokens;
            expect(tokens.get(0).value).to eq "(";
            expect(tokens.get(1).value).to eq "0xfeed42";
            expect(tokens.get(2).value).to eq "+";
            expect(tokens.get(3).value).to eq "0xbeef41";
            expect(tokens.get(4).value).to eq ")";

            expect(tokens.get(1).type).to eq Type::INTEGER;
            expect(tokens.get(3).type).to eq Type::INTEGER;
        end

        it "tokenizes octal literals" do
            l = Lexer.new "file.marg", "(0o752 + 0O52)".chars;
            tokens = l.make_tokens;
            expect(tokens.get(0).value).to eq "(";
            expect(tokens.get(1).value).to eq "0o752";
            expect(tokens.get(2).value).to eq "+";
            expect(tokens.get(3).value).to eq "0o52";
            expect(tokens.get(4).value).to eq ")";

            expect(tokens.get(1).type).to eq Type::INTEGER;
            expect(tokens.get(3).type).to eq Type::INTEGER;
        end

        it "tokenizes character literals" do
            l = Lexer.new "file.marg", "('a' puts)";
            tokens = l.make_tokens;
            expect(tokens.get(1).value).to eq "'a'";
            expect(tokens.get(1).type).to eq Type::CHAR;
        end

        it "tokenizes string literals" do
            l = Lexer.new "file.marg", %Q{("hello" puts)};
            token = l.make_tokens;
            expect(token.get(1).value).to eq %Q{"hello"};

            l = Lexer.new "file.marg", %Q{("multi\nline\nstring" puts)};
            token = l.make_tokens;
            expect(token.get(1).value).to eq %Q{"multi\nline\nstring"};
        end

        it "tokenizes identifiers" do
            l = Lexer.new "file.marg", "(42 factorial\nx = (2 times: 3)\n3 plus: 4)".chars;
            tokens = l.make_tokens;
            expect(tokens.size).to eq 17;
            expect(tokens.get(2).value).to eq "factorial";
            expect(tokens.get(3).value).to eq "x";
            expect(tokens.get(7).value).to eq "times";
            expect(tokens.get(12).value).to eq "plus";
        end

        it "tokenizes identifiers starting with an underscore" do
            l = Lexer.new "file.marg", "((1 2 3) __msg)".chars;
            tokens = l.make_tokens;
            expect(tokens.get(6).value).to eq "__msg";
        end

        it "prints the token table" do
            l = Lexer.new "file.marg", "(42 factorial)";
            tokens = l.make_tokens;
            expect(tokens.size).to eq 5;

            tokens.display;
        end
    end
end
