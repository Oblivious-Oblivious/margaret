#include "on_demand_compilation_pipeline.h"

#include "../emitter/Emitter.h"
#include "../evaluator/Evaluator.h"
#include "../lexer/Lexer.h"
#include "../loader/file_loader.h"
#include "../optimizer/Optimizer.h"

char *LOAD(char *filename) {
  return file_loader_load(file_loader_new(), filename);
}

TokenTable *READ(char *chars) {
  return lexer_make_tokens(lexer_new("repl", chars));
}

char **FORMALIZE(TokenTable *tokens) {
  return parser_analyze_syntax(parser_new(tokens));
}

VM *EMIT(VM *vm, char **formal_bytecode) {
  return emitter_emit(vm, formal_bytecode);
}

VM *OPTIMIZE(VM *vm) { return optimizer_optimize(vm); }

MargValue EVAL(VM *vm) { return evaluator_evaluate(vm); }
