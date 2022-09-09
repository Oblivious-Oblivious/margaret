describe Parser do
    context "on method definitions" do
        it "parses unary methods" do
            parse("#incr => self + 1",   ["STARTpush_unary_method", %Q{"incr"}, "push_self", "push_1", "binary", "+", "ENDpush_unary_method"]);
            parse("#  incr => self + 1", ["STARTpush_unary_method", %Q{"incr"}, "push_self", "push_1", "binary", "+", "ENDpush_unary_method"]);
            parse("#is_empty? => true", ["STARTpush_unary_method", %Q{"is_empty?"}, "push_true", "ENDpush_unary_method"]);

            # TODO prolog-like multimethod polymorphism
            # parse("#0 fact => 1");
            "
            #0 fact => 1,
            #self fact => self * (self-1) fact
            "
        end

        it "parses binary methods" do
            parse("#** a_number => self raised_to: a_number", ["STARTpush_binary_method", %Q{"**"}, "push_variable", "a_number", "push_self", "push_variable", "a_number", "keyword", "raised_to:", "1", "ENDpush_binary_method"]);
            # parse("#0 ** a_number => 0");
            # parse("#0 ** 0 => nil");
        end

        it "parses keyword methods" do
            parse("#add: element at: position => 42", ["STARTpush_keyword_method", %Q{"add:at:"}, "push_variable", "element", "push_variable", "position", "push_tensor", "2", "push_integer", "42", "ENDpush_keyword_method"]);
            parse("#ok?: value1 otherwise!: value2 => 17", ["STARTpush_keyword_method", %Q{"ok?:otherwise!:"}, "push_variable", "value1", "push_variable", "value2", "push_tensor", "2", "push_integer", "17", "ENDpush_keyword_method"]);
            # parse("#[] add: element at: position => 17");
            # parse("#[] add: 'a' at: 0 => ['a']");
            # parse("#add: 'a' at: 0 => ['a'] ++ self");

            parse("#times: a_proc => (
                remaining = self,
                ->{ (remaining = remaining - 1) >= 0 } while_true: ->{ a_proc value }
            )", ["STARTpush_keyword_method", %Q{"times:"}, "push_variable", "a_proc", "push_tensor", "1", "push_self", "store", "remaining", "STARTpush_proc", "push_tensor", "0", "push_variable", "remaining", "push_1", "binary", "-", "store", "remaining", "push_0", "binary", ">=", "ENDpush_proc", "STARTpush_proc", "push_tensor", "0", "push_variable", "a_proc", "unary", "value", "ENDpush_proc", "keyword", "while_true:", "1", "ENDpush_keyword_method"]);
        end
    end
end
