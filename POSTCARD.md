```margaret
#example_with_number: x => (
    true & false not & (nil is_nil?) if_false: -> { self halt },
    y = self size + super size,
    ['a', "a", 1, 1.0, {"k1": 42, k2: 43}] each: -> { elem | (
        elem class name puts,
        " " puts
    )},
    x < y
)
```