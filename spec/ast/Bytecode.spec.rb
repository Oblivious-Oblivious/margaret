describe Bytecode do
    it "creates a Bytecode ast type" do
        l = Lexer.new "file.marg", "2 + 3".chars;
        p = Parser.new l.make_tokens, "bytecode";
        expect(p.ast).to be_kind_of ASTInterface;
    end

    it "emits for a simple message" do
        opcodes("2 + 3", [
            "push_2",
            "push_integer", "3",
            "binary", "+"
        ]);
    end

    it "emits for integers" do
        opcodes("0", ["push_0"]);
        opcodes("-0", ["push_0"]);
        opcodes("+0", ["push_0"]);
        opcodes("1", ["push_1"]);
        opcodes("+1", ["push_1"]);
        opcodes("-1", ["push_minus_1"]);
        opcodes("2", ["push_2"]);
        opcodes("+2", ["push_2"]);
        opcodes("42", ["push_integer","42"]);
        opcodes("-42", ["push_integer","-42"]);
        opcodes("+42", ["push_integer","42"]);
        opcodes("4_200", ["push_integer","4200"]);
        opcodes("-4_200", ["push_integer","-4200"]);
    end

    it "emits for floats" do
        opcodes("42.0", ["push_float", "42.0"]);
        opcodes("-42.0", ["push_float", "-42.0"]);
        opcodes("986513.00056129", ["push_float", "986513.00056129"]);
        opcodes("-986513.00056129", ["push_float", "-986513.00056129"]);
    end

    it "emits for binaries" do
        opcodes("0b0110", ["push_integer", "6"]);
        opcodes("0B10", ["push_integer", "2"]);
        opcodes("-0b0110", ["push_integer", "-6"]);
        opcodes("-0B10", ["push_integer", "-2"]);
        opcodes("(
            x = 0b0101 + 0b1011,
            x to_int puts,
        )", ["push_integer", "5", "push_integer", "11", "binary", "+", "store", "x", "push_variable", "x", "unary", "to_int", "unary", "puts"]);
    end

    it "emits for hexadecimals" do
        opcodes("0xbeef", ["push_integer", "48879"]);
        opcodes("-0xbeEf", ["push_integer", "-48879"]);
        opcodes("0X0427", ["push_integer", "1063"]);
        opcodes("-0X0427", ["push_integer", "-1063"]);
        opcodes("x = 0xbeef to_bin to_int puts", ["push_integer", "48879", "unary", "to_bin", "unary", "to_int", "unary", "puts", "store", "x"]);
        opcodes("0xbeef - 0xabb2", ["push_integer", "48879", "push_integer", "43954", "binary", "-"]);
    end

    it "emits for octals" do
        opcodes("0o741", ["push_integer", "481"]);
        opcodes("-0o741", ["push_integer", "-481"]);
        opcodes("0O0210", ["push_integer", "136"]);
        opcodes("-0O0210", ["push_integer", "-136"]);
        opcodes("x = 0o751 to_hex to_bin to_int puts", ["push_integer", "489", "unary", "to_hex", "unary", "to_bin", "unary", "to_int", "unary", "puts", "store", "x"]);
        opcodes("0O541 + 0o777", ["push_integer", "353", "push_integer", "511", "binary", "+"]);
    end

    it "emits for strings" do
        opcodes(%Q{"string"}, ["push_string", %Q{"string"}]);
    end

    it "emits for variables" do
        opcodes("ident", ["push_variable", "ident"]);
        opcodes("variable", ["push_variable", "variable"]);
        opcodes("@instvar", ["push_instance", "instvar"]);
        opcodes("@x", ["push_instance", "x"]);
        opcodes("nil", ["push_nil"]);
        opcodes("true", ["push_true"]);
        opcodes("false", ["push_false"]);
        opcodes("self", ["push_self"]);
        opcodes("super", ["push_super"]);
    end

    it "emits for lists" do
        opcodes("()", []);
        opcodes("(1, 2, 3)", ["push_1", "push_2", "push_integer", "3"]);
        opcodes("(1, 2, (10, 20, 30), 3)", ["push_1", "push_2", "push_integer", "10", "push_integer", "20", "push_integer", "30", "push_integer", "3"]);
        opcodes(%Q{(1, "2", c, 42.42)}, ["push_1", "push_string", %Q{"2"}, "push_variable", "c", "push_float", "42.42"]);
    end

    it "emits for tensors" do
        opcodes("[]", ["push_tensor", "0"]);
        opcodes("[41, 42]", ["push_integer", "41", "push_integer", "42", "push_tensor", "2"]);
        opcodes(%Q{[42, "str", var]}, ["push_integer", "42", "push_string", %Q{"str"}, "push_variable", "var", "push_tensor", "3"]);
    end

    it "emits for hashes" do
        opcodes("{}", ["push_hash", "0"]);
        opcodes("{a: {}, b: {}}", ["push_variable", "Association", "push_string", %Q{"a"}, "push_hash", "0", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_hash", "0", "keyword", "key:value:", "2", "push_hash", "2"]);
        opcodes("{a: 1, b: 2, c: 3}", ["push_variable", "Association", "push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3"]);
        opcodes(%Q{{"a": 1, "b": 2, "c": 3}}, ["push_variable", "Association", "push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3"]);
    end

    it "emits for procs" do
        opcodes("->{x = (x = 1, y = 2)}", ["STARTpush_proc", "push_tensor", "0", "push_1", "store", "x", "push_2", "store", "y", "store", "x", "ENDpush_proc"]);
        opcodes("x = ->{
            v1, v2, (
                v1 += 1,
                v1 += 2,
                v1 * v2
            )
        }", ["STARTpush_proc", "push_variable", "v1", "push_variable", "v2", "push_tensor", "2", "push_variable", "v1", "push_1", "binary", "+=", "push_variable", "v1", "push_2", "binary", "+=", "push_variable", "v1", "push_variable", "v2", "binary", "*", "ENDpush_proc", "store", "x"]);
        opcodes("->{42}", ["STARTpush_proc", "push_tensor", "0", "push_integer", "42", "ENDpush_proc"]);
        opcodes("->{a | a puts}", ["STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "unary", "puts", "ENDpush_proc"]);
        opcodes("->{2 + 3}", ["STARTpush_proc", "push_tensor", "0", "push_2", "push_integer", "3", "binary", "+", "ENDpush_proc"]);
        opcodes("->{(x = 1, y = 2, x + y)}", ["STARTpush_proc", "push_tensor", "0", "push_1", "store", "x", "push_2", "store", "y", "push_variable", "x", "push_variable", "y", "binary", "+", "ENDpush_proc"]);
        opcodes("->{a, b | a + b}", ["STARTpush_proc", "push_variable", "a", "push_variable", "b", "push_tensor", "2", "push_variable", "a", "push_variable", "b", "binary", "+", "ENDpush_proc"]);
        opcodes("->{a, a}", ["STARTpush_proc", "push_variable", "a", "push_tensor", "1", "push_variable", "a", "ENDpush_proc"]);
        opcodes("->{x = 2} exec", ["STARTpush_proc", "push_tensor", "0", "push_2", "store", "x", "ENDpush_proc", "unary", "exec"]);
        opcodes("->{param | param puts} value: 42", ["STARTpush_proc", "push_variable", "param", "push_tensor", "1", "push_variable", "param", "unary", "puts", "ENDpush_proc", "push_integer", "42", "keyword", "value:", "1"]);
    end

    it "emits for assignment" do
        opcodes("x = 4", ["push_integer", "4", "store", "x"]);
        opcodes("x = y = z = 6", ["push_integer", "6", "store", "z", "store", "y", "store", "x"]);
        opcodes("x = (y = 6) + 1", ["push_integer", "6", "store", "y", "push_1", "binary", "+", "store", "x"]);
        opcodes("@x = x + 2", ["push_variable", "x", "push_2", "binary", "+", "store_instance", "x"]);
        opcodes("a = b = (c = 42) + 12", ["push_integer", "42", "store", "c", "push_integer", "12", "binary", "+", "store", "b", "store", "a"]);
        opcodes("a = a negate", ["push_variable", "a", "unary", "negate", "store", "a"]);
        opcodes("@a = @a negate", ["push_instance", "a", "unary", "negate", "store_instance", "a"]);
    end

    it "emits for unary messages" do
        opcodes("42 factorial", ["push_integer", "42", "unary", "factorial"]);
        opcodes("17 incr puts", ["push_integer", "17", "unary", "incr", "unary", "puts"]);
        opcodes("23 one two three", ["push_integer", "23", "unary", "one", "unary", "two", "unary", "three"]);
        opcodes("@inst one two three", ["push_instance", "inst", "unary", "one", "unary", "two", "unary", "three"]);
        opcodes("42 puts", ["push_integer", "42", "unary", "puts"]);
        opcodes("obj puts", ["push_variable", "obj", "unary", "puts"]);
        opcodes("x = obj puts", ["push_variable", "obj", "unary", "puts", "store", "x"]);
        opcodes("(obj puts, 42 incr)", ["push_variable", "obj", "unary", "puts", "push_integer", "42", "unary", "incr"]);
        opcodes("((obj puts), (42 incr))", ["push_variable", "obj", "unary", "puts", "push_integer", "42", "unary", "incr"]);
        opcodes("42 incr incr decr decr", ["push_integer", "42", "unary", "incr", "unary", "incr", "unary", "decr", "unary", "decr"]);
        opcodes("x = 42 incr incr decr decr", ["push_integer", "42", "unary", "incr", "unary", "incr", "unary", "decr", "unary", "decr", "store", "x"]);
        opcodes("x incr!", ["push_variable", "x", "unary", "incr!"]);
        opcodes("x is_empty?", ["push_variable", "x", "unary", "is_empty?"]);
        opcodes("(42 one, 43 two, 44 three, 45, 46 four)", ["push_integer", "42", "unary", "one", "push_integer", "43", "unary", "two", "push_integer", "44", "unary", "three", "push_integer", "45", "push_integer", "46", "unary", "four"]);
        opcodes("p1 + p2 calc puts", ["push_variable", "p1", "push_variable", "p2", "unary", "calc", "unary", "puts", "binary", "+"]);
        opcodes("(p1 + p2 calc) puts", ["push_variable", "p1", "push_variable", "p2", "unary", "calc", "binary", "+", "unary", "puts"]);
    end

    it "emits for binary messages" do
        opcodes("2 + 3", ["push_2", "push_integer", "3", "binary", "+"]);
        opcodes("2 + 3 * 4 + 5", ["push_2", "push_integer", "3", "binary", "+", "push_integer", "4", "binary", "*", "push_integer", "5", "binary", "+"]);
        opcodes("2 * 5", ["push_2", "push_integer", "5", "binary", "*"]);
        opcodes("a + b", ["push_variable", "a", "push_variable", "b", "binary", "+"]);
        opcodes("42 factorial + 17", ["push_integer", "42", "unary", "factorial", "push_integer", "17", "binary", "+"]);
        opcodes("41 factorial + 42 factorial + 43 factorial", ["push_integer", "41", "unary", "factorial", "push_integer", "42", "unary", "factorial", "binary", "+", "push_integer", "43", "unary", "factorial", "binary", "+"]);
        opcodes("(41 + 1, 42 + 0, 43 - 1)", ["push_integer", "41", "push_1", "binary", "+", "push_integer", "42", "push_0", "binary", "+", "push_integer", "43", "push_1", "binary", "-"]);
        opcodes("((41 + 1), (42 + 0), (43 - 1))", ["push_integer", "41", "push_1", "binary", "+", "push_integer", "42", "push_0", "binary", "+", "push_integer", "43", "push_1", "binary", "-"]);
        opcodes("x = a + b * 2 - 5", ["push_variable", "a", "push_variable", "b", "binary", "+", "push_2", "binary", "*", "push_integer", "5", "binary", "-", "store", "x"]);
        opcodes("x << item", ["push_variable", "x", "push_variable", "item", "binary", "<<"]);
        opcodes("[1, 2, 3] ++ [4, 5]", ["push_1", "push_2", "push_integer", "3", "push_tensor", "3", "push_integer", "4", "push_integer", "5", "push_tensor", "2", "binary", "++"]);
        opcodes("(4 + 3) * (5 + 6)", ["push_integer", "4", "push_integer", "3", "binary", "+", "push_integer", "5", "push_integer", "6", "binary", "+", "binary", "*"]);
    end

    it "emits for keyword messages" do
        opcodes("list put: 42 at: 5", ["push_variable", "list", "push_integer", "42", "push_integer", "5", "keyword", "put:at:", "2"]);
        opcodes("list put: (42 incr) at: 5", ["push_variable", "list", "push_integer", "42", "unary", "incr", "push_integer", "5", "keyword", "put:at:", "2"]);
        opcodes("(
            list = List new,
            list put: 42 at: 5,
            x = list get: 2,
            x puts
        )", ["push_variable", "List", "unary", "new", "store", "list", "push_variable", "list", "push_integer", "42", "push_integer", "5", "keyword", "put:at:", "2", "push_variable", "list", "push_2", "keyword", "get:", "1", "store", "x", "push_variable", "x", "unary", "puts"]);
        opcodes("2 + 3 incr add: 11", ["push_2", "push_integer", "3", "unary", "incr", "binary", "+", "push_integer", "11", "keyword", "add:", "1"]);
        opcodes("[1, 2, 3] reverse!: true", ["push_1", "push_2", "push_integer", "3", "push_tensor", "3", "push_true", "keyword", "reverse!:", "1"]);
        opcodes("true then: 1 else: 2", ["push_true", "push_1", "push_2", "keyword", "then:else:", "2"]);
        opcodes("x ok?: true otherwise!: false", ["push_variable", "x", "push_true", "push_false", "keyword", "ok?:otherwise!:", "2"]);
        opcodes("(5 + 13) greater_than?: (11 + 2)", ["push_integer", "5", "push_integer", "13", "binary", "+", "push_integer", "11", "push_2", "binary", "+", "keyword", "greater_than?:", "1"]);
        opcodes("42 factorial and: (2 + 3)", ["push_integer", "42", "unary", "factorial", "push_2", "push_integer", "3", "binary", "+", "keyword", "and:", "1"]);
        opcodes("(list at: 3) + (list at: 5)", ["push_variable", "list", "push_integer", "3", "keyword", "at:", "1", "push_variable", "list", "push_integer", "5", "keyword", "at:", "1", "binary", "+"]);
        opcodes("arr add: 1 add: 2 add: 3", ["push_variable", "arr", "push_1", "keyword", "add:", "1", "push_variable", "arr", "push_2", "keyword", "add:", "1", "push_variable", "arr", "push_integer", "3", "keyword", "add:", "1", "push_tensor", "3"]);
        opcodes("arr add: 'a' add: 'b' at: 3", ["push_variable", "arr", "push_char", "'a'", "push_char", "'b'", "push_integer", "3", "keyword", "add:add:at:", "3"]);
        opcodes("arr add: 'a' at: 1 add: 'b' at: 2", ["push_variable", "arr", "push_char", "'a'", "push_1", "push_char", "'b'", "push_2", "keyword", "add:at:add:at:", "4"]);
    end

    it "emits for unary method definitions" do
        opcodes("#incr => self + 1",   ["STARTpush_unary_method", %Q{"incr"}, "push_self", "push_1", "binary", "+", "ENDpush_unary_method"]);
        opcodes("#  incr => self + 1", ["STARTpush_unary_method", %Q{"incr"}, "push_self", "push_1", "binary", "+", "ENDpush_unary_method"]);
        opcodes("#is_empty? => true", ["STARTpush_unary_method", %Q{"is_empty?"}, "push_true", "ENDpush_unary_method"]);
        # opcodes("# 0 fact => 1");
        "
        # 0 fact => 1,
        # _ fact => self * (self-1) fact
        "
    end

    it "emits for binary method definitions" do
        opcodes("#** a_number => self raised_to: a_number", ["STARTpush_binary_method", %Q{"**"}, "push_variable", "a_number", "push_self", "push_variable", "a_number", "keyword", "raised_to:", "1", "ENDpush_binary_method"]);
        # opcodes("# 0 ** a_number => 0", "");
        # opcodes("# 0 ** 0 => nil", "");
    end

    it "emits for keyword method definitions" do
        opcodes("#add: element at: position => 42", ["STARTpush_keyword_method", %Q{"add:at:"}, "push_variable", "element", "push_variable", "position", "push_tensor", "2", "push_integer", "42", "ENDpush_keyword_method"]);
        opcodes("#ok?: value1 otherwise!: value2 => 17", ["STARTpush_keyword_method", %Q{"ok?:otherwise!:"}, "push_variable", "value1", "push_variable", "value2", "push_tensor", "2", "push_integer", "17", "ENDpush_keyword_method"]);
        # opcodes("# [] add: element at: position => 17");
        # opcodes("# [] add: 'a' at: 0 => ['a']");
        # opcodes("#add: 'a' at: 0 => ['a'] ++ self");

        opcodes("#times: a_block => (
            remaining = self,
            ->{ (remaining = remaining - 1) >= 0 } while_true: ->{ a_block value }
        )", ["STARTpush_keyword_method", %Q{"times:"}, "push_variable", "a_block", "push_tensor", "1", "push_self", "store", "remaining", "STARTpush_proc", "push_tensor", "0", "push_variable", "remaining", "push_1", "binary", "-", "store", "remaining", "push_0", "binary", ">=", "ENDpush_proc", "STARTpush_proc", "push_tensor", "0", "push_variable", "a_block", "unary", "value", "ENDpush_proc", "keyword", "while_true:", "1", "ENDpush_keyword_method"]);
    end

    it "emits for C function definitions" do
        opcodes("###void f()", ["STARTpush_c_function", "push_variable", "void", "push_variable", "f", "push_tensor", "0", "ENDpush_c_function"]);
        opcodes("###void f2(int a, int b)", ["STARTpush_c_function", "push_variable", "void", "push_variable", "f2", "push_variable", "CFunParam", "push_variable", "int", "push_variable", "a", "keyword", "c_type:c_name:", "2", "push_variable", "CFunParam", "push_variable", "int", "push_variable", "b", "keyword", "c_type:c_name:", "2", "push_tensor", "2", "ENDpush_c_function"]);
    end
end
