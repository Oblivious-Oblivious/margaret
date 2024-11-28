#ifndef __EMMITER_SPEC_H_
#define __EMMITER_SPEC_H_

#include "../../libs/cSpec/export/cSpec.h"
#include "../../libs/EmeraldsString/export/EmeraldsString.h"
#include "../../src/emitter/Emitter.h"
#include "../../src/lexer/Lexer.h"
#include "../../src/opcode/instruction.h"
#include "../../src/opcode/MargMethod.h"
#include "../../src/opcode/opcodes.h"
#include "../../src/parser/Parser.h"

static void emit(VM *vm, char *code) {
  vm_reset();
  vm->source = string_new(code);
  lexer_make_tokens(vm);
  parser_analyze_syntax(vm);
  emitter_emit(vm);
}

module(EmmiterSpec, {
  VM *vm = vm_new("file.marg");
  describe("literals", {
    context("on scalars", {
      it("emits labels", {
        emit(vm, "::l");
        vm->current->ip++;
        assert_that(O is OP_STOZK);
        vm->current->ip++;
        assert_that(O is OP_HALT);
        assert_that(IS_LABEL(L("::l")));

        emit(vm, "::@l");
        vm->current->ip++;
        assert_that(O is OP_STOZK);
        vm->current->ip++;
        assert_that(O is OP_HALT);
        assert_that(IS_LABEL(I("::@l")));

        emit(vm, "::$l");
        vm->current->ip++;
        assert_that(O is OP_STOZK);
        vm->current->ip++;
        assert_that(O is OP_HALT);
        assert_that(IS_LABEL(G("::$l")));
      });

      it("emits symbols", {
        emit(vm, ":s");
        vm->current->ip++;
        assert_that(O is OP_STOZK);
        assert_that(IS_SYMBOL(K(-1)));
        assert_that_charptr(AS_SYMBOL(K(-1))->value equals to "s");
        vm->current->ip++;
        assert_that(O is OP_HALT);
      });

      it("emits integers", {
        emit(vm, "42");
        vm->current->ip++;
        assert_that(O is OP_STOZK);
        assert_that(IS_INTEGER(K(-1)));
        assert_that_int(AS_INTEGER(K(-1))->value equals to 42);
        vm->current->ip++;
        assert_that(O is OP_HALT);
      });

      it("emits floats", {
        emit(vm, "42.05");
        vm->current->ip++;
        assert_that(O is OP_STOZK);
        assert_that(IS_FLOAT(K(-1)));
        assert_that_double(AS_FLOAT(K(-1))->value equals to 42.05);
        vm->current->ip++;
        assert_that(O is OP_HALT);
      });

      it("emits strings", {
        emit(vm, "\"hello\"");
        vm->current->ip++;
        assert_that(O is OP_STOZK);
        assert_that(IS_STRING(K(-1)));
        assert_that_charptr(AS_STRING(K(-1))->value equals to "hello");
        vm->current->ip++;
        assert_that(O is OP_HALT);
      });

      context("on variables", {
        it("emits nil", {
          emit(vm, "$nil");
          vm->current->ip++;
          assert_that(O is OP_STOZK);
          assert_that(IS_NIL(K(-1)));
          vm->current->ip++;
          assert_that(O is OP_HALT);
        });

        it("emits false", {
          emit(vm, "$false");
          vm->current->ip++;
          assert_that(O is OP_STOZK);
          assert_that(IS_FALSE(K(-1)));
          vm->current->ip++;
          assert_that(O is OP_HALT);
        });

        it("emits true", {
          emit(vm, "$true");
          vm->current->ip++;
          assert_that(O is OP_STOZK);
          assert_that(IS_TRUE(K(-1)));
          vm->current->ip++;
          assert_that(O is OP_HALT);
        });

        it("emits self", {
          emit(vm, "@self");
          vm->current->ip++;
          assert_that(O is OP_STOZI);
          assert_that_size_t(I("@self") equals to G("$Margaret"));
          vm->current->ip++;
          assert_that(O is OP_HALT);
        });

        it("emits super", {
          emit(vm, "@super");
          vm->current->ip++;
          assert_that(O is OP_STOZI);
          assert_that_size_t(I("@super") equals to G("$Margaret"));
          vm->current->ip++;
          assert_that(O is OP_HALT);
        });

        it("emits global variables", {
          emit(vm, "$Margaret");
          vm->current->ip++;
          assert_that(O is OP_STOZG);
          assert_that_charptr(
            AS_OBJECT(G("$Margaret"))->name equals to "$Margaret"
          );
          vm->current->ip++;
          assert_that(O is OP_HALT);

          emit(vm, "$newglob");
          vm->current->ip++;
          assert_that(O is OP_STOZG);
          assert_that_charptr(AS_OBJECT(G("$newglob"))->name equals to "$nil");
          vm->current->ip++;
          assert_that(O is OP_HALT);
        });

        it("emits instance variables", {
          emit(vm, "@newinst");
          vm->current->ip++;
          assert_that(O is OP_STOZI);
          assert_that_size_t(I("@newinst") equals to G("$nil"));
          vm->current->ip++;
          assert_that(O is OP_HALT);
        });

        it("emits local variables", {
          emit(vm, "newlocal");
          vm->current->ip++;
          assert_that(O is OP_STOZL);
          assert_that_size_t(L("newlocal") equals to G("$nil"));
          vm->current->ip++;
          assert_that(O is OP_HALT);
        });
      });
    });

    it("emits tensors", {
      emit(vm, "[42, 42.05, \"hello\"]");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that(IS_INTEGER(K(A)));
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that(IS_FLOAT(K(A)));
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that(IS_STRING(K(A)));
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_tensor_new:"
      );
      vm->current->ip++;
      assert_that(O is OP_HALT);

      emit(vm, "[42, [1, 2, [43, 44, 45]]]");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_tensor_new:"
      );
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 3);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_tensor_new:"
      );
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 3);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_tensor_new:"
      );
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 2);
    });

    context("on headless methods", {
      xit("emits headless without arguments", {});

      xit("emits headless with 1 argument", {});

      xit("emits headless with 3 arguments", {});

      xit("executes headless and returns result of last instruction", {});
    });

    it("emits bitstrings", {
      emit(vm, "%(3::4)");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to
                          "__PRIM_bitstring_new:");
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 2);

      emit(vm, "%(1::1, 0::1, 1::1, 0::1)");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to
                          "__PRIM_bitstring_new:");
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 8);
      vm->current->ip++;
      assert_that(O is OP_HALT);
    });

    it("emits tuples", {
      emit(vm, "%[42, 42.05, \"hello\"]");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_tuple_new:");
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 3);
      vm->current->ip++;
      assert_that(O is OP_HALT);

      emit(vm, "%[1, %[2, 3, %[4, 5, 6]]]");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_tuple_new:");
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 3);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_tuple_new:");
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 3);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_tuple_new:");
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 2);
    });

    it("emits tables", {
      emit(vm, "%{a: 1, b: 2, c: 3}");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_charptr(AS_STRING(K(A))->value equals to "a");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_charptr(AS_STRING(K(A))->value equals to "b");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_charptr(AS_STRING(K(A))->value equals to "c");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_table_new:");
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 6);

      emit(vm, "%{a: %{aa: 1, bb: 2}, b: %{cc: 3, dd: 4}}");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_charptr(AS_STRING(K(A))->value equals to "a");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_charptr(AS_STRING(K(A))->value equals to "aa");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_size_t(AS_INTEGER(K(A))->value equals to 1);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_charptr(AS_STRING(K(A))->value equals to "bb");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_size_t(AS_INTEGER(K(A))->value equals to 2);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_table_new:");
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 4);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_charptr(AS_STRING(K(A))->value equals to "b");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_charptr(AS_STRING(K(A))->value equals to "cc");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_size_t(AS_INTEGER(K(A))->value equals to 3);
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_charptr(AS_STRING(K(A))->value equals to "dd");
      vm->current->ip++;
      assert_that(O is OP_STOZK);
      assert_that_size_t(AS_INTEGER(K(A))->value equals to 4);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_table_new:");
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 4);
      vm->current->ip++;
      assert_that(O is OP_SEND);
      assert_that_charptr(AS_STRING(K(A))->value equals to "__PRIM_table_new:");
      assert_that_size_t(AS_INTEGER(K(B))->value equals to 4);
    });

    context("on methods", {
      xit("creates keyword methods", {});

      xit("creates binary methods", {});

      xit("creates unary methods", {});

      xit("creates lhs methods", {});

      xit("creates subscript methods", {});

      xit("creates assignment mqethods", {});
    });
  });

  xdescribe("", {});
})

#endif
