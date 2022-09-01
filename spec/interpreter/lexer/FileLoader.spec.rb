describe FileLoader do
    it "creates a FileLoader object" do
        f = FileLoader.new "test.marg";
        expect(f).not_to be nil;
    end

    it "responds to api messages" do
        f = FileLoader.new "test.marg";
        expect(f).to respond_to :load;
    end

    it "loads text character by character" do
        File.open("test.marg", "w") do |f|
            f.write("text");
        end

        f = FileLoader.new "test.marg";
        expect(f.load).to eq ['t','e','x','t'];

        File.delete("test.marg");
    end

    it "loads a bigger file" do
        File.open("test2.marg", "w") do |f|
            f.write("(42 factorial. 2 + 3)");
        end

        f = FileLoader.new "test2.marg";
        expect(f.load).to eq [
            '(','4','2',' ','f','a','c','t','o','r','i','a','l','.',' ','2',' ','+',' ','3',')'
        ];

        File.delete("test2.marg");
    end
end
