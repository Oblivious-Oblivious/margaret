## (✗) ver. 0.4.0
-----------------
    🟥 Add green threads
    🟥 Upgrade to a concurrent tricolor generational mark & sweep gc
       Employ a separate process/thread for collection
       Store a fiber in each object that listens for collections
       This fiber can choose to give itself for collection or not depending on whether the objects is being used for performance oriented calculation.

## (✗) ver. 0.3.0
-----------------
    🟥 Add a custom mark and sweep garbage collector
    🟥 Upgrade to a mark & sweep generational gc
       gen0, gen1, gen2
       every 3 gen0 collections, collect gen1 once, every 10 gen0 collections collect gen2 once
    🟥 Upgrade to a tricolor generational mark & sweep gc
       Precursor to concurrent implementation

## (✗) ver. 0.2.0
-----------------
    🟥 Optimize the design Hash to be data-oriented (separate keys from values for locality).
    🟥 Optimize hash function for better string interning.
    🟥 Add a character literal.
    🟥 Add big integers and big floats.
    🟥 Implement precedent rules on multibound method dispatch (not just order of definition)
    🟥 Add visual literals of trees, graphs and matrices (2-dimentional data representation).
    🟥 Use comments for docs or TODO graphs.
    🟥 Use crystal-lang C extensions to bind native values to margaret ones. C code should be exported as a static library and the exposed API should be declared in code.
    🟥 Add cascaded messages.
    🟥 Optimize repeating bytecodes that offer no state change outside the loop
    🟥 Add syntax for using user defined inferred objects -> Inferred start_using: MyObject, one: 1 two: 2   -> (MyObject one: 1 two: 2) Inferred stop_using: MyObject
       Possibly MyObject can inherit from Margaret to not lose predefined marg messages
       FormalMessages step can always infer `Margaret` because at runtime it can replace the correct object using the inheritance structures.
       `one:two:` can be sent to MyObject, but `if:then:` can be sent to Margaret.
       `Margaret` uses delegation pattern: maintains a priority queue of objects with priority based on inheritance, first sends message to all children and to itself at last.
       e.g. for `MyObject2 < MyObject1 < Margaret`, we send `one:two:` to MyObject2, it fowards it to parents and finally to Margaret, which responds or sends `method_missing`.

## (✗) ver. 0.1.0
-----------------
    🟥 Add lexically removed comments.
    🟥 Make comments part of the language (Comment new: "...").
    🟥 Make comments dynamic and persistent on code files.
    🟥 Since comments are dynamic, we can use interpolation to change them according to data (for documentation comments).
    🟥 Add string interpolation and formatting with `#{..}` or similar.
    🟥 Separate value types from object types
       Nil, True, False, Integer, Float, String are `VALUES` (cannot change self)
       Tensor, Hash, Tuple, BitString are `OBJECTS`          (can change self)
    🟥 Procs, methods and functions return tensors of bytecodes.
    🟥 Add primitives for `while:` to avoid endless recursion.
    🟥 Add a switch matcher -> `obj match: [[1, 100], [2, 200], [3, 300],]`.
    🟥 Make bang (!) messages denote persistant changes in object state.
    🟥 Add complex numbers `(0+2i)`, and rational numbers `(1/2r)` -> unary messages.
    🟥 Use GOTO for break and continue. -> `list iterate: { elem | if: { elem == 42 } then: {( goto: exit_label )} elem puts } Label new: "exit_label"`.
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
    🟥 Typecheck default parameters on multimethods!!
    ---------------------------
    🟩 Compile time bytecodes
       Stored along with runtime ones.
       Executed only once.
       End-to-end optimization.
    🟩 Methods and functions compile to procs with own context.
       Procs compile to bitstrings/tensors/arrays of opcodes and are first class literals.
    🟩 Objects are (maybe?) represented as hashmap of slots.
       Preferably only one parent.
