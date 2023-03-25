# Margaret

[![GPLv3 License](https://img.shields.io/badge/license-GPL%20v3-yellow.svg)](./LICENSE)

Margaret is a modern programming language focused around objects and messages.
It offers powerful literals, easy to use objects and smalltalk-like message structures.

* Every value in Margaret is treated as an object.
* There are no reserved words and no explicit syntax apart from message sends.
* Uses prototype based objects in the likes of Self or Javascript.
* Uses C-style literals like char, int, float, string.
* Implements tensors and hashes as the only built in, array-like data structures.
* Runs on a portable, lightweight and embeddable stack based VM.

## Installation

TODO Write installation instructions

## "Postcard"

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

- [Oblivious](https://github.com/Oblivious-Oblivious) - creator and maintainer
