#ifndef __ON_DEMAND_COMPILATION_PIPELINE_H_
#define __ON_DEMAND_COMPILATION_PIPELINE_H_

#include "../base/string.h"
#include "../base/vector.h"
#include "../emitter/Emitter.h"
#include "../evaluator/Evaluator.h"
#include "../lexer/Lexer.h"
#include "../loader/file_loader.h"
#include "../optimizer/Optimizer.h"
#include "../parser/Parser.h"
#include "../vm/vm.h"

string *LOAD(char *filename);
TokenTable *READ(string *chars);
vector *FORMALIZE(TokenTable *tokens);
VM *EMIT(VM *vm, vector *formal_bytecode);
VM *OPTIMIZE(VM *vm);
MargValue EVAL(VM *vm);

#endif
