#include "Parser.h"

Parser *parser_new(TokenTable *tokens) {
    Parser *self = (Parser*)malloc(sizeof(Parser));

    self->table = tokens;

    return self;
}
