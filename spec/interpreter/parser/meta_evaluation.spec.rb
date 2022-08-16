require_relative "_parser_helpers";

describe Parser do
    context "on meta-evaluation" do
        it "compiles and calls messages dynamically" do
            # NOTE Figure out dynamic send
        end

        it "parses metaclass messages" do
            parse("(x = String name)", "(= x name String)");
            parse("(x = String category)", "(= x category String)");
            parse("(x = String description)", "(= x description String)");
            parse("(x = String kind_of_subclass)", "(= x kind_of_subclass String)");
            parse("(x = String definition)", "(= x definition String)");
            parse("(x = String field_names)", "(= x field_names String)");
            parse("(x = String all_field_names)", "(= x all_field_names String)");
            parse("(x = String selectors)", "(= x selectors String)");
            parse("(x = String source_code_at: :message)", %Q{(= x source_code_at: String :"message")});
            parse(%Q{(x = String source_code_at: "message")}, %Q{(= x source_code_at: String "message")});
            parse("(x = String all_instances)", "(= x all_instances String)");
            parse("(x = String superclass)", "(= x superclass String)");
            parse("(x = String all_superclasses)", "(= x all_superclasses String)");
            parse("(x = String subclasses)", "(= x subclasses String)");
            parse("(x = String all_subclasses)", "(= x all_subclasses String)");
            parse("(x = String number_of_instances)", "(= x number_of_instances String)");
        end
    end
end
