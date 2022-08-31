require_relative "_bytecode_helpers";

describe Bytecode do
    it "creates a Bytecode ast type" do
        l = Lexer.new "file.obl", "2 + 3".chars;
        p = Parser.new l.make_tokens, "bytecode";
        expect(p.ast).to be_kind_of ASTInterface;
    end

    it "emits for a simple message" do
        opcodes("2 + 3", [
            "push_2",
            "push_integer", "3",
            "binary", "+",
            "pop"
        ]);
    end

    it "emits for integers" do
        opcodes("0", ["push_0", "pop"]);
        opcodes("-0", ["push_0", "pop"]);
        opcodes("+0", ["push_0", "pop"]);
        opcodes("1", ["push_1", "pop"]);
        opcodes("+1", ["push_1", "pop"]);
        opcodes("-1", ["push_minus_1", "pop"]);
        opcodes("2", ["push_2", "pop"]);
        opcodes("+2", ["push_2", "pop"]);
        opcodes("42", ["push_integer","42", "pop"]);
        opcodes("-42", ["push_integer","-42", "pop"]);
        opcodes("+42", ["push_integer","+42", "pop"]);
        opcodes("4_200", ["push_integer","4200", "pop"]);
        opcodes("-4_200", ["push_integer","-4200", "pop"]);
    end

    it "emits for floats" do
        opcodes("42.0", ["push_float", "42.0", "pop"]);
        opcodes("-42.0", ["push_float", "-42.0", "pop"]);
        opcodes("986513.00056129", ["push_float", "986513.00056129", "pop"]);
        opcodes("-986513.00056129", ["push_float", "-986513.00056129", "pop"]);
    end

    it "emits for binaries" do
        opcodes("0b0110", ["push_integer", "0b0110", "pop"]);
        opcodes("0B10", ["push_integer", "0b10", "pop"]);
        opcodes("-0b0110", ["push_integer", "-0b0110", "pop"]);
        opcodes("-0B10", ["push_integer", "-0b10", "pop"]);
        opcodes("(
            x = 0b0101 + 0b1011,
            x to_int puts,
        )", ["push_integer", "0b0101", "push_integer", "0b1011", "binary", "+", "store", "x", "push_variable", "x", "unary", "to_int", "unary", "puts", "push_list", "2", "pop"]);
    end

    it "emits for hexadecimals" do
        opcodes("0xbeef", ["push_integer", "0xbeef", "pop"]);
        opcodes("-0xbeEf", ["push_integer", "-0xbeef", "pop"]);
        opcodes("0X0427", ["push_integer", "0x0427", "pop"]);
        opcodes("-0X0427", ["push_integer", "-0x0427", "pop"]);
        opcodes("x = 0xbeef to_bin to_int puts", ["push_integer", "0xbeef", "unary", "to_bin", "unary", "to_int", "unary", "puts", "store", "x", "pop"]);
        opcodes("0xbeef - 0xabb2", ["push_integer", "0xbeef", "push_integer", "0xabb2", "binary", "-", "pop"]);
    end

    it "emits for octals" do
        opcodes("0o741", ["push_integer", "0o741", "pop"]);
        opcodes("-0o741", ["push_integer", "-0o741", "pop"]);
        opcodes("0O0210", ["push_integer", "0o0210", "pop"]);
        opcodes("-0O0210", ["push_integer", "-0o0210", "pop"]);
        opcodes("x = 0o751 to_hex to_bin to_int puts", ["push_integer", "0o751", "unary", "to_hex", "unary", "to_bin", "unary", "to_int", "unary", "puts", "store", "x", "pop"]);
        opcodes("0O541 + 0o777", ["push_integer", "0o541", "push_integer", "0o777", "binary", "+", "pop"]);
    end

    it "emits for strings" do
        opcodes(%Q{"string"}, ["push_string", %Q{"string"}, "pop"]);
    end

    it "emits for variables" do
        opcodes("ident", ["push_variable", "ident", "pop"]);
        opcodes("variable", ["push_variable", "variable", "pop"]);
        opcodes("@instvar", ["push_instance", "instvar", "pop"]);
        opcodes("@x", ["push_instance", "x", "pop"]);
        opcodes("nil", ["push_nil", "pop"]);
        opcodes("true", ["push_true", "pop"]);
        opcodes("false", ["push_false", "pop"]);
        opcodes("self", ["push_self", "pop"]);
        opcodes("super", ["push_super", "pop"]);
    end

    it "emits for lists" do
        # TODO extract grammar rule higher
        # TODO Simplify bytecode for lists, maybe have an array-list immediate for fast translation
        opcodes("()", ["push_list", "0", "pop"]);
        opcodes("(1, 2, 3)", ["push_1", "push_2", "push_integer", "3", "push_list", "3", "pop"]);
        opcodes("(1, 2, (10, 20, 30), 3)", ["push_1", "push_2", "push_integer", "10", "push_integer", "20", "push_integer", "30", "push_list", "3", "push_integer", "3", "push_list", "4", "pop"]);
        opcodes(%Q{(1, "2", c, 42.42)}, ["push_1", "push_string", %Q{"2"}, "push_variable", "c", "push_float", "42.42", "push_list", "4", "pop"]);
    end

    it "emits for tuples" do
        opcodes("[]", ["push_tuple", "0", "pop"]);
        opcodes("[41, 42]", ["push_integer", "41", "push_integer", "42", "push_tuple", "2", "pop"]);
        opcodes(%Q{[42, "str", var]}, ["push_integer", "42", "push_string", %Q{"str"}, "push_variable", "var", "push_tuple", "3", "pop"]);
    end

    it "emits for hashes" do
        opcodes("{}", ["push_hash", "0", "pop"]);
        opcodes("{a: {}, b: {}}", ["push_variable", "Association", "push_string", %Q{"a"}, "push_hash", "0", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_hash", "0", "keyword", "key:value:", "2", "push_hash", "2", "pop"]);
        opcodes("{a: 1, b: 2, c: 3}", ["push_variable", "Association", "push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3", "pop"]);
        opcodes(%Q{{"a": 1, "b": 2, "c": 3}}, ["push_variable", "Association", "push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_variable", "Association", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3", "pop"]);
    end

    it "emits for procs" do
        opcodes("->{x = (x = 1, y = 2)}", ["STARTpush_proc", "push_list", "0", "push_1", "store", "x", "push_2", "store", "y", "push_list", "2", "store", "x", "ENDpush_proc", "pop"]);
        opcodes("x = ->{
            v1, v2, (
                v1 += 1,
                v1 += 2,
                v1 * v2
            )
        }", ["STARTpush_proc", "push_variable", "v1", "push_variable", "v2", "push_list", "2", "push_variable", "v1", "push_1", "binary", "+=", "push_variable", "v1", "push_2", "binary", "+=", "push_variable", "v1", "push_variable", "v2", "binary", "*", "push_list", "3", "ENDpush_proc", "store", "x", "pop"]);
        opcodes("->{42}", ["STARTpush_proc", "push_list", "0", "push_integer", "42", "ENDpush_proc", "pop"]);
        opcodes("->{a | a puts}", ["STARTpush_proc", "push_variable", "a", "push_list", "1", "push_variable", "a", "unary", "puts", "ENDpush_proc", "pop"]);
        opcodes("->{2 + 3}", ["STARTpush_proc", "push_list", "0", "push_2", "push_integer", "3", "binary", "+", "ENDpush_proc", "pop"]);
        opcodes("->{(x = 1, y = 2, x + y)}", ["STARTpush_proc", "push_list", "0", "push_1", "store", "x", "push_2", "store", "y", "push_variable", "x", "push_variable", "y", "binary", "+", "push_list", "3", "ENDpush_proc", "pop"]);
        opcodes("->{a, b | a + b}", ["STARTpush_proc", "push_variable", "a", "push_variable", "b", "push_list", "2", "push_variable", "a", "push_variable", "b", "binary", "+", "ENDpush_proc", "pop"]);
        opcodes("->{a, a}", ["STARTpush_proc", "push_variable", "a", "push_list", "1", "push_variable", "a", "ENDpush_proc", "pop"]);
        opcodes("->{x = 2} exec", ["STARTpush_proc", "push_list", "0", "push_2", "store", "x", "ENDpush_proc", "unary", "exec", "pop"]);
        opcodes("->{param | param puts} value: 42", ["STARTpush_proc", "push_variable", "param", "push_list", "1", "push_variable", "param", "unary", "puts", "ENDpush_proc", "push_integer", "42", "keyword", "value:", "1", "pop"]);
    end

    it "emits for assignment" do
        opcodes("x = 4", ["push_integer", "4", "store", "x", "pop"]);
        opcodes("x = y = z = 6", ["push_integer", "6", "store", "z", "store", "y", "store", "x", "pop"]);
        opcodes("x = (y = 6) + 1", ["push_integer", "6", "store", "y", "push_list", "1", "push_1", "binary", "+", "store", "x", "pop"]);
        opcodes("@x = x + 2", ["push_variable", "x", "push_2", "binary", "+", "store_instance", "x", "pop"]);
        opcodes("a = b = (c = 42) + 12", ["push_integer", "42", "store", "c", "push_list", "1", "push_integer", "12", "binary", "+", "store", "b", "store", "a", "pop"]);
        opcodes("a = a negate", ["push_variable", "a", "unary", "negate", "store", "a", "pop"]);
        opcodes("@a = @a negate", ["push_instance", "a", "unary", "negate", "store_instance", "a", "pop"]);
    end

    it "emits for unary messages" do
        opcodes("42 factorial", ["push_integer", "42", "unary", "factorial", "pop"]);
        opcodes("17 incr puts", ["push_integer", "17", "unary", "incr", "unary", "puts", "pop"]);
        opcodes("23 one two three", ["push_integer", "23", "unary", "one", "unary", "two", "unary", "three", "pop"]);
        opcodes("@inst one two three", ["push_instance", "inst", "unary", "one", "unary", "two", "unary", "three", "pop"]);
        opcodes("42 puts", ["push_integer", "42", "unary", "puts", "pop"]);
        opcodes("obj puts", ["push_variable", "obj", "unary", "puts", "pop"]);
        opcodes("x = obj puts", ["push_variable", "obj", "unary", "puts", "store", "x", "pop"]);
        opcodes("(obj puts, 42 incr)", ["push_variable", "obj", "unary", "puts", "push_integer", "42", "unary", "incr", "push_list", "2", "pop"]);
        opcodes("((obj puts), (42 incr))", ["push_variable", "obj", "unary", "puts", "push_list", "1", "push_integer", "42", "unary", "incr", "push_list", "1", "push_list", "2", "pop"]);
        opcodes("42 incr incr decr decr", ["push_integer", "42", "unary", "incr", "unary", "incr", "unary", "decr", "unary", "decr", "pop"]);
        opcodes("x = 42 incr incr decr decr", ["push_integer", "42", "unary", "incr", "unary", "incr", "unary", "decr", "unary", "decr", "store", "x", "pop"]);
        opcodes("x incr!", ["push_variable", "x", "unary", "incr!", "pop"]);
        opcodes("x is_empty?", ["push_variable", "x", "unary", "is_empty?", "pop"]);
        opcodes("(42 one, 43 two, 44 three, 45, 46 four)", ["push_integer", "42", "unary", "one", "push_integer", "43", "unary", "two", "push_integer", "44", "unary", "three", "push_integer", "45", "push_integer", "46", "unary", "four", "push_list", "5", "pop"]);
        opcodes("p1 + p2 calc puts", ["push_variable", "p1", "push_variable", "p2", "unary", "calc", "unary", "puts", "binary", "+", "pop"]);
        opcodes("(p1 + p2 calc) puts", ["push_variable", "p1", "push_variable", "p2", "unary", "calc", "binary", "+", "push_list", "1", "unary", "puts", "pop"]);
    end

    it "emits for binary messages" do
        opcodes("2 + 3", ["push_2", "push_integer", "3", "binary", "+", "pop"]);
        opcodes("2 + 3 * 4 + 5", ["push_2", "push_integer", "3", "binary", "+", "push_integer", "4", "binary", "*", "push_integer", "5", "binary", "+", "pop"]);
        opcodes("2 * 5", ["push_2", "push_integer", "5", "binary", "*", "pop"]);
        opcodes("a + b", ["push_variable", "a", "push_variable", "b", "binary", "+", "pop"]);
        opcodes("42 factorial + 17", ["push_integer", "42", "unary", "factorial", "push_integer", "17", "binary", "+", "pop"]);
        opcodes("41 factorial + 42 factorial + 43 factorial", ["push_integer", "41", "unary", "factorial", "push_integer", "42", "unary", "factorial", "binary", "+", "push_integer", "43", "unary", "factorial", "binary", "+", "pop"]);
        opcodes("(41 + 1, 42 + 0, 43 - 1)", ["push_integer", "41", "push_1", "binary", "+", "push_integer", "42", "push_0", "binary", "+", "push_integer", "43", "push_1", "binary", "-", "push_list", "3", "pop"]);
        opcodes("((41 + 1), (42 + 0), (43 - 1))", ["push_integer", "41", "push_1", "binary", "+", "push_list", "1", "push_integer", "42", "push_0", "binary", "+", "push_list", "1", "push_integer", "43", "push_1", "binary", "-", "push_list", "1", "push_list", "3", "pop"]);
        opcodes("x = a + b * 2 - 5", ["push_variable", "a", "push_variable", "b", "binary", "+", "push_2", "binary", "*", "push_integer", "5", "binary", "-", "store", "x", "pop"]);
        opcodes("x << item", ["push_variable", "x", "push_variable", "item", "binary", "<<", "pop"]);
        opcodes("[1, 2, 3] ++ [4, 5]", ["push_1", "push_2", "push_integer", "3", "push_tuple", "3", "push_integer", "4", "push_integer", "5", "push_tuple", "2", "binary", "++", "pop"]);
        opcodes("(4 + 3) * (5 + 6)", ["push_integer", "4", "push_integer", "3", "binary", "+", "push_list", "1", "push_integer", "5", "push_integer", "6", "binary", "+", "push_list", "1", "binary", "*", "pop"]);
    end

    it "emits for keyword messages" do
        opcodes("list put: 42 at: 5", ["push_variable", "list", "push_integer", "42", "push_integer", "5", "keyword", "put:at:", "2", "pop"]);
        opcodes("list put: (42 incr) at: 5", ["push_variable", "list", "push_integer", "42", "unary", "incr", "push_list", "1", "push_integer", "5", "keyword", "put:at:", "2", "pop"]);
        opcodes("(
            list = List new,
            list put: 42 at: 5,
            x = list get: 2,
            x puts
        )", ["push_variable", "List", "unary", "new", "store", "list", "push_variable", "list", "push_integer", "42", "push_integer", "5", "keyword", "put:at:", "2", "push_variable", "list", "push_2", "keyword", "get:", "1", "store", "x", "push_variable", "x", "unary", "puts", "push_list", "4", "pop"]);
        opcodes("2 + 3 incr add: 11", ["push_2", "push_integer", "3", "unary", "incr", "binary", "+", "push_integer", "11", "keyword", "add:", "1", "pop"]);
        opcodes("(1, 2, 3) reverse!: true", ["push_1", "push_2", "push_integer", "3", "push_list", "3", "push_true", "keyword", "reverse!:", "1", "pop"]);
        opcodes("true then: 1 else: 2", ["push_true", "push_1", "push_2", "keyword", "then:else:", "2", "pop"]);
        opcodes("x ok?: true otherwise!: false", ["push_variable", "x", "push_true", "push_false", "keyword", "ok?:otherwise!:", "2", "pop"]);
        opcodes("(5 + 13) greater_than?: (11 + 2)", ["push_integer", "5", "push_integer", "13", "binary", "+", "push_list", "1", "push_integer", "11", "push_2", "binary", "+", "push_list", "1", "keyword", "greater_than?:", "1", "pop"]);
        opcodes("42 factorial and: (2 + 3)", ["push_integer", "42", "unary", "factorial", "push_2", "push_integer", "3", "binary", "+", "push_list", "1", "keyword", "and:", "1", "pop"]);
        opcodes("(list at: 3) + (list at: 5)", ["push_variable", "list", "push_integer", "3", "keyword", "at:", "1", "push_list", "1", "push_variable", "list", "push_integer", "5", "keyword", "at:", "1", "push_list", "1", "binary", "+", "pop"]);
        opcodes("arr add: 1 add: 2 add: 3", ["push_variable", "arr", "push_1", "keyword", "add:", "1", "push_variable", "arr", "push_2", "keyword", "add:", "1", "push_variable", "arr", "push_integer", "3", "keyword", "add:", "1", "push_list", "3", "pop"]);
        opcodes("arr add: 'a' add: 'b' at: 3", ["push_variable", "arr", "push_char", "'a'", "push_char", "'b'", "push_integer", "3", "keyword", "add:add:at:", "3", "pop"]);
        opcodes("arr add: 'a' at: 1 add: 'b' at: 2", ["push_variable", "arr", "push_char", "'a'", "push_1", "push_char", "'b'", "push_2", "keyword", "add:at:add:at:", "4", "pop"]);
    end

    it "emits for unary method definitions" do
        opcodes("#incr => self + 1",   ["STARTpush_unary_method", %Q{"incr"}, "push_self", "push_1", "binary", "+", "ENDpush_unary_method", "pop"]);
        opcodes("#  incr => self + 1", ["STARTpush_unary_method", %Q{"incr"}, "push_self", "push_1", "binary", "+", "ENDpush_unary_method", "pop"]);
        opcodes("#is_empty? => true", ["STARTpush_unary_method", %Q{"is_empty?"}, "push_true", "ENDpush_unary_method", "pop"]);
        # opcodes("# 0 fact => 1");
        "
        # 0 fact => 1,
        # _ fact => self * (self-1) fact
        "
    end

    it "emits for binary method definitions" do
        opcodes("#** a_number => self raised_to: a_number", ["STARTpush_binary_method", %Q{"**"}, "push_variable", "a_number", "push_self", "push_variable", "a_number", "keyword", "raised_to:", "1", "ENDpush_binary_method", "pop"]);
        # opcodes("# 0 ** a_number => 0", "");
        # opcodes("# 0 ** 0 => nil", "");
    end

    it "emits for keyword method definitions" do
        opcodes("#add: element at: position => 42", ["STARTpush_keyword_method", %Q{"add:at:"}, "push_variable", "element", "push_variable", "position", "push_list", "2", "push_integer", "42", "ENDpush_keyword_method", "pop"]);
        opcodes("#ok?: value1 otherwise!: value2 => 17", ["STARTpush_keyword_method", %Q{"ok?:otherwise!:"}, "push_variable", "value1", "push_variable", "value2", "push_list", "2", "push_integer", "17", "ENDpush_keyword_method", "pop"]);
        # opcodes("# [] add: element at: position => 17");
        # opcodes("# [] add: 'a' at: 0 => ['a']");
        # opcodes("#add: 'a' at: 0 => ['a'] ++ self");

        opcodes("#times: a_block => (
            remaining = self,
            ->{ (remaining = remaining - 1) >= 0 } while_true: ->{ a_block value }
        )", ["STARTpush_keyword_method", %Q{"times:"}, "push_variable", "a_block", "push_list", "1", "push_self", "store", "remaining", "STARTpush_proc", "push_list", "0", "push_variable", "remaining", "push_1", "binary", "-", "store", "remaining", "push_list", "1", "push_0", "binary", ">=", "ENDpush_proc", "STARTpush_proc", "push_list", "0", "push_variable", "a_block", "unary", "value", "ENDpush_proc", "keyword", "while_true:", "1", "push_list", "2", "ENDpush_keyword_method", "pop"]);
    end

    it "emits for C function definitions" do
        opcodes("###void f()", ["STARTpush_c_function", "push_variable", "void", "push_variable", "f", "push_list", "0", "ENDpush_c_function", "pop"]);
        opcodes("###void f2(int a, int b)", ["STARTpush_c_function", "push_variable", "void", "push_variable", "f2", "push_variable", "CFunParam", "push_variable", "int", "push_variable", "a", "keyword", "c_type:c_name:", "2", "push_variable", "CFunParam", "push_variable", "int", "push_variable", "b", "keyword", "c_type:c_name:", "2", "push_list", "2", "ENDpush_c_function", "pop"]);
    end
end
