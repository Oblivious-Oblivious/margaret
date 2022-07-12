require_relative "_parser_helpers";

describe Parser do
    context "on identifiers" do
        it "parses self and super" do
            parse("(123)", "(123)");
            parse("(self)", "(self)");
            parse("(super)", "(super)");
            parse("(self self self)", "(self self self)");
            parse("(self super self)", "(self super self)");
            parse("(self 42 super (10) ((self) (super 42)))", "(self 42 super (10) ((self) (super 42)))");
        end
        
        it "parses identifiers" do
            parse("(s (42) self)", "(s (42) self)");
            parse("(ident, 42, another)", "(, (, ident 42) another)");
            parse("(stuff,ident2)", "(, stuff ident2)");
        end
    end
end
