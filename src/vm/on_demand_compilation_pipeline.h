#ifndef __ON_DEMAND_COMPILATION_PIPELINE_H_
#define __ON_DEMAND_COMPILATION_PIPELINE_H_

#include "../opcode/MargValue.h"
#include "../parser/Parser.h"
#include "../vm/vm.h"

char *SCAN(char *prompt);
char *LOAD(char *filename);
Token **READ(char *chars, char *filename);
char **FORMALIZE(Token **tokens);
char **PRINT_FORMAL(char **formal_bytecode);
VM *EMIT(VM *vm, char **formal_bytecode);
VM *OPTIMIZE(VM *vm);
MargValue EVAL(VM *vm);
void PRINT(MargValue evaluated);

#endif
