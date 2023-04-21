🟩 nil -> (NilClass new) -> singleton
🟩 true -> (TrueClass new) -> singleton
🟩 false -> (FalseClass new) -> singleton

🟩 42, -42, 4_200, -4_200 -> (Integer new)
🟩 0b0110, 0B10 -> (Binary new < Integer new)
🟩 0xbeef, 0X0427 -> (Hexadecimal new < Integer new)
🟩 0o741, 0O210 -> (Octal new < Integer new)

🟩 42.0, -42.42 -> (Float new)

🟩 "foo\tbar" -> (String new)

🟩 [42, "Hello", 'x'] -> (Tensor new)
🟩 {"a": 1, b: 2} -> (Hash new)
🟩 [< 1, 2] -> (Tuple new)
🟩 {< 1:1, 0:1} -> (Bitstring new)

🟩 {a | a + 1} -> (Proc new)
🟩 #put: element at: position => () -> (Method new)
🟩 ###void fun(double a, int *b) -> (CFunction new)
