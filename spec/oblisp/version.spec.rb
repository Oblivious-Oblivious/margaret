CURR_VERSION = "0.1.0";

describe Oblisp do
    it "checks that latest version should be #{CURR_VERSION}" do
        expect(Oblisp::VERSION).to eq(CURR_VERSION);
    end
end
