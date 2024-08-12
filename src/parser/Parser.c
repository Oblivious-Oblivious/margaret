#include "Parser.h"

#include "../../libs/EmeraldsVector/export/EmeraldsVector.h" /* IWYU pragma: keep */
#include "../opcode/fmcodes.h"
#include "../tokens/TokenTable.h"

#define la1value(token)        token_equals_values(table[0], string_new((token)))
#define la2value(token)        token_equals_values(table[1], string_new((token)))
#define la3value(token)        token_equals_values(table[2], string_new((token)))
#define la1type(expected_type) table[0]->type == (expected_type)
#define la2type(expected_type) table[1]->type == (expected_type)
#define la3type(expected_type) table[2]->type == (expected_type)

#define ensure_value(value, msg) token_table_ensure_value(table, (value), (msg))
#define ensure_type(type, msg)   token_table_ensure_type(table, (type), (msg))
#define generate(value)          vector_add(*fmcodes, value)

#define first_unit()             parser_first_unit(table, fmcodes)
#define unit_list()              parser_unit_list(table, fmcodes)
#define unit()                   parser_unit(table, fmcodes)
#define assignment_message()     parser_assignment_message(table, fmcodes)
#define keyword_message()        parser_keyword_message(table, fmcodes)
#define keyword_selector_chain() parser_keyword_selector_chain(table, fmcodes)
#define binary_message()         parser_binary_message(table, fmcodes)
#define binary_selector_chain()  parser_binary_selector_chain(table, fmcodes)
#define unary_message()          parser_unary_message(table, fmcodes)
#define unary_selector_chain()   parser_unary_selector_chain(table, fmcodes)
#define lhs_message()            parser_lhs_message(table, fmcodes)
#define lhs_selector()           parser_lhs_selector(table, fmcodes)
#define literal()                parser_literal(table, fmcodes)
#define param_list()             parser_param_list(table, fmcodes)
#define bit_list()               parser_bit_list(table, fmcodes)
#define bit()                    parser_bit(table, fmcodes)
#define association_list()       parser_association_list(table, fmcodes)
#define key()                    parser_key(table, fmcodes)
#define method_definition()      parser_method_definition(table, fmcodes)
#define keyword_list()           parser_keyword_list(table, fmcodes)
#define scalar()                 parser_scalar(table, fmcodes)
#define variable()               parser_variable(table, fmcodes)

VM *parser_analyze_syntax(VM *vm) {
  parser_first_unit(vm->tokens, &vm->formal_bytecode);
  return vm;
}

void parser_first_unit(Token **table, char ***fmcodes) {
  unit_list();
  ensure_value("eof", "reached end of program.");
}

char *parser_unit_list(Token **table, char ***fmcodes) {
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

  string_addf(number_of_elements, "%zu", no_elements);
  return number_of_elements;
}

void parser_unit(Token **table, char ***fmcodes) { assignment_message(); }

void parser_assignment_message(Token **table, char ***fmcodes) {
  keyword_message();
  if(la1value("=")) {
    char *eq = ensure_value("=", "expected '=' on assignment message.");
    assignment_message();
    generate(FM_BINARY);
    generate(eq);
  }
}

