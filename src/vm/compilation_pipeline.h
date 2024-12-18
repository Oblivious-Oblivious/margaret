#ifndef __COMPILATION_PIPELINE_H_
#define __COMPILATION_PIPELINE_H_

#include "../emitter/Emitter.h"
#include "../evaluator/Evaluator.h"
#include "../lexer/Lexer.h"
#include "../loader/Loader.h"
#include "../opcode/MargValue.h"
#include "../optimizer/Optimizer.h"
#include "../parser/Parser.h"
#include "../scanner/Scanner.h"
#include "../vm/vm.h"

#define SCAN(prompt)  scanner_scan((vm), (prompt))
#define LOAD(vm)      loader_load((vm))
#define READ(vm)      lexer_make_tokens((vm))
#define FORMALIZE(vm) parser_analyze_syntax((vm))
#define EMIT(vm)      emitter_emit((vm))
#define OPTIMIZE(vm)  optimizer_optimize((vm))
#define EVAL(vm)      evaluator_evaluate((vm))
#define PRINT(evaluated)                              \
  do {                                                \
    if(vm->error) {                                   \
      vm_reset();                                     \
    } else {                                          \
      MargValue res = (evaluated);                    \
      if(!IS_UNDEFINED(res) && !vm->do_not_display) { \
        printf("%s\n", marg_value_format(vm, res));   \
      }                                               \
      vector_free(vm->current->bytecode);             \
      vm->do_not_display = false;                     \
    }                                                 \
  } while(0)

#endif
