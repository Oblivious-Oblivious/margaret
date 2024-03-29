#include "on_demand_compilation_pipeline.h"

string *LOAD(char *filename) {
    return file_loader_load(file_loader_new(), filename);
}

TokenTable *READ(string *chars) {
    return lexer_make_tokens(lexer_new("repl", chars));
}

vector *FORMALIZE(TokenTable *tokens) {
    return parser_analyze_syntax(parser_new(tokens));
}

VM *EMIT(VM *vm, vector *formal_bytecode) {
    return emitter_emit(vm, formal_bytecode);
}

VM *OPTIMIZE(VM *vm) {
    return optimizer_optimize(vm);
}

MargValue EVAL(VM *vm) {
    return evaluator_evaluate(vm);
}
