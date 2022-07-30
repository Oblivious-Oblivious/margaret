require_relative "_parser_helpers";

describe Parser do
    context "on identifiers" do        
        it "parses identifiers" do
            parse("(ident, 42, another)", "(, (, ident 42) another)");
            parse("(stuff,ident2)", "(, stuff ident2)");
        end
    end
end
