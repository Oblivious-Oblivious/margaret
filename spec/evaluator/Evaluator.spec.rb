describe Evaluator do
    it "evaluates a simple message" do
        # evalcodes("2 + 3", "5");
    end

    it "evaluates integers" do
        evalcodes("0", "0");
        evalcodes("-0", "0");
        evalcodes("+0", "0");
        evalcodes("1", "1");
        evalcodes("+1", "1");
        evalcodes("-1", "-1");
        evalcodes("2", "2");
        evalcodes("+2", "2");
        evalcodes("42", "42");
        evalcodes("-42", "-42");
        evalcodes("+42", "42");
        evalcodes("4_200", "4200");
        evalcodes("-4_200", "-4200");
    end

    it "evaluates floats" do
        evalcodes("42.0", "42.0");
        evalcodes("-42.0", "-42.0");
        evalcodes("986513.00056129", "986513.00056129");
        evalcodes("-986513.00056129", "-986513.00056129");
    end

    it "evaluates binaries" do
        evalcodes("0b0110", "6");
        evalcodes("0B10", "2");
        evalcodes("-0b0110", "-6");
        evalcodes("-0B10", "-2");
        # evalcodes("(
        #     x = 0b0101 + 0b1011,
        #     x to_int puts,
        # )", "16");
    end

    it "evaluates hexadecimals" do
        evalcodes("0xbeef", "48879");
        evalcodes("-0xbeEf", "-48879");
        evalcodes("0X0427", "1063");
        evalcodes("-0X0427", "-1063");
        # evalcodes("x = 0xbeef to_bin to_int puts", "48879");
        # evalcodes("0xbeef - 0xabb2", "4925");
    end

    it "evaluates octals" do
        evalcodes("0o741", "481");
        evalcodes("-0o741", "-481");
        evalcodes("0O0210", "136");
        evalcodes("-0O0210", "-136");
        # evalcodes("0o751 to_hex to_bin to_int puts", "489");
        # evalcodes("0O541 + 0o777", "864");
    end

    it "evaluates characters" do
        evalcodes("'a'", "'a'");
        evalcodes("'\n'", "'\n'");
        evalcodes("'œ'", "'œ'");
        # evalcodes("('a' to_uppercase)", "'A'");
        # evalcodes("('B' to_ascii)", "42");
        # evalcodes("('a' <= 'b')", "true");
    end

    it "evaluates strings" do
        evalcodes(%Q{"string"}, %Q{"string"});
    end

    # it "evaluates variables" do
    #     evalcodes("ident", ["push_variable", "ident", "pop"]);
    #     evalcodes("variable", ["push_variable", "variable", "pop"]);
    #     evalcodes("@instvar", ["push_instance", "instvar", "pop"]);
    #     evalcodes("@x", ["push_instance", "x", "pop"]);
    #     evalcodes("nil", ["push_nil", "pop"]);
    #     evalcodes("true", ["push_true", "pop"]);
    #     evalcodes("false", ["push_false", "pop"]);
    #     evalcodes("self", ["push_self", "pop"]);
    #     evalcodes("super", ["push_super", "pop"]);
    # end

    it "evaluates groups" do
        evalcodes("()", "nil");
        evalcodes("(1, 2, 3)", "3");
        evalcodes("(1, 2, (10, 20, 30), 3)", "3");
        evalcodes(%Q{(1, "2", c, 42.42)}, "42.42");
    end

    # it "evaluates tensors" do
    #     evalcodes("[]", "[]");
    #     evalcodes("[41, 42]", "[41, 42]");
    #     evalcodes(%Q{[42, "str", var]}, %Q{[42, "str", var]});
    # end

    # it "evaluates hashes" do
    #     evalcodes("{}", ["push_hash", "0", "pop"]);
    #     evalcodes("{a: {}, b: {}}", ["push_variable", "Association", "push_string", %Q{"a"}, "push_hash", "0", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_hash", "0", "keyword", "key:value:", "2", "push_hash", "2", "pop"]);
    #     evalcodes("{a: 1, b: 2, c: 3}", ["push_variable", "Association", "push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3", "pop"]);
    #     evalcodes(%Q{{"a": 1, "b": 2, "c": 3}}, ["push_variable", "Association", "push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3", "pop"]);
    # end

    # it "evaluates procs" do
    #     evalcodes("->{x = (x = 1, y = 2)}", ["STARTpush_proc", "push_tensor", "0", "push_1", "store", "x", "push_2", "store", "y", "store", "x", "ENDpush_proc", "pop"]);
    #     evalcodes("x = ->{
    #         v1, v2, (
    #             v1 += 1,
    #             v1 += 2,
    #             v1 * v2
    #         )
    #     }", ["STARTpush_proc", "push_variable", "v1", "push_variable", "v2", "push_tensor", "2", "push_variable", "v1", "push_1", "binary", "+=", "push_variable", "v1", "push_2", "binary", "+=", "push_variable", "v1", "push_variable", "v2", "binary", "*", "ENDpush_proc", "store", "x", "pop"]);
    #     evalcodes("->{42}", ["STARTpush_proc", "push_tensor", "0", "push_integer", "42", "ENDpush_proc", "pop"]);
    #     evalcodes("->{a | a puts}", ["STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "unary", "puts", "ENDpush_proc", "pop"]);
    #     evalcodes("->{2 + 3}", ["STARTpush_proc", "push_tensor", "0", "push_2", "push_integer", "3", "binary", "+", "ENDpush_proc", "pop"]);
    #     evalcodes("->{(x = 1, y = 2, x + y)}", ["STARTpush_proc", "push_tensor", "0", "push_1", "store", "x", "push_2", "store", "y", "push_variable", "x", "push_variable", "y", "binary", "+", "ENDpush_proc", "pop"]);
    #     evalcodes("->{a, b | a + b}", ["STARTpush_proc", "push_variable", "a", "push_variable", "b", "push_tensor", "2", "push_variable", "a", "push_variable", "b", "binary", "+", "ENDpush_proc", "pop"]);
    #     evalcodes("->{a, a}", ["STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "ENDpush_proc", "pop"]);
    #     evalcodes("->{x = 2} exec", ["STARTpush_proc", "push_tensor", "0", "push_2", "store", "x", "ENDpush_proc", "unary", "exec", "pop"]);
    #     evalcodes("->{param | param puts} value: 42", ["STARTpush_proc", "push_variable", "param", "push_tensor", "1", "push_variable", "param", "unary", "puts", "ENDpush_proc", "push_integer", "42", "keyword", "value:", "1", "pop"]);
    # end

    # it "evaluates assignment" do
    #     evalcodes("x = 4", ["push_integer", "4", "store", "x", "pop"]);
    #     evalcodes("x = y = z = 6", ["push_integer", "6", "store", "z", "store", "y", "store", "x", "pop"]);
    #     evalcodes("x = (y = 6) + 1", ["push_integer", "6", "store", "y", "push_1", "binary", "+", "store", "x", "pop"]);
    #     evalcodes("@x = x + 2", ["push_variable", "x", "push_2", "binary", "+", "store_instance", "x", "pop"]);
    #     evalcodes("a = b = (c = 42) + 12", ["push_integer", "42", "store", "c", "push_integer", "12", "binary", "+", "store", "b", "store", "a", "pop"]);
    #     evalcodes("a = a negate", ["push_variable", "a", "unary", "negate", "store", "a", "pop"]);
    #     evalcodes("@a = @a negate", ["push_instance", "a", "unary", "negate", "store_instance", "a", "pop"]);
    # end

    # it "evaluates unary messages" do
    #     evalcodes("42 factorial", ["push_integer", "42", "unary", "factorial", "pop"]);
    #     evalcodes("17 incr puts", ["push_integer", "17", "unary", "incr", "unary", "puts", "pop"]);
    #     evalcodes("23 one two three", ["push_integer", "23", "unary", "one", "unary", "two", "unary", "three", "pop"]);
    #     evalcodes("@inst one two three", ["push_instance", "inst", "unary", "one", "unary", "two", "unary", "three", "pop"]);
    #     evalcodes("42 puts", ["push_integer", "42", "unary", "puts", "pop"]);
    #     evalcodes("obj puts", ["push_variable", "obj", "unary", "puts", "pop"]);
    #     evalcodes("x = obj puts", ["push_variable", "obj", "unary", "puts", "store", "x", "pop"]);
    #     evalcodes("(obj puts, 42 incr)", ["push_variable", "obj", "unary", "puts", "push_integer", "42", "unary", "incr", "pop"]);
    #     evalcodes("((obj puts), (42 incr))", ["push_variable", "obj", "unary", "puts", "push_integer", "42", "unary", "incr", "pop"]);
    #     evalcodes("42 incr incr decr decr", ["push_integer", "42", "unary", "incr", "unary", "incr", "unary", "decr", "unary", "decr", "pop"]);
    #     evalcodes("x = 42 incr incr decr decr", ["push_integer", "42", "unary", "incr", "unary", "incr", "unary", "decr", "unary", "decr", "store", "x", "pop"]);
    #     evalcodes("x incr!", ["push_variable", "x", "unary", "incr!", "pop"]);
    #     evalcodes("x is_empty?", ["push_variable", "x", "unary", "is_empty?", "pop"]);
    #     evalcodes("(42 one, 43 two, 44 three, 45, 46 four)", ["push_integer", "42", "unary", "one", "push_integer", "43", "unary", "two", "push_integer", "44", "unary", "three", "push_integer", "45", "push_integer", "46", "unary", "four", "pop"]);
    #     evalcodes("p1 + p2 calc puts", ["push_variable", "p1", "push_variable", "p2", "unary", "calc", "unary", "puts", "binary", "+", "pop"]);
    #     evalcodes("(p1 + p2 calc) puts", ["push_variable", "p1", "push_variable", "p2", "unary", "calc", "binary", "+", "unary", "puts", "pop"]);
    # end

    # it "evaluates binary messages" do
    #     evalcodes("2 + 3", ["push_2", "push_integer", "3", "binary", "+", "pop"]);
    #     evalcodes("2 + 3 * 4 + 5", ["push_2", "push_integer", "3", "binary", "+", "push_integer", "4", "binary", "*", "push_integer", "5", "binary", "+", "pop"]);
    #     evalcodes("2 * 5", ["push_2", "push_integer", "5", "binary", "*", "pop"]);
    #     evalcodes("a + b", ["push_variable", "a", "push_variable", "b", "binary", "+", "pop"]);
    #     evalcodes("42 factorial + 17", ["push_integer", "42", "unary", "factorial", "push_integer", "17", "binary", "+", "pop"]);
    #     evalcodes("41 factorial + 42 factorial + 43 factorial", ["push_integer", "41", "unary", "factorial", "push_integer", "42", "unary", "factorial", "binary", "+", "push_integer", "43", "unary", "factorial", "binary", "+", "pop"]);
    #     evalcodes("(41 + 1, 42 + 0, 43 - 1)", ["push_integer", "41", "push_1", "binary", "+", "push_integer", "42", "push_0", "binary", "+", "push_integer", "43", "push_1", "binary", "-", "pop"]);
    #     evalcodes("((41 + 1), (42 + 0), (43 - 1))", ["push_integer", "41", "push_1", "binary", "+", "push_integer", "42", "push_0", "binary", "+", "push_integer", "43", "push_1", "binary", "-", "pop"]);
    #     evalcodes("x = a + b * 2 - 5", ["push_variable", "a", "push_variable", "b", "binary", "+", "push_2", "binary", "*", "push_integer", "5", "binary", "-", "store", "x", "pop"]);
    #     evalcodes("x << item", ["push_variable", "x", "push_variable", "item", "binary", "<<", "pop"]);
    #     evalcodes("[1, 2, 3] ++ [4, 5]", ["push_1", "push_2", "push_integer", "3", "push_tensor", "3", "push_integer", "4", "push_integer", "5", "push_tensor", "2", "binary", "++", "pop"]);
    #     evalcodes("(4 + 3) * (5 + 6)", ["push_integer", "4", "push_integer", "3", "binary", "+", "push_integer", "5", "push_integer", "6", "binary", "+", "binary", "*", "pop"]);
    # end

    # it "evaluates keyword messages" do
    #     evalcodes("list put: 42 at: 5", ["push_variable", "list", "push_integer", "42", "push_integer", "5", "keyword", "put:at:", "2", "pop"]);
    #     evalcodes("list put: (42 incr) at: 5", ["push_variable", "list", "push_integer", "42", "unary", "incr", "push_integer", "5", "keyword", "put:at:", "2", "pop"]);
    #     evalcodes("(
    #         list = List new,
    #         list put: 42 at: 5,
    #         x = list get: 2,
    #         x puts
    #     )", ["push_variable", "List", "unary", "new", "store", "list", "push_variable", "list", "push_integer", "42", "push_integer", "5", "keyword", "put:at:", "2", "push_variable", "list", "push_2", "keyword", "get:", "1", "store", "x", "push_variable", "x", "unary", "puts", "pop"]);
    #     evalcodes("2 + 3 incr add: 11", ["push_2", "push_integer", "3", "unary", "incr", "binary", "+", "push_integer", "11", "keyword", "add:", "1", "pop"]);
    #     evalcodes("[1, 2, 3] reverse!: true", ["push_1", "push_2", "push_integer", "3", "push_tensor", "3", "push_true", "keyword", "reverse!:", "1", "pop"]);
    #     evalcodes("true then: 1 else: 2", ["push_true", "push_1", "push_2", "keyword", "then:else:", "2", "pop"]);
    #     evalcodes("x ok?: true otherwise!: false", ["push_variable", "x", "push_true", "push_false", "keyword", "ok?:otherwise!:", "2", "pop"]);
    #     evalcodes("(5 + 13) greater_than?: (11 + 2)", ["push_integer", "5", "push_integer", "13", "binary", "+", "push_integer", "11", "push_2", "binary", "+", "keyword", "greater_than?:", "1", "pop"]);
    #     evalcodes("42 factorial and: (2 + 3)", ["push_integer", "42", "unary", "factorial", "push_2", "push_integer", "3", "binary", "+", "keyword", "and:", "1", "pop"]);
    #     evalcodes("(list at: 3) + (list at: 5)", ["push_variable", "list", "push_integer", "3", "keyword", "at:", "1", "push_variable", "list", "push_integer", "5", "keyword", "at:", "1", "binary", "+", "pop"]);
    #     evalcodes("arr add: 1 add: 2 add: 3", ["push_variable", "arr", "push_1", "keyword", "add:", "1", "push_variable", "arr", "push_2", "keyword", "add:", "1", "push_variable", "arr", "push_integer", "3", "keyword", "add:", "1", "push_tensor", "3", "pop"]);
    #     evalcodes("arr add: 'a' add: 'b' at: 3", ["push_variable", "arr", "push_char", "'a'", "push_char", "'b'", "push_integer", "3", "keyword", "add:add:at:", "3", "pop"]);
    #     evalcodes("arr add: 'a' at: 1 add: 'b' at: 2", ["push_variable", "arr", "push_char", "'a'", "push_1", "push_char", "'b'", "push_2", "keyword", "add:at:add:at:", "4", "pop"]);
    # end

    # it "evaluates unary method definitions" do
    #     evalcodes("#incr => self + 1",   ["STARTpush_unary_method", %Q{"incr"}, "push_self", "push_1", "binary", "+", "ENDpush_unary_method", "pop"]);
    #     evalcodes("#  incr => self + 1", ["STARTpush_unary_method", %Q{"incr"}, "push_self", "push_1", "binary", "+", "ENDpush_unary_method", "pop"]);
    #     evalcodes("#is_empty? => true", ["STARTpush_unary_method", %Q{"is_empty?"}, "push_true", "ENDpush_unary_method", "pop"]);
    #     # evalcodes("# 0 fact => 1");
    #     "
    #     # 0 fact => 1,
    #     # _ fact => self * (self-1) fact
    #     "
    # end

    # it "evaluates binary method definitions" do
    #     evalcodes("#** a_number => self raised_to: a_number", ["STARTpush_binary_method", %Q{"**"}, "push_variable", "a_number", "push_self", "push_variable", "a_number", "keyword", "raised_to:", "1", "ENDpush_binary_method", "pop"]);
    #     # evalcodes("# 0 ** a_number => 0", "");
    #     # evalcodes("# 0 ** 0 => nil", "");
    # end

    # it "evaluates keyword method definitions" do
    #     evalcodes("#add: element at: position => 42", ["STARTpush_keyword_method", %Q{"add:at:"}, "push_variable", "element", "push_variable", "position", "push_tensor", "2", "push_integer", "42", "ENDpush_keyword_method", "pop"]);
    #     evalcodes("#ok?: value1 otherwise!: value2 => 17", ["STARTpush_keyword_method", %Q{"ok?:otherwise!:"}, "push_variable", "value1", "push_variable", "value2", "push_tensor", "2", "push_integer", "17", "ENDpush_keyword_method", "pop"]);
    #     # evalcodes("# [] add: element at: position => 17");
    #     # evalcodes("# [] add: 'a' at: 0 => ['a']");
    #     # evalcodes("#add: 'a' at: 0 => ['a'] ++ self");

    #     evalcodes("#times: a_block => (
    #         remaining = self,
    #         ->{ (remaining = remaining - 1) >= 0 } while_true: ->{ a_block value }
    #     )", ["STARTpush_keyword_method", %Q{"times:"}, "push_variable", "a_block", "push_tensor", "1", "push_self", "store", "remaining", "STARTpush_proc", "push_tensor", "0", "push_variable", "remaining", "push_1", "binary", "-", "store", "remaining", "push_0", "binary", ">=", "ENDpush_proc", "STARTpush_proc", "push_tensor", "0", "push_variable", "a_block", "unary", "value", "ENDpush_proc", "keyword", "while_true:", "1", "ENDpush_keyword_method", "pop"]);
    # end

    # it "evaluates C function definitions" do
    #     evalcodes("###void f()", ["STARTpush_c_function", "push_variable", "void", "push_variable", "f", "push_tensor", "0", "ENDpush_c_function", "pop"]);
    #     evalcodes("###void f2(int a, int b)", ["STARTpush_c_function", "push_variable", "void", "push_variable", "f2", "push_variable", "CFunParam", "push_variable", "int", "push_variable", "a", "keyword", "c_type:c_name:", "2", "push_variable", "CFunParam", "push_variable", "int", "push_variable", "b", "keyword", "c_type:c_name:", "2", "push_tensor", "2", "ENDpush_c_function", "pop"]);
    # end
end
