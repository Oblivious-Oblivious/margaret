#include "Parser.h"

#include "../../libs/EmeraldsVector/export/EmeraldsVector.h"
#include "../opcode/fmcodes.h"

#define token_get_value(index)                                        \
  ((index) < vector_size((vm)->tokens) ? (vm)->tokens[(index)]->value \
                                       : vm->eof_token->value)

#define token_get_type(index)                                        \
  ((index) < vector_size((vm)->tokens) ? (vm)->tokens[(index)]->type \
                                       : vm->eof_token->type)

/* NOTE - Lookaheads */
#define la1value(token)        (string_equals(token_get_value(vm->tid), token))
#define la2value(token)        (string_equals(token_get_value(vm->tid + 1), token))
#define la3value(token)        (string_equals(token_get_value(vm->tid + 2), token))
#define la1type(expected_type) (token_get_type(vm->tid) == (expected_type))
#define la2type(expected_type) (token_get_type(vm->tid + 1) == (expected_type))
#define la3type(expected_type) (token_get_type(vm->tid + 2) == (expected_type))

#define ensure(type, msg) parser_ensure(vm, (type), (msg))
#define generate(value)   vector_add(vm->formal_bytecode, value)

#define first_unit()             parser_first_unit(vm)
#define unit_list()              parser_unit_list(vm)
#define unit()                   parser_unit(vm)
#define assignment_message()     parser_assignment_message(vm)
#define keyword_message()        parser_keyword_message(vm)
#define keyword_selector_chain() parser_keyword_selector_chain(vm)
#define binary_message()         parser_binary_message(vm)
#define binary_selector_chain()  parser_binary_selector_chain(vm)
#define unary_message()          parser_unary_message(vm)
#define unary_selector_chain()   parser_unary_selector_chain(vm)
#define lhs_message()            parser_lhs_message(vm)
#define lhs_selector()           parser_lhs_selector(vm)
#define literal()                parser_literal(vm)
#define param_list()             parser_param_list(vm)
#define bit_list()               parser_bit_list(vm)
#define bit()                    parser_bit(vm)
#define association_list()       parser_association_list(vm)
#define key()                    parser_key(vm)
#define method_definition()      parser_method_definition(vm)
#define method_body()            parser_method_body(vm)
#define keyword_list()           parser_keyword_list(vm)
#define scalar()                 parser_scalar(vm)
#define variable()               parser_variable(vm)

/**
 * @brief Displays a parser-level error message (grabs latest line and column)
 * @param vm -> The vm containing the token table
 * @param token -> The token where the error occured at
 * @param message -> The message to display
 * @return string* -> NULL pointer
 */
static char *parser_error(VM *vm, Token *token, const char *message) {
  printf(
    "%s:%zu:%zu \033[1;31merror:\033[0m %s  Token: \033[1;31m`%s`\033[0m\n",
    vm->filename,
    token->lineno,
    token->charno - (string_size(token->value) - 1),
    message,
    token->value
  );
  vm->has_error = true;

  return vm->eof_token->value;
}

/**
 * @brief Consumes and removes the next token from the table
 * @param vm -> The vm containing the token table
 * @return Token* -> The token consumed
 */
static Token *parser_consume(VM *vm) {
  if(vector_size(vm->tokens) == vm->tid) {
    return vm->eof_token;
  } else {
    return vm->tokens[vm->tid++];
  }
}

char *parser_ensure(VM *vm, Type type, const char *error_msg) {
  Token *token = parser_consume(vm);
  if(token->type == type) {
    return token->value;
  } else {
    return parser_error(vm, token, error_msg);
  }
}

VM *parser_analyze_syntax(VM *vm) {
  parser_first_unit(vm);
  vm_free_eof_token();
  vm_free_tokens();
  return vm;
}

void parser_first_unit(VM *vm) {
  unit_list();
  ensure(TOKEN_EOF, "reached end of program.");
}

char *parser_unit_list(VM *vm) {
  size_t no_elements       = 0;
  char *number_of_elements = NULL;

  while(!la1value(")") && !la1value("]") && !la1value("}") && !la1value("eof")
  ) {
    unit();
    no_elements++;

    if(!la1value(")") && !la1value("]") && !la1value("}") && !la1value("eof")) {
      ensure(TOKEN_COMMA, "grouped items should be separated by commas.");
    }
  }

  string_addf(&number_of_elements, "%zu", no_elements);
  return number_of_elements;
}

void parser_unit(VM *vm) { assignment_message(); }

