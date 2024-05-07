#ifndef __ON_DEMAND_COMPILATION_PIPELINE_H_
#define __ON_DEMAND_COMPILATION_PIPELINE_H_

#include "../parser/Parser.h"
#include "../vm/vm.h"

string *LOAD(char *filename);
TokenTable *READ(string *chars);
vector *FORMALIZE(TokenTable *tokens);
VM *EMIT(VM *vm, vector *formal_bytecode);
VM *OPTIMIZE(VM *vm);
MargValue EVAL(VM *vm);

#endif
