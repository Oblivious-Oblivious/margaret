describe Type do
    it "contains an EOF syntax symbol" do
        expect(Type::EOF).to eq 0;
    end

    it "contains message normal and syntax symbols" do
        expect(Type::MESSAGE_SYMBOL).to eq 1;
        expect(Type::SYNTAX_SYMBOL).to eq 2;
    end

    it "contains all terminal literal types" do
        expect(Type::INTEGER).to eq 11;
        expect(Type::FLOAT).to eq 12;

        expect(Type::BINARY).to eq 101;
        expect(Type::HEXADECIMAL).to eq 102;
        expect(Type::OCTAL).to eq 103;

        expect(Type::STRING).to eq 111;
    end

    it "contains non terminal literal types" do
        expect(Type::IDENTIFIER).to eq 201;
    end

    it "contains the 2 omega hype keywords of the language" do
        expect(Type::SELF).to eq 1033;
        expect(Type::SUPER).to eq 3301;
    end
end
