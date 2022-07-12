require_relative "_parser_helpers";

describe Parser do
    context "on lists" do
        it "parses an empty list as a first unit" do
            parse("()", "()");
            error("(", "missing closing parenthesis on list");
            error(")", "missing opening parenthesis on list");
            error("()stuff", "reached end of program");
        end

        it "parses multiple lists as translation units" do
            parse("(())", "(())");
            parse("((()))", "((()))");
            parse("(() () () ())", "(() () () ())");
            parse("((()) ())", "((()) ())");
            error("(()", "missing closing parenthesis on list");
            error("())", "reached end of program");
        end
    
        it "parses infinite lists of lists" do
            parse("(42)", "(42)");
            parse("(42 43 44)", "(42 43 44)");
            parse("(42 () 43 ())", "(42 () 43 ())");
            parse("(42 (43) 44 ())", "(42 (43) 44 ())");
            parse("((((()))))", "((((()))))");
        end
        
        it "parses list messages" do
            parse("(arr = (1 2 3 4))", "(= arr (1 2 3 4))");
            # TODO cascaded messages
            # parse("(arr at: 1 put: 5; at: 2: put: 6)", "()");
            parse("(b = arr is_empty?)", "(= b (is_empty? arr))");
            parse("(x = arr size)", "(= x (size arr))");
            parse("(x = arr at: 4)", "(= x (at: arr 4))");
            # TODO Keyword messages with id symbols
            # parse("(x = arr includes?: 3)", "(= x (includes?: arr 3))");
            parse("(x = arr includes: 3)", "(= x (includes: arr 3))");
            parse("(x = arr copy_from: 2 to: 4)", "(= x (copy_from:to: arr 2 4))");
            parse("(x = arr index_of: 3 if_absent: -1)", "(= x (index_of:if_absent: arr 3 (negated 1)))");
            parse("(x = arr occurrences_of: 3)", "(= x (occurrences_of: arr 3))");
            parse("(arr each: [(a) (a puts)])", "(each: arr (new Tuple ((a) (puts a))))");
            # TODO Left hand side parenthesized operands
            # parse("(b = arr conform: [(a) ((a >= 1) && (a <= 4))])", "(= b (conform: arr (new Tuple ((a) ((a >= 1) && (a <= 4))))))");
            parse("(x = arr select: [(a) (a > 2)])", "(= x (select: arr (new Tuple ((a) (> a 2)))))");
            parse("(x = arr reject: [(a) (a < 2)])", "(= x (reject: arr (new Tuple ((a) (< a 2)))))");
            parse("(x = arr collect: [(a) (a + a)])", "(= x (collect: arr (new Tuple ((a) (+ a a)))))");
            parse("(x = arr detect: [(a) (a > 3)] if_none: ())", "(= x (detect:if_none: arr (new Tuple ((a) (> a 3))) ()))");
            parse("(
                (arr = (1 2 3 4))
                (sum = 0)
                (arr each: [(a) (sum += a)])
                (sum)
            )", "((= arr (1 2 3 4)) (= sum 0) (each: arr (new Tuple ((a) (+= sum a)))) (sum))");
            # TODO Quotted list
            # parse("(sum = arr inject: 0 into: [(a c) (a + c)])", "(= sum (inject:into: arr 0 (new Tuple ((a c) (+ a c)))))");
            # parse("(sum = arr fold: 0 into: [(a c) (a + c)])");
            # parse("(max = arr
            #         inject: 0
            #         into: [
            #             (a c)
            #             ((a > c)
            #                 if_true: (a)
            #                 if_false: (b)
            #             )
            #         ]
            # )");
            parse("(x = arr shuffled)", "(= x (shuffled arr))");
        end
    end
end
