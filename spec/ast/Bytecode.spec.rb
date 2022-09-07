describe Bytecode do
    it "creates a Bytecode ast type" do
        l = Lexer.new "file.marg", "2 + 3".chars;
        p = Parser.new l.make_tokens;
        expect(p.ast).to be_kind_of Bytecode;
    end

    it "emits for a simple message" do
        parse("2 + 3", [
            "push_2",
            "push_integer", "3",
            "binary", "+"
        ]);
    end

    it "emits for assignment" do
        parse("x = 4", ["push_integer", "4", "store", "x"]);
        parse("x = y = z = 6", ["push_integer", "6", "store", "z", "store", "y", "store", "x"]);
        parse("x = (y = 6) + 1", ["push_integer", "6", "store", "y", "push_1", "binary", "+", "store", "x"]);
        parse("@x = x + 2", ["push_variable", "x", "push_2", "binary", "+", "store_instance", "x"]);
        parse("a = b = (c = 42) + 12", ["push_integer", "42", "store", "c", "push_integer", "12", "binary", "+", "store", "b", "store", "a"]);
        parse("a = a negate", ["push_variable", "a", "unary", "negate", "store", "a"]);
        parse("@a = @a negate", ["push_instance", "a", "unary", "negate", "store_instance", "a"]);
    end

    it "emits for unary messages" do
        parse("42 factorial", ["push_integer", "42", "unary", "factorial"]);
        parse("17 incr puts", ["push_integer", "17", "unary", "incr", "unary", "puts"]);
        parse("23 one two three", ["push_integer", "23", "unary", "one", "unary", "two", "unary", "three"]);
        parse("@inst one two three", ["push_instance", "inst", "unary", "one", "unary", "two", "unary", "three"]);
        parse("42 puts", ["push_integer", "42", "unary", "puts"]);
        parse("obj puts", ["push_variable", "obj", "unary", "puts"]);
        parse("x = obj puts", ["push_variable", "obj", "unary", "puts", "store", "x"]);
        parse("(obj puts, 42 incr)", ["push_variable", "obj", "unary", "puts", "push_integer", "42", "unary", "incr"]);
        parse("((obj puts), (42 incr))", ["push_variable", "obj", "unary", "puts", "push_integer", "42", "unary", "incr"]);
        parse("42 incr incr decr decr", ["push_integer", "42", "unary", "incr", "unary", "incr", "unary", "decr", "unary", "decr"]);
        parse("x = 42 incr incr decr decr", ["push_integer", "42", "unary", "incr", "unary", "incr", "unary", "decr", "unary", "decr", "store", "x"]);
        parse("x incr!", ["push_variable", "x", "unary", "incr!"]);
        parse("x is_empty?", ["push_variable", "x", "unary", "is_empty?"]);
        parse("(42 one, 43 two, 44 three, 45, 46 four)", ["push_integer", "42", "unary", "one", "push_integer", "43", "unary", "two", "push_integer", "44", "unary", "three", "push_integer", "45", "push_integer", "46", "unary", "four"]);
        parse("p1 + p2 calc puts", ["push_variable", "p1", "push_variable", "p2", "unary", "calc", "unary", "puts", "binary", "+"]);
        parse("(p1 + p2 calc) puts", ["push_variable", "p1", "push_variable", "p2", "unary", "calc", "binary", "+", "unary", "puts"]);
    end

    it "emits for binary messages" do
        parse("2 + 3", ["push_2", "push_integer", "3", "binary", "+"]);
        parse("2 + 3 * 4 + 5", ["push_2", "push_integer", "3", "binary", "+", "push_integer", "4", "binary", "*", "push_integer", "5", "binary", "+"]);
        parse("2 * 5", ["push_2", "push_integer", "5", "binary", "*"]);
        parse("a + b", ["push_variable", "a", "push_variable", "b", "binary", "+"]);
        parse("42 factorial + 17", ["push_integer", "42", "unary", "factorial", "push_integer", "17", "binary", "+"]);
        parse("41 factorial + 42 factorial + 43 factorial", ["push_integer", "41", "unary", "factorial", "push_integer", "42", "unary", "factorial", "binary", "+", "push_integer", "43", "unary", "factorial", "binary", "+"]);
        parse("(41 + 1, 42 + 0, 43 - 1)", ["push_integer", "41", "push_1", "binary", "+", "push_integer", "42", "push_0", "binary", "+", "push_integer", "43", "push_1", "binary", "-"]);
        parse("((41 + 1), (42 + 0), (43 - 1))", ["push_integer", "41", "push_1", "binary", "+", "push_integer", "42", "push_0", "binary", "+", "push_integer", "43", "push_1", "binary", "-"]);
        parse("x = a + b * 2 - 5", ["push_variable", "a", "push_variable", "b", "binary", "+", "push_2", "binary", "*", "push_integer", "5", "binary", "-", "store", "x"]);
        parse("x << item", ["push_variable", "x", "push_variable", "item", "binary", "<<"]);
        parse("[1, 2, 3] ++ [4, 5]", ["push_1", "push_2", "push_integer", "3", "push_tensor", "3", "push_integer", "4", "push_integer", "5", "push_tensor", "2", "binary", "++"]);
        parse("(4 + 3) * (5 + 6)", ["push_integer", "4", "push_integer", "3", "binary", "+", "push_integer", "5", "push_integer", "6", "binary", "+", "binary", "*"]);
    end

    it "emits for keyword messages" do
        parse("list put: 42 at: 5", ["push_variable", "list", "push_integer", "42", "push_integer", "5", "keyword", "put:at:", "2"]);
        parse("list put: (42 incr) at: 5", ["push_variable", "list", "push_integer", "42", "unary", "incr", "push_integer", "5", "keyword", "put:at:", "2"]);
        parse("(
            list = List new,
            list put: 42 at: 5,
            x = list get: 2,
            x puts
        )", ["push_variable", "List", "unary", "new", "store", "list", "push_variable", "list", "push_integer", "42", "push_integer", "5", "keyword", "put:at:", "2", "push_variable", "list", "push_2", "keyword", "get:", "1", "store", "x", "push_variable", "x", "unary", "puts"]);
        parse("2 + 3 incr add: 11", ["push_2", "push_integer", "3", "unary", "incr", "binary", "+", "push_integer", "11", "keyword", "add:", "1"]);
        parse("[1, 2, 3] reverse!: true", ["push_1", "push_2", "push_integer", "3", "push_tensor", "3", "push_true", "keyword", "reverse!:", "1"]);
        parse("true then: 1 else: 2", ["push_true", "push_1", "push_2", "keyword", "then:else:", "2"]);
        parse("x ok?: true otherwise!: false", ["push_variable", "x", "push_true", "push_false", "keyword", "ok?:otherwise!:", "2"]);
        parse("(5 + 13) greater_than?: (11 + 2)", ["push_integer", "5", "push_integer", "13", "binary", "+", "push_integer", "11", "push_2", "binary", "+", "keyword", "greater_than?:", "1"]);
        parse("42 factorial and: (2 + 3)", ["push_integer", "42", "unary", "factorial", "push_2", "push_integer", "3", "binary", "+", "keyword", "and:", "1"]);
        parse("(list at: 3) + (list at: 5)", ["push_variable", "list", "push_integer", "3", "keyword", "at:", "1", "push_variable", "list", "push_integer", "5", "keyword", "at:", "1", "binary", "+"]);
        parse("arr add: 1 add: 2 add: 3", ["push_variable", "arr", "push_1", "keyword", "add:", "1", "push_variable", "arr", "push_2", "keyword", "add:", "1", "push_variable", "arr", "push_integer", "3", "keyword", "add:", "1", "push_tensor", "3"]);
        parse("arr add: 'a' add: 'b' at: 3", ["push_variable", "arr", "push_char", "'a'", "push_char", "'b'", "push_integer", "3", "keyword", "add:add:at:", "3"]);
        parse("arr add: 'a' at: 1 add: 'b' at: 2", ["push_variable", "arr", "push_char", "'a'", "push_1", "push_char", "'b'", "push_2", "keyword", "add:at:add:at:", "4"]);
    end

    it "emits for groups" do
        parse("()", []);
        parse("(1, 2, 3)", ["push_1", "push_2", "push_integer", "3"]);
        parse("(1, 2, (10, 20, 30), 3)", ["push_1", "push_2", "push_integer", "10", "push_integer", "20", "push_integer", "30", "push_integer", "3"]);
        parse(%Q{(1, "2", c, 42.42)}, ["push_1", "push_string", %Q{"2"}, "push_variable", "c", "push_float", "42.42"]);
    end

    it "emits for variables" do
        parse("ident", ["push_variable", "ident"]);
        parse("variable", ["push_variable", "variable"]);
        parse("@instvar", ["push_instance", "instvar"]);
        parse("@x", ["push_instance", "x"]);
        parse("nil", ["push_nil"]);
        parse("true", ["push_true"]);
        parse("false", ["push_false"]);
        parse("self", ["push_self"]);
        parse("super", ["push_super"]);
    end

    it "emits for procs" do
        parse("->{x = (x = 1, y = 2)}", ["STARTpush_proc", "push_tensor", "0", "push_1", "store", "x", "push_2", "store", "y", "store", "x", "ENDpush_proc"]);
        parse("x = ->{
            v1, v2, (
                v1 += 1,
                v1 += 2,
                v1 * v2
            )
        }", ["STARTpush_proc", "push_variable", "v1", "push_variable", "v2", "push_tensor", "2", "push_variable", "v1", "push_1", "binary", "+=", "push_variable", "v1", "push_2", "binary", "+=", "push_variable", "v1", "push_variable", "v2", "binary", "*", "ENDpush_proc", "store", "x"]);
        parse("->{42}", ["STARTpush_proc", "push_tensor", "0", "push_integer", "42", "ENDpush_proc"]);
        parse("->{a | a puts}", ["STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "unary", "puts", "ENDpush_proc"]);
        parse("->{2 + 3}", ["STARTpush_proc", "push_tensor", "0", "push_2", "push_integer", "3", "binary", "+", "ENDpush_proc"]);
        parse("->{(x = 1, y = 2, x + y)}", ["STARTpush_proc", "push_tensor", "0", "push_1", "store", "x", "push_2", "store", "y", "push_variable", "x", "push_variable", "y", "binary", "+", "ENDpush_proc"]);
        parse("->{a, b | a + b}", ["STARTpush_proc", "push_variable", "a", "push_variable", "b", "push_tensor", "2", "push_variable", "a", "push_variable", "b", "binary", "+", "ENDpush_proc"]);
        parse("->{a, a}", ["STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "ENDpush_proc"]);
        parse("->{x = 2} exec", ["STARTpush_proc", "push_tensor", "0", "push_2", "store", "x", "ENDpush_proc", "unary", "exec"]);
        parse("->{param | param puts} value: 42", ["STARTpush_proc", "push_variable", "param", "push_tensor", "1", "push_variable", "param", "unary", "puts", "ENDpush_proc", "push_integer", "42", "keyword", "value:", "1"]);
    end

    it "emits for unary method definitions" do
        parse("#incr => self + 1",   ["STARTpush_unary_method", %Q{"incr"}, "push_self", "push_1", "binary", "+", "ENDpush_unary_method"]);
        parse("#  incr => self + 1", ["STARTpush_unary_method", %Q{"incr"}, "push_self", "push_1", "binary", "+", "ENDpush_unary_method"]);
        parse("#is_empty? => true", ["STARTpush_unary_method", %Q{"is_empty?"}, "push_true", "ENDpush_unary_method"]);
        # parse("# 0 fact => 1");
        "
        # 0 fact => 1,
        # _ fact => self * (self-1) fact
        "
    end

    it "emits for binary method definitions" do
        parse("#** a_number => self raised_to: a_number", ["STARTpush_binary_method", %Q{"**"}, "push_variable", "a_number", "push_self", "push_variable", "a_number", "keyword", "raised_to:", "1", "ENDpush_binary_method"]);
        # parse("# 0 ** a_number => 0", "");
        # parse("# 0 ** 0 => nil", "");
    end

    it "emits for keyword method definitions" do
        parse("#add: element at: position => 42", ["STARTpush_keyword_method", %Q{"add:at:"}, "push_variable", "element", "push_variable", "position", "push_tensor", "2", "push_integer", "42", "ENDpush_keyword_method"]);
        parse("#ok?: value1 otherwise!: value2 => 17", ["STARTpush_keyword_method", %Q{"ok?:otherwise!:"}, "push_variable", "value1", "push_variable", "value2", "push_tensor", "2", "push_integer", "17", "ENDpush_keyword_method"]);
        # parse("# [] add: element at: position => 17");
        # parse("# [] add: 'a' at: 0 => ['a']");
        # parse("#add: 'a' at: 0 => ['a'] ++ self");

        parse("#times: a_block => (
            remaining = self,
            ->{ (remaining = remaining - 1) >= 0 } while_true: ->{ a_block value }
        )", ["STARTpush_keyword_method", %Q{"times:"}, "push_variable", "a_block", "push_tensor", "1", "push_self", "store", "remaining", "STARTpush_proc", "push_tensor", "0", "push_variable", "remaining", "push_1", "binary", "-", "store", "remaining", "push_0", "binary", ">=", "ENDpush_proc", "STARTpush_proc", "push_tensor", "0", "push_variable", "a_block", "unary", "value", "ENDpush_proc", "keyword", "while_true:", "1", "ENDpush_keyword_method"]);
    end

    it "emits for C function definitions" do
        parse("###void f()", ["STARTpush_c_function", "push_variable", "void", "push_variable", "f", "push_tensor", "0", "ENDpush_c_function"]);
        parse("###void f2(int a, int b)", ["STARTpush_c_function", "push_variable", "void", "push_variable", "f2", "push_variable", "CFunParam", "push_variable", "int", "push_variable", "a", "keyword", "c_type:c_name:", "2", "push_variable", "CFunParam", "push_variable", "int", "push_variable", "b", "keyword", "c_type:c_name:", "2", "push_tensor", "2", "ENDpush_c_function"]);
    end

    it "emits for integers" do
        parse("0", ["push_0"]);
        parse("-0", ["push_0"]);
        parse("+0", ["push_0"]);
        parse("1", ["push_1"]);
        parse("+1", ["push_1"]);
        parse("-1", ["push_minus_1"]);
        parse("2", ["push_2"]);
        parse("+2", ["push_2"]);
        parse("42", ["push_integer","42"]);
        parse("-42", ["push_integer","-42"]);
        parse("+42", ["push_integer","42"]);
        parse("4_200", ["push_integer","4200"]);
        parse("-4_200", ["push_integer","-4200"]);
        parse("4____20__0", ["push_integer","4200"]);
        parse("-4____20__0", ["push_integer","-4200"]);
        parse("+4____20__0", ["push_integer","4200"]);
    end

    it "emits for floats" do
        parse("42.0", ["push_float", "42.0"]);
        parse("-42.0", ["push_float", "-42.0"]);
        parse("986513.00056129", ["push_float", "986513.00056129"]);
        parse("-986513.00056129", ["push_float", "-986513.00056129"]);
        parse("0.1_2_3", ["push_float", "0.123"]);
        parse("0.1__23", ["push_float", "0.123"]);
    end

    it "emits for binaries" do
        parse("0b0110", ["push_integer", "6"]);
        parse("0B10", ["push_integer", "2"]);
        parse("-0b0110", ["push_integer", "-6"]);
        parse("-0B10", ["push_integer", "-2"]);
        parse("(
            x = 0b0101 + 0b1011,
            x to_int puts,
        )", ["push_integer", "5", "push_integer", "11", "binary", "+", "store", "x", "push_variable", "x", "unary", "to_int", "unary", "puts"]);
    end

    it "emits for hexadecimals" do
        parse("0xbeef", ["push_integer", "48879"]);
        parse("-0xbeEf", ["push_integer", "-48879"]);
        parse("0X0427", ["push_integer", "1063"]);
        parse("-0X0427", ["push_integer", "-1063"]);
        parse("x = 0xbeef to_bin to_int puts", ["push_integer", "48879", "unary", "to_bin", "unary", "to_int", "unary", "puts", "store", "x"]);
        parse("0xbeef - 0xabb2", ["push_integer", "48879", "push_integer", "43954", "binary", "-"]);
        parse("0xbe____e___f", ["push_integer", "48879"]);
    end

    it "emits for octals" do
        parse("0o741", ["push_integer", "481"]);
        parse("-0o741", ["push_integer", "-481"]);
        parse("0O0210", ["push_integer", "136"]);
        parse("-0O0210", ["push_integer", "-136"]);
        parse("x = 0o751 to_hex to_bin to_int puts", ["push_integer", "489", "unary", "to_hex", "unary", "to_bin", "unary", "to_int", "unary", "puts", "store", "x"]);
        parse("0O541 + 0o777", ["push_integer", "353", "push_integer", "511", "binary", "+"]);
    end

    it "emits for characters" do
        parse("'a'", ["push_char", "'a'"]);
        parse("'\n'", ["push_char", "'\n'"]);
        parse("'œ'", ["push_char", "'œ'"]);
        parse("-'œ'", ["push_char", "-'œ'"]);
        parse("('a' to_uppercase)", ["push_char", "'a'", "unary", "to_uppercase"]);
        parse("('B' to_ascii)", ["push_char", "'B'", "unary", "to_ascii"]);
        parse("('a' <= 'b')", ["push_char", "'a'", "push_char", "'b'", "binary", "<="]);
    end

    it "emits for strings" do
        parse(%Q{"string"}, ["push_string", %Q{"string"}]);
        parse(%Q{"foo\tbar"}, ["push_string", %Q{"foo\tbar"}]);
        parse(%Q{"a string lit"}, ["push_string", %Q{"a string lit"}]);
        parse(%Q{"str"}, ["push_string", %Q{"str"}]);
    end

    it "emits for tensors" do
        parse("[]", ["push_tensor", "0"]);
        parse("[41, 42]", ["push_integer", "41", "push_integer", "42", "push_tensor", "2"]);
        parse(%Q{[42, "str", var]}, ["push_integer", "42", "push_string", %Q{"str"}, "push_variable", "var", "push_tensor", "3"]);
    end

    it "emits for hashes" do
        parse("{}", ["push_hash", "0"]);
        parse("{a: {}, b: {}}", ["push_variable", "Association", "push_string", %Q{"a"}, "push_hash", "0", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_hash", "0", "keyword", "key:value:", "2", "push_hash", "2"]);
        parse("{a: 1, b: 2, c: 3}", ["push_variable", "Association", "push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3"]);
        parse(%Q{{"a": 1, "b": 2, "c": 3}}, ["push_variable", "Association", "push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3"]);
    end
end