void parser_assignment_message(VM *vm) {
  keyword_message();
  if(la1value("=")) {
    char *eq =
      ensure(TOKEN_MESSAGE_SYMBOL, "missing '=' on assignment message.");
    assignment_message();
    generate(FM_BINARY);
    generate(eq);
  }
}

void parser_keyword_message(VM *vm) {
  if(la1type(TOKEN_IDENTIFIER) && la2value(":")) {
    generate(FM_GLOBAL);
    generate(string_new("$Margaret"));
    keyword_selector_chain();
  } else {
    binary_message();

    if(la1type(TOKEN_IDENTIFIER) && la2value(":")) {
      keyword_selector_chain();
    }
  }
}

void parser_keyword_selector_chain(VM *vm) {
  char *message_name       = NULL;
  size_t no_keywords       = 0;
  char *number_of_keywords = NULL;

  while(la1type(TOKEN_IDENTIFIER) && la2value(":")) {
    no_keywords++;
    string_addf(
      &message_name,
      "%s",
      ensure(TOKEN_IDENTIFIER, "missing identifier on keyword selector chain.")
    );
    string_addf(
      &message_name,
      "%s",
      ensure(TOKEN_COLON, "missing ':' on keyword selector chain.")
    );
    binary_message();
  }

  generate(FM_KEYWORD);
  generate(message_name);
  string_addf(&number_of_keywords, "%zu", no_keywords);
  generate(number_of_keywords);
}

void parser_binary_message(VM *vm) {
  unary_message();
  if(la1type(TOKEN_MESSAGE_SYMBOL)) {
    binary_selector_chain();
  }
}

void parser_binary_selector_chain(VM *vm) {
  while(la1type(TOKEN_MESSAGE_SYMBOL) && !la1value("=")) {
    char *message_name = ensure(
      TOKEN_MESSAGE_SYMBOL, "missing message symbol on binary selector."
    );
    unary_message();
    generate(FM_BINARY);
    generate(message_name);
  }
}

void parser_unary_message(VM *vm) {
  lhs_message();
  if(la1type(TOKEN_IDENTIFIER) && !la2value(":")) {
    unary_selector_chain();
  }
}

void parser_unary_selector_chain(VM *vm) {
  while(la1type(TOKEN_IDENTIFIER) && !la2value(":")) {
    generate(FM_UNARY);
    generate(ensure(TOKEN_IDENTIFIER, "missing identifier on unary selector."));
  }
}

void parser_lhs_message(VM *vm) {
  size_t i;
  char **messages_list = NULL;
  while(la1type(TOKEN_MESSAGE_SYMBOL) && !la1value("=")) {
    vector_add(
      messages_list,
      ensure(TOKEN_MESSAGE_SYMBOL, "missing message symbol on lhs selector.")
    );
  }

  literal();

  if(vector_size(messages_list) > 0) {
    for(i = vector_size(messages_list) - 1; i > 0; i--) {
      generate(FM_LHS);
      generate(messages_list[i]);
    }
    generate(FM_LHS);
    generate(messages_list[0]);
    vector_free(messages_list);
  }
}

