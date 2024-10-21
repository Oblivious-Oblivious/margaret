#ifndef __EMITTER_H_
#define __EMITTER_H_

#include "../libs/EmeraldsString/export/EmeraldsString.h"
#include "instruction.h"
#include "object.h"
#include "opcode.h"

static Instruction *emit_tokens(VM *vm, char *source) {
  Instruction *bc = NULL;
  size_t i;
  char **tokens = string_split(source, ' ');
  size_t size   = vector_size(tokens);

  for(i = 0; i < size; i++) {
    if(string_equals(tokens[i], "exit")) {
      exit(0);
    } else if(string_equals(tokens[i], "print")) {
      OA(OP_PRINT, tokens[i + 1]);
      i++;
    } else if(string_equals(tokens[i + 1], "=")) {
      if(string_equals(tokens[i + 2], "nil")) {
        OAk(OP_NIL, tokens[i], NIL());
        i += 2;
      } else if(string_equals(tokens[i + 2], "false")) {
        OAk(OP_FALSE, tokens[i], FALSE());
        i += 2;
      } else if(string_equals(tokens[i + 2], "true")) {
        OAk(OP_TRUE, tokens[i], TRUE());
        i += 2;
      } else if(string_equals(tokens[i + 2], "number")) {
        OAk(OP_NUMBER, tokens[i], NUMBER(atof(tokens[i + 3])));
        i += 3;
      } else if(string_equals(tokens[i + 2], "string")) {
        char *str = tokens[i + 3];
        string_skip_first(str, 1);
        string_ignore_last(str, 1);
        OAk(OP_STRING, tokens[i], STRING(tokens[i + 3]));
        i += 3;
      } else if(string_equals(tokens[i + 3], "+")) {
        OABC(OP_ADD, tokens[i], tokens[i + 2], tokens[i + 4]);
        i += 4;
      } else if(string_equals(tokens[i + 3], "-")) {
        OABC(OP_SUB, tokens[i], tokens[i + 2], tokens[i + 4]);
        i += 4;
      } else if(string_equals(tokens[i + 3], "*")) {
        OABC(OP_MUL, tokens[i], tokens[i + 2], tokens[i + 4]);
        i += 4;
      } else if(string_equals(tokens[i + 3], "/")) {
        OABC(OP_DIV, tokens[i], tokens[i + 2], tokens[i + 4]);
        i += 4;
      } else {
        printf("unknown token: %s\n", tokens[i]);
      }
    }
  }

  O(OP_HALT);
  return bc;
}

static Instruction *emit_example_bytecode(VM *vm) {
  Instruction *bc = NULL;

  /* x = nil */
  OAk(OP_NIL, "x", NIL());
  OAk(OP_FALSE, "y", FALSE());
  OAk(OP_TRUE, "y2", TRUE());
  /* y3 = number 1 */
  OAk(OP_NUMBER, "y3", NUMBER(1));
  OAk(OP_NUMBER, "z", NUMBER(10));
  OAk(OP_NUMBER, "a", NUMBER(3.14));
  /* msg = string "hello" */
  OAk(OP_STRING, "msg", STRING("Hello"));
  /* result_add = z + a */
  OABC(OP_ADD, "result_add", "z", "a");
  OABC(OP_SUB, "result_sub", "result_add", "y3");
  OABC(OP_MUL, "result_mul", "result_sub", "z");
  OABC(OP_DIV, "result_div", "result_mul", "a");
  /* print x */
  OA(OP_PRINT, "x");
  OA(OP_PRINT, "y");
  OA(OP_PRINT, "y2");
  OA(OP_PRINT, "y3");
  OA(OP_PRINT, "z");
  OA(OP_PRINT, "a");
  OA(OP_PRINT, "msg");
  OA(OP_PRINT, "result_add");
  OA(OP_PRINT, "result_sub");
  OA(OP_PRINT, "result_mul");
  OA(OP_PRINT, "result_div");
  /* exit */
  O(OP_HALT);

  return bc;
}

#endif
