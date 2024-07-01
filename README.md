# margaret

[![GPLv3 License](https://img.shields.io/badge/license-GPL%20v3-yellow.svg)](./LICENSE)

Margaret is a modern programming language focused around objects and messages.
It offers powerful literals, easy to use objects and smalltalk-like message structures.

- Every value in margaret is treated as an object.
- There are no reserved words and no explicit syntax apart from message sends.
- Uses prototype based objects in the likes of Self or Javascript.
- Uses C-style literals like int, float, string.
- Implements tensors, hashes, tuples as modern built-in data structures.
- Runs on a portable, lightweight and embeddable stack based VM.

## Installation

TODO Write installation instructions

## "Postcard"

```margaret
$Margaret -- #ultimate_answer: x => (
  $true && !$false not not && ($nil is_nil?) if_false: { exit: 0 },
  y = @self methods size + @super to_string length * 42,
  [::label, 42, 42.2, "str", 0b0110, 0xbeef, 0o741, %[y, 42, "val"],
    %{"k1": -42, k2: 43}, %(1::1, 0::1)] each: { elem |
      puts: elem object_id,
    },
  if: x < y then: { x } else: { y },
),
puts: (ultimate_answer: 42),
```

## Development

- [Changelog](https://github.com/Oblivious-Oblivious/margaret/blob/master/CHANGELOG.md)
- [Contributing](https://github.com/Oblivious-Oblivious/margaret/blob/master/CONTRIBUTING.md)

## Contributing

1. Fork it (<https://github.com/Oblivious-Oblivious/margaret/fork>)
2. Create your feature branch (`git checkout -b my-new-feature`)
3. Commit your changes (`git commit -am 'Add some feature'`)
4. Push to the branch (`git push origin my-new-feature`)
5. Create a new Pull Request

## Contributors

- [oblivious](https://github.com/Oblivious-Oblivious) - creator and maintainer
