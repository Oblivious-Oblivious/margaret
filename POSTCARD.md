```margaret
($Margaret bind: #ultimate_answer: x => (
    $true && $false not && ($nil is_nil?) if_false: {( exit: 0 )},
    y = @self methods size + @super to_string length * 42,
    ["str", 42, 42.2, 0b0110, 0xbeef, 0o741,
     {"k1": 42, k2: 43}, [< 1, 2], {< 1:1, 0:1}] each: { elem | (
        puts: elem object_id,
    )},
    if: x < y then: { x } else: { y },
),
puts: (ultimate_answer: 42))
```
