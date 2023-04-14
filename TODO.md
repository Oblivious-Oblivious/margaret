## (✗) ver. 0.2.0
-----------------
    🟥 Add visual literals of trees, graphs and matrices (2-dimentional data representation).
    🟥 Use comments for docs or TODO graphs.
    🟥 Use crystal-lang C extensions to bind native values to margaret ones. C code should be exported as a static library and the exposed API should be declared in code.
    🟥 Add string interpolation and formatting with `#{..}` or similar.

## (✗) ver. 0.1.0
-----------------
    🟥 Make comments part of the language (Comment new: "...").
    🟥 Make comments dynamic and persistent on code files.
    🟥 Add primitives for `while_true` to avoid endless recursion.
    🟥 Add a switch matcher -> `obj match: [[1, 100], [2, 200], [3, 300],]`.
    🟥 Make bang (!) messages denote persistant changes in object state.
    🟥 Add a `message then: unit1 else: unit2`.
    🟥 Add complex numbers `(0+2i)`, and rational numbers `(1/2r)` -> unary messages.
    🟥 Use custom syntax structures for break and continue. -> `list iterate: { elem | elem puts } exit_on: { elem | elem == 42 }`
    ---------------------------
    🟥 Add functional features:
    🟥 [<a, b, c] = [<"hello", "world", 42] (TUPLES)
    🟥 [<car, cdr] = [1, 2, 3] # car = 1, cdr = [2, 3]
    🟥 l = [1,2,3], [[list, 4], 5] compact!. # [1,2,3,4,5]
    🟥 hash = {a: 1, b: 2}, hash = hash ++ {c: 3}. #{a: 1, b: 2, c: 3}
    🟥 Numeric bind: # 0 fact => 1
       Numeric bind: # _ fact => self * (self - 1) fact
       Numeric bind: # 0 ** a_number => 0
       Numeric bind: # 0 ** 0 => nil
       Array bind: # [] add: element at: position => 17
       Array bind: # [] add: 'a' at 0 => ['a']
       Array bind: # _ add: 'a' at 0 => ['a'] ++ self
    🟥 Numeric bind_multi: [
        # 0 ** 0 => nil,
        # 0 ** _ => 0,
        # _ ** 0 => 1,
        # ** other => self raised_to: other,
    ]
    ---------------------------
    🟥 Compile time bytecodes
        Stored along with runtime ones.
        Executed only once.
        End-toend optimization.
    🟥 Methods and functions compile to procs with own context.
        Procs compile to bitstrings/tensors/arrays of opcodes and are first class literals.
        Can be passed into optimization phases at runtime.
    🟥 Objects are (maybe?) represented as hashmap of slots.
        Preferably only one parent.
        Hashes though serving as activation windows should be optimized,
        abstracted out or at least follow data-oriented programming principles.
