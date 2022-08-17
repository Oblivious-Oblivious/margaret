describe TokenTable do
    before(:all) do
        @tok_arr = [
            (Token.new "a", Type::IDENTIFIER, 1),
            (Token.new "+", Type::MESSAGE_SYMBOL, 1),
            (Token.new "2", Type::INTEGER, 1),
            (Token.new "eof", Type::EOF, 1)
        ]
    end

    it "takes a tok array as parameter and is not nil" do
        expect(TokenTable.new @tok_arr).to be_kind_of TokenTable;
    end

    it "counts 4 elements in the list" do
        l = TokenTable.new @tok_arr;
        expect(l.size).to eq 4;
    end

    it "peeks a token at the current position on the array" do
        l = TokenTable.new @tok_arr;
        expect(l.lookahead 1).to eq "a";
        expect(l.lookahead 2).to eq "+";
        expect(l.lookahead 3).to eq "2";
        expect(l.lookahead 4).to eq "eof";
        expect(l.lookahead 5).to eq "eof";
    end

    it "consumes a token and returns the value" do
        l = TokenTable.new @tok_arr;
        expect(l.consume).to eq "a";
        expect(l.consume).to eq "+";
        expect(l.consume).to eq "2";
        expect(l.consume).to eq "eof";

        expect(l.consume).to eq "eof";
        expect(l.consume).to eq "eof";
    end

    it "resumes a previous token and returns the value" do
        l = TokenTable.new @tok_arr;
        expect(l.consume).to eq "a";
        expect(l.consume).to eq "+";
        expect(l.consume).to eq "2";
        expect(l.consume).to eq "eof";
    end

    it "returns the current position of the list" do
        l = TokenTable.new @tok_arr;
        expect(l.token_table_pos).to eq 0;
        l.consume;
        l.consume;
        expect(l.token_table_pos).to eq 2;
        expect(l.token_table_pos).to eq 2;
        l.consume;
        expect(l.token_table_pos).to eq 3;
    end

    it "gets a list element by index" do
        l = TokenTable.new @tok_arr;
        expect(l.get(1)).to eq "+";
        expect(l.get(0)).to eq "a";
        expect(l.get(3)).to eq "eof";
        expect(l.get(2)).to eq "2";

        expect(l.get(99)).to eq "eof";
        expect(l.get(42)).to eq "eof";
    end

    it "ensures it consumes of a specific token type" do
        table = TokenTable.new @tok_arr;
        expect(table.ensure_type(Type::IDENTIFIER, "")).to eq "a";
        expect(table.ensure_type(Type::MESSAGE_SYMBOL, "")).to eq "+";
        expect(table.ensure_type(Type::INTEGER, "")).to eq "2";
        expect(table.ensure_type(Type::EOF, "")).to eq "eof";
    end
end
