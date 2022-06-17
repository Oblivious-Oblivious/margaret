class FileLoader
    attr_reader :filename;

    def initialize(filename)
        @filename = filename;
    end

    def load
        chars = [];

        File.open(self.filename).each_char do |byte|
            chars << byte;
        end

        return chars;
    end
end
