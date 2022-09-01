CURR_VERSION = "0.2.0";

describe Margaret do
    it "checks that latest version should be #{CURR_VERSION}" do
        expect(Margaret::VERSION).to eq(CURR_VERSION);
    end
end
