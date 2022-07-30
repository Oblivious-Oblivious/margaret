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
        expect(l.peek.value).to eq "a";
        expect(l.peek.value).to eq "a";
        expect(l.peek.value).to eq "a";
    end

    it "consumes a token and returns the value" do
        l = TokenTable.new @tok_arr;
        expect(l.consume.value).to eq "a";
        expect(l.consume.value).to eq "+";
        expect(l.consume.value).to eq "2";
        expect(l.consume.value).to eq "eof";

        expect(l.consume).to eq nil;
        expect(l.consume).to eq nil;
    end

    it "resumes a previous token and returns the value" do
        l = TokenTable.new @tok_arr;
        expect(l.consume.value).to eq "a";
        expect(l.consume.value).to eq "+";
        expect(l.consume.value).to eq "2";
        expect(l.consume.value).to eq "eof";
        expect(l.resume.value).to eq "2";
        expect(l.resume.value).to eq "+";
        expect(l.resume.value).to eq "a";
        expect(l.resume.value).to eq "eof";
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
        l.resume;
        expect(l.token_table_pos).to eq 2;
    end

    it "gets a list element by index" do
        l = TokenTable.new @tok_arr;
        expect(l.get(1).value).to eq "+";
        expect(l.get(0).value).to eq "a";
        expect(l.get(3).value).to eq "eof";
        expect(l.get(2).value).to eq "2";

        expect(l.get(99).value).to eq "eof";
        expect(l.get(42).value).to eq "eof";
    end
end
