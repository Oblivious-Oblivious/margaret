require "rspec/autorun";
require_relative "_helpers";

# All source files
Dir["#{Dir.pwd}/src/**/*.rb"].each { |f| require f };

# margaret
require_relative "version.spec";

# ast
require_relative "ast/Bytecode.spec";

# evaluator
require_relative "evaluator/Evaluator.spec";
require_relative "evaluator/Stack.spec";

# generic
# require_relative "generic/arithmetic.spec";
# require_relative "generic/assignments.spec";
# require_relative "generic/bitwise.spec";
# require_relative "generic/booleans.spec";
# require_relative "generic/c_functions.spec";
# require_relative "generic/characters.spec";
# require_relative "generic/classes.spec";
# require_relative "generic/code_as_data.spec";
# require_relative "generic/complex.spec";
# require_relative "generic/conditionals.spec";
# require_relative "generic/constants.spec";
# require_relative "generic/conversions.spec";
# require_relative "generic/date_time.spec";
# require_relative "generic/errors.spec";
# require_relative "generic/groups.spec";
# require_relative "generic/hashes.spec";
# require_relative "generic/identifiers.spec";
# require_relative "generic/intervals.spec";
# require_relative "generic/iterations.spec";
# require_relative "generic/messages.spec";
# require_relative "generic/meta_evaluation.spec";
# require_relative "generic/method_definition.spec";
# require_relative "generic/numeric.spec";
# require_relative "generic/procs.spec";
# require_relative "generic/rational.spec";
# require_relative "generic/strings.spec";
# require_relative "generic/symbols.spec";
# require_relative "generic/tensors.spec";

# lexer
require_relative "lexer/FileLoader.spec";
require_relative "lexer/Lexer.spec";

# opcode
require_relative "opcode/Opcode.spec";

# parser
require_relative "parser/Parser.spec";

# tokens
require_relative "tokens/Token.spec";
require_relative "tokens/TokenTable.spec";
require_relative "tokens/Type.spec";
