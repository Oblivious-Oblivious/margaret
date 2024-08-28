#ifndef __LEXER_H_
#define __LEXER_H_

#include "../tokens/Token.h"
#include "../vm/vm.h"

/**
 * @brief Tokenizes the input and stores into a token table
 * @param vm -> The VM object
 * @return VM* -> The VM object
 */
VM *lexer_make_tokens(VM *vm);

#endif
