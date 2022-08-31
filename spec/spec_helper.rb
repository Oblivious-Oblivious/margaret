require "rspec/autorun";

# All source files
Dir["#{Dir.pwd}/src/interpreter/**/*.rb"].each { |f| require f };

# oblisp
require_relative "interpreter/version.spec";

# ast
require_relative "interpreter/ast/Bytecode.spec";

# lexer
require_relative "interpreter/lexer/FileLoader.spec";
require_relative "interpreter/lexer/Lexer.spec";

# opcode
require_relative "interpreter/opcode/Opcode.spec";

# parser
require_relative "interpreter/parser/Parser.spec";
require_relative "interpreter/parser/arithmetic.spec";
require_relative "interpreter/parser/assignments.spec";
require_relative "interpreter/parser/bitwise.spec";
require_relative "interpreter/parser/booleans.spec";
require_relative "interpreter/parser/c_functions.spec";
require_relative "interpreter/parser/characters.spec";
require_relative "interpreter/parser/classes.spec";
require_relative "interpreter/parser/code_as_data.spec";
require_relative "interpreter/parser/complex.spec";
require_relative "interpreter/parser/conditionals.spec";
require_relative "interpreter/parser/constants.spec";
require_relative "interpreter/parser/conversions.spec";
require_relative "interpreter/parser/date_time.spec";
require_relative "interpreter/parser/errors.spec";
require_relative "interpreter/parser/hashes.spec";
require_relative "interpreter/parser/identifiers.spec";
require_relative "interpreter/parser/intervals.spec";
require_relative "interpreter/parser/iterations.spec";
require_relative "interpreter/parser/lists.spec";
require_relative "interpreter/parser/messages.spec";
require_relative "interpreter/parser/meta_evaluation.spec";
require_relative "interpreter/parser/method_definition.spec";
require_relative "interpreter/parser/numeric.spec";
require_relative "interpreter/parser/procs.spec";
require_relative "interpreter/parser/rational.spec";
require_relative "interpreter/parser/strings.spec";
require_relative "interpreter/parser/symbols.spec";
require_relative "interpreter/parser/tensors.spec";

# tokens
require_relative "interpreter/tokens/Token.spec";
require_relative "interpreter/tokens/TokenTable.spec";
require_relative "interpreter/tokens/Type.spec";
