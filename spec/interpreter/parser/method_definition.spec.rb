require_relative "_parser_helpers";

describe Parser do
    context "on method definitions" do
        it "parses unary methods" do
            parse("#incr => self + 1",   %Q{selector:proc: Method "incr" params:function: Proc () + self 1});
            parse("#  incr => self + 1", %Q{selector:proc: Method "incr" params:function: Proc () + self 1});
            parse("#is_empty? => true", %Q{selector:proc: Method "is_empty?" params:function: Proc () true});

            # TODO prolog-like multimethod polymorphism
            # parse("#0 fact => 1");
            "
            #0 fact => 1,
            #self fact => self * (self-1) fact
            "
        end

        it "parses binary methods" do
            parse("#** a_number => self raised_to: a_number", %Q{selector:proc: Method "**" params:function: Proc (a_number) raised_to: self a_number});
            # parse("#0 ** a_number => 0", "");
            # parse("#0 ** 0 => nil", "");
        end

        it "parses keyword methods" do
            parse("#add: element at: position => 42", %Q{selector:proc: Method "add:at:" params:function: Proc (element, position) 42});
            parse("#ok?: value1 otherwise!: value2 => 17", %Q{selector:proc: Method "ok?:otherwise!:" params:function: Proc (value1, value2) 17});
            # parse("#[] add: element at: position => 17");
            # parse("#[] add: 'a' at: 0 => ['a']");
            # parse("#add: 'a' at: 0 => ['a'] ++ self");

            parse("#times: a_proc => (
                remaining = self,
                ->{ (remaining = remaining - 1) >= 0 } while_true: ->{ a_proc value }
            )", %Q{selector:proc: Method "times:" params:function: Proc (a_proc) (= remaining self, while_true: params:function: Proc () >= (= remaining - remaining 1) 0 params:function: Proc () value a_proc)});
        end
    end
end