void parser_literal(VM *vm) {
  if(la1value("(")) {
    ensure(TOKEN_LPAREN, "missing opening parenthesis on group.");
    while(la1value(",")) {
      ensure(TOKEN_COMMA, "");
    }
    if(la1value(")")) {
      generate(FM_NIL);
    } else {
      unit_list();
    }
    ensure(TOKEN_RPAREN, "missing closing parenthesis on group.");
  } else if(la1value("[")) {
    char *number_of_elements = NULL;
    ensure(TOKEN_LBRACKET, "missing opening bracket on tensor.");
    number_of_elements = unit_list();
    ensure(TOKEN_RBRACKET, "missing closing bracket on tensor.");
    generate(FM_TENSOR);
    generate(number_of_elements);
  } else if(la1value("{")) {
    ensure(TOKEN_LCURLY, "missing opening curly on headless method.");
    generate(FM_METHOD_START);

    if(la1value("}")) {
      generate(FM_NIL);
    } else if(la1value("|") && la2value("}")) {
      ensure(TOKEN_MESSAGE_SYMBOL, "missing '|' on headless method.");
      generate(FM_NIL);
    } else {
      param_list();
      unit_list();
    }

    ensure(TOKEN_RCURLY, "missing closing curly on headless method.");
    generate(FM_METHOD_END);
  } else if(la1value("%") && la2value("(")) {
    char *number_of_elements = NULL;
    ensure(TOKEN_PERCENT, "missing `%` on bitstring.");
    ensure(TOKEN_LPAREN, "missing opening parenthesis on bitstring.");
    number_of_elements = bit_list();
    ensure(TOKEN_RPAREN, "missing closing parenthesis on bitstring.");
    generate(FM_BITSTRING);
    generate(number_of_elements);
  } else if(la1value("%") && la2value("[")) {
    char *number_of_elements = NULL;
    ensure(TOKEN_PERCENT, "missing `%` on tuple.");
    ensure(TOKEN_LBRACKET, "missing opening bracket on tuple.");
    number_of_elements = unit_list();
    ensure(TOKEN_RBRACKET, "missing closing bracket on tuple.");
    generate(FM_TUPLE);
    generate(number_of_elements);
  } else if(la1value("%") && la2value("{")) {
    char *number_of_elements = NULL;
    ensure(TOKEN_PERCENT, "missing `%` on hash.");
    ensure(TOKEN_LCURLY, "missing opening curly on hash.");
    number_of_elements = association_list();
    ensure(TOKEN_RCURLY, "missing closing curly on hash.");
    generate(FM_HASH);
    generate(number_of_elements);
  } else if(la1value("#")) {
    size_t prev_size;
    ensure(TOKEN_HASH, "missing `#` on method definition.");
    generate(FM_METHOD_START);

    generate(FM_METHOD_RECEIVER);
    prev_size = vm->tid;

    if(!((la1type(TOKEN_MESSAGE_SYMBOL) && la2value("=>")) ||
         (la1type(TOKEN_IDENTIFIER) && la2value("=>")) ||
         (la1type(TOKEN_MESSAGE_SYMBOL) && la3value("=>")) ||
         (la1type(TOKEN_IDENTIFIER) && la2value(":")))) {
      literal();
    }
    if(vm->tid == prev_size) {
      generate(FM_METHOD_ANY_OBJECT);
    }

    method_definition();
    generate(FM_METHOD_END);
  } else {
    scalar();
  }
}

void parser_param_list(VM *vm) {
  if(la2value(",")) {
    generate(FM_METHOD_PARAMETER);
    generate(ensure(
      TOKEN_IDENTIFIER, "missing identifier on headless method parameter."
    ));
    ensure(TOKEN_COMMA, "missing ',' on headless method parameter list.");
    param_list();
  } else if(!la1value("#") && la2value("|")) {
    generate(FM_METHOD_PARAMETER);
    generate(ensure(
      TOKEN_IDENTIFIER, "missing identifier on headless method parameter."
    ));
    ensure(
      TOKEN_MESSAGE_SYMBOL, "missing '|' on headless method parameter list."
    );
  }
}

char *parser_bit_list(VM *vm) {
  size_t no_elements       = 0;
  char *number_of_elements = NULL;

  while(!la1value(")") && !la1value("eof")) {
    bit();
    no_elements++;

    if(!la1value(")")) {
      ensure(TOKEN_COMMA, "missing ',' on bit list.");
    }
  }

  string_addf(&number_of_elements, "%zu", no_elements * 2);
  return number_of_elements;
}

void parser_bit(VM *vm) {
  scalar();

  if(la1value(":") && la2value(":")) {
    ensure(TOKEN_COLON, "missing '::' on bit.");
    ensure(TOKEN_COLON, "missing '::' on bit.");
    generate(FM_INTEGER);
    generate(ensure(TOKEN_INTEGER, "missing integer on bit."));
  } else {
    generate(FM_INTEGER);
    generate(string_new("8"));
  }
}

char *parser_association_list(VM *vm) {
  size_t no_elements       = 0;
  char *number_of_elements = NULL;

  while(!la1value("}") && !la1value("eof")) {
    key();
    ensure(TOKEN_COLON, "missing ':' on association list.");
    unit();
    no_elements++;

    if(!la1value("}")) {
      ensure(TOKEN_COMMA, "missing ',' on association list.");
    }
  }

  string_addf(&number_of_elements, "%zu", no_elements * 2);
  return number_of_elements;
}

void parser_key(VM *vm) {
  if(la1type(TOKEN_IDENTIFIER)) {
    generate(FM_STRING);
    generate(ensure(TOKEN_IDENTIFIER, "missing identifier on key."));
  } else if(la1type(TOKEN_STRING)) {
    generate(FM_STRING);
    generate(ensure(TOKEN_STRING, "missing string on key."));
  }
}

