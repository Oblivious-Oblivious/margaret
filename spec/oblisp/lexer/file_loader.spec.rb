describe FileLoader do
    it "creates a FileLoader object" do
        f = FileLoader.new "test.obl";
        expect(f).not_to be nil;
    end

    it "responds to api messages" do
        f = FileLoader.new "test.obl";
        expect(f).to respond_to :load;
    end

    it "loads text character by character" do
        File.open("test.obl", "w") do |f|
            f.write("text");
        end

        f = FileLoader.new "test.obl";
        expect(f.load).to eq ['t','e','x','t'];

        File.delete("test.obl");
    end

    it "loads a bigger file" do
        File.open("test2.obl", "w") do |f|
            f.write("(42 factorial. 2 + 3)");
        end

        f = FileLoader.new "test2.obl";
        expect(f.load).to eq [
            '(','4','2',' ','f','a','c','t','o','r','i','a','l','.',' ','2',' ','+',' ','3',')'
        ];

        File.delete("test2.obl");
    end
end
