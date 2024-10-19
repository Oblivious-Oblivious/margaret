## (✗) ver. 1.0.0
-----------------
  🟥 Implement all literals and stdlib
    🟩 $nil                                                  -> ($NilProto clone)   -> singleton
    🟩 $true                                                 -> ($TrueProto clone)  -> singleton
    🟩 $false                                                -> ($FalseProto clone) -> singleton
    🟩 42, 4_200, 0b0110, 0B10, 0xbeef, 0X0427, 0o741, 0O210 -> ($IntegerProto clone)
    🟩 42.0, 42_42.42_42                                     -> ($FloatProto clone)
    🟩 :some_symbol                                          -> ($SymbolProto clone)
    🟩 ::label                                               -> ($LabelProto clone)
    🟩 "foo\tbar"                                            -> ($StringProto clone)
    🟩 [42, "Hello", false]                                  -> ($TensorProto clone)
    🟩 %[1, 2]                                               -> ($TupleProto clone)
    🟩 %{"a": 1, b: 2}                                       -> ($TableProto clone)
    🟩 %(1::1, 0::1)                                         -> ($BitstringProto clone)
    🟩 {a | a + 1}                                           -> ($MethodProto clone) -> headless
    🟩 #put: element at: position => ()                      -> ($MethodProto clone) -> object bound
  🟥 Add an IDE that live inspects all values next to the code similar to Quokka.js
  🟥 Add visual literals of trees, graphs and matrices (2-dimentional data representation).
     Most likely part of an IDE that casts the data into tensors.
  🟥 Add a way to encode/encrypt bytecode deployables with some sort of PGP/Diffie Hellman.

## (✗) ver. 0.0.3
-----------------
  🟥 Decrease the size of the Instruction to 32 bits to imporove performance.
     This will require that registers are at most 256 in size since `A` value will be 8 bits.
     Handle spilling by splitting methods into smaller ones.
  🟥 Add green threads.
  🟥 Upgrade to a mark & sweep generational gc, gen0, gen1, gen2.
  🟥 Upgrade to a tricolor generational mark & sweep gc.
     Employ a separate process/thread for collection.
     Store a fiber in each object that listens for collections.
     This fiber can choose to give itself for collection or not depending on whether the objects is being used for performance oriented calculation.
  🟥 Upgrade to a compacting concurrent tricolor generational mark & sweep gc.
     Stress test for fragmentation issues.
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
  🟩 Optimize the design Table to be data-oriented (separate keys from values for locality).
  🟥 Implement storing and loading bytecode from compiled files, similar to Java.
     Pipeline: compile constants to direct data -> load and store constants in VM -> execute by loading constants from table.
  🟩 Optimize hash function for better string interning.
  🟥 Add big integers and big floats.
  🟥 Refactor `include:`, `call` and `call:`, `<-` into primitive messages.
  🟥 Use comments for docs or TODO graphs.
  🟥 Add cascaded messages.
  🟥 Add a custom mark and sweep garbage collector.
  🟥 Optimize repeating bytecodes that offer no state change outside the loop.
  🟥 Think of most syntax, semantic or runtime errors and spec them.
  🟩 Add UTF8 and Unicode support.
  🟥 Add regular expressions.
  🟥 Create an object `detatch` functionality that removes the inheritance link and object model metadata.
     Add object `freezing` that removes state modification capabilities.
  🟥 Separate value types from object types.
     Add atomic types that become atemporal (cannot be extended through prototypes).