void parser_method_definition(VM *vm) {
  char *name = NULL;

  if(la1type(TOKEN_IDENTIFIER) && la2value(":")) {
    name = keyword_list();
    ensure(TOKEN_ROCKET, "missing '=>' on keyword keyword method definition.");
  } else if(la1type(TOKEN_IDENTIFIER) && la2value("=>")) {
    name = ensure(
      TOKEN_IDENTIFIER, "missing identifier on unary method definition."
    );
    ensure(TOKEN_ROCKET, "missing '=>' on unary method definition.");
  } else if(la1type(TOKEN_MESSAGE_SYMBOL) && la2value("=>")) {
    name = ensure(
      TOKEN_MESSAGE_SYMBOL, "missing message symbol on lhs method definition."
    );
    ensure(TOKEN_ROCKET, "missing '=>' on lhs method definition.");
  } else if(la1type(TOKEN_MESSAGE_SYMBOL)) {
    name = ensure(
      TOKEN_MESSAGE_SYMBOL,
      "missing message symbol on binary method definition."
    );
    generate(FM_METHOD_PARAMETER);
    literal();
    ensure(TOKEN_ROCKET, "missing '=>' on binary method definition.");
  }

  generate(FM_METHOD_NAME);
  generate(name);
  method_body();
}

void parser_method_body(VM *vm) {
  if(la1value("{")) {
    ensure(TOKEN_LCURLY, "missing opening curly on method body.");
    unit_list();
    ensure(TOKEN_RCURLY, "missing closing curly on method body.");
  } else {
    unit();
  }
}

char *parser_keyword_list(VM *vm) {
  char *keyword_method_name = NULL;

  while(la1type(TOKEN_IDENTIFIER) && la2value(":")) {
    string_addf(
      &keyword_method_name,
      "%s%s",
      ensure(TOKEN_IDENTIFIER, "missing identifier on keyword list."),
      ensure(TOKEN_COLON, "missing ':' on keyword list.")
    );
    generate(FM_METHOD_PARAMETER);
    literal();
  }

  return keyword_method_name;
}

void parser_scalar(VM *vm) {
  if(la1value(":") && la2value(":")) {
    ensure(TOKEN_COLON, "expected ':' on label.");
    ensure(TOKEN_COLON, "expected ':' on label.");
    generate(FM_LABEL);
    generate(ensure(TOKEN_IDENTIFIER, "expected identifier on label."));
  } else if(la1type(TOKEN_INTEGER)) {
    generate(FM_INTEGER);
    generate(ensure(TOKEN_INTEGER, "expected integer literal."));
  } else if(la1type(TOKEN_FLOAT)) {
    generate(FM_FLOAT);
    generate(ensure(TOKEN_FLOAT, "expected float literal."));
  } else if(la1type(TOKEN_STRING)) {
    generate(FM_STRING);
    generate(ensure(TOKEN_STRING, "expected string literal."));
  } else {
    variable();
  }
}

void parser_variable(VM *vm) {
  if(la1value("$nil")) {
    ensure(TOKEN_GLOBAL, "expected '$nil' on nil literal.");
    generate(FM_NIL);
  } else if(la1value("$false")) {
    ensure(TOKEN_GLOBAL, "expected '$false' on false literal.");
    generate(FM_FALSE);
  } else if(la1value("$true")) {
    ensure(TOKEN_GLOBAL, "expected '$true' on true literal.");
    generate(FM_TRUE);
  } else if(la1value("@self")) {
    ensure(
      TOKEN_INSTANCE, "expected '@self' on instance variable declaration."
    );
    generate(FM_SELF);
  } else if(la1value("@super")) {
    ensure(
      TOKEN_INSTANCE, "expected '@super' on instance variable declaration."
    );
    generate(FM_SUPER);
  } else if(la1type(TOKEN_GLOBAL)) {
    generate(FM_GLOBAL);
    generate(ensure(
      TOKEN_GLOBAL, "expected identifier on global variable declaration."
    ));
  } else if(la1type(TOKEN_INSTANCE)) {
    generate(FM_INSTANCE);
    generate(ensure(
      TOKEN_INSTANCE, "expected identifier on instance variable declaration."
    ));
  } else if(la1type(TOKEN_IDENTIFIER)) {
    generate(FM_LOCAL);
    generate(
      ensure(TOKEN_IDENTIFIER, "expected identifier on variable declaration.")
    );
  }
}
