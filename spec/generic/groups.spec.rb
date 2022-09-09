describe Parser do
    context "on groups" do
        it "parses an empty group as a first unit" do
            parse("()", []);
            error("(", "missing closing parenthesis on group.");
            error(")", "missing opening parenthesis on group.");
        end

        it "parses multiple groups as translation units" do
            parse("(())", []);
            parse("((()))", []);
            parse("((), (), (), ())", []);
            parse("((()), ())", []);
            error("(()", "missing closing parenthesis on group.");
            error("())", "reached end of program.");
        end
    
        it "parses infinite groups of groups" do
            parse("(42)", ["push_integer", "42"]);
            parse("(42, 43, 44)", ["push_integer", "42", "push_integer", "43", "push_integer", "44"]);
            parse("(42, (), 43, ())", ["push_integer", "42", "push_integer", "43"]);
            parse("(42, (43), 44, ())", ["push_integer", "42", "push_integer", "43", "push_integer", "44"]);
            parse("((((()))))", []);
            parse("(1, 2, (10, 20, 30), 3)", ["push_1", "push_2", "push_integer", "10", "push_integer", "20", "push_integer", "30", "push_integer", "3"]);
        end
        
        it "parses list messages" do
            parse("(arr = [1, 2, 3, 4])", ["push_1", "push_2", "push_integer", "3", "push_integer", "4", "push_tensor", "4", "store", "arr"]);
            parse("arr << 1 << 2 << 3", ["push_variable", "arr", "push_1", "binary", "<<", "push_2", "binary", "<<", "push_integer", "3", "binary", "<<"]);
            parse("arr add: 1 add: 2 add: 3", ["push_variable", "arr", "push_1", "keyword", "add:", "1", "push_variable", "arr", "push_2", "keyword", "add:", "1", "push_variable", "arr", "push_integer", "3", "keyword", "add:", "1"]);
            parse("(arr at: 1 put: 5, arr at: 2 put: 6)", ["push_variable", "arr", "push_1", "push_integer", "5", "keyword", "at:put:", "2", "push_variable", "arr", "push_2", "push_integer", "6", "keyword", "at:put:", "2"]);
            parse("(b = arr is_empty?)", ["push_variable", "arr", "unary", "is_empty?", "store", "b"]);
            parse("(x = arr size)", ["push_variable", "arr", "unary", "size", "store", "x"]);
            parse("(x = arr at: 4)", ["push_variable", "arr", "push_integer", "4", "keyword", "at:", "1", "store", "x"]);
            parse("(x = arr includes?: 3)", ["push_variable", "arr", "push_integer", "3", "keyword", "includes?:", "1", "store", "x"]);
            parse("(x = arr includes: 3)", ["push_variable", "arr", "push_integer", "3", "keyword", "includes:", "1", "store", "x"]);
            parse("(x = arr copy_from: 2 to: 4)", ["push_variable", "arr", "push_2", "push_integer", "4", "keyword", "copy_from:to:", "2", "store", "x"]);
            parse("(x = arr index_of: 3 if_absent: -1)", ["push_variable", "arr", "push_integer", "3", "push_minus_1", "keyword", "index_of:if_absent:", "2", "store", "x"]);
            parse("(x = arr occurrences_of: 3)", ["push_variable", "arr", "push_integer", "3", "keyword", "occurrences_of:", "1", "store", "x"]);
            parse("(arr each: ->{ a | a puts })", ["push_variable", "arr", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "unary", "puts", "ENDpush_proc", "keyword", "each:", "1"]);
            parse("(b = arr conform: ->{ a | (a >= 1) && (a <= 4) })", ["push_variable", "arr", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "push_1", "binary", ">=", "push_variable", "a", "push_integer", "4", "binary", "<=", "binary", "&&", "ENDpush_proc", "keyword", "conform:", "1", "store", "b"]);
            parse("(x = arr select: ->{ a | a > 2 })", ["push_variable", "arr", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "push_2", "binary", ">", "ENDpush_proc", "keyword", "select:", "1", "store", "x"]);
            parse("(x = arr reject: ->{ a | a < 2 })", ["push_variable", "arr", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "push_2", "binary", "<", "ENDpush_proc", "keyword", "reject:", "1", "store", "x"]);
            parse("(x = arr collect: ->{ a | a + a })", ["push_variable", "arr", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "push_variable", "a", "binary", "+", "ENDpush_proc", "keyword", "collect:", "1", "store", "x"]);
            parse("(x = arr detect: ->{ a | a > 3 } if_none: ())", ["push_variable", "arr", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "push_integer", "3", "binary", ">", "ENDpush_proc", "keyword", "detect:if_none:", "2", "store", "x"]);
            parse("(
                arr = [1, 2, 3, 4],
                sum = 0,
                arr each: ->{ a | sum += a },
                sum
            )", ["push_1", "push_2", "push_integer", "3", "push_integer", "4", "push_tensor", "4", "store", "arr", "push_0", "store", "sum", "push_variable", "arr", "STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "sum", "push_variable", "a", "binary", "+=", "ENDpush_proc", "keyword", "each:", "1", "push_variable", "sum"]);
            parse("(sum = arr inject: 0 into: ->{ a, c | a + c })", ["push_variable", "arr", "push_0", "STARTpush_proc", "push_variable", "a", "push_variable", "c", "push_tensor", "2", "push_variable", "a", "push_variable", "c", "binary", "+", "ENDpush_proc", "keyword", "inject:into:", "2", "store", "sum"]);
            parse("(sum = arr fold: 0 into: ->{ a, c | a + c })", ["push_variable", "arr", "push_0", "STARTpush_proc", "push_variable", "a", "push_variable", "c", "push_tensor", "2", "push_variable", "a", "push_variable", "c", "binary", "+", "ENDpush_proc", "keyword", "fold:into:", "2", "store", "sum"]);
            parse("(max = arr
                    inject: 0
                    into: -> { a, c |
                        (a > c) if_true: a
                                 if_false: b
                    }
            )", ["push_variable", "arr", "push_0", "STARTpush_proc", "push_variable", "a", "push_variable", "c", "push_tensor", "2", "push_variable", "a", "push_variable", "c", "binary", ">", "push_variable", "a", "push_variable", "b", "keyword", "if_true:if_false:", "2", "ENDpush_proc", "keyword", "inject:into:", "2", "store", "max"]);
            parse("(x = arr shuffled)", ["push_variable", "arr", "unary", "shuffled", "store", "x"]);
        end
    end
end
