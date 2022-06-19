describe Token do
    it "has a type and a value" do
        tok = Token.new(42, Type::INTEGER, 125);
        expect(tok.value).to eq 42;
        expect(tok.type).to eq Type::INTEGER;
        expect(tok.line_number).to eq 125;
    end

    it "prints a string representation of the token" do
        tok = Token.new("hello", Type::STRING, 10);
        expect(tok.to_s).to eq "(\"#{tok.value}\" #{tok.type} #{tok.line_number})";
    end

    it "has an equals message" do
        tok = Token.new("hello", Type::STRING, 10);
        expect(tok == "hello").to be true;
        expect(tok == "not hello").to be false;
    end
end
