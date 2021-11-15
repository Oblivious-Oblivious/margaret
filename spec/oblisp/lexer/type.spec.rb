describe Type do
    it "contains syntax token types" do
        expect(Type::LEFT_PAREN).to eq 1;
        expect(Type::RIGHT_PAREN).to eq 2;
        expect(Type::COLON).to eq 3;
    end

    it "contains literal syntax types" do
        expect(Type::COMMA).to eq 11;
        expect(Type::DOT).to eq 12;
        expect(Type::ROCKET).to eq 21;
        expect(Type::ARROW).to eq 31;
        expect(Type::PIPE).to eq 41;
        expect(Type::LEFT_CURLY).to eq 42;
        expect(Type::RIGHT_CURLY).to eq 43;
    end

    it "contains all terminal literal types" do
        expect(Type::INTEGER).to eq 101;
        expect(Type::BIG_INTEGER).to eq 102;
        expect(Type::FLOAT).to eq 103;
        expect(Type::BIG_FLOAT).to eq 104;

        expect(Type::BINARY).to eq 111;
        expect(Type::HEXADECIMAL).to eq 112;
        expect(Type::OCTAL).to eq 113;

        expect(Type::STRING).to eq 121;
    end

    it "contains non terminal literal types" do
        expect(Type::IDENTIFIER).to eq 201;
    end

    it "contains the 2 omega hype keywords of the language" do
        expect(Type::SELF).to eq 1033;
        expect(Type::SUPER).to eq 3301;
    end
end
