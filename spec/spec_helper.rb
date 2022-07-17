require "rspec/autorun";

# All source files
Dir["#{Dir.pwd}/src/oblisp/**/*.rb"].each { |f| require f };

# oblisp
require_relative "oblisp/version.spec";

# ast
require_relative "oblisp/ast/ASTFactory.spec";
require_relative "oblisp/ast/ast_types/Default.spec";
require_relative "oblisp/ast/ast_types/SExpression.spec";

# lexer
require_relative "oblisp/lexer/FileLoader.spec";
require_relative "oblisp/lexer/Lexer.spec";

# parser
require_relative "oblisp/parser/Parser.spec";
require_relative "oblisp/parser/arithmetic.spec";
require_relative "oblisp/parser/assignments.spec";
require_relative "oblisp/parser/bitwise.spec";
require_relative "oblisp/parser/blocks.spec";
require_relative "oblisp/parser/booleans.spec";
require_relative "oblisp/parser/characters.spec";
require_relative "oblisp/parser/classes.spec";
require_relative "oblisp/parser/code_as_data.spec";
require_relative "oblisp/parser/conditionals.spec";
require_relative "oblisp/parser/constants.spec";
require_relative "oblisp/parser/conversions.spec";
require_relative "oblisp/parser/date_time.spec";
require_relative "oblisp/parser/hashes.spec";
require_relative "oblisp/parser/identifiers.spec";
require_relative "oblisp/parser/intervals.spec";
require_relative "oblisp/parser/iterations.spec";
require_relative "oblisp/parser/lists.spec";
require_relative "oblisp/parser/messages.spec";
require_relative "oblisp/parser/meta_evaluation.spec";
require_relative "oblisp/parser/numeric.spec";
require_relative "oblisp/parser/strings.spec";
require_relative "oblisp/parser/symbols.spec";
require_relative "oblisp/parser/tuples.spec";

# tokens
require_relative "oblisp/tokens/Token.spec";
require_relative "oblisp/tokens/TokenTable.spec";
require_relative "oblisp/tokens/Type.spec";
