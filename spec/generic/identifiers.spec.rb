describe Parser do
    context "on identifiers" do        
        it "parses identifiers" do
            parse("(ident, 42, another)", ["push_variable", "ident", "push_integer", "42", "push_variable", "another"]);
            parse("(stuff,ident2)", ["push_variable", "stuff", "push_variable", "ident2"]);
        end

        it "parses normal and instance variables" do
            parse("variable", ["push_variable", "variable"]);
            parse("@instvar", ["push_instance", "instvar"]);
            parse("@x", ["push_instance", "x"]);
        end

        it "parses pseudo variables (used as normal identifiers)" do
            parse("nil", ["push_nil"]);
            parse("true", ["push_true"]);
            parse("false", ["push_false"]);
            parse("self", ["push_self"]);
            parse("super", ["push_super"]);
        end
    end
end
