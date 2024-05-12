#ifndef __ON_DEMAND_COMPILATION_PIPELINE_H_
#define __ON_DEMAND_COMPILATION_PIPELINE_H_

#include "../parser/Parser.h"
#include "../vm/vm.h"

EmeraldsString *LOAD(char *filename);
TokenTable *READ(EmeraldsString *chars);
EmeraldsVector *FORMALIZE(TokenTable *tokens);
VM *EMIT(VM *vm, EmeraldsVector *formal_bytecode);
VM *OPTIMIZE(VM *vm);
MargValue EVAL(VM *vm);

#endif
