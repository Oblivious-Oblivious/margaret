describe Parser do
    context "on meta-evaluation" do
        it "compiles and calls messages dynamically" do
            # NOTE Figure out dynamic send
        end

        it "parses metaclass messages" do
            parse("(x = String name)", ["push_variable", "String", "unary", "name", "store", "x"]);
            parse("(x = String category)", ["push_variable", "String", "unary", "category", "store", "x"]);
            parse("(x = String description)", ["push_variable", "String", "unary", "description", "store", "x"]);
            parse("(x = String kind_of_subclass)", ["push_variable", "String", "unary", "kind_of_subclass", "store", "x"]);
            parse("(x = String definition)", ["push_variable", "String", "unary", "definition", "store", "x"]);
            parse("(x = String field_names)", ["push_variable", "String", "unary", "field_names", "store", "x"]);
            parse("(x = String all_field_names)", ["push_variable", "String", "unary", "all_field_names", "store", "x"]);
            parse("(x = String selectors)", ["push_variable", "String", "unary", "selectors", "store", "x"]);
            parse(%Q{(x = String source_code_at: "message")}, ["push_variable", "String", "push_string", %Q{"message"}, "keyword", "source_code_at:", "1", "store", "x"]);
            parse("(x = String all_instances)", ["push_variable", "String", "unary", "all_instances", "store", "x"]);
            parse("(x = String superclass)", ["push_variable", "String", "unary", "superclass", "store", "x"]);
            parse("(x = String all_superclasses)", ["push_variable", "String", "unary", "all_superclasses", "store", "x"]);
            parse("(x = String subclasses)", ["push_variable", "String", "unary", "subclasses", "store", "x"]);
            parse("(x = String all_subclasses)", ["push_variable", "String", "unary", "all_subclasses", "store", "x"]);
            parse("(x = String number_of_instances)", ["push_variable", "String", "unary", "number_of_instances", "store", "x"]);
        end
    end
end
