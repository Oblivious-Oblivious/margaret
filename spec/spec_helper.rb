require "rspec/autorun";

# All source files
Dir["#{Dir.pwd}/src/oblisp/**/*.rb"].each { |f| require f };

# oblisp
require_relative "oblisp/version.spec.rb";

# lexer
require_relative "oblisp/lexer/file_loader.spec.rb";
require_relative "oblisp/lexer/lexer.spec.rb";

# parser
require_relative "oblisp/parser/parser.spec.rb";
require_relative "oblisp/parser/arithmetic.spec.rb";
require_relative "oblisp/parser/assignments.spec.rb";
require_relative "oblisp/parser/bitwise.spec.rb";
require_relative "oblisp/parser/blocks.spec.rb";
require_relative "oblisp/parser/booleans.spec.rb";
require_relative "oblisp/parser/characters.spec.rb";
require_relative "oblisp/parser/classes.spec.rb";
require_relative "oblisp/parser/code_as_data.spec.rb";
require_relative "oblisp/parser/conditionals.spec.rb";
require_relative "oblisp/parser/constants.spec.rb";
require_relative "oblisp/parser/conversions.spec.rb";
require_relative "oblisp/parser/date_time.spec.rb";
require_relative "oblisp/parser/hashes.spec.rb";
require_relative "oblisp/parser/identifiers.spec.rb";
require_relative "oblisp/parser/intervals.spec.rb";
require_relative "oblisp/parser/iterations.spec.rb";
require_relative "oblisp/parser/lists.spec.rb";
require_relative "oblisp/parser/messages.spec.rb";
require_relative "oblisp/parser/meta_evaluation.spec.rb";
require_relative "oblisp/parser/numeric.spec.rb";
require_relative "oblisp/parser/strings.spec.rb";
require_relative "oblisp/parser/symbols.spec.rb";
require_relative "oblisp/parser/tuples.spec.rb";

# tokens
require_relative "oblisp/tokens/token.spec.rb";
require_relative "oblisp/tokens/type.spec.rb";
