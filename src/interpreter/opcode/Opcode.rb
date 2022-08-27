module Opcode
    STACK_CODES = [
        "push_nil",
        "push_true",
        "push_false",
        "push_0",
        "push_1",
        "push_minus_1",
        "push_2",
        "push_integer",
        "push_float",
        "push_binary",
        "push_hexadecimal",
        "push_octal",
        "push_big_integer",
        "push_big_float",
        "push_string",
        "push_variable",
        "push_instance",
        "push_list",


        "pop",
        # "popn",

        "store",
        # "store_local",
        # "store_global",
        # "store_upvalue",
        "store_instance",
    ];

    JUMP_CODES = [
        # "label",

        # # 8 bit jumps
        # "jump",
        # "jump_if_zero",
        # "jump_if_not_zero",
        # "jump_if_true",
        # "jump_if_false",

        # # 16 bit jumps
        # "longjump",
        # "longjump_if_zero",
        # "longjump_if_not_zero",
        # "longjump_if_true",
        # "longjump_if_false",

        # "return",
        # "return_nil",
        # "return_true",
        # "return_false",
        # "return_stack_top",
    ];

    SEND_CODES = [
        "unary",
        # ... most used unaries
        # ...
        # ...
        "binary",
        # ... most used binaries
        # ...
        # ...
        "keyword",
        # ... most used keywords
        # ...
        # ...

        # "self_unary",
        # "self_binary",
        # "self_keyword",

        # "super_unary",
        # "super_binary",
        # "super_keyword",
    ];
end
