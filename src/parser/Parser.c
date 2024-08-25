#include "Parser.h"

#include "../../libs/EmeraldsVector/export/EmeraldsVector.h"
#include "../opcode/fmcodes.h"

#define token_get_value_safe(index)                                   \
  ((index) < vector_size((vm)->tokens) ? (vm)->tokens[(index)]->value \
                                       : vm->eof_token->value)

#define token_get_type_safe(index)                                   \
  ((index) < vector_size((vm)->tokens) ? (vm)->tokens[(index)]->type \
                                       : vm->eof_token->type)

/** Lookaheads */
#define la1value(token)        (string_equals(token_get_value_safe(0), token))
#define la2value(token)        (string_equals(token_get_value_safe(1), token))
#define la3value(token)        (string_equals(token_get_value_safe(2), token))
#define la1type(expected_type) (token_get_type_safe(0) == (expected_type))
#define la2type(expected_type) (token_get_type_safe(1) == (expected_type))
#define la3type(expected_type) (token_get_type_safe(2) == (expected_type))

#define ensure_value(value, msg) parser_ensure_value(vm, (value), (msg))
#define ensure_type(type, msg)   parser_ensure_type(vm, (type), (msg))
#define generate(value)          vector_add(vm->formal_bytecode, value)

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
    token->charno,
    message,
    token->value
  );
  return vm->eof_token->value;
}

/**
 * @brief Consumes and removes the next token from the table
 * @param vm -> The vm containing the token table
 * @return Token* -> The token consumed
 */
static Token *parser_consume(VM *vm) {
  if(vector_size(vm->tokens) == 0) {
    return vm->eof_token;
  } else {
    Token *token = vm->tokens[0];
    /* TODO - Handle memory leaking right here */
    vector_remove(vm->tokens, 0);
    return token;
  }
}

char *parser_ensure_value(VM *vm, const char *value, const char *error_msg) {
  Token *token = parser_consume(vm);
  if(string_equals(token->value, value)) {
    return token->value;
  } else {
    return parser_error(vm, token, error_msg);
  }
}

char *parser_ensure_type(VM *vm, Type type, const char *error_msg) {
  Token *token = parser_consume(vm);
  if(token->type == type) {
    return token->value;
  } else {
    return parser_error(vm, token, error_msg);
  }
}

static void parser_free_parsing_specific_values(VM *vm) {
  size_t i;

  string_free(vm->source);
  for(i = 0; i < vector_size(vm->tokens); i++) {
    string_free(vm->tokens[i]->value);
    free(vm->tokens[i]);
  }
  vector_free(vm->tokens);
}

VM *parser_analyze_syntax(VM *vm) {
  parser_first_unit(vm);
  parser_free_parsing_specific_values(vm);
  return vm;
}

void parser_first_unit(VM *vm) {
  unit_list();
  ensure_value("eof", "reached end of program.");
}

char *parser_unit_list(VM *vm) {
  size_t no_elements       = 0;
  char *number_of_elements = NULL;

  while(!la1value(")") && !la1value("]") && !la1value("}") && !la1value("eof")
  ) {
    unit();
    no_elements++;

    if(!la1value(")") && !la1value("]") && !la1value("}") && !la1value("eof")) {
      ensure_value(",", "grouped items should be separated by commas.");
    }
  }

  string_addf(&number_of_elements, "%zu", no_elements);
  return number_of_elements;
}

void parser_unit(VM *vm) { assignment_message(); }

