describe Type do
    it "contains all literal types" do
        expect(Type::INTEGER).to eq 1;
        expect(Type::BIG_INTEGER).to eq 2;
        expect(Type::FLOAT).to eq 3;
        expect(Type::BIG_FLOAT).to eq 4;

        expect(Type::BINARY).to eq 11;
        expect(Type::HEXADECIMAL).to eq 12;
        expect(Type::OCTAL).to eq 13;

        expect(Type::STRING).to eq 21;
        expect(Type::SYMBOL).to eq 22;

        expect(Type::BLOCK).to eq 41;
        expect(Type::ARRAY).to eq 42;
        expect(Type::HASH).to eq 43;
        expect(Type::NEW_OBJECT).to eq 44;
    end
end
