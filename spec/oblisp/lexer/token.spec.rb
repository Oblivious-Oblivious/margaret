describe Token do
    it "has a type and a value" do
        tok = Token.new(Type::INTEGER, 42);
        expect(tok.type).to eq Type::INTEGER;
        expect(tok.value).to eq 42;
    end

    it "prints a string representation of the token" do
        tok = Token.new(Type::STRING, "hello");
        expect(tok.to_s).to eq "(#{tok.type}:#{tok.value})";
    end
end