void parser_assignment_message(VM *vm) {
  keyword_message();
  if(la1value("=")) {
    char *eq = ensure_value("=", "expected '=' on assignment message.");
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
      ensure_type(
        TOKEN_IDENTIFIER, "expected identifier on keyword selector chain."
      )
    );
    string_addf(
      &message_name,
      "%s",
      ensure_value(":", "expected ':' on keyword selector chain.")
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
    char *message_name = ensure_type(
      TOKEN_MESSAGE_SYMBOL, "expected message symbol on binary selector."
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
    generate(
      ensure_type(TOKEN_IDENTIFIER, "expected identifier on unary selector.")
    );
  }
}

void parser_lhs_message(VM *vm) {
  char *message_name = NULL;
  if(la1type(TOKEN_MESSAGE_SYMBOL) && !la1value("=")) {
    message_name = ensure_type(
      TOKEN_MESSAGE_SYMBOL, "expected message symbol on lhs selector."
    );
  }

  literal();

  if(message_name != NULL) {
    generate(FM_LHS);
    generate(message_name);
  }
}

void parser_literal(VM *vm) {
  if(la1value("(")) {
    ensure_value("(", "missing opening parenthesis on group.");
    while(la1value(",")) {
      ensure_value(",", "");
    }
    if(la1value(")")) {
      generate(FM_NIL);
    } else {
      unit_list();
    }
    ensure_value(")", "missing closing parenthesis on group.");
  } else if(la1value("[")) {
    char *number_of_elements = NULL;
    ensure_value("[", "missing opening bracket on tensor.");
    number_of_elements = unit_list();
    ensure_value("]", "missing closing bracket on tensor.");
    generate(FM_TENSOR);
    generate(number_of_elements);
  } else if(la1value("{")) {
    ensure_value("{", "missing opening curly on proc.");
    generate(FM_PROC_START);

    if(la1value("}")) {
      generate(FM_NIL);
    } else if(la1value("|") && la2value("}")) {
      ensure_value("|", "missing '|' on proc.");
      generate(FM_NIL);
    } else {
      param_list();
      unit_list();
    }

    ensure_value("}", "missing closing curly on proc.");
    generate(FM_PROC_END);
  } else if(la1value("%") && la2value("(")) {
    char *number_of_elements = NULL;
    ensure_value("%", "missing `%` on bitstring.");
    ensure_value("(", "missing opening parenthesis on bitstring.");
    number_of_elements = bit_list();
    ensure_value(")", "missing closing parenthesis on bitstring.");
    generate(FM_BITSTRING);
    generate(number_of_elements);
  } else if(la1value("%") && la2value("[")) {
    char *number_of_elements = NULL;
    ensure_value("%", "missing `%` on tuple.");
    ensure_value("[", "missing opening bracket on tuple.");
    number_of_elements = unit_list();
    ensure_value("]", "missing closing bracket on tuple.");
    generate(FM_TUPLE);
    generate(number_of_elements);
  } else if(la1value("%") && la2value("{")) {
    char *number_of_elements = NULL;
    ensure_value("%", "missing `%` on hash.");
    ensure_value("{", "missing opening curly on hash.");
    number_of_elements = association_list();
    ensure_value("}", "missing closing curly on hash.");
    generate(FM_HASH);
    generate(number_of_elements);
  } else if(la1value("#")) {
    size_t prev_size;
    ensure_value("#", "missing `#` on method definition.");
    generate(FM_METHOD_START);

    generate(FM_METHOD_RECEIVER);
    prev_size = vector_size(vm->formal_bytecode);

    if(!((la1type(TOKEN_MESSAGE_SYMBOL) && la2value("=>")) ||
         (la1type(TOKEN_IDENTIFIER) && la2value("=>")) ||
         (la1type(TOKEN_MESSAGE_SYMBOL) && la3value("=>")) ||
         (la1type(TOKEN_IDENTIFIER) && la2value(":")))) {
      literal();
    }
    if(vector_size(vm->formal_bytecode) == prev_size) {
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
    generate(FM_PROC_PARAMETER);
    generate(
      ensure_type(TOKEN_IDENTIFIER, "expected identifier on proc parameters.")
    );
    ensure_value(",", "missing ',' on proc parameter list.");
    param_list();
  } else if(la2value("|")) {
    generate(FM_PROC_PARAMETER);
    generate(
      ensure_type(TOKEN_IDENTIFIER, "expected identifier on proc parameters.")
    );
    ensure_value("|", "missing '|' on proc parameter list.");
  }
}

char *parser_bit_list(VM *vm) {
  size_t no_elements       = 0;
  char *number_of_elements = NULL;

  while(!la1value(")") && !la1value("eof")) {
    bit();
    no_elements++;

    if(!la1value(")")) {
      ensure_value(",", "missing ',' on bit list.");
    }
  }

  string_addf(&number_of_elements, "%zu", no_elements * 2);
  return number_of_elements;
}

void parser_bit(VM *vm) {
  scalar();

  if(la1value(":") && la2value(":")) {
    ensure_value(":", "expected '::' on bit.");
    ensure_value(":", "expected '::' on bit.");
    generate(FM_INTEGER);
    generate(ensure_type(TOKEN_INTEGER, "expected integer on bit."));
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
    ensure_value(":", "missing ':' on association list.");
    unit();
    no_elements++;

    if(!la1value("}")) {
      ensure_value(",", "missing ',' on association list.");
    }
  }

  string_addf(&number_of_elements, "%zu", no_elements * 2);
  return number_of_elements;
}

void parser_key(VM *vm) {
  if(la1type(TOKEN_IDENTIFIER)) {
    generate(FM_STRING);
    generate(ensure_type(TOKEN_IDENTIFIER, "expected identifier on key."));
  } else if(la1type(TOKEN_STRING)) {
    generate(FM_STRING);
    generate(ensure_type(TOKEN_STRING, "expected string on key."));
  }
}

void parser_method_definition(VM *vm) {
  char *name = NULL;

  if(la1type(TOKEN_IDENTIFIER) && la2value(":")) {
    name = keyword_list();
    ensure_value("=>", "missing '=>' on keyword keyword method definition.");
  } else if(la1type(TOKEN_IDENTIFIER) && la2value("=>")) {
    name = ensure_type(
      TOKEN_IDENTIFIER, "expected identifier on unary method definition."
    );
    ensure_value("=>", "missing '=>' on unary method definition.");
  } else if(la1type(TOKEN_MESSAGE_SYMBOL) && la2value("=>")) {
    name = ensure_type(
      TOKEN_MESSAGE_SYMBOL, "expected message symbol on lhs method definition."
    );
    ensure_value("=>", "missing '=>' on lhs method definition.");
  } else if(la1type(TOKEN_MESSAGE_SYMBOL)) {
    name = ensure_type(
      TOKEN_MESSAGE_SYMBOL,
      "expected message symbol on binary method definition."
    );
    generate(FM_METHOD_PARAMETER);
    literal();
    ensure_value("=>", "missing '=>' on binary method definition.");
  }

  generate(FM_METHOD_NAME);
  generate(name);
  unit();
}

char *parser_keyword_list(VM *vm) {
  char *keyword_method_name = NULL;

  while(la1type(TOKEN_IDENTIFIER) && la2value(":")) {
    string_addf(
      &keyword_method_name,
      "%s%s",
      ensure_type(TOKEN_IDENTIFIER, "expected identifier on keyword list."),
      ensure_value(":", "missing ':' on keyword list.")
    );
    generate(FM_METHOD_PARAMETER);
    literal();
  }

  return keyword_method_name;
}

void parser_scalar(VM *vm) {
  if(la1value(":") && la2value(":")) {
    ensure_value(":", "expected ':' on label.");
    ensure_value(":", "expected ':' on label.");
    generate(FM_LABEL);
    generate(ensure_type(TOKEN_IDENTIFIER, "expected identifier on label."));
  } else if(la1type(TOKEN_INTEGER)) {
    generate(FM_INTEGER);
    generate(ensure_type(TOKEN_INTEGER, "expected integer literal."));
  } else if(la1type(TOKEN_FLOAT)) {
    generate(FM_FLOAT);
    generate(ensure_type(TOKEN_FLOAT, "expected float literal."));
  } else if(la1type(TOKEN_STRING)) {
    generate(FM_STRING);
    generate(ensure_type(TOKEN_STRING, "expected string literal."));
  } else {
    variable();
  }
}

void parser_variable(VM *vm) {
  if(la1value("$nil")) {
    ensure_value("$nil", "expected '$nil' on nil literal.");
    generate(FM_NIL);
  } else if(la1value("$false")) {
    ensure_value("$false", "expected '$false' on false literal.");
    generate(FM_FALSE);
  } else if(la1value("$true")) {
    ensure_value("$true", "expected '$true' on true literal.");
    generate(FM_TRUE);
  } else if(la1value("@self")) {
    ensure_value("@self", "expected '@self' on instance variable declaration.");
    generate(FM_SELF);
  } else if(la1value("@super")) {
    ensure_value(
      "@super", "expected '@super' on instance variable declaration."
    );
    generate(FM_SUPER);
  } else if(la1type(TOKEN_GLOBAL)) {
    generate(FM_GLOBAL);
    generate(ensure_type(
      TOKEN_GLOBAL, "expected identifier on global variable declaration."
    ));
  } else if(la1type(TOKEN_INSTANCE)) {
    generate(FM_INSTANCE);
    generate(ensure_type(
      TOKEN_INSTANCE, "expected identifier on instance variable declaration."
    ));
  } else if(la1type(TOKEN_IDENTIFIER)) {
    generate(FM_LOCAL);
    generate(ensure_type(
      TOKEN_IDENTIFIER, "expected identifier on variable declaration."
    ));
  }
}