## (✗) ver. 0.0.1
-----------------
  🟥 Add lexically removed comments.
  🟥 Make comments part of the language (comment: "...", todo: "...").
  🟥 Separate value representation for small strings that stores the characters inline in the value.
  🟥 Add symbol objects and frozen strings.
  🟥 Make comments dynamic and persistent on code files.
  🟥 Add string interpolation and formatting with `#{..}` or similar.
  🟥 Since comments are dynamic, we can use interpolation to change them according to data (for documentation comments).
  🟥 In the NaN boxing scheme do not reallocate integer and float representations, instead use unboxed values directly.
  🟥 Add a `@this`, `@it` or equivalent that refers to the original object.
     @this would always refer to object where original method is defined,
     not the object where the method is called.
  🟥 Define an opcode for calling native C functions and extensions.
     OABC command where:
       O is the opcode.
       A is the function name.
       B is the output register.
       C is the input tensor of arguments.
     Native C extensions require rebuilding of the language
     Use a ./margaret rebuild command of some sort that rebuilds with user-defined extensions and replaces itself.
  🟩 Methods return tensors of bytecodes.
  🟩 Implement if:then:else: using lambda calculus.
  🟥 Add functionality for reading multiple files and changing the VM pointer to the currect file we are scanning.
  🟥 Implement `while:` using the `goto:` primitive to avoid endless recursion.
  🟥 Add a `bind:` message to tensors so we can add tensors of unbound methods.
     `$Object bind: [m1, m2, m3]` binds those methods into $Object.
  🟥 Add a switch matcher -> `obj match: %[%[1, 100], %[2, 200], %[3, 300],]`.
  🟥 Make bang (!) messages denote persistant changes in object state.
  🟥 Add __LINE__ __FILE__ and __DIR__ macros.
  🟥 Add a primitive for raising errors.  The raise: message is the only one that crashes the VM.
     $Numeric -- #/ 0 => raise: "division by zero",
     $Numeric -- #/ other => @self / other,
     If the analyzer cannot figure out the inputs of the division message, LSP warns for potential runtime crash.
  🟥 Create compile-time messages, which will make calculations in the emitter phase but will not generate bytecode.
  🟥 Use GOTO for break and continue. -> `list iterate: { elem | if: { elem == 42 } then: { goto: exit_label } elem puts } ::exit_label`.
  🟥 Disallow all dynamic code generation.
     All code should be lexically defined.
     Extension happens only through the primitive bind message.
     Primitive bind only accepts method objects.
     Creating method objects are restricted to the literal definition.
     Method.new is NOT exposed to the front end directly, only indirectly through literal.
     The LSP should recusively track all messages and warn about the ones that raise.
     Raising errors should theoretically define all boundaries in whether an object can receive some message or not.
     When we send a message the LSP analyzes all paths and figures out which conditions would trigger a #dnu with a raise.
     If we lexically understand all state (which requires non-dynamically evaluated code) all potential #dnus should be caught.
       $Margaret -- #raise: message_name => _PRIM_RAISE_a1: @self a2: message_name,
       $Margaret -- #dnu: message_name => _PRIM_DNU_RAISE_a1: @self a2: message_name,
       $Numeric -- #/ 0 => raise: "division by zero",
       $Numeric -- #/ other => _PRIM_DIV_a1: @self a2: other,
     Here the LSP catches all `raise_from_dnu` messages.
     Normal raises are only caught when the multimethod can be lexically resovled.
       v1 = 0,
       v2 = $Margaret some_service,
       42 / 0,  comment: "static            -> always caught by the multimethod",
       42 / v1, comment: "deterministic     -> caught if we perform constant folding",
       42 / v2, comment: "non-deterministic -> cannot be caught",
  🟥 Double check that vm works on 16-bit word machines with 32-bit pointers/doubles.
  🟥 Add complex numbers `(0+2i)`, and rational numbers `(1/2r)` -> unary messages.
  🟥 Add complex and rational specific messages.
  🟩 Create an `import/require` Margaret message.
     Probably simple concatenation of files (C-like include), not actual module system.
  🟥 Add an internal include guard for the require primitive.
  🟥 %[a, b, c] = %["hello", "world", 42]
  [a, b, c] = [1, 2, 3]
  $List bind: #= other => self.size.times: { i |
    bytecode: [
      "INTEGER", other get: i,
      "STORE_LOCAL", self get: i,
    ]
  }
  🟥 %[:car, :cdr] = %[1, 2, 3] # car = 1, cdr = %[2, 3]
  🟥 %[:car, :cdr] = %[1, 2] # car = 1, cdr = %[2], (flatten), cdr = 2
  🟥 %[:car, :cdr] = %[1] # car = 1, cdr = %[], (flatten), cdr = nil
  🟥 %[:car, :cdr] = %[] # car = nil, cdr = nil
  🟥 l = [1,2,3], [[list, 4], 5] compact!. # [1,2,3,4,5]
  🟥 table = {a: 1, b: 2}, table = table ++ {c: 3}. #{a: 1, b: 2, c: 3}
  🟥 Numeric bind: # 0 fact => 1
     Numeric bind: # _ fact => self * (self - 1) fact
     Numeric bind: # 0 ** a_number => 0
     Numeric bind: # 0 ** 0 => nil
     Array bind: # [] add: element at: position => 17
     Array bind: # [] add: 'a' at 0 => ['a']
     Array bind: # _ add: 'a' at 0 => ['a'] ++ self
  🟩 Setup 6 types of message binding and sending:
     subscript, lhs, unary, binary, keyword, assignment
  🟩 Compile time bytecodes
     Stored along with runtime ones.
     Executed only once.
     End-to-end optimization.
  🟩 Methods and functions compile to procs with own context.
     Procs compile to bitstrings/tensors/arrays of opcodes and are first class literals.
  🟩 Objects are (maybe?) represented as table of slots.
     Preferably only one parent.
