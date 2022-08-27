require_relative "_parser_helpers";

describe Parser do
    context "on method definitions" do
        it "parses unary methods" do
            parse("#incr => self + 1",   %Q{selector:block: Method "incr" params:function: Block () + self 1});
            parse("#  incr => self + 1", %Q{selector:block: Method "incr" params:function: Block () + self 1});
            parse("#is_empty? => true", %Q{selector:block: Method "is_empty?" params:function: Block () true});

            # TODO prolog-like multimethod polymorphism
            # parse("#(0) fact => 1");
            "
            #(0) fact => 1,
            #(_) fact => self * (self-1) fact
            "
        end

        it "parses binary methods" do
            parse("#** a_number => self raised_to: a_number", %Q{selector:block: Method "**" params:function: Block (a_number) raised_to: self a_number});
            # parse("#(0) ** a_number => 0", "");
            # parse("#(0) ** (0) => nil", "");
        end

        it "parses keyword methods" do
            parse("#add: element at: position => 42", %Q{selector:block: Method "add:at:" params:function: Block (element, position) 42});
            parse("#ok?: value1 otherwise!: value2 => 17", %Q{selector:block: Method "ok?:otherwise!:" params:function: Block (value1, value2) 17});
            # parse("#([]) add: (element) at: (position) => 17");
            # parse("#([]) add: ('a') at: (0) => ['a']");
            # parse("#add: ('a') at: (0) => ['a'] ++ self");

            parse("#times: a_block => (
                remaining = self,
                ->{ (remaining = remaining - 1) >= 0 } while_true: ->{ a_block value }
            )", %Q{selector:block: Method "times:" params:function: Block (a_block) (= remaining self, while_true: params:function: Block () >= (= remaining - remaining 1) 0 params:function: Block () value a_block)});
        end
    end
end
