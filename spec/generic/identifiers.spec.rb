describe Parser do
    context "on identifiers" do        
        it "parses identifiers" do
            parse("(ident, 42, another)", "(ident, 42, another)");
            parse("(stuff,ident2)", "(stuff, ident2)");
        end

        it "parses normal and instance variables" do
            parse("variable", "variable");
            parse("@instvar", "@instvar");
            parse("@x", "@x");
        end

        it "parses pseudo variables (used as normal identifiers)" do
            parse("nil", "nil");
            parse("true", "true");
            parse("false", "false");
            parse("self", "self");
            parse("super", "super");
        end
    end
end
