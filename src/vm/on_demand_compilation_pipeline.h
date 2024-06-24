#ifndef __ON_DEMAND_COMPILATION_PIPELINE_H_
#define __ON_DEMAND_COMPILATION_PIPELINE_H_

#include "../parser/Parser.h"
#include "../vm/vm.h"

char *LOAD(char *filename);
TokenTable *READ(char *chars, char *filename);
char **FORMALIZE(TokenTable *tokens);
VM *EMIT(VM *vm, char **formal_bytecode);
VM *OPTIMIZE(VM *vm);
MargValue EVAL(VM *vm);

#endif
