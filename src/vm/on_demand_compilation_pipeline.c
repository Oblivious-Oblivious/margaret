#include "on_demand_compilation_pipeline.h"

#include "../../libs/EmeraldsString/export/EmeraldsString.h" /* IWYU pragma: keep */
#include "../emitter/Emitter.h"
#include "../evaluator/Evaluator.h"
#include "../lexer/Lexer.h"
#include "../loader/file_loader.h"
#include "../optimizer/Optimizer.h"

char *LOAD(char *filename) {
  return file_loader_load(file_loader_new(), filename);
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

char **FORMALIZE(Token **tokens) {
  return parser_analyze_syntax(parser_new(tokens));
}

VM *EMIT(VM *vm, char **formal_bytecode) {
  return emitter_emit(vm, formal_bytecode);
}

VM *OPTIMIZE(VM *vm) { return optimizer_optimize(vm); }

MargValue EVAL(VM *vm) { return evaluator_evaluate(vm); }
