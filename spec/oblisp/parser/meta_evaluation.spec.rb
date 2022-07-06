require_relative "_parser_helpers";

describe Parser do
    context "on meta-evaluation" do
        it "compiles and calls messages dynamically" do
            # TODO dynamic send
        end

        it "parses metaclass messages" do
            parse("(x = String name)");
            parse("(x = String category)");
            parse("(x = String description)");
            parse("(x = String kind_of_subclass)");
            parse("(x = String definition)");
            parse("(x = String field_names)");
            parse("(x = String all_field_names)");
            # parse("(x = String all_instance_vars_names)");
            # parse("(x = String class_instance_vars_names)");
            parse("(x = String selectors)");
            parse("(x = String source_code_at: :message)");
            parse(%Q{(x = String source_code_at: "message")});
            parse("(x = String all_instances)");
            parse("(x = String superclass)");
            parse("(x = String all_superclasses)");
            parse("(x = String subclasses)");
            parse("(x = String all_subclasses)");
            parse("(x = String number_of_instances)");
        end
    end
end
