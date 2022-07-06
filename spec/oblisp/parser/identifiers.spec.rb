require_relative "_parser_helpers";

describe Parser do
    context "on identifiers" do
        it "parses self and super" do
            parse("(self)");
            parse("(super)");
            parse("(self self self)");
            parse("(self super self)");
            parse("(self 42 super (10) ((self) (super 42)))");
        end
        
        it "parses identifiers" do
            parse("(s (42) self)");
            parse("(ident 42 another)");
            parse("(stuff ident2)");
            # TODO
            parse("(obj msg?)");
        end
    end
end
