## (✗) ver. 1.0.0
-----------------
  🟥 Implement all literals and stdlib
    🟩 $nil                                                  -> ($NilProto clone)   -> singleton
    🟩 $true                                                 -> ($TrueProto clone)  -> singleton
    🟩 $false                                                -> ($FalseProto clone) -> singleton
    🟩 ::label                                               -> ($LabelProto clone)
    🟩 42, 4_200, 0b0110, 0B10, 0xbeef, 0X0427, 0o741, 0O210 -> ($IntegerProto clone)
    🟩 42.0, 42_42.42_42                                     -> ($FloatProto clone)
    🟩 "foo\tbar"                                            -> ($StringProto clone)
    🟩 [42, "Hello", false]                                  -> ($TensorProto clone)
    🟩 %{"a": 1, b: 2}                                       -> ($HashProto clone)
    🟩 %[1, 2]                                               -> ($TupleProto clone)
    🟩 %(1::1, 0::1)                                         -> ($BitstringProto clone)
    🟩 {a | a + 1}                                           -> ($ProcProto clone)
    🟩 #put: element at: position => ()                      -> ($MethodProto clone)
  🟥 Add visual literals of trees, graphs and matrices (2-dimentional data representation).
     Most likely part of an IDE that casts the data into tensors.
  🟥 Add a way to encode/encrypt bytecode deployables with some sort of PGP/Diffie Hellman.

## (✗) ver. 0.0.4
-----------------
  🟥 Add green threads.
  🟥 Upgrade to a concurrent tricolor generational mark & sweep gc.
     Employ a separate process/thread for collection.
     Store a fiber in each object that listens for collections.
     This fiber can choose to give itself for collection or not depending on whether the objects is being used for performance oriented calculation.
  🟥 Upgrade to a compacting concurrent tricolor generational mark & sweep gc.
     Stress test for fragmentation issues.

## (✗) ver. 0.0.3
-----------------
  🟥 Upgrade to a mark & sweep generational gc, gen0, gen1, gen2.
  🟥 Upgrade to a tricolor generational mark & sweep gc.
     Precursor to concurrent implementation.
  🟥 Modify the pipeline for cocurrent execution (tokenization -> parsing -> evaluation) token by token.
  🟥 Add syntax for using user defined inferred objects -> Inferred start_using: MyObject, one: 1 two: 2   -> (MyObject one: 1 two: 2) Inferred stop_using: MyObject
     Possibly MyObject can inherit from Margaret to not lose predefined marg messages
     FormalMessages step can always infer `Margaret` because at runtime it can replace the correct object using the inheritance structures.
     `one:two:` can be sent to MyObject, but `if:then:` can be sent to Margaret.
     `Margaret` uses delegation pattern: maintains a priority queue of objects with priority based on inheritance, first sends message to all children and to itself at last.
     e.g. for `MyObject2 < MyObject1 < Margaret`, we send `one:two:` to MyObject2, it fowards it to parents and finally to Margaret, which responds or sends `method_missing`.

## (✗) ver. 0.0.2
-----------------
  🟥 Pattern-match multimethods by hashing receiver and parameters.
     Every multi-method is hashed into a unique value and searched for in the method table of the receiver.
  🟥 Optimize the design Hash to be data-oriented (separate keys from values for locality).
  🟥 Optimize hash function for better string interning.
  🟥 Add big integers and big floats.
  🟥 Refactor `include:`, `call` and `call:` into primitive messages.
  🟥 Use comments for docs or TODO graphs.
  🟥 Add cascaded messages.
  🟥 Add a custom mark and sweep garbage collector.
  🟥 Optimize repeating bytecodes that offer no state change outside the loop.
  🟥 Think of most syntax, semantic or runtime errors and spec them.
  🟥 Add UTF8 and Unicode support.

