require_relative "_parser_helpers";

describe Parser do
    context "on C functions" do
        it "parses C function definitions" do
            parse("###void f()", %Q{name:params:return_type: CLib "f" "void" []});
            parse("###void f2(int a, int b)", %Q{name:params:return_type: CLib "f2" "void" [c_type:c_name: CFunParam "int" "a", c_type:c_name: CFunParam "int" "b"]});
            # TODO Creates matchers and extensions at compile time
        end
    end
end
