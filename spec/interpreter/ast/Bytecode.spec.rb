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
        opcodes("0b0110", ["push_binary", "0b0110", "pop"]);
        opcodes("0B10", ["push_binary", "0b10", "pop"]);
        opcodes("-0b0110", ["push_binary", "-0b0110", "pop"]);
        opcodes("-0B10", ["push_binary", "-0b10", "pop"]);
        opcodes("(
            x = 0b0101 + 0b1011,
            x to_int puts,
        )", ["push_binary", "0b0101", "push_binary", "0b1011", "binary", "+", "store", "x", "push_variable", "x", "unary", "to_int", "unary", "puts", "push_list", "2", "pop"]);
    end

    it "emits for hexadecimals" do
        opcodes("0xbeef", ["push_hexadecimal", "0xbeef", "pop"]);
        opcodes("-0xbeEf", ["push_hexadecimal", "-0xbeef", "pop"]);
        opcodes("0X0427", ["push_hexadecimal", "0x0427", "pop"]);
        opcodes("-0X0427", ["push_hexadecimal", "-0x0427", "pop"]);
        opcodes("x = 0xbeef to_bin to_int puts", ["push_hexadecimal", "0xbeef", "unary", "to_bin", "unary", "to_int", "unary", "puts", "store", "x", "pop"]);
        opcodes("0xbeef - 0xabb2", ["push_hexadecimal", "0xbeef", "push_hexadecimal", "0xabb2", "binary", "-", "pop"]);
    end

    it "emits for octals" do
        opcodes("0o741", ["push_octal", "0o741", "pop"]);
        opcodes("-0o741", ["push_octal", "-0o741", "pop"]);
        opcodes("0O0210", ["push_octal", "0o0210", "pop"]);
        opcodes("-0O0210", ["push_octal", "-0o0210", "pop"]);
        opcodes("x = 0o751 to_hex to_bin to_int puts", ["push_octal", "0o751", "unary", "to_hex", "unary", "to_bin", "unary", "to_int", "unary", "puts", "store", "x", "pop"]);
        opcodes("0O541 + 0o777", ["push_octal", "0o541", "push_octal", "0o777", "binary", "+", "pop"]);
    end

    it "emits for big integers" do
        opcodes("0bi42_000", ["push_big_integer", %Q{"42000"}, "pop"]);
        opcodes("-0bi42_000", ["push_big_integer", %Q{"-42000"}, "pop"]);
        opcodes("0bi42000", ["push_big_integer", %Q{"42000"}, "pop"]);
        opcodes("-0bi42000", ["push_big_integer", %Q{"-42000"}, "pop"]);
    end

    it "emits for big floats" do
        opcodes("0bf0.042", ["push_big_float", %Q{"0.042"}, "pop"]);
        opcodes("-0bf0.042", ["push_big_float", %Q{"-0.042"}, "pop"]);
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
        opcodes("self", ["push_variable", "self", "pop"]);
        opcodes("super", ["push_variable", "super", "pop"]);
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
        opcodes("{a: {}, b: {}}", ["push_string", %Q{"a"}, "push_hash", "0", "keyword", "key:value:", "2", "push_string", %Q{"b"}, "push_hash", "0", "keyword", "key:value:", "2", "push_hash", "2", "pop"]);
        opcodes("{a: 1, b: 2, c: 3}", ["push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3", "pop"]);
        opcodes(%Q{{"a": 1, "b": 2, "c": 3}}, ["push_string", %Q{"a"}, "push_1", "keyword", "key:value:", "2", "push_string", %Q{"b"}, "push_2", "keyword", "key:value:", "2", "push_string", %Q{"c"}, "push_integer", "3", "keyword", "key:value:", "2", "push_hash", "3", "pop"]);
    end

    it "emits for blocks" do
        opcodes("->{x = (x = 1, y = 2)}", ["push_variable", "List", "push_0", "keyword", "new:", "1", "push_1", "store", "x", "push_2", "store", "y", "push_variable", "List", "push_2", "keyword", "new:", "1", "store", "x", "keyword", "params:function:", "2", "pop"]);
        opcodes("x = ->{
            v1, v2, (
                v1 += 1,
                v1 += 2,
                v1 * v2
            )
        }", ["push_variable", "v1", "push_variable", "v2", "push_variable", "List", "push_2", "keyword", "new:", "1", "push_variable", "v1", "push_1", "binary", "+=", "push_variable", "v1", "push_2", "binary", "+=", "push_variable", "v1", "push_variable", "v2", "binary", "*", "push_variable", "List", "push_integer", "3", "keyword", "new:", "1", "keyword", "params:function:", "2", "store", "x", "pop"]);
        opcodes("->{42}", ["push_variable", "List", "push_0", "keyword", "new:", "1", "push_integer", "42", "keyword", "params:function:", "2", "pop"]);
        opcodes("->{a | a puts}", ["push_variable", "a", "push_variable", "List", "push_1", "keyword", "new:", "1", "push_variable", "a", "unary", "puts", "keyword", "params:function:", "2", "pop"]);
        opcodes("->{2 + 3}", ["push_variable", "List", "push_0", "keyword", "new:", "1", "push_2", "push_integer", "3", "binary", "+", "keyword", "params:function:", "2", "pop"]);
        opcodes("->{(x = 1, y = 2, x + y)}", ["push_variable", "List", "push_0", "keyword", "new:", "1", "push_1", "store", "x", "push_2", "store", "y", "push_variable", "x", "push_variable", "y", "binary", "+", "push_variable", "List", "push_integer", "3", "keyword", "new:", "1", "keyword", "params:function:", "2", "pop"]);
        opcodes("->{a, b | a + b}", ["push_variable", "a", "push_variable", "b", "push_variable", "List", "push_2", "keyword", "new:", "1", "push_variable", "a", "push_variable", "b", "binary", "+", "keyword", "params:function:", "2", "pop"]);
        opcodes("->{a, a}", ["push_variable", "a", "push_variable", "List", "push_1", "keyword", "new:", "1", "push_variable", "a", "keyword", "params:function:", "2", "pop"]);
        opcodes("->{x = 2} exec", ["push_variable", "List", "push_0", "keyword", "new:", "1", "push_2", "store", "x", "keyword", "params:function:", "2", "unary", "exec", "pop"]);
        opcodes("->{param | param puts} value: 42", ["push_variable", "param", "push_variable", "List", "push_1", "keyword", "new:", "1", "push_variable", "param", "unary", "puts", "keyword", "params:function:", "2", "push_integer", "42", "keyword", "value:", "1", "pop"]);
    end

    it "emits for assignment" do
        opcodes("x = 4", ["push_integer", "4", "store", "x", "pop"]);
        opcodes("x = y = z = 6", ["push_integer", "6", "store", "z", "store", "y", "store", "x", "pop"]);
        opcodes("x = (y = 6) + 1", ["push_integer", "6", "store", "y", "push_list", "1", "push_1", "binary", "+", "store", "x", "pop"]);
        opcodes("@x = x + 2", ["push_variable", "x", "push_2", "binary", "+", "store_instance", "x", "pop"]);
        opcodes("a = b = (c = 42) + 12", ["push_integer", "42", "store", "c", "push_list", "1", "push_integer", "12", "binary", "+", "store", "b", "store", "a", "pop"]);
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
        opcodes("arr add: 'a' add: 'b' at: 3", ["push_variable", "arr", "push_string", "'a'", "push_string", "'b'", "push_integer", "3", "keyword", "add:add:at:", "3", "pop"]);
        opcodes("arr add: 'a' at: 1 add: 'b' at: 2", ["push_variable", "arr", "push_string", "'a'", "push_1", "push_string", "'b'", "push_2", "keyword", "add:at:add:at:", "4", "pop"]);
    end
end
