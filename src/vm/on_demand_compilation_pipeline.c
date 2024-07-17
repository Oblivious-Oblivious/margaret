#include "on_demand_compilation_pipeline.h"

#include "../../libs/EmeraldsReadHandler/export/EmeraldsReadHandler.h" /* IWYU pragma: keep */
#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "../emitter/Emitter.h"
#include "../evaluator/Evaluator.h"
#include "../lexer/Lexer.h"
#include "../optimizer/Optimizer.h"

char *LOAD(char *filename) {
  return read_handler_load(read_handler_new(), filename);
}

Token **READ(char *chars, char *filename) {
  char *str_filename = string_new(filename);
  char **vec         = string_split(str_filename, "/");

  if(vector_size(vec) > 1) {
    return lexer_make_tokens(lexer_new(vec[vector_size(vec) - 1], chars));
  } else {
    return lexer_make_tokens(lexer_new(filename, chars));
  }
}

char **FORMALIZE(Token **tokens) { return parser_analyze_syntax(tokens); }

VM *EMIT(VM *vm, char **formal_bytecode) {
  return emitter_emit(vm, formal_bytecode);
}

VM *OPTIMIZE(VM *vm) { return optimizer_optimize(vm); }

MargValue EVAL(VM *vm) { return evaluator_evaluate(vm); }
