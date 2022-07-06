require "rspec/autorun";

# All source files
Dir["#{Dir.pwd}/src/oblisp/**/*.rb"].each { |f| require f };

# lexer
require "#{Dir.pwd}/spec/oblisp/lexer/file_loader.spec.rb";
require "#{Dir.pwd}/spec/oblisp/lexer/lexer.spec.rb";

# tokens
require "#{Dir.pwd}/spec/oblisp/tokens/token.spec.rb";
require "#{Dir.pwd}/spec/oblisp/tokens/type.spec.rb";

# parser
require "#{Dir.pwd}/spec/oblisp/parser/parser.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/arithmetic.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/assignments.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/bitwise.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/blocks.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/booleans.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/characters.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/classes.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/conditionals.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/constants.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/conversions.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/date_time.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/hashes.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/identifiers.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/intervals.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/iterations.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/lists.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/messages.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/meta_evaluation.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/numeric.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/strings.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/symbols.spec.rb"
require "#{Dir.pwd}/spec/oblisp/parser/tuples.spec.rb"

# oblisp
require "#{Dir.pwd}/spec/oblisp/version.spec.rb";