## (✗) ver. 0.0.1
-----------------
  🟥 Add lexically removed comments.
  🟥 Make comments part of the language (Comment new: "...").
  🟥 Add a macro system where you can pass formal bytecode as a message implementation.
     primitive `bytecode:` message that simply places the formal bytecodes in between the rest of the code.
  🟥 Add code-as-data functionality, storing bytecode as byte arrays and messages to interpret them.
  🟥 Figure out dynamic send for dynamically called messages.
  🟥 Add symbol objects and frozen strings.
  🟥 Make comments dynamic and persistent on code files.
  🟥 Add string interpolation and formatting with `#{..}` or similar.
  🟥 Since comments are dynamic, we can use interpolation to change them according to data (for documentation comments).
  🟥 Separate value types from object types.
     Add atomic types that become atemporal (cannot be extended through prototypes).
  🟥 Add spec for missing code from C side.
     Scanner module.
     byte_conversions module.
     Stack tests and vm data tests.
  🟩 Procs and methods return tensors of bytecodes.
  🟩 Implement if:then:else: using lambda calculus.
  🟥 Implement `while:` using the `goto:` primitive to avoid endless recursion.
  🟥 Add a `bind:` message to tensors so we can add tensors of unbound methods.
     `$Object extend: [m1, m2, m3]` binds those methods into $Object.
  🟥 Add a switch matcher -> `obj match: %[%[1, 100], %[2, 200], %[3, 300],]`.
  🟥 Make bang (!) messages denote persistant changes in object state.
  🟥 Add complex numbers `(0+2i)`, and rational numbers `(1/2r)` -> unary messages.
  🟥 Add complex and rational specific messages.
  🟥 Use GOTO for break and continue. -> `list iterate: { elem | if: { elem == 42 } then: { goto: exit_label } elem puts } ::exit_label`.
  🟥 Create an object `detatch` functionality that removes the inheritance link and object model metadata.
     Add object `freezing` that removes state modification capabilities.
  🟩 Create an `import/require` Margaret message.
     Probably simple concatenation of files (C-like include), not actual module system.
  🟥 Add an internal include guard for the require primitive.
  🟥 Add functionality for reading multiple files and changing the VM pointer to the currect file we are scanning.
  ---------------------------
  🟥 Add functional features:
  🟥 %[a, b, c] = %["hello", "world", 42]
  [a, b, c] = [1, 2, 3]
  $List bind: #= other => self.size.times: { i |
    bytecode: [
      "INTEGER", other get: i,
      "STORE_LOCAL", self get: i,
    ]
  }
  🟥 %[car, cdr] = %[1, 2, 3] # car = 1, cdr = [2, 3]
  🟥 l = [1,2,3], [[list, 4], 5] compact!. # [1,2,3,4,5]
  🟥 hash = {a: 1, b: 2}, hash = hash ++ {c: 3}. #{a: 1, b: 2, c: 3}
  🟥 Numeric bind: # 0 fact => 1
     Numeric bind: # _ fact => self * (self - 1) fact
     Numeric bind: # 0 ** a_number => 0
     Numeric bind: # 0 ** 0 => nil
     Array bind: # [] add: element at: position => 17
     Array bind: # [] add: 'a' at 0 => ['a']
     Array bind: # _ add: 'a' at 0 => ['a'] ++ self
  🟩 Setup message binding and sending:
     $Lhs msg -> Method {name: "msg", parameters: {}}
     msg $Lhs (no change)

     $Unary msg -> Method {name: "msg", parameters: {}}
     $Unary msg -> (no change)

     $Binary + other -> Method {name: "+", parameters: ["other"]}
     $Binary + 3 -> parameters: "+": 3 -> table_add(locals, parameters.get[0], 3)

     $Keyword at: position put: element -> Method {name: "at:put:", parameters: ["position", "element"]}
     $Keyword at: 0 put: 42 -> parameters: "at": 0, "put": 42
        -> actual_params = [0, 42]
        -> foreach param:
            table_add(locals, parameters.get[i], actual_params[i])
  ---------------------------
  🟩 Compile time bytecodes
     Stored along with runtime ones.
     Executed only once.
     End-to-end optimization.
  🟩 Methods and functions compile to procs with own context.
     Procs compile to bitstrings/tensors/arrays of opcodes and are first class literals.
  🟩 Objects are (maybe?) represented as hashmap of slots.
     Preferably only one parent.
