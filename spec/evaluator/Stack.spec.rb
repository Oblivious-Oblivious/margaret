describe Stack do
    it "performs generic tests" do
        s = Stack.new;
        s.push(1);
        s.push(2);
        s.push(3);

        expect(s.peek(0)).to eq 3;
        expect(s.peek(1)).to eq 2;
        expect(s.peek(2)).to eq 1;
        expect(s.peek(3)).to eq nil;
        expect(s.peek(4)).to eq nil;
        expect(s.pop).to eq 3;
        expect(s.pop).to eq 2;
        expect(s.pop).to eq 1;
        expect(s.pop).to eq nil;
        expect(s.pop).to eq nil;
        expect(s.pop).to eq nil;

        expect(s.arr).to eq [];
    end
end