void parser_keyword_message(Token **table, char ***fmcodes) {
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

void parser_keyword_selector_chain(Token **table, char ***fmcodes) {
  char *message_name = NULL;
  size_t no_keywords = 0;

  while(la1type(TOKEN_IDENTIFIER) && la2value(":")) {
    no_keywords++;
    string_addf(
      message_name,
      "%s",
      ensure_type(
        TOKEN_IDENTIFIER, "expected identifier on keyword selector chain."
      )
    );
    string_addf(
      message_name,
      "%s",
      ensure_value(":", "expected ':' on keyword selector chain.")
    );
    binary_message();
  }

  generate(FM_KEYWORD);
  generate(message_name);
  char *number_of_keywords = NULL;
  string_addf(number_of_keywords, "%zu", no_keywords);
  generate(number_of_keywords);
}

void parser_binary_message(Token **table, char ***fmcodes) {
  unary_message();
  if(la1type(TOKEN_MESSAGE_SYMBOL)) {
    binary_selector_chain();
  }
}

void parser_binary_selector_chain(Token **table, char ***fmcodes) {
  while(la1type(TOKEN_MESSAGE_SYMBOL) && !la1value("=")) {
    char *message_name = ensure_type(
      TOKEN_MESSAGE_SYMBOL, "expected message symbol on binary selector."
    );
    unary_message();
    generate(FM_BINARY);
    generate(message_name);
  }
}

void parser_unary_message(Token **table, char ***fmcodes) {
  lhs_message();
  if(la1type(TOKEN_IDENTIFIER) && !la2value(":")) {
    unary_selector_chain();
  }
}

void parser_unary_selector_chain(Token **table, char ***fmcodes) {
  while(la1type(TOKEN_IDENTIFIER) && !la2value(":")) {
    generate(FM_UNARY);
    generate(
      ensure_type(TOKEN_IDENTIFIER, "expected identifier on unary selector.")
    );
  }
}

void parser_lhs_message(Token **table, char ***fmcodes) {
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

void parser_literal(Token **table, char ***fmcodes) {
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
    ensure_value("[", "missing opening bracket on tensor.");
    char *number_of_elements = unit_list();
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
    ensure_value("%", "missing `%` on bitstring.");
    ensure_value("(", "missing opening parenthesis on bitstring.");
    char *number_of_elements = bit_list();
    ensure_value(")", "missing closing parenthesis on bitstring.");
    generate(FM_BITSTRING);
    generate(number_of_elements);
  } else if(la1value("%") && la2value("[")) {
    ensure_value("%", "missing `%` on tuple.");
    ensure_value("[", "missing opening bracket on tuple.");
    char *number_of_elements = unit_list();
    ensure_value("]", "missing closing bracket on tuple.");
    generate(FM_TUPLE);
    generate(number_of_elements);
  } else if(la1value("%") && la2value("{")) {
    ensure_value("%", "missing `%` on hash.");
    ensure_value("{", "missing opening curly on hash.");
    char *number_of_elements = association_list();
    ensure_value("}", "missing closing curly on hash.");
    generate(FM_HASH);
    generate(number_of_elements);
  } else if(la1value("#")) {
    ensure_value("#", "missing `#` on method definition.");
    generate(FM_METHOD_START);

    generate(FM_METHOD_RECEIVER);
    size_t prev_size = vector_size(*fmcodes);

    if(!((la1type(TOKEN_MESSAGE_SYMBOL) && la2value("=>")) ||
         (la1type(TOKEN_IDENTIFIER) && la2value("=>")) ||
         (la1type(TOKEN_MESSAGE_SYMBOL) && la3value("=>")) ||
         (la1type(TOKEN_IDENTIFIER) && la2value(":")))) {
      literal();
    }
    if(vector_size(*fmcodes) == prev_size) {
      generate(FM_METHOD_ANY_OBJECT);
    }

    method_definition();
    generate(FM_METHOD_END);
  } else {
    scalar();
  }
}

void parser_param_list(Token **table, char ***fmcodes) {
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

char *parser_bit_list(Token **table, char ***fmcodes) {
  size_t no_elements       = 0;
  char *number_of_elements = NULL;

  while(!la1value(")") && !la1value("eof")) {
    bit();
    no_elements++;

    if(!la1value(")")) {
      ensure_value(",", "missing ',' on bit list.");
    }
  }

  string_addf(number_of_elements, "%zu", no_elements * 2);
  return number_of_elements;
}

void parser_bit(Token **table, char ***fmcodes) {
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

char *parser_association_list(Token **table, char ***fmcodes) {
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

  string_addf(number_of_elements, "%zu", no_elements * 2);
  return number_of_elements;
}

void parser_key(Token **table, char ***fmcodes) {
  if(la1type(TOKEN_IDENTIFIER)) {
    generate(FM_STRING);
    generate(ensure_type(TOKEN_IDENTIFIER, "expected identifier on key."));
  } else if(la1type(TOKEN_STRING)) {
    generate(FM_STRING);
    generate(ensure_type(TOKEN_STRING, "expected string on key."));
  }
}

void parser_method_definition(Token **table, char ***fmcodes) {
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

char *parser_keyword_list(Token **table, char ***fmcodes) {
  char *keyword_method_name = NULL;

  while(la1type(TOKEN_IDENTIFIER) && la2value(":")) {
    string_addf(
      keyword_method_name,
      "%s%s",
      ensure_type(TOKEN_IDENTIFIER, "expected identifier on keyword list."),
      ensure_value(":", "missing ':' on keyword list.")
    );
    generate(FM_METHOD_PARAMETER);
    literal();
  }

  return keyword_method_name;
}

void parser_scalar(Token **table, char ***fmcodes) {
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

void parser_variable(Token **table, char ***fmcodes) {
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

#undef la1value
#undef la2value
#undef la3value
#undef la1type
#undef la2type
#undef la3type

#undef ensure_value
#undef ensure_type
#undef generate

#undef first_unit
#undef unit_list
#undef unit
#undef assignment_message
#undef keyword_message
#undef keyword_selector_chain
#undef binary_message
#undef binary_selector_chain
#undef unary_message
#undef unary_selector_chain
#undef lhs_message
#undef lhs_selector
#undef literal
#undef param_list
#undef bit_list
#undef bit
#undef association_list
#undef key
#undef method_definition
#undef keyword_list
#undef scalar
#undef variable
