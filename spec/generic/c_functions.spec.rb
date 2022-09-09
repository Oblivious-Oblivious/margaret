describe Parser do
    context "on C functions" do
        it "parses C function definitions" do
            parse("###void f()", ["STARTpush_c_function", "push_variable", "void", "push_variable", "f", "push_tensor", "0", "ENDpush_c_function"]);
            parse("###void f2(int a, int b)", ["STARTpush_c_function", "push_variable", "void", "push_variable", "f2", "push_variable", "CFunParam", "push_variable", "int", "push_variable", "a", "keyword", "c_type:c_name:", "2", "push_variable", "CFunParam", "push_variable", "int", "push_variable", "b", "keyword", "c_type:c_name:", "2", "push_tensor", "2", "ENDpush_c_function"]);
            # TODO Creates matchers and extensions at compile time
        end
    end
end
