class FileLoader
    def load(filename)
        chars = [];

        File.open(filename).each_char do |byte|
            chars << byte;
        end

        return chars;
    end
end
